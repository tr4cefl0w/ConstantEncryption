#pragma once
#include <functional>
#include "includes.hpp"

class disassembler
{
public:
	static bool DisassembleFunction(const u8*, const std::size_t, const std::uintptr_t, const std::function<bool(cs_insn&)>&); //disassembles a function given its starting address, size and callback which is invoked on each instruction in that function
};