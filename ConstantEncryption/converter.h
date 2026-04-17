#pragma once
#include "includes.hpp"
#include <random>

using namespace asmjit;

class converter //converter between capstone and asmjit 
{
public:
	[[nodiscard]]
	static x86::Inst::Id MapInstruction(const u32 id);
	[[nodiscard]]
	static x86::Gp GetTargetRegister(const x86_reg& operand);
	static bool IsJcc(x86::Inst::Id id);

	template <std::integral T>
	static T GenRandom();

	[[nodiscard]]
	static x86::Gp GetRandomRegister64();
};

template <std::integral T>
T converter::GenRandom()
{
	std::mt19937_64 mt{ std::random_device{}() };

	return static_cast<T>(mt());
}


