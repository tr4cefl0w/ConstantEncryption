#include "inst_passes.h"

bool inst_passes::subImmFromRsp(assembler& emitter, const cs_x86& inst) //what the hell did i do here!
{
	using namespace x86;

	const x86::Gp bn_reg = converter::GetRandomRegister64();
	const x86::Gp rsp_offset = converter::GetRandomRegister64();

	static constexpr std::uintptr_t ntbuildaddr = 0x7FFE0260;
	static constexpr auto divaddres = ntbuildaddr / 4;

	const auto key = converter::GenRandom<u32>();

	const auto encraddr = divaddres ^ key;

	const u8 shift = converter::GenRandom<u8>();
	const auto rotkey = _rotl(key, shift);

	const auto notencaddr = static_cast<u32>(~encraddr);

	//access ntbuildnumber 
	Error status = emitter.sub(rsp, 0x10);
	status = emitter.mov(ptr(rsp), bn_reg);
	status =emitter.mov(bn_reg.r32(), notencaddr);
	status = emitter.not_(bn_reg.r32());
	status = emitter.mov(dword_ptr(rsp, 8), rotkey);
	status = emitter.ror(dword_ptr(rsp, 8), shift);
	status = emitter.xor_(bn_reg.r32(), dword_ptr(rsp, 8));
	status = emitter.lea(bn_reg, ptr(0, bn_reg, 2));
	status = emitter.movzx(bn_reg, word_ptr(bn_reg));

	const auto imm = inst.operands[1].imm;

	const u16 nt_build_bumber = *reinterpret_cast<u16*>(ntbuildaddr);
	const auto encrimm = static_cast<u32>(imm ^ nt_build_bumber);

	status = emitter.push(rsp_offset);
	status = emitter.mov(rsp_offset, encrimm);
	status = emitter.xor_(rsp_offset, bn_reg);
	status = emitter.neg(rsp_offset);
	status = emitter.mov(bn_reg, ptr(rsp, 8));
	status = emitter.lea(rsp, ptr(rsp, rsp_offset));
	status = emitter.mov(rsp_offset, ptr(rsp, rsp_offset));
	status = emitter.add(rsp,0x18);

	return status == kErrorOk;
}

