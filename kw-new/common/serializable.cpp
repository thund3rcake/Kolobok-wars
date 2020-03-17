#include <qmetaobject.h>

#include <QDebug>

#include "Serializable.h"

Serializable::Serializable(QObject * parent)
    :QObject(parent) {

}


Serializable::Serializable(const Serializable & rhs)
    :QObject() {

    Q_UNUSED(rhs);
}

Serializable & Serializable::operator=(const Serializable & rhs) {

    Q_UNUSED(rhs);
    return *this;
}

Serializable::~Serializable() {

}


QDataStream & operator << (QDataStream & stream, const Serializable & data) {

    for (qint32 i = 0; i < data.metaObject() -> propertyCount(); ++i) {
        if (data.metaObject() -> property(i).isStored(&data)
                && data.metaObject() -> property(i).isReadable()
                && data.metaObject() -> property(i).isWritable()) {
            stream << i;
            stream << data.metaObject() -> property(i).read(&data);
        }
    }

    return stream;
}


QDataStream & operator >> (QDataStream & stream, Serializable & data) {

    qint32 propertyNum = 0;

    for (qint32 i = 0; i < data.metaObject() -> propertyCount(); ++i) {
        QVariant property;
        stream >> propertyNum;
        stream >> property;
        if (propertyNum == i) {
            data.metaObject() -> property(i).write(&data, property);
        }
    }

    return stream;
}