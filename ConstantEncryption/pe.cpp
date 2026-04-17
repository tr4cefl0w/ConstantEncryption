#include "pe.h"
#include <algorithm>
#include <iostream>

PIMAGE_DOS_HEADER pe::GetDosHeader()
{
	return reinterpret_cast<PIMAGE_DOS_HEADER>(m_file.data());
}

PIMAGE_NT_HEADERS64 pe::GetNtHeader()
{
	return reinterpret_cast<PIMAGE_NT_HEADERS64>(m_file.data() + GetDosHeader()->e_lfanew);
}

PIMAGE_OPTIONAL_HEADER64 pe::GetOptionalHeader()
{
	return &GetNtHeader()->OptionalHeader;
}

PIMAGE_FILE_HEADER pe::GetFileHeader()
{
	return &GetNtHeader()->FileHeader;
}

PIMAGE_SECTION_HEADER pe::FirstSection()
{
	return IMAGE_FIRST_SECTION(GetNtHeader());
}

PIMAGE_SECTION_HEADER pe::LastSection()
{
	return FirstSection() + (GetFileHeader()->NumberOfSections - 1);
}

std::uintptr_t pe::GetImageBase()
{
	return GetOptionalHeader()->ImageBase;
}

u32 pe::OffsetToRva(const u32 offset) 
{
	u32 rva{ 0 };

	std::for_each_n(FirstSection(), GetFileHeader()->NumberOfSections, [&] (const auto& sec_header)
	{
		if (offset >= sec_header.PointerToRawData && offset < (sec_header.PointerToRawData + sec_header.SizeOfRawData))
		{
			rva = (offset - sec_header.PointerToRawData) + sec_header.VirtualAddress;
		}
	});

	return rva;
}

u32 pe::RvaToOffset(const u32 rva) 
{
	u32 offset{0};

	std::for_each_n(FirstSection(), GetFileHeader()->NumberOfSections, [&](const IMAGE_SECTION_HEADER& sec_header)
	{
		if (rva >= sec_header.VirtualAddress && rva < (sec_header.VirtualAddress + sec_header.Misc.VirtualSize))
		{
			offset = (rva - sec_header.VirtualAddress) + sec_header.PointerToRawData;
		}
	});

	return offset;
}

#define ALIGN_UP(x, align) (((x) + ((align) - 1)) & ~((align) - 1))

PIMAGE_SECTION_HEADER pe::CreateSection(const char* sec_name) //creates a section inside file but doesn't append any data cuz final size is unknown at this time
{
	const auto last_sec = LastSection();

	IMAGE_SECTION_HEADER new_sec{ 0 };
	new_sec.Characteristics = 0x60000020; //rx section for now

	//add section name (8 chars max)
	std::memcpy(new_sec.Name, sec_name, std::strlen(sec_name));

	new_sec.PointerToRawData = last_sec->PointerToRawData + last_sec->SizeOfRawData;
	new_sec.VirtualAddress = last_sec->VirtualAddress + ALIGN_UP(last_sec->Misc.VirtualSize, GetOptionalHeader()->SectionAlignment); //page align this 

	const auto sec_dst = LastSection() + 1;

	std::memcpy(sec_dst, &new_sec, sizeof(IMAGE_SECTION_HEADER));

	GetFileHeader()->NumberOfSections += 1;

	return sec_dst;
}
