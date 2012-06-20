/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativegeolocation_p.h"

QT_USE_NAMESPACE

/*!
    \qmlclass Location QDeclarativeGeoLocation
    \inqmlmodule QtLocation 5.0
    \ingroup qml-QtLocation5-positioning
    \since Qt Location 5.0

    \brief The Location element holds location data.

    Location elements represent a geographic "location", in a human sense. This
    consists of a specific \l {coordinate}, an \l {address} and a \l {boundingBox}{bounding box}.
    The \l {boundingBox}{bounding box} represents the recommended region
    to display when viewing this location.

    The Location element is most commonly seen as the contents of a search
    model such as the GeocodeModel. When a GeocodeModel returns the list of
    locations found for a given query, it represents these as Location elements.

    \section2 Example Usage

    The following example shows a simple Location element being declared with
    a set \l{coordinate} and \l{address}.

    \code
    Address {
        id: houseAddress
        ...
    }

    Coordinate {
        id: coord
        latitude: -27.3; longitude: 153.1
    }

    Location {
        coordinate: coord
        address: houseAddress
    }
    \endcode
*/

QDeclarativeGeoLocation::QDeclarativeGeoLocation(QObject *parent)
    : QObject(parent), m_address(0), m_coordinate(0), m_boundingBox(0)

{
    setLocation(QGeoLocation());
}

QDeclarativeGeoLocation::QDeclarativeGeoLocation(const QGeoLocation &src, QObject *parent)
    : QObject(parent), m_address(0), m_coordinate(0), m_boundingBox(0)
{
    setLocation(src);
}

QDeclarativeGeoLocation::~QDeclarativeGeoLocation()
{
}

/*!
    \qmlproperty QGeoLocation QtLocation5::Location::location

    For details on how to use this property to interface between C++ and QML see
    "\l {location-cpp-qml.html#location} {Interfaces between C++ and QML Code}".
*/
void QDeclarativeGeoLocation::setLocation(const QGeoLocation &src)
{
    if (m_address && m_address->parent() == this) {
        m_address->setAddress(src.address());
    } else if (!m_address || m_address->parent() != this) {
        m_address = new QDeclarativeGeoAddress(src.address(), this);
        emit addressChanged();
    }

    if (m_coordinate && m_coordinate->parent() == this) {
        m_coordinate->setCoordinate(src.coordinate());
    } else if (!m_coordinate || m_coordinate->parent() != this) {
        m_coordinate = new QDeclarativeCoordinate(src.coordinate(), this);
        emit coordinateChanged();
    }

    if (m_boundingBox && m_boundingBox->parent() == this) {
        m_boundingBox->setRectangle(src.boundingBox());
    } else if (!m_boundingBox || m_boundingBox->parent() != this) {
        m_boundingBox = new QDeclarativeGeoRectangle(src.boundingBox(), this);
        emit boundingBoxChanged();
    }
}

QGeoLocation QDeclarativeGeoLocation::location()
{
    QGeoLocation retValue;
    retValue.setAddress(m_address ? m_address->address() : QGeoAddress());
    retValue.setCoordinate(m_coordinate ? m_coordinate->coordinate() : QGeoCoordinate());
    retValue.setBoundingBox(m_boundingBox ? m_boundingBox->rectangle() : QGeoRectangle());
    return retValue;
}

/*!
    \qmlproperty Address QtLocation5::Location::address

    This property holds the address of the location which can be use to retrieve address details of the location.
*/
void QDeclarativeGeoLocation::setAddress(QDeclarativeGeoAddress *address)
{
    if (m_address == address)
        return;

    if (m_address && m_address->parent() == this)
        delete m_address;

    m_address = address;
    emit addressChanged();
}

QDeclarativeGeoAddress *QDeclarativeGeoLocation::address()
{
    return m_address;
}

/*!
    \qmlproperty Coordinate QtLocation5::Location::coordinate

    This property holds the exact geographical coordinate of the location which can be used to retrieve the latitude, longitude and altitude of the location.

    Note: this property's changed() signal is currently emitted only if the
    whole element changes, not if only the contents of the element change.
*/
void QDeclarativeGeoLocation::setCoordinate(QDeclarativeCoordinate *coordinate)
{
    if (m_coordinate == coordinate)
        return;

    if (m_coordinate && m_coordinate->parent() == this)
        delete m_coordinate;

    m_coordinate = coordinate;
    emit coordinateChanged();
}

QDeclarativeCoordinate *QDeclarativeGeoLocation::coordinate()
{
    return m_coordinate;
}

/*!
    \qmlproperty GeoRectangle QtLocation5::Location::boundingBox

    This property holds the recommended region to use when displaying the location.
    For example, a building's location may have a region centered around the building,
    but the region is large enough to show it's immediate surrounding geographical
    context.

    Note: this property's changed() signal is currently emitted only if the
    whole element changes, not if only the contents of the element change.
*/
void QDeclarativeGeoLocation::setBoundingBox(QDeclarativeGeoRectangle *boundingBox)
{
    if (m_boundingBox == boundingBox)
        return;

    if (m_boundingBox && m_boundingBox->parent() == this)
        delete m_boundingBox;

    m_boundingBox = boundingBox;
    emit boundingBoxChanged();
}

QDeclarativeGeoRectangle *QDeclarativeGeoLocation::boundingBox()
{
    return m_boundingBox;
}
