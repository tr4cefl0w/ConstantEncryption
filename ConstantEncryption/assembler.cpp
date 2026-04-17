#include "assembler.h"

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include "mutation.h"
#include "inst_passes.h"

Operand assembler::HandleMemoryOperand(const cs_x86_op& operand, const std::uintptr_t org_rip)
{
    if (operand.mem.base == X86_REG_RIP) // we can give asmjit absolut address, and it will do the work for us
    {
        const uint64_t target = org_rip + operand.mem.disp;

        std::cout << std::hex << target << std::endl;

        return x86::ptr(target, operand.size);
    }

    x86::Gp base_reg;
    x86::Gp index_reg;

    if (operand.mem.base != X86_REG_INVALID)
        base_reg = converter::GetTargetRegister(operand.mem.base);

    if (operand.mem.index != X86_REG_INVALID)
        index_reg = converter::GetTargetRegister(operand.mem.index);

    const int32_t disp = static_cast<int32_t>(operand.mem.disp);

    return x86::ptr(base_reg, index_reg, operand.mem.scale, disp, operand.size);
}


Operand assembler::GetOperand(const cs_x86_op& operand, const std::uintptr_t org_rip)
{
    switch (operand.type)
    {
    case X86_OP_REG:
        return converter::GetTargetRegister(operand.reg);
    case X86_OP_IMM:
        return imm(operand.imm);
    case X86_OP_MEM:
        return HandleMemoryOperand(operand, org_rip);
    default: //should not happen 
        throw std::runtime_error("Invalid operand type");
    }
}

bool assembler::EmitControlFlowInstruction(const x86::Inst::Id id, const Label& label) {

    switch (id) {
    case x86::Inst::kIdJz:  this->jz(label); break;
    case x86::Inst::kIdJnz: this->jnz(label); break;
    case x86::Inst::kIdJa:  this->ja(label); break;
    case x86::Inst::kIdJb:  this->jb(label); break;
    case x86::Inst::kIdJg:  this->jg(label); break;
    case x86::Inst::kIdJl:  this->jl(label); break;
    case x86::Inst::kIdJne: this->jne(label); break;
    case x86::Inst::kIdJmp: this->jmp(label); break;
    default: throw std::runtime_error("Unsupported jcc id");
    }

    return true;
}

bool assembler::HandleCFInstruction(const x86::Inst::Id id, const cs_insn& inst)
{
    if (converter::IsJcc(id)) { //needs rework jmp can also be far -> maybe discover branches before emitting
        
    	const cs_x86_op& op = inst.detail->x86.operands[0];

        if (op.type == X86_OP_IMM) {

            const std::uintptr_t target_addr = op.imm;

            if (!jump_table.contains(target_addr))
                jump_table[target_addr] = this->newLabel(); //allows asmjit to resolve targets before we even processed them

            return this->EmitControlFlowInstruction(id, jump_table[target_addr]);
        }
    }

    return false;
}

bool assembler::SetCFTarget(const cs_insn& inst)
{
    if (!jump_table.contains(inst.address)) {
        jump_table[inst.address] = this->newLabel();
    }

    return this->bind(jump_table[inst.address]) == kErrorOk; //this creates a label for every inst, so technically we can branch to every instruction in our function
}

bool assembler::HandleNonCFInstruction(const x86::Inst::Id id, const cs_insn& inst)
{
    Operand ops[4];
    const cs_x86& x86 = inst.detail->x86;

    for (u32 i{ 0 }; i < x86.op_count; ++i)
    {
        ops[i] = GetOperand(x86.operands[i], inst.address + inst.size);
    }

    switch (x86.op_count)
    {
    case 0:
        return this->emit(id) == kErrorOk;
    case 1:
        return this->emit(id, ops[0]) == kErrorOk;
    case 2:
        return this->emit(id, ops[0], ops[1]) == kErrorOk;
    case 3:
        return this->emit(id, ops[0], ops[1], ops[2]) == kErrorOk;
    case 4:
        return this->emit(id, ops[0], ops[1], ops[2], ops[3]) == kErrorOk;
    default:
        return false;
    }
}

bool assembler::HandleEncryptionPasses(const x86::Inst::Id id, const cs_insn& inst)
{
    const cs_x86& x86 = inst.detail->x86;

	if (id == x86::Inst::kIdSub && 
        x86.operands[0].type == X86_OP_REG && 
        x86.operands[0].reg == X86_REG_RSP && 
        x86.operands[1].type == X86_OP_IMM)
	{
        if (inst_passes::subImmFromRsp(*this, x86))
            return true;
	}

    return false;
}

bool assembler::HandleMutationPasses(const x86::Inst::Id id, const cs_insn& inst)
{
    const cs_x86& x86 = inst.detail->x86;

    mutation mut(*this);
    mut.InsertJunkCode();

    if (id == x86::Inst::kIdXor &&
        x86.operands[0].type == X86_OP_REG &&
        x86.operands[1].type == X86_OP_REG &&
        x86.operands[0].reg == x86.operands[1].reg)
    {
        return mut.MutateXor(converter::GetTargetRegister(x86.operands[0].reg));
    }

	if (id == x86::Inst::kIdCall && 
        x86.operands[0].type == X86_OP_IMM)
    {
        return mut.MutateNearRelativeCall(imm(x86.operands[0].imm));
    }

    return false;
}

bool assembler::HandleInstruction(const cs_insn& inst)
{
    const x86::Inst::Id id = converter::MapInstruction(inst.id);

    if (!this->SetCFTarget(inst))
        return false;

    if (this->HandleMutationPasses(id, inst))
        return true;

	 if (this->HandleEncryptionPasses(id, inst))
        return true;

     if (this->HandleCFInstruction(id, inst)) 
        return true;
    
	  if (this->HandleNonCFInstruction(id, inst))
        return true;

    return false;
}



