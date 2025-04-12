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
#ifndef MU_APPSHELL_MANUALREPAIRMODEL_H
#define MU_APPSHELL_MANUALREPAIRMODEL_H

#include <QObject>

#include "context/iglobalcontext.h"
#include "modularity/ioc.h"
#include "async/asyncable.h"

#include "project/internal/iexportprojectscenario.h"
#include "project/iprojectfilescontroller.h"

#include "actions/iactionsdispatcher.h"


namespace mu::appshell {
class ManualRepairModel : public QObject, public muse::Injectable, public muse::async::Asyncable
{
    Q_OBJECT

    muse::Inject<context::IGlobalContext> globalContext = { this };
    muse::Inject<project::IProjectFilesController> projectFilesController = { this };
    muse::Inject<project::IExportProjectScenario> exportProjectScenario = { this };
    muse::Inject<muse::actions::IActionsDispatcher> dispatcher = { this };

public:
    explicit ManualRepairModel(QObject* parent = nullptr);

    // These are the functions invokable from a qml.
    Q_INVOKABLE void load();

    Q_INVOKABLE QStringList musicXMLPathFilter() const;
    Q_INVOKABLE QStringList scanPathFilter() const;
    Q_INVOKABLE void startRepair(const QString& score, const QString& scan) const;

    project::INotationProjectPtr currentNotationProject() const;

};
}

#endif // MU_APPSHELL_MANUALREPAIRMODEL_H
