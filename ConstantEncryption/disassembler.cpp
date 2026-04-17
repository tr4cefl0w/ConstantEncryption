#include "disassembler.h"

bool disassembler::DisassembleFunction(const u8* start, const std::size_t size, const std::uintptr_t address, const std::function<bool(cs_insn&)>& callback)
{
	csh handle;
	cs_insn* insn;

	cs_err err = cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
	if (err != CS_ERR_OK) {
		printf("cs_open failed: %s\n", cs_strerror(err));
		return false;
	}

	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

	std::size_t count = cs_disasm(handle, start, size, address, 0, &insn);
	if (count > 0) {
		size_t j;

		for (j = 0; j < count; j++) {

			if (!callback(insn[j]))
				return false;
		}

		cs_free(insn, count);
	}

	cs_close(&handle);

	return true;
}
