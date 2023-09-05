import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
	id: window
	width: 2000
	height: 800
	title: "qml"
	visible: true

	// Action {
	// 	shortcut: StandardKey.Escape
	// 	onTriggered: window.close()
	// }

	DataBus {
		id: bus
	}

	Subscribe {
		target: bus
	}

	Store {
		id: store
	}

	RowLayout {
		anchors.fill: parent

		View {
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.preferredWidth: window.width * 0.33
			model: store.model
			color: "red"
		}

		View {
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.preferredWidth: window.width * 0.33
			model: store.model
			color: "white"
		}

		View {
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.preferredWidth: window.width * 0.33
			model: store.model
			color: "blue"
		}
	}
}
