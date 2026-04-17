#pragma once
#include "file.h"
#include <windows.h>

class pe : public file
{
public:

	[[nodiscard]]
	PIMAGE_DOS_HEADER GetDosHeader();
	[[nodiscard]]
	PIMAGE_NT_HEADERS64 GetNtHeader();
	[[nodiscard]]
	PIMAGE_OPTIONAL_HEADER64 GetOptionalHeader();
	[[nodiscard]]
	PIMAGE_FILE_HEADER GetFileHeader();
	[[nodiscard]]
	PIMAGE_SECTION_HEADER FirstSection();
	[[nodiscard]]
	PIMAGE_SECTION_HEADER LastSection();
	[[nodiscard]]
	PIMAGE_SECTION_HEADER CreateSection(const char*);

	[[nodiscard]]
	u32 RvaToOffset(u32);
	[[nodiscard]]
	u32 OffsetToRva(u32);

	[[nodiscard]]
	std::uintptr_t GetImageBase();
};
