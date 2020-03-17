#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <CommonGlobal.h>

#include <QObject>
#include <QString>
#include <QDataStream>

class DATA_EXPORT Serializable: public QObject {
    Q_OBJECT

public:
    explicit Serializable (QObject * parent = 0);
    explicit Serializable (const Serializable & rhs);
    Serializable & operator=(const Serializable & rhs);

    virtual ~Serializable();

    static const QDataStream::Version version = QDataStream::Qt_4_6;

    friend DATA_EXPORT QDataStream & operator << (QDataStream & stream,
        const Serializable & data);

    friend DATA_EXPORT QDataStream & operator >> (QDataStream & stream,
        Serializable & data);
};

/** @cond */
Q_DECLARE_TYPEINFO(Serializable, Q_COMPLEX_TYPE);
/** @endcond */


#endif // SERIALIZABLE_H