#ifndef COMMONGLOBAL_H
#define COMMONGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtGui>
#include <GameWorldConsts.h>

#if defined(_COMMON_LIBRARY)
    #define DATA_EXPORT Q_DECL_EXPORT
#else
    #define DATA_EXPORT Q_DECL_IMPORT
#endif

//Была проблема, что из-за списков инициализации не компилировалось,
//    поэтому в конструкторе копирoвания обычная инициализация.

class Exception // Класс просто присваивает те значения переменных, которые ему подали.
{
public:
    explicit Exception(int no) {
        errNo = no;
    }

    Exception(int no, const QString & msg) {
        errNo = no;
        message = msg;
    }

    int errNo;
    QString message;
};


template <class T>
class OnceCreated {// Просто 3 конструктора.
public:
    OnceCreated():
        isNULL( true ) {};

    explicit OnceCreated( const T & data ):
        isNULL(false),
        data(data) {};

    OnceCreated & operator = (const T & rhs) {
        isNULL = false;
        data = rhs;
        return *this;
    };

    inline bool isNull()   { return isNULL; };
    inline T    getdData() { return data; };

private:
    bool isNULL;
    T data;

};


#ifdef KOLOBOK_CLIENT
    QPoint getDesktopSize();
    double scale_x_100 ();
#endif

double scaledPlayerSize();

#endif // COMMONGLOBAL_H