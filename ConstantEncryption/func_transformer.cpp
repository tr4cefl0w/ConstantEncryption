#include "func_transformer.h"

#include <iostream>
#include <algorithm>

bool func_trans::Build(const u32 start_rva, const u32 end_rva)
{
	const std::size_t func_size = end_rva - start_rva;
	const std::uintptr_t rip = this->GetImageBase() + start_rva;

	const auto new_sec = this->CreateSection(".enc");
	const std::uintptr_t new_rip = this->GetImageBase() + new_sec->VirtualAddress;

	auto function_assembler = this->InitAssemblerContext(new_rip);

	if (!disassembler::DisassembleFunction(
		reinterpret_cast<u8*>(m_file.data()) + this->RvaToOffset(start_rva),
		func_size,
		rip,
		[&](const cs_insn& inst)
		{
			return function_assembler.HandleInstruction(inst);
		}))
	{
		return false;
	}

	const auto sec_size = static_cast<DWORD>(code_buffer.codeSize());

	new_sec->SizeOfRawData = sec_size;
	new_sec->Misc.VirtualSize = sec_size;
	m_file.resize(m_file.size() + sec_size);

	this->GetOptionalHeader()->SizeOfImage += sec_size;

	code_buffer.copySectionData(m_file.data() + new_sec->PointerToRawData, new_sec->SizeOfRawData, 0);

	const auto disp = func_trans::CalcDisp(new_rip, rip); //displacement from org_func to new_func

	if (!func_trans::PatchOrginalFunction(m_file.data() + this->RvaToOffset(start_rva), disp, func_size))
	{
		return false;
	}

	return true;
}

assembler func_trans::InitAssemblerContext(const std::uintptr_t base)
{
	code_buffer.init(rt.environment(), base);

	logger.setFlags(
		FormatFlags::kExplainImms |
		FormatFlags::kHexImms |
		FormatFlags::kHexOffsets);

	code_buffer.setLogger(&logger);

	return assembler{ &code_buffer };
}

#include <random>

bool func_trans::PatchOrginalFunction(i8* org_func, const i32 disp, const std::size_t func_size)
{
	if (func_size < 5)
		return false;

	u8 jump_inst[5]{ 0xE9, 0x00, 0x00, 0x00, 0x00 };

	*reinterpret_cast<i32*>(jump_inst + 1) = disp;

	std::memcpy(org_func, jump_inst, 5);

	std::mt19937 mt{ std::random_device{}() };

	std::for_each_n(org_func + 5, static_cast<std::ptrdiff_t>(func_size) - 5, [&](i8& byte)
	{
		byte = static_cast<i8>(mt() % 255);
	});

	return true;
}

i32 func_trans::CalcDisp(const std::uintptr_t new_rip, const std::uintptr_t old_rip)
{
	return static_cast<i32>(new_rip - (old_rip + 5));
}
