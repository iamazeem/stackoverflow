import QtQuick 2.12
import QtQuick.Window 2.12
import qml.test 1.0

Window {
    Test {
        id: test
    }

    visible: true
    width: 640
    height: 480
    //title: qsTr("Hello World!")

    title: qsTr( test.get1_RetByValue_NonConstLocalString() )
//    title: qsTr( test.get2_RetByConstValue_ConstLocalString() )
//    title: qsTr( test.get3_RetByConstValue_StaticString() )
//    title: qsTr( test.get4_RetByConstRef_LocalString() )
//    title: qsTr( test.get5_RetByStaticConstRef_StaticString() )
}
