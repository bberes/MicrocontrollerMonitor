#include "SymbolTree.hpp"

// #FileHandler
#include "RelevantSymbols.hpp"
#include "TreeNodes.hpp"


File::COFF::SymbolTree::SymbolTree (const SymbolFile& symbolFile)
{
	Build (symbolFile);
}


File::COFF::SymbolTree::~SymbolTree () = default;


void File::COFF::SymbolTree::EnumerateLeaves (const ObjectProcessor& process) const
{
	for (const auto& object : objects) {
		if (object->IsLeaf ()) {
			process (*object);
		} else {
			object->Enumerate (process);
		}
	}
}


void File::COFF::SymbolTree::Build (const SymbolFile& symbolFile)
{
	RelevantSymbols symbols (symbolFile);
	symbols.Enumerate ([this, &symbolFile] (const SymbolEntry& symbol) {
		auto object = ObjectFactory (symbol);
		object->Process (symbolFile);
		objects.push_back (std::move (object));
	});
}