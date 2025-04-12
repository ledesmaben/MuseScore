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
#include "manualrepairmodel.h"

#include "languages/languageserrors.h"

#include "log.h"
#include "translation.h"
#include "QFileInfo"

using namespace mu::appshell;
using namespace muse;
using namespace muse::languages;

ManualRepairModel::ManualRepairModel(QObject* parent)
    : QObject(parent), muse::Injectable(muse::iocCtxForQmlObject(this))
{
}

void ManualRepairModel::load()
{

}

QStringList ManualRepairModel::musicXMLPathFilter() const
{
    return { muse::qtrc("appshell/repair", "MusicXML file") + " (*.musicXML)" };
}

QStringList ManualRepairModel::scanPathFilter() const
{
    return { muse::qtrc("appshell/repair", "PDF file") + " (*.pdf)",
             muse::qtrc("appshell/repair", "JPEG file") + " (*.jpg,*.jpeg)"};
}

void ManualRepairModel::startRepair(const QString& score, const QString& scan) const
{
    // Check whether there's an open project already. If there is, close it.
    projectFilesController()->closeOpenedProject();

    // Open the chosen MusicXML project file.
    QUrl url = QUrl::fromLocalFile(score);
    Ret ret = projectFilesController()->openProject(url);
    if (!ret) {
        // Failure to open
        LOGE() << ret.toString();
    }
    else
    {
        // TODO : manual repair logic should occur here.

        dispatcher.get()->dispatch("toggle-repair");

        // What additional pieces should we add?
        // We would probably benefit from adding additional XML information that denotes some issue with the score.
        // What do we want to do then?
        // We could add some panel that allows the user to select one or multiple notes and "tag" them.

        // Create a temporary copy of the musicXML file with filename suffix "_repaired" appended
        QUrl nonLocalUrl(score);
        QString scorePath = nonLocalUrl.toString(QUrl::RemoveFilename);
        QFileInfo info(nonLocalUrl.toString());
        QString repairedPath = scorePath + info.baseName() + "_repaired" + "." + info.suffix();

        // Get the master notation from the open project.
        notation::INotationPtrList notations;
        notations.push_back(globalContext()->currentMasterNotation()->notation());
        project::INotationWriter::UnitType m_selectedUnitType = project::INotationWriter::UnitType::PER_PART;
        exportProjectScenario()->exportScores(notations, repairedPath, m_selectedUnitType,false);
    }
}
