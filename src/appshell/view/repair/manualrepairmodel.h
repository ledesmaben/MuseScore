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
#include "iappshellconfiguration.h"
#include "async/asyncable.h"

#include "project/internal/iexportprojectscenario.h"
#include "project/iprojectfilescontroller.h"

#include "global/iinteractive.h"
#include "shortcuts/ishortcutsconfiguration.h"


namespace mu::appshell {
class ManualRepairModel : public QObject, public muse::Injectable, public muse::async::Asyncable
{
    Q_OBJECT

    // These properties are what ultimately what show up in the qml repairModel in ManualRepairPage.qml.
    // It seems
    Q_PROPERTY(QStringList keyboardLayouts READ keyboardLayouts CONSTANT)
    Q_PROPERTY(QString currentKeyboardLayout READ currentKeyboardLayout WRITE setCurrentKeyboardLayout NOTIFY currentKeyboardLayoutChanged)

    Q_PROPERTY(bool isOSCRemoteControl READ isOSCRemoteControl WRITE setIsOSCRemoteControl NOTIFY isOSCRemoteControlChanged)
    Q_PROPERTY(int oscPort READ oscPort WRITE setOscPort NOTIFY oscPortChanged)

    Q_PROPERTY(bool isNeedRestart READ isNeedRestart WRITE setIsNeedRestart NOTIFY isNeedRestartChanged)

    muse::Inject<IAppShellConfiguration> configuration = { this };
    muse::Inject<context::IGlobalContext> globalContext = { this };
    muse::Inject<muse::IInteractive> interactive = { this };
    muse::Inject<muse::shortcuts::IShortcutsConfiguration> shortcutsConfiguration = { this };
    muse::Inject<project::IProjectFilesController> projectFilesController = { this };
    muse::Inject<project::IExportProjectScenario> exportProjectScenario = { this };

public:
    explicit ManualRepairModel(QObject* parent = nullptr);

    // These are the functions invokable from a qml.
    Q_INVOKABLE void load();

    Q_INVOKABLE QStringList musicXMLPathFilter() const;
    Q_INVOKABLE QStringList scanPathFilter() const;
    Q_INVOKABLE void startRepair(const QString& score, const QString& scan) const;

    QStringList keyboardLayouts() const;
    QString currentKeyboardLayout() const;

    project::INotationProjectPtr currentNotationProject() const;

    QVariantList startupModes() const;

    bool isOSCRemoteControl() const;
    int oscPort() const;
    bool isNeedRestart() const;

public slots:
    void setCurrentKeyboardLayout(const QString& keyboardLayout);
    void setIsOSCRemoteControl(bool isOSCRemoteControl);
    void setOscPort(int oscPort);
    void setIsNeedRestart(bool newIsNeedRestart);

signals:
    void languagesChanged(QVariantList languages);
    void currentLanguageCodeChanged(QString currentLanguageCode);
    void currentKeyboardLayoutChanged();
    void isOSCRemoteControlChanged(bool isOSCRemoteControl);
    void oscPortChanged(int oscPort);

     void isNeedRestartChanged();

    void startupModesChanged();

private:

    bool m_isNeedRestart = false;

    struct StartMode
    {
        StartupModeType type = StartupModeType::StartWithNewScore;
        QString title;
        bool checked = false;
        bool canSelectScorePath = false;
        QString scorePath;
    };

    using StartModeList = QList<StartMode>;

    StartModeList allStartupModes() const;
};
}

#endif // MU_APPSHELL_MANUALREPAIRMODEL_H
