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
import QtQuick.Layouts 1.15

import Muse.Ui 1.0
import Muse.UiComponents 1.0
import MuseScore.Repair 1.0

import "internal"

StyledDialogView {
    id: root

    title: qsTrc("appshell/repair", "Repair")

    contentWidth: 880
    contentHeight: 640
    resizable: true

    property string currentPageId: ""
    property var params: null

    property QtObject prv: QtObject {
        property var pagesObjects: (new Map())

        function resolveStackCurrentIndex() {
            var keys = Object.keys(root.prv.pagesObjects)
            return keys.indexOf(repairModel.currentPageId)
        }

        function updateStackCurrentIndex() {
            stack.currentIndex = resolveStackCurrentIndex()
        }
    }

    Component.onCompleted: {
        repairModel.load(root.currentPageId)

        initPagesObjects()

        prv.updateStackCurrentIndex()
    }

    function initPagesObjects() {
        var pages = repairModel.availablePages()
        for (var i in pages) {
            var pageInfo = pages[i]

            if (!Boolean(pageInfo.path)) {
                continue
            }

            var pageComponent = Qt.createComponent("../" + pageInfo.path)

            var properties = {
                navigationSection: root.navigationSection,
                navigationOrderStart: (i + 1) * 100
            }

            if (root.currentPageId === pageInfo.id) {
                var params = root.params
                for (var key in params) {
                    var value = params[key]
                    properties[key] = value
                }
            }

            var obj = pageComponent.createObject(stack, properties)

            if (!Boolean(obj)) {
                continue
            }

            obj.hideRequested.connect(function() {
                root.hide()
            })

            root.prv.pagesObjects[pageInfo.id] = obj
        }
    }

    RepairModel {
        id: repairModel

        onCurrentPageIdChanged: function(currentPageId) {
            prv.updateStackCurrentIndex()
        }
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            spacing: 0

            RepairMenu {
                id: menu

                Layout.fillHeight: true
                Layout.preferredWidth: 220

                navigation.section: root.navigationSection
                navigation.order: 1

                model: repairModel
            } // END RepairMenu

            SeparatorLine { orientation: Qt.Vertical }

            StackLayout {
                id: stack
            }
        }

        SeparatorLine { }
    }
}
