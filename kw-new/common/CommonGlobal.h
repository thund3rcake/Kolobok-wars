#ifndef COMMONGLOBAL_H
#define COMMONGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMON_LIBRARY)
    #define KW_COMMON_EXPORT Q_DECL_EXPORT
#else
    #define KW_COMMON_EXPORT Q_DECL_IMPORT
#endif


#endif // COMMONGLOBAL_H
