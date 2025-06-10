// #ToDo: review this file and conception
#pragma once
#ifndef Kernel__Debug__hpp
#define Kernel__Debug__hpp

// #ExportHeader
#include "KernelExport.hpp"


#ifdef _DEBUG
#define DEBUG_MODE
#endif


#ifdef DEBUG_MODE
KERNEL_EXPORT void HandleInspection (const char* condition, const char* file, int line, const char* info = nullptr);
KERNEL_EXPORT void HandleAssertion  (const char* condition, const char* file, int line, const char* info = nullptr);
#endif


#ifdef DEBUG_MODE
#	define DEBUG_ONLY(p)	p
#	define OMIT_IN_DEBUG(p)
#	define INSPECT(c, ...)	(c) ? static_cast<void> (0) : HandleInspection (#c, __FILE__, __LINE__, __VA_ARGS__)
//#	define ASSERT(p)		Q_ASSERT(p)
#	define ASSERT(c, ...)	(c) ? static_cast<void> (0) : HandleAssertion  (#c, __FILE__, __LINE__, __VA_ARGS__)
#else
#	define DEBUG_ONLY(p)
#	define OMIT_IN_DEBUG(p)	p
#	define INSPECT(c, ...)
#	define ASSERT(p, ...)
#endif


struct KnownProblem OMIT_IN_DEBUG (final) {
	explicit constexpr KnownProblem (const char* const guid) : guid (guid) {}
	const char* const guid;
};


#ifdef DEBUG_MODE
struct NoImplementation final : public KnownProblem {
	explicit constexpr NoImplementation (const char* const file, int line, const char* const guid)
		: KnownProblem	(guid)
		, file			(file)
		, line			(line)
	{}
	const char* const	file;
	const int			line;
};
#endif


#ifdef DEBUG_MODE
#	define TODO				throw NoImplementation	(__FILE__, __LINE__, nullptr)
#	define LIMITATION(guid)	throw NoImplementation	(__FILE__, __LINE__, guid)
#else
#	define TODO				static_assert (false, "Use macro LIMITATION instead!")
#	define LIMITATION(guid)	throw KnownProblem		(guid)
#endif


#endif