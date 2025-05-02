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
import QtQuick.Layouts 1.15

import Muse.Ui 1.0
import Muse.UiComponents 1.0
import Muse.Audio 1.0
import MuseScore.Playback 1.0

import "internal"

ColumnLayout {
    id: root

    property NavigationSection navigationSection: null
    property int contentNavigationPanelOrderStart: 2 // TODO : don't use magic numbers

    signal resizeRequested(var newWidth, var newHeight)

    spacing: 0

    onImplicitHeightChanged: {
        if (contentColumn.completed) {
            resizeRequested(width, implicitHeight)
        }
    }

    QtObject {
        id: prv

        property var currentNavigateControlIndex: undefined
        property bool isPanelActivated: false

        readonly property real headerWidth: 98
        readonly property real channelItemWidth: 108

        function setNavigateControlIndex(index) {
            if (!Boolean(prv.currentNavigateControlIndex) ||
                    index.row !== prv.currentNavigateControlIndex.row ||
                    index.column !== prv.currentNavigateControlIndex.column) {
                prv.isPanelActivated = false
            }

            prv.currentNavigateControlIndex = index
        }
    }

    function scrollToFocusedItem(focusedIndex) {
        let targetScrollPosition = (focusedIndex) * (prv.channelItemWidth + 1) // + 1 for separators
        let maxContentX = flickable.contentWidth - flickable.width

        if (targetScrollPosition + prv.channelItemWidth > flickable.contentX + flickable.width) {
            flickable.contentX = Math.min(targetScrollPosition + prv.channelItemWidth - flickable.width, maxContentX)
        } else if (targetScrollPosition < flickable.contentX) {
            flickable.contentX = Math.max(targetScrollPosition - prv.channelItemWidth, 0)
        }
    }

    StyledFlickable {
        id: flickable

        Layout.fillWidth: true
        Layout.fillHeight: true

        contentWidth: contentColumn.width + 1 // for trailing separator
        contentHeight: Math.max(contentColumn.height, height)

        implicitHeight: contentColumn.height

        interactive: height < contentHeight || width < contentWidth

        ScrollBar.horizontal: horizontalScrollBar

        ScrollBar.vertical: StyledScrollBar { policy: ScrollBar.AlwaysOn }

        property bool completed: false

        function positionViewAtEnd() {
            if (!flickable.completed) {
                return
            }

            if (flickable.contentY == flickable.contentHeight) {
                return
            }

            flickable.contentY = flickable.contentHeight - flickable.height
        }

        onContentHeightChanged: {
            flickable.positionViewAtEnd()
        }

        Component.onCompleted: {
            flickable.completed = true
        }
    }

    Column {
        spacing: 0
        Layout.fillWidth: true
        visible: horizontalScrollBar.isScrollbarNeeded

        SeparatorLine {}

        StyledScrollBar {
            id: horizontalScrollBar
            width: parent.width
            policy: ScrollBar.AlwaysOn
        }
    }

    onHeightChanged: {
        flickable.positionViewAtEnd()
    }
}
