#ifndef GIT_GLOBAL_HPP
#define GIT_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(GIT_LIBRARY)
#  define GIT_EXPORT Q_DECL_EXPORT
#else
#  define GIT_EXPORT Q_DECL_IMPORT
#endif

#endif // GIT_GLOBAL_HPP