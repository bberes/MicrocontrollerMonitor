#pragma once
#ifndef FileHandler__FileHandlerExport__hpp
#define FileHandler__FileHandlerExport__hpp

// #Qt
#include <QtCore\qglobal.h>


#ifndef BUILD_STATIC
# if defined (FILEHANDLER_LIB)
#  define FILEHANDLER_EXPORT Q_DECL_EXPORT
# else
#  define FILEHANDLER_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILEHANDLER_EXPORT
#endif


#endif