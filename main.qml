import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
	width: 200
	height: 200
	color: "red"
}

// ApplicationWindow {
// 	id: window
// 	width: 2000
// 	height: 800
// 	title: "qml"
// 	visible: true

// 	// Action {
// 	// 	shortcut: StandardKey.Escape
// 	// 	onTriggered: window.close()
// 	// }

// 	RowLayout {
// 		id: mainLayout
// 		anchors.fill: parent

// 		// Left Column
// 		Item {
// 			id: columnLeft
// 			Layout.preferredWidth: window.width * 0.25
// 			Layout.fillWidth: true
// 			Layout.fillHeight: true

// 			ColumnLayout
// 			{
// 				anchors.fill: parent

// 				MouseArea {
// 					id: mouseArea
// 					Layout.fillWidth: true
// 					Layout.fillHeight: true
// 					Layout.preferredHeight: window.height * 0.65

// 					drag.target: tile

// 					Rectangle {
// 						id: tile
// 						anchors.fill: parent
// 						color: "darkRed"
// 						Drag.active: mouseArea.drag.active
// 					}
// 				}

// 				RowLayout {
// 					id: secondaryLeft
// 					Layout.preferredHeight: window.height * 0.35

// 					Rectangle {
// 						color: "darkGreen"
// 						Layout.fillWidth: true
// 						Layout.fillHeight: true
// 					}
// 					Rectangle {
// 						color: "darkBlue"
// 						Layout.fillWidth: true
// 						Layout.fillHeight: true
// 					}
// 				}
// 			}

// 			Button {
// 				id: expandLeft
// 				anchors.bottom: columnLeft.bottom
// 				anchors.right: columnLeft.right
// 				width: 50
// 				height: 50
// 				checkable: true
// 				onToggled: {
// 					columnCenter.visible = !expandLeft.checked
// 				}
// 			}

// 			Button {
// 				id: expandSecondaryLeft
// 				anchors.bottom: columnLeft.bottom
// 				anchors.left: columnLeft.left
// 				width: 50
// 				height: 50
// 				checkable: true
// 				onToggled: {
// 					secondaryLeft.visible = !expandSecondaryLeft.checked
// 				}
// 			}
// 		}

// 		// Center Column
// 		ColumnLayout {
// 			id: columnCenter
// 			Layout.preferredWidth: window.width * 0.5
// 			Rectangle {
// 				color: "darkCyan"
// 				Layout.fillWidth: true
// 				Layout.fillHeight: true
// 				// implicitWidth: 640
// 			}
// 		}

// 		Item {
// 			id: columnRight
// 			Layout.preferredWidth: window.width * 0.25
// 			Layout.fillWidth: true
// 			Layout.fillHeight: true

// 			// Right Column
// 			ColumnLayout {
// 				anchors.fill: parent
// 				// Layout.preferredWidth: window.width * 0.25
// 				Rectangle {
// 					color: "darkRed"
// 					Layout.fillWidth: true
// 					Layout.fillHeight: true
// 					Layout.preferredHeight: window.height * 0.65
// 				}

// 				RowLayout {
// 					id: secondary
// 					Layout.preferredHeight: window.height * 0.35
// 					Rectangle {
// 						color: "darkGreen"
// 						Layout.fillWidth: true
// 						Layout.fillHeight: true
// 					}
// 					Rectangle {
// 						color: "darkBlue"
// 						Layout.fillWidth: true
// 						Layout.fillHeight: true
// 					}
// 				}
// 			}

// 			Button {
// 				id: expand
// 				anchors.bottom: columnRight.bottom
// 				anchors.left: columnRight.left
// 				width: 50
// 				height: 50
// 				checkable: true
// 				onToggled: {
// 					columnCenter.visible = !expand.checked
// 				}
// 			}

// 			Button {
// 				id: expandSecondary
// 				anchors.bottom: columnRight.bottom
// 				anchors.right: columnRight.right
// 				width: 50
// 				height: 50
// 				checkable: true
// 				onToggled: {
// 					secondary.visible = !expandSecondary.checked
// 				}
// 			}
// 		}
// 	}
// }
