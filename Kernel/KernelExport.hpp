#pragma once
#ifndef Kernel__KernelExport__hpp
#define Kernel__KernelExport__hpp

// #Qt
#include <QtCore\qglobal.h>


#ifndef BUILD_STATIC
# if defined (KERNEL_LIB)
#  define KERNEL_EXPORT Q_DECL_EXPORT
# else
#  define KERNEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define KERNEL_EXPORT
#endif


#endif