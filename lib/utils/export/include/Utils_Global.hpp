#ifndef UTILS_GLOBAL_HPP
#define UTILS_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(UTILS_LIBRARY)
#  define UTILS_EXPORT Q_DECL_EXPORT
#else
#  define UTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // UTILS_GLOBAL_HPP