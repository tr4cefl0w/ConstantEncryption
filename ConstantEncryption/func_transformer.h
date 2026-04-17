#pragma once
#include <string_view>
#include "pe.h"
#include "assembler.h"

class func_trans : public pe
{
private:
	CodeHolder code_buffer;
	JitRuntime rt;
	FileLogger logger;
	static bool PatchOrginalFunction(i8*, i32, std::size_t);
	static i32 CalcDisp(std::uintptr_t, std::uintptr_t);
	assembler InitAssemblerContext(std::uintptr_t);
public:
	bool Build(u32, u32);
	func_trans() : logger(stdout) {}
};
