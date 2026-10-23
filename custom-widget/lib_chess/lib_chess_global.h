#ifndef LIB_CHESS_GLOBAL_H
#define LIB_CHESS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIB_CHESS_LIBRARY)
#define LIB_CHESS_EXPORT Q_DECL_EXPORT
#else
#define LIB_CHESS_EXPORT Q_DECL_IMPORT
#endif

#endif // LIB_CHESS_GLOBAL_H
