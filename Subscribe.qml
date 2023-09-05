import QtQuick

// Subscribe
Connections {
    // Update state as it comes across the wire.
    function onDataUpdate(x) {
        Actions.updateItem(x);
   }
}
