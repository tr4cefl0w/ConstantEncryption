#pragma once
#include "assembler.h"

class inst_passes
{
private: 
	static bool GenerateNtBuildNumber(assembler&);
public:
	static bool subImmFromRsp(assembler&, const cs_x86&);
};
