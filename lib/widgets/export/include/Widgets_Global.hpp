#ifndef WIDGETS_GLOBAL_HPP
#define WIDGETS_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(WIDGETS_LIBRARY)
#  define WIDGETS_EXPORT Q_DECL_EXPORT
#else
#  define WIDGETS_EXPORT Q_DECL_IMPORT
#endif

#endif // WIDGETS_GLOBAL_HPP