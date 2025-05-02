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
import QtQuick.Controls 2.15

import Muse.Ui 1.0
import Muse.UiComponents 1.0

BaseRepairSection {
    id: root

    title: qsTrc("appshell/repair", "Manual Repair")

    navigation.direction: NavigationPanel.Vertical

    property string input_musicxml: ""
    property string input_scans: ""
    property string output_musicxml: ""

    signal selectInputMusicXML
    signal selectInputScans
    signal startRepair(var score, var scan)

    Column {
        spacing: 24
        width: parent.width
        height: contentHeight  // Automatically adjusts to the height of its children

        FilePicker {
            id: inputfilePicker
            height: 24
            pathFieldWidth: root.columnWidth
            spacing: root.columnSpacing

            dialogTitle: qsTrc("appshell/repair", "Choose a MusicXML score to repair")
            filter: root.musicXMLPathFilter

            visible: true
            path: root.input_musicxml

            navigation: root.navigation
            navigationRowOrderStart: 1
            navigationColumnOrderStart: 1

            onPathEdited: function(newPath) {
                path = newPath
                root.input_musicxml = newPath
            }
        }

        FilePicker {
            id: scanfilePicker
            height: 24
            pathFieldWidth: root.columnWidth
            spacing: root.columnSpacing

            dialogTitle: qsTrc("appshell/repair", "Select the scan, image, or document")
            filter: root.scanPathFilter

            visible: true
            path: root.input_scans

            navigation: root.navigation
            navigationRowOrderStart: 2
            navigationColumnOrderStart: 1

            onPathEdited: function(newPath) {
                path = newPath
                root.input_scans = newPath
            }
        }

        ProgressButton {
            id: startBtn
            height: 24
            text: qsTrc("appshell/repair", "Start")
            navigationName: "Start"
            navigationPanel: root.navigation

            onClicked: {
                root.startRepair(root.input_musicxml,root.input_scans)
                hideRequested()
            }
        }

        StyledTextLabel {
            id:url
            text: {
                var license = "<a href='%1'>%2</a>"
                var hereText = qsTrc("appshell/repair","here")
                // TODO : replace link per Peter's piece
                var retlink = license.arg("https://www.google.com/").arg(hereText)
                return qsTrc("appshell/repair", "Click ") +
                       retlink +
                       qsTrc("appshell/repair", " to upload manually")
            }
            visible: true
        }
    }
}
