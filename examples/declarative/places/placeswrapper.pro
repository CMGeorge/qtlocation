TARGET = qml_location_places
TEMPLATE = app

QT += declarative quick network
SOURCES += qmlplaceswrapper.cpp

RESOURCES += \
    placeswrapper.qrc

include(places.pri)

target.path = $$[QT_INSTALL_EXAMPLES]/qtlocation/declarative/places

INSTALLS += target
