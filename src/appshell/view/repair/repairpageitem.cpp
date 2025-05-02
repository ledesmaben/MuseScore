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
#include "repairpageitem.h"

#include "translation.h"

using namespace mu::appshell;

RepairPageItem::RepairPageItem(QObject* parent)
    : QObject(parent)
{
}

RepairPageItem::~RepairPageItem()
{
    for (RepairPageItem* child : m_children) {
        child->deleteLater();
    }
}

QString RepairPageItem::id() const
{
    return m_id;
}

QString RepairPageItem::title() const
{
    return muse::qtrc("appshell/repair", m_title.toUtf8());
}

int RepairPageItem::icon() const
{
    return static_cast<int>(m_icon);
}

QString RepairPageItem::path() const
{
    return m_path;
}

bool RepairPageItem::expanded() const
{
    return m_expanded;
}

RepairPageItem* RepairPageItem::parentItem() const
{
    return m_parent;
}

void RepairPageItem::setParentItem(RepairPageItem* parent)
{
    m_parent = parent;
}

QList<RepairPageItem*> RepairPageItem::childrenItems() const
{
    return m_children;
}

bool RepairPageItem::isEmpty() const
{
    return m_children.isEmpty();
}

RepairPageItem* RepairPageItem::childAtRow(const int row) const
{
    if (row < 0 || row >= childCount()) {
        return nullptr;
    }

    return m_children.at(row);
}

void RepairPageItem::appendChild(RepairPageItem* child)
{
    if (!child) {
        return;
    }

    child->setParentItem(this);

    m_children.append(child);
}

int RepairPageItem::childCount() const
{
    return m_children.size();
}

int RepairPageItem::row() const
{
    if (!parentItem()) {
        return 0;
    }

    return parentItem()->childrenItems().indexOf(const_cast<RepairPageItem*>(this));
}

void RepairPageItem::setId(QString id)
{
    if (m_id == id) {
        return;
    }

    m_id = id;
    emit idChanged(m_id);
}

void RepairPageItem::setTitle(QString title)
{
    if (m_title == title) {
        return;
    }

    m_title = title;
    emit titleChanged(m_title);
}

void RepairPageItem::setIcon(muse::ui::IconCode::Code icon)
{
    if (m_icon == icon) {
        return;
    }

    m_icon = icon;
    emit iconChanged(this->icon());
}

void RepairPageItem::setPath(QString path)
{
    if (m_path == path) {
        return;
    }

    m_path = path;
    emit pathChanged(m_path);
}

void RepairPageItem::setExpanded(bool expanded)
{
    if (m_expanded == expanded) {
        return;
    }

    m_expanded = expanded;
    emit expandedChanged(m_expanded);
}
