#ifndef UTILS_H
#define UTILS_H

#include <QtGui>
#include <GameWorldConsts.h>
#include <CommonGlobal.h>

//Была проблема, что из-за списков инициализации не компилировалось,
//    поэтому в конструкторе копирoвания обычная инициализация.

class KW_COMMON_EXPORT Exception // Класс просто присваивает те значения переменных, которые ему подали.
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
class KW_COMMON_EXPORT OnceCreated {// Просто 3 конструктора.
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
    QPoint KW_COMMON_EXPORT getDesktopSize();
    double KW_COMMON_EXPORT scale_x_100 ();
#endif

double KW_COMMON_EXPORT scaledPlayerSize();

#endif // UTILS_H
