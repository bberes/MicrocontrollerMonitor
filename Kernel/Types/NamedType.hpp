#pragma once
#ifndef Kernel__NamedType__hpp
#define Kernel__NamedType__hpp


class NamedType {
public:
	virtual ~NamedType () = default;

	virtual const char* ClassName () const = 0;
};


#define STRINGIFY(param) #param

// '::QualifierPrefix::className' must be Fully Qualified Class Name (FQCN)
#define DECLARE_CLASS_NAME(QualifierPrefix, className)			\
	virtual const char* className::ClassName () const override	\
	{															\
		return STRINGIFY (QualifierPrefix ## :: ## className);	\
	}															\
	using NamedType = ::QualifierPrefix::className::NamedType;	// to enforce FQCN


#endif