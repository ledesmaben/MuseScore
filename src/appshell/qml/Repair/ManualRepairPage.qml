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
import QtQuick 2.15

import Muse.Ui 1.0
import Muse.UiComponents 1.0
import MuseScore.Repair 1.0

import "internal"
import "../Preferences/internal"

RepairPage {
    id: root

    Component.onCompleted: {
        repairModel.load()
    }

    ManualRepairModel {
        id: repairModel
    }

    Column {
        width: parent.width
        spacing: root.sectionsSpacing

        ManualRepairSection {
            id: manualrepairSection

            property string input_musicxml: ""
            property string input_scans: ""
            property string output_musicxml: ""

            // Filters from the repairModel which dictate what the file
            // selection may choose.
            property var musicXMLPathFilter: repairModel.musicXMLPathFilter()
            property var scanPathFilter: repairModel.scanPathFilter()

            navigation.section: root.navigationSection
            navigation.order: root.navigationOrderStart + 1

            onSelectInputMusicXML: function(selection) {
               input_musicxml = selection
            }

            onSelectInputScans: function(selection) {
                input_scans = selection
            }

            onStartRepair: function(input_musicxml,input_scans) {
                repairModel.startRepair(input_musicxml,input_scans)
            }
        }

        SeparatorLine { }
    }
}
