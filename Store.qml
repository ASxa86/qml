import QtQuick

QtObject {
    id: store

    property ListModel model: ListModel {
        id: root
    }

    property var connection: Connections {
        target: Actions

        function onUpdateItem(x) {
            store.model.insert(x.uuid, {"uuid": x.uuid, "value": x.value});

            let element = model.get(x.uuid);
            console.log("update", element.uuid, ": ", element.value);
        }
    }
}
