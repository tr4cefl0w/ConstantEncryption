#pragma once
#include "assembler.h"

//todo add real mutation instead of junkcode

using namespace asmjit;

class mutation
{
private:
	x86::Assembler& emitter;

	[[nodiscard]]
	bool InsertNop();
	[[nodiscard]]
	bool InsertMovJunk();
	[[nodiscard]]
	bool InsertBitJunk();

public:

	explicit mutation(x86::Assembler& emi)
		: emitter(emi)
	{
		
	}

	bool InsertJunkCode();

	//used when xor reg, reg with itself
	[[nodiscard]]
	bool MutateXor(const x86::Gp&) const;
	[[nodiscard]]
	bool MutateNearRelativeCall(const Imm&) const;
};