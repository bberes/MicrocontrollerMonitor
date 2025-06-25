// #TODO separate classes
// Should it be moved into folder SymbolTable?
#pragma once
#ifndef FileHandler__COFF_TreeNodes__hpp
#define FileHandler__COFF_TreeNodes__hpp

// #ExportHeader
#include "FileHandlerExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "Types\Owner.hpp"
#include "Types\Vector.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolTable\TypeDescriptor.hpp"
#include "FileFormats\COFF\SymbolTable\SymbolEntry.hpp"
#include "FileHandlerTypes.hpp"
#include "TypeInfo.hpp"


namespace File::COFF {

class FILEHANDLER_EXPORT Object {
public:
	explicit Object (const SymbolEntry& symbol);
	virtual ~Object ();

	Object (const Object&)							= delete;
	Object&				operator=	(const Object&)	= delete;

	void				Process		(const SymbolFile& symbolFile);

	void				AddChild	(Owner<Object> object);
	bool				IsLeaf		() const;
	void				Enumerate	(const ObjectProcessor& process) const;

	std::string			CalcSymbol	() const;

	const Object*		GetParent	() const;
	std::string			GetName		() const;
	const SymbolEntry&	GetSymbol	() const;

	virtual Object*		Create		(const SymbolEntry& symbol) const = 0;
	virtual std::string	GetType		() const = 0;

public:
	std::string			GetFullName	() const;
	std::string			GetAddress	() const;

private:
	virtual std::string	MemberExpr	() const;
	uint32_t			CalcAddress	() const;
	virtual uint32_t	CalcOffset	() const;
	virtual void		ProcessImpl	(const SymbolFile& symbolFile) = 0;

protected:
	SymbolEntry				symbol;
	std::string				name;

private:
	Object*					parent;
	Vector<Owner<Object>>	childNodes;
};


class Struct final : public Object {
public:
	using Object::Object;

	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override;
	virtual std::string		GetType		() const override;

private:
	virtual Object*			Create		(const SymbolEntry& symbol) const override;

private:
	static const TypeInfo	typeInfo;
};


class Union final : public Object {
public:
	using Object::Object;

	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override;
	virtual std::string		GetType		() const override;

private:
	virtual Object*			Create		(const SymbolEntry& symbol) const override;

private:
	static const TypeInfo	typeInfo;
};


class BasicType : public Object {
public:
	using Object::Object;
	
	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override final;
};


class Pointer final : public Object {
public:
	using Object::Object;

	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override;
	virtual std::string		GetType		() const override;

private:
	virtual Object*			Create		(const SymbolEntry& symbol) const override;

private:
	static const TypeInfo	typeInfo;
};


class Array final : public Object {
public:
	using Object::Object;

	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override;
	virtual std::string		GetType		() const override;

private:
	virtual Object*			Create		(const SymbolEntry& symbol) const override;

private:
	static const TypeInfo	typeInfo;
};


class ArrayElement final : public Object { // #Note: technical class, no TypeInfo!
public:
	explicit ArrayElement (const SymbolEntry& symbol, const UInt16 offset, const UInt16 index);

	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override;
	virtual std::string		GetType		() const override;

private:
	virtual Object*			Create		(const SymbolEntry& symbol) const override;
	virtual std::string		MemberExpr	() const override;
	virtual uint32_t		CalcOffset	() const override;

private:
	const UInt16 offset;
	const UInt16 index;
};


class BitField final : public Object {
public:
	using Object::Object;

	virtual void			ProcessImpl	(const SymbolFile& symbolFile) override;
	virtual std::string		GetType		() const override;

private:
	virtual Object*			Create		(const SymbolEntry& symbol) const override;

	std::string				GetMask		() const;

private:
	static const TypeInfo	typeInfo;
};


template <BaseType baseType>
class SpecialType final : public BasicType {
public:
	using BasicType::BasicType;

	virtual std::string		GetType	() const override;

private:
	virtual SpecialType*	Create	(const SymbolEntry& symbol) const override;

private:
	static const TypeInfo	typeInfo;
};


typedef SpecialType<BaseType::Char>			CharType;
typedef SpecialType<BaseType::Int16_Other>	Int16Type;
typedef SpecialType<BaseType::Int32>		Int32Type;
typedef SpecialType<BaseType::Float>		FloatType;
typedef SpecialType<BaseType::Double>		DoubleType;
typedef SpecialType<BaseType::Enum>			EnumType;
typedef SpecialType<BaseType::UChar>		UCharType;
typedef SpecialType<BaseType::UInt16_Other>	UInt16Type;
typedef SpecialType<BaseType::UInt32>		UInt32Type;


Owner<Object> ObjectFactory (const File::COFF::SymbolEntry& symbol);

}


template <File::COFF::BaseType baseType>
const File::COFF::TypeInfo	File::COFF::SpecialType<baseType>::typeInfo (SpecialType<baseType> (SymbolEntry {ForDeserialization}), File::COFF::TypeDescriptor (baseType));


template <File::COFF::BaseType baseType>
inline std::string File::COFF::SpecialType<baseType>::GetType () const
{
	ASSERT (baseType == symbol.GetTypeSpecifier ().GetBaseType ());
	return ::ToString (symbol.GetTypeSpecifier ().GetBaseType ());
}


template <File::COFF::BaseType baseType>
inline File::COFF::SpecialType<baseType>* File::COFF::SpecialType<baseType>::Create (const SymbolEntry& symbol) const
{
	return MakeRaw<SpecialType<baseType>> (symbol);
}


#endif