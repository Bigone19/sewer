#ifndef DOCXUTILS_GLOBAL_H
#define DOCXUTILS_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QDebug>

#if defined(DOCXUTILS_LIBRARY)
#  define DOCXUTILS_EXPORT Q_DECL_EXPORT
#else
#  define DOCXUTILS_EXPORT Q_DECL_IMPORT
#endif

/************************************************************************/
/* 操作微软docx文件的模块                                               */
/* 2023/02/05                                                           */
/************************************************************************/

#endif // DOCXUTILS_GLOBAL_H
