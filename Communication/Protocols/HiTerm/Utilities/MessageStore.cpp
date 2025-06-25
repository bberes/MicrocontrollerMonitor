#include "MessageStore.hpp"

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"
#include "Protocols\HiTerm\Exceptions\HiTermExceptions.hpp"
#include "MessageTypeID.hpp"


using namespace Communication::HiTerm;


MessageStore::~MessageStore () = default;


void MessageStore::Register (const Message& message)
{
	const MessageTypeID& typeID = message.GetTypeID ();
	if (IsRegistered (message)) {
		throw std::invalid_argument ("{75B7A6D2-1F18-46AE-A0B1-A29A1F22C8D0}");
	}

	store[typeID].reset (message.New (ForDeserialization));
}


bool Communication::HiTerm::MessageStore::IsRegistered (const Message& message) const
{
	return store.count (message.GetTypeID ()) != 0u;
}


Message* MessageStore::CreateNew (const MessageTypeID& typeID) const
{
	if (store.count (typeID) != 1u) {
		throw MissingTypeID (typeID, "{B0F25F71-2DF1-426D-B044-0D3089C8415B}");
	}

	return store.at (typeID)->New (ForDeserialization);
}