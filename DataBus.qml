import QtQuick

QtObject {
    id: databus

    signal dataUpdate(variant x);

    property var data: ListModel {
        id: data

        ListElement {
            uuid: 0
            value: 0.0
        }

        ListElement {
            uuid: 1
            value: 0.0
        }

        ListElement {
            uuid: 2
            value: 0.0
        }
    }

    property var timer: Timer {
        id: timer
        running: true
        repeat: true
        interval: 10
        onTriggered: {
            console.log("timeout")
            for(let i = 0; i < databus.data.count; i++)
            {
                var element = databus.data.get(i);
                databus.data.setProperty(i, "value", element.value + 1.0);
                // element.value += 1
                dataUpdate(element)
            }
        }
    }
}
