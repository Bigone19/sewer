#ifndef DOCXUTILS_GLOBAL_H
#define DOCXUTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DOCXUTILS_LIBRARY)
#  define DOCXUTILS_EXPORT Q_DECL_EXPORT
#else
#  define DOCXUTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // DOCXUTILS_GLOBAL_H
