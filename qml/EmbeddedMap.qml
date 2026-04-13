import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15

Rectangle {
    id: root
    width: 900
    height: 600
    color: "#0a1012"

    property double latitude: typeof initialLatitude === "number" ? initialLatitude : 36.8065
    property double longitude: typeof initialLongitude === "number" ? initialLongitude : 10.1815
    property string locationName: (typeof initialLocationName === "string" && initialLocationName.length > 0) ? initialLocationName : "Location"

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/"
        }
        PluginParameter {
            name: "osm.useragent"
            value: "ManarWasteApp/1.0"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(root.latitude, root.longitude)
        zoomLevel: 13
        minimumZoomLevel: 3
        maximumZoomLevel: 19

        property var dragStartCoord: QtPositioning.coordinate(root.latitude, root.longitude)

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onPressed: {
                map.dragStartCoord = map.toCoordinate(Qt.point(mouse.x, mouse.y), false)
            }

            onPositionChanged: {
                if (!pressed)
                    return

                var currentCoord = map.toCoordinate(Qt.point(mouse.x, mouse.y), false)
                var dLat = map.dragStartCoord.latitude - currentCoord.latitude
                var dLon = map.dragStartCoord.longitude - currentCoord.longitude
                map.center = QtPositioning.coordinate(map.center.latitude + dLat, map.center.longitude + dLon)
            }

            onWheel: {
                if (wheel.angleDelta.y > 0)
                    map.zoomLevel = Math.min(map.maximumZoomLevel, map.zoomLevel + 1)
                else if (wheel.angleDelta.y < 0)
                    map.zoomLevel = Math.max(map.minimumZoomLevel, map.zoomLevel - 1)
                wheel.accepted = true
            }
        }

        MapQuickItem {
            id: markerItem
            coordinate: QtPositioning.coordinate(root.latitude, root.longitude)
            anchorPoint.x: marker.width / 2
            anchorPoint.y: marker.height

            sourceItem: Rectangle {
                id: marker
                width: 20
                height: 20
                radius: 10
                color: "#00d084"
                border.width: 2
                border.color: "#043b2b"
            }
        }

    }

    Rectangle {
        id: popup
        visible: true
        radius: 8
        color: "#05231a"
        border.color: "#00d084"
        border.width: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 12
        width: Math.min(parent.width - 30, popupText.implicitWidth + 24)
        height: popupText.implicitHeight + 14

        Text {
            id: popupText
            text: root.locationName
            color: "#d8fff1"
            font.pixelSize: 14
            anchors.centerIn: parent
        }
    }
}
