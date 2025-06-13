#pragma once
#ifndef FileHandler__COFF_HeaderFlags__hpp
#define FileHandler__COFF_HeaderFlags__hpp

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Utilities\Debug.hpp"

// #FileHandler
#include "TargetID.hpp"


namespace File::COFF {

class HeaderFlags final
	: private Serializable
	, private Deserializable
{
public:
	explicit HeaderFlags (DeserializationSelector);

	virtual size_t	Read					(DataStream& is) override;
	virtual size_t	Write					(DataStream& os) const override;

	bool			HasRelocationInfo		() const;
	bool			IsRelocatable			() const;
	bool			HasLineNumbers			(const TargetID& targetID) const;
	bool			HasLocalSymbols			() const;
	bool			IsLittleEndianDevice	() const;
	bool			IsBigEndianDevice		(const TargetID& targetID) const;
	bool			HasDuplicatedSymbols	(const TargetID& targetID) const;

private:
	UInt16	flags;

DEBUG_ONLY (
	void	DebugInit ();

	bool	hasRelocationInfo;
	bool	isRelocatable;
	bool	hasLineNumbers;
	bool	hasLocalSymbols;
	bool	isLittleEndianDevice;
	bool	isBigEndianDevice;
	bool	hasDuplicatedSymbols;
)
};

}


#endif