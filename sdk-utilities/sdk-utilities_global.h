#ifndef SDKUTILITIES_GLOBAL_H
#define SDKUTILITIES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SDKUTILITIES_LIBRARY)
#  define SDKUTILITIESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SDKUTILITIESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SDKUTILITIES_GLOBAL_H
