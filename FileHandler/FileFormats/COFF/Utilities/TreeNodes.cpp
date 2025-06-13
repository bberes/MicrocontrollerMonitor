// #TODO Review the content of this file!
// There are unimplemented functions.
#include "TreeNodes.hpp"

// #Kernel
#include "Utilities\Variable.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolTable\AuxiliaryEntry.hpp"
#include "FileFormats\COFF\SymbolFile.hpp"


using namespace File::COFF;


template SpecialType<BaseType::Char>;
template SpecialType<BaseType::Int16>;
template SpecialType<BaseType::Int16_Other>;
template SpecialType<BaseType::Int32>;
template SpecialType<BaseType::Float>;
template SpecialType<BaseType::Double>;
template SpecialType<BaseType::Enum>;
template SpecialType<BaseType::UChar>;
template SpecialType<BaseType::UInt16>;
template SpecialType<BaseType::UInt16_Other>;
template SpecialType<BaseType::UInt32>;


Object::Object (const SymbolEntry& symbol)
	: symbol (symbol)
	, parent (nullptr)
{
}


Object::~Object () = default;


void Object::Process (const SymbolFile& symbolFile)
{
	name = symbol.GetName (symbolFile);
	INSPECT (name[0] == '_', name.c_str ());
	if (name[0] == '_') {
		name = name.substr (1u);
	}

	ProcessImpl (symbolFile);
}


void Object::AddChild (Owner<Object> object)
{
	ASSERT (object->parent == nullptr);
	object->parent = this;
	childNodes.push_back (std::move (object));
}


bool Object::IsLeaf () const
{
	return childNodes.empty ();
}


void Object::Enumerate (const ObjectProcessor& process) const
{
	for (const auto& object : childNodes) {
		if (object->IsLeaf ()) {
			process (*object);
		} else {
			object->Enumerate (process);
		}
	}
}


std::string Object::CalcSymbol () const
{
	return GetFullName () + " " + GetAddress () + " %" + GetType ();
}


const Object* Object::GetParent () const
{
	return parent;
}


std::string Object::GetName () const
{
	return name;
}


const SymbolEntry& Object::GetSymbol () const
{
	return symbol;
}


std::string Object::GetFullName () const
{
	if (parent == nullptr) {
		return name;
	}

	return parent->GetFullName () + MemberExpr ();
}


std::string Object::GetAddress () const
{
	const uint32_t address = CalcAddress ();
	Utilities::Variable<uint32_t> var (address);
	return var.ToHEX (Utilities::ToHexModifier::KeepZeros);
}


template <typename Derived, typename Base>
static bool IsIt (Base* ptr)
{
	static_assert (std::is_base_of_v<Base, Derived> && std::is_convertible_v<Derived*, Base*>);
	return dynamic_cast<Derived*> (ptr) != nullptr;
}


std::string Object::MemberExpr () const
{
	ASSERT (parent != nullptr);
	if (IsIt<ArrayElement> (parent)) {
		return {};
	}
	return "." + name;
}


uint32_t Object::CalcAddress () const
{
	if (parent == nullptr) {
		return symbol.GetValue ();
	}

	return parent->CalcAddress () + CalcOffset ();
}


uint32_t Object::CalcOffset () const
{
	ASSERT (parent != nullptr);
	if (IsIt<ArrayElement> (parent)) {
		return 0u;
	}
	const StorageClass sc = symbol.GetStorageClass ();
	ASSERT (sc == StorageClass::C_MOS || sc == StorageClass::C_MOU || sc == StorageClass::C_FIELD);
	return (sc == StorageClass::C_MOS) ? (symbol.GetValue () / 16) : 0u;
}


const TypeInfo Struct::typeInfo (Struct (SymbolEntry {ForDeserialization}), TypeDescriptor (BaseType::Struct));


void Struct::ProcessImpl (const SymbolFile& symbolFile)
{
	ASSERT (symbol.HasAuxiliaryEntry ());
	const auto& auxEntry = symbol.GetAuxiliaryEntry ();

	auto indexOfMembers = auxEntry.GetSectionLength ();
	for (;; indexOfMembers += 2u) {
		const auto& symb = symbolFile.GetEntryByIndex (indexOfMembers);
		if (symb.GetStorageClass () == StorageClass::C_STRTAG) {
			continue;
		}
		if (symb.GetStorageClass () == StorageClass::C_EOS) {
			ASSERT (symb.GetName (symbolFile) == ".eos");
			break;
		}

		const auto storageClass = symb.GetStorageClass ();
		ASSERT (storageClass == StorageClass::C_FIELD || storageClass == StorageClass::C_MOS);
		auto childObject = ObjectFactory (symb);
		childObject->Process (symbolFile);
		AddChild (std::move (childObject));
	}
}


std::string Struct::GetType () const
{
	const TypeDescriptor& typeDescriptor = symbol.GetTypeSpecifier ();

	std::string result;
	if (typeDescriptor.GetFirstDerived () == DerivedType::Pointer) {
		result = "*";
	}

	return result += ::ToString (typeDescriptor.GetBaseType ());
}


Object* Struct::Create (const SymbolEntry& symbol) const
{
	return MakeRaw<Struct> (symbol);
}


const TypeInfo Union::typeInfo (Union (SymbolEntry {ForDeserialization}), TypeDescriptor (BaseType::Union));


void Union::ProcessImpl (const SymbolFile& symbolFile)
{
	ASSERT (symbol.HasAuxiliaryEntry ());
	const auto& auxEntry = symbol.GetAuxiliaryEntry ();

	auto indexOfMembers = auxEntry.GetSectionLength ();
	for (;; indexOfMembers += 2u) {
		const auto& symb = symbolFile.GetEntryByIndex (indexOfMembers);
		if (symb.GetStorageClass () == StorageClass::C_UNTAG) {
			continue;
		}
		if (symb.GetStorageClass () == StorageClass::C_EOS) {
			ASSERT (symb.GetName (symbolFile) == ".eos");
			break;
		}

		ASSERT (symb.GetStorageClass () == StorageClass::C_MOU);
		auto childObject = ObjectFactory (symb);
		childObject->Process (symbolFile);
		AddChild (std::move (childObject));
	}
}


std::string Union::GetType () const
{
	return std::string ();
}


Object* Union::Create (const SymbolEntry& symbol) const
{
	return MakeRaw<Union> (symbol);
}


void BasicType::ProcessImpl (const SymbolFile& symbolFile)
{
}


void Pointer::ProcessImpl (const SymbolFile& symbolFile)
{
}


std::string Pointer::GetType () const
{
	return "*" + ::ToString (symbol.GetTypeSpecifier ().GetBaseType ());
}


Object* Pointer::Create (const SymbolEntry& symbol) const
{
	return MakeRaw<Pointer> (symbol);
}


const TypeInfo Array::typeInfo (Array (SymbolEntry {ForDeserialization}), TypeDescriptor (BaseType::Void, DerivedType::Array));


static Owner<Object> ObjectFactoryForBasicTypes (const SymbolEntry& symbol);


static Owner<Object> ObjectFactoryForArray (const SymbolEntry& symbol)
{
	const auto& typeDescriptor = symbol.GetTypeSpecifier ();
	ASSERT (typeDescriptor.GetFirstDerived () == DerivedType::Array);

	const auto& baseType = typeDescriptor.GetBaseType ();
	switch (baseType) {
	case BaseType::Struct:
		return std::make_unique<Struct> (symbol);
	}

	return ObjectFactoryForBasicTypes (symbol);
}


void Array::ProcessImpl (const SymbolFile& symbolFile)
{
	const TypeDescriptor& typeDescriptor = symbol.GetTypeSpecifier ();
	INSPECT (typeDescriptor.GetSecondDerived () == DerivedType::None, "What is the role of 2nd DerivedType?");

	ASSERT (symbol.HasAuxiliaryEntry ());
	const AuxEntry& auxEntry = symbol.GetAuxiliaryEntry ();
	INSPECT (auxEntry.GetNumOfLineNumberEntries () == 0u);

	const UInt16 dimSize = auxEntry.GetArrayDimensionSize ();
	ASSERT (dimSize != 0u);

	const UInt16 reloc  = auxEntry.GetNumOfRelocationEntries ();
	ASSERT (reloc % (16 * dimSize) == 0u);
	const UInt16 offset = reloc / 16 / dimSize;

	const UInt32 index  = auxEntry.GetSectionLength ();
	const BaseType baseType = typeDescriptor.GetBaseType ();
	ASSERT (baseType == BaseType::Struct && index != 0u ||
			baseType != BaseType::Struct && index == 0u);

	for (UInt16 i = 0u; i < dimSize; ++i) {
		auto childObject = std::make_unique<ArrayElement> (symbol, offset, i);
		childObject->Process (symbolFile);
		AddChild (std::move (childObject));
	}
}


std::string Array::GetType () const
{
	TODO;

	ASSERT (symbol.HasAuxiliaryEntry ());
	const AuxEntry& auxEntry = symbol.GetAuxiliaryEntry ();
	const UInt16& dimSize = auxEntry.GetArrayDimensionSize ();

	std::string result = ::ToString (symbol.GetTypeSpecifier ().GetBaseType ());
	result += "[" + std::to_string (dimSize) + "]";
	if (auxEntry.IsMultidimensional ()) {
		TODO;
	}

	return result;
}


Object* Array::Create (const SymbolEntry& symbol) const
{
	return MakeRaw<Array> (symbol);
}


ArrayElement::ArrayElement (const SymbolEntry& symbol, const UInt16 offset, const UInt16 index)
	: Object	(symbol)
	, offset	(offset)
	, index		(index)
{
}


static SymbolEntry CreateDecreasedDimensionSymbol (const SymbolEntry& symbol)
{
	auto symbolCopy = symbol; // #Note: unnecessary aux copy
	auto auxEntryCopy = std::make_unique<AuxEntry> (symbol.GetAuxiliaryEntry ());
	auxEntryCopy->DecreaseDimension ();
	symbolCopy.SetAuxiliaryEntry (std::move (auxEntryCopy));
	return symbolCopy;
}


void ArrayElement::ProcessImpl (const SymbolFile& symbolFile)
{
	name = "[" + std::to_string (index) + "]";

	ASSERT (symbol.HasAuxiliaryEntry ());
	const AuxEntry& auxEntry = symbol.GetAuxiliaryEntry ();

	Owner<Object> object;
	if (auxEntry.IsMultidimensional ()) {
		object = std::make_unique<Array> (CreateDecreasedDimensionSymbol (symbol));
	} else {
		object = ObjectFactoryForArray (symbol);
	}

	object->Process (symbolFile);
	AddChild (std::move (object));
}


std::string ArrayElement::GetType () const
{
	TODO;
}


Object* ArrayElement::Create (const SymbolEntry& symbol) const
{
	TODO; // #ToDo: invalid state
}


std::string ArrayElement::MemberExpr () const
{
	ASSERT (GetParent () != nullptr);
	return name;
}


uint32_t ArrayElement::CalcOffset () const
{
	ASSERT (GetParent () != nullptr);
	return offset * index;
}


const TypeInfo BitField::typeInfo (BitField (SymbolEntry {ForDeserialization}), TypeDescriptor (BaseType::Void));


void BitField::ProcessImpl (const SymbolFile& symbolFile)
{
}


std::string BitField::GetType () const
{
	std::string result ("B");
	const auto baseType = symbol.GetTypeSpecifier ().GetBaseType ();
	if (baseType == BaseType::UInt32) {
		result += "32";
	} else if (baseType == BaseType::UInt16_Other || baseType == BaseType::UInt16) {
		result += "16";
	}
	return result + " #" + GetMask ();
}


Object* BitField::Create (const SymbolEntry& symbol) const
{
	return MakeRaw<BitField> (symbol);
}


std::string BitField::GetMask () const
{
	ASSERT (symbol.HasAuxiliaryEntry ());
	const uint16_t maskSize = symbol.GetAuxiliaryEntry ().GetNumOfRelocationEntries ();
	uint64_t mask = 0;
	for (uint16_t i = 0u; i < maskSize; ) {
		mask += 1;
		if (++i < maskSize) {
			mask <<= 1;
		}
	}
	const uint32_t maskOffset = symbol.GetValue ();
	mask <<= maskOffset;

	Utilities::Variable<uint32_t> var (mask);
	return "MASK=" + var.ToHEX (Utilities::ToHexModifier::KeepZeros);
}


static Owner<Object> ObjectFactoryForBasicTypes (const SymbolEntry& symbol)
{
	const auto& typeDescriptor = symbol.GetTypeSpecifier ();
	const auto& baseType = typeDescriptor.GetBaseType ();
	switch (baseType) {
	case BaseType::Void:
	case BaseType::UNKNOWN:
		ASSERT (false);
		TODO; // #TODO
	case BaseType::Char:
		return Owner<Object> (TypeInfo::Create (typeDescriptor, symbol));
//		return std::make_unique<CharType> (symbol);
	case BaseType::Int16:
	case BaseType::Int16_Other:
		return std::make_unique<Int16Type> (symbol);
	case BaseType::Int32:
		return std::make_unique<Int32Type> (symbol);
	case BaseType::Float:
		return std::make_unique<FloatType> (symbol);
	case BaseType::Double:
		return std::make_unique<DoubleType> (symbol);
	case BaseType::Enum:
		return std::make_unique<EnumType> (symbol);
	case BaseType::UChar:
		return Owner<Object> (TypeInfo::Create (typeDescriptor, symbol));
	case BaseType::UInt16:
	case BaseType::UInt16_Other:
		return std::make_unique<UInt16Type> (symbol);
	case BaseType::UInt32:
		return std::make_unique<UInt32Type> (symbol);
	}

	ASSERT (false);
	TODO; // #TODO
}


Owner<Object> File::COFF::ObjectFactory (const SymbolEntry& symbol)
{
	const auto& typeDescriptor = symbol.GetTypeSpecifier ();
	const auto& derivedType = typeDescriptor.GetFirstDerived ();
	switch (derivedType) {
	case DerivedType::Pointer:
		return std::make_unique<Pointer> (symbol);
	case DerivedType::Function:
		ASSERT (false, "This is not implemented yet.");
		TODO; // #TODO
	case DerivedType::Array:
		return std::make_unique<Array> (symbol);
	}

	const auto& baseType = typeDescriptor.GetBaseType ();
	switch (baseType) {
	case BaseType::Struct:
		return std::make_unique<Struct> (symbol);
	case BaseType::Union:
		return std::make_unique<Union> (symbol);
	}

	if (baseType == BaseType::Void ||
		baseType == BaseType::UNKNOWN ||
//		baseType == BaseType::Enum ||
		baseType == BaseType::MemberOfEnum)
	{
		ASSERT (false, "This is not implemented yet.");
		TODO; // #TODO
	}

	if (symbol.GetStorageClass () == StorageClass::C_FIELD) {
		return std::make_unique<BitField> (symbol);
	}

	ASSERT (derivedType == DerivedType::None);
	return ObjectFactoryForBasicTypes (symbol);
}