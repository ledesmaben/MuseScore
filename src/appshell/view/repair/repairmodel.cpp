/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-Studio-CLA-applies
 *
 * MuseScore Studio
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore Limited
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <QApplication>

#include "repairmodel.h"

#include "ui/view/iconcodes.h"


using namespace mu::appshell;
using namespace muse::ui;

RepairModel::RepairModel(QObject* parent)
    : QAbstractItemModel(parent), muse::Injectable(muse::iocCtxForQmlObject(this))
{
}

RepairModel::~RepairModel()
{
    delete m_rootItem;
    m_rootItem = nullptr;
}

QModelIndex RepairModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    RepairPageItem* parentItem = nullptr;

    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = modelIndexToItem(parent);
    }

    if (!parentItem) {
        return QModelIndex();
    }

    RepairPageItem* childItem = parentItem->childAtRow(row);

    if (childItem) {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex RepairModel::parent(const QModelIndex& child) const
{
    RepairPageItem* childItem = modelIndexToItem(child);
    if (!childItem) {
        return QModelIndex();
    }

    RepairPageItem* parentItem = qobject_cast<RepairPageItem*>(childItem->parentItem());

    if (parentItem == m_rootItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int RepairModel::rowCount(const QModelIndex& parent) const
{
    RepairPageItem* parentItem = nullptr;

    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = modelIndexToItem(parent);
    }

    if (!parentItem) {
        return 0;
    }

    return parentItem->childCount();
}

int RepairModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant RepairModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() && role != ItemRole) {
        return QVariant();
    }

    RepairPageItem* item = modelIndexToItem(index);

    if (!item) {
        return QVariant();
    }

    return QVariant::fromValue(qobject_cast<QObject*>(item));
}

QHash<int, QByteArray> RepairModel::roleNames() const
{
    return { { ItemRole, "itemRole" } };
}

QString RepairModel::currentPageId() const
{
    return m_currentPageId;
}

void RepairModel::load(const QString& currentPageId)
{
    beginResetModel();

    if (!currentPageId.isEmpty()) {
        setCurrentPageId(currentPageId);
    } else {
        setCurrentPageId("Manual");
    }

    m_rootItem = new RepairPageItem();

    QList<RepairPageItem*> items {
        makeItem("Manual", QT_TRANSLATE_NOOP("appshell/repair", "Manual"), IconCode::Code::CONFIGURE,
                 "Repair/ManualRepairPage.qml"),

        makeItem("Auto", QT_TRANSLATE_NOOP("appshell/repair", "Auto"), IconCode::Code::CONFIGURE,
                 "Repair/AutoRepairPage.qml"),
    };

    for (RepairPageItem* item: items) {
        m_rootItem->appendChild(item);
    }

    endResetModel();
}

void RepairModel::selectRow(const QModelIndex& rowIndex)
{
    QModelIndex parentItemIndex = parent(rowIndex);
    RepairPageItem* parentItem = nullptr;
    if (!parentItemIndex.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = modelIndexToItem(parentItemIndex);
    }

    QList<RepairPageItem*> children = parentItem->childrenItems();
    for (RepairPageItem* child: children) {
        child->setExpanded(false);
    }

    RepairPageItem* selectedItem = parentItem->childAtRow(rowIndex.row());
    if (!selectedItem) {
        return;
    }

    selectedItem->setExpanded(true);
    setCurrentPageId(selectedItem->id());
}

QVariantList RepairModel::availablePages() const
{
    std::function<QVariantList(const RepairPageItem*)> childPages;
    childPages = [&childPages](const RepairPageItem* item) {
        QVariantList result;

        for (int i = 0; i < item->childCount(); ++i) {
            RepairPageItem* child = item->childAtRow(i);
            QVariantMap childObj;
            childObj["id"] = child->id();
            childObj["path"] = child->path();
            result << childObj;

            QVariantList pages = childPages(child);
            for (const QVariant& page: pages) {
                result << page;
            }
        }

        return result;
    };

    return childPages(m_rootItem);
}

void RepairModel::setCurrentPageId(QString currentPageId)
{
    if (m_currentPageId == currentPageId) {
        return;
    }

    m_currentPageId = currentPageId;
    emit currentPageIdChanged(m_currentPageId);
}

RepairPageItem* RepairModel::makeItem(const QString& id, const QString& title, muse::ui::IconCode::Code icon,
                                               const QString& path,
                                               const QList<RepairPageItem*>& children) const
{
    RepairPageItem* item = new RepairPageItem();
    item->setId(id);
    item->setTitle(title);
    item->setIcon(icon);
    item->setPath(path);
    item->setExpanded(id == currentPageId());

    for (RepairPageItem* child: children) {
        item->appendChild(child);

        if (child->id() == currentPageId()) {
            item->setExpanded(true);
        }
    }

    return item;
}

RepairPageItem* RepairModel::modelIndexToItem(const QModelIndex& index) const
{
    return static_cast<RepairPageItem*>(index.internalPointer());
}
