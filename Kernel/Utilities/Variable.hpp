#pragma once
#ifndef Kernel__Utilities_Variable__hpp
#define Kernel__Utilities_Variable__hpp

// #ExportHeader
#include "KernelExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Utilities {

enum class ToHexModifier {
	SkipZeros,
	KeepZeros
};


class KERNEL_EXPORT IVariable {
public:
	virtual ~IVariable ();

	virtual std::string		ToHEX		(const ToHexModifier modifier) const = 0;
	virtual std::string		ToString	() const = 0;
};


template <typename Type>
class Variable final : public IVariable {
public:
	explicit Variable (const Type& value);
	virtual ~Variable ();

	virtual std::string		ToHEX		(const ToHexModifier modifier) const override;
	virtual std::string		ToString	() const override;

private:
	Type	value;
};


KERNEL_EXPORT
std::string ByteToHEX (const UInt8 byte);

}


template <typename Type>
inline Utilities::Variable<Type>::Variable (const Type& value)
	: value (value)
{
}


template <typename Type>
inline Utilities::Variable<Type>::~Variable ()
{
}


template <typename Type>
inline std::string Utilities::Variable<Type>::ToHEX (const ToHexModifier modifier) const
{
	constexpr size_t size = sizeof (Type);
	std::string result;
	bool skipEnabled = true;
	for (UInt32 i = size; i > 0u; ) {
		const auto byte = reinterpret_cast<const UInt8*> (&value)[--i];
		if (skipEnabled && modifier == ToHexModifier::SkipZeros && i > 0u) {
			if (byte == 0u) {
				continue;
			} else {
				skipEnabled = false;
			}
		}
		result += ByteToHEX (byte);
	}

	if (modifier == ToHexModifier::SkipZeros && result[0] == '0') {
		result = result.substr (1u);
	}

	return "0x" + result;
}


template <typename Type>
inline std::string Utilities::Variable<Type>::ToString () const
{
	return std::to_string (value);
}


#endif