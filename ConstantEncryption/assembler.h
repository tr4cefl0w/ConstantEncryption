#pragma once
#include <memory>
#include <unordered_map>
#include "converter.h"
#include "includes.hpp"

using namespace asmjit;

class assembler : public x86::Assembler
{
private:
	[[nodiscard]]
	static Operand GetOperand(const cs_x86_op&, std::uintptr_t);
	[[nodiscard]]
	static Operand HandleMemoryOperand(const cs_x86_op&, std::uintptr_t);
	bool HandleCFInstruction(x86::Inst::Id, const cs_insn&);
	bool HandleNonCFInstruction(x86::Inst::Id, const cs_insn&);
	bool HandleEncryptionPasses(x86::Inst::Id, const cs_insn&);
	bool HandleMutationPasses(x86::Inst::Id, const cs_insn&);
	bool EmitControlFlowInstruction(const x86::Inst::Id, const Label&);
	std::unordered_map<uint64_t, Label> jump_table;
	bool SetCFTarget(const cs_insn&);

public:
	using x86::Assembler::Assembler;

	assembler() = delete;
	assembler(const assembler&) = delete;

	bool HandleInstruction(const cs_insn& inst);

	[[nodiscard]]
	CodeHolder& GetCodeBuffer();
};