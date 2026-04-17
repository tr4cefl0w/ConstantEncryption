#include "mutation.h"

#include <iostream>


bool mutation::InsertBitJunk()
{
    return true;
}

bool mutation::InsertMovJunk() 
{
    return true;
}

bool mutation::InsertNop()
{
    const x86::Gp reg = converter::GetRandomRegister64();
    return emitter.nop(x86::qword_ptr(reg)) == kErrorOk;
}

bool mutation::InsertJunkCode()
{
    const Label next = emitter.newLabel(); //insane cf obfuscation haha
    emitter.jmp(next);
    emitter.bind(next); //jump next junk

    using FuncPtr = bool(mutation::*)(); 
    static constexpr FuncPtr funcs[] = {
        &mutation::InsertBitJunk,
        &mutation::InsertMovJunk,
        &mutation::InsertNop
    };

    const auto idx = converter::GenRandom<i8>() % std::size(funcs);
    return (this->*funcs[idx])();
}

bool mutation::MutateXor(const x86::Gp& reg) const
{
    const auto val = converter::GenRandom<i8>();

    Error status = emitter.mov(reg, val);
	status = emitter.sub(reg, reg);

    return status == kErrorOk;
}

bool mutation::MutateNearRelativeCall(const Imm& imm) const //call -> push ret, jump target (trips ida up)
{
    const Label returnofjump = emitter.newLabel();

    const x86::Gp reg = converter::GetRandomRegister64();

    Error status = emitter.sub(x86::rsp, 0x10);
    status = emitter.mov(x86::qword_ptr(x86::rsp), reg);
    status = emitter.lea(reg, x86::ptr(returnofjump));
    status = emitter.mov(x86::qword_ptr(x86::rsp, 8), reg);
    status = emitter.pop(reg);
    status = emitter.jmp(imm);
    status = emitter.bind(returnofjump);

    return status == kErrorOk;
}