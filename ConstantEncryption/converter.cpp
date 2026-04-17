#include "converter.h"

#include <iostream>
#include <stdexcept>

//thanks chatgpt
x86::Gp converter::GetTargetRegister(const x86_reg& operand)
{
    using namespace asmjit::x86;

    switch (operand)
    {
        // RAX family
    case X86_REG_RAX: return rax;
    case X86_REG_EAX: return eax;
    case X86_REG_AX:  return ax;
    case X86_REG_AL:  return al;
    case X86_REG_AH:  return ah;

        // RBX family
    case X86_REG_RBX: return rbx;
    case X86_REG_EBX: return ebx;
    case X86_REG_BX:  return bx;
    case X86_REG_BL:  return bl;
    case X86_REG_BH:  return bh;

        // RCX family
    case X86_REG_RCX: return rcx;
    case X86_REG_ECX: return ecx;
    case X86_REG_CX:  return cx;
    case X86_REG_CL:  return cl;
    case X86_REG_CH:  return ch;

        // RDX family
    case X86_REG_RDX: return rdx;
    case X86_REG_EDX: return edx;
    case X86_REG_DX:  return dx;
    case X86_REG_DL:  return dl;
    case X86_REG_DH:  return dh;

        // RSI family
    case X86_REG_RSI: return rsi;
    case X86_REG_ESI: return esi;
    case X86_REG_SI:  return si;
    case X86_REG_SIL: return sil;

        // RDI family
    case X86_REG_RDI: return rdi;
    case X86_REG_EDI: return edi;
    case X86_REG_DI:  return di;
    case X86_REG_DIL: return dil;

        // RBP family
    case X86_REG_RBP: return rbp;
    case X86_REG_EBP: return ebp;
    case X86_REG_BP:  return bp;
    case X86_REG_BPL: return bpl;

        // RSP family
    case X86_REG_RSP: return rsp;
    case X86_REG_ESP: return esp;
    case X86_REG_SP:  return sp;
    case X86_REG_SPL: return spl;

        // R8–R15 families
    case X86_REG_R8:  return r8;
    case X86_REG_R8D: return r8d;
    case X86_REG_R8W: return r8w;
    case X86_REG_R8B: return r8b;

    case X86_REG_R9:  return r9;
    case X86_REG_R9D: return r9d;
    case X86_REG_R9W: return r9w;
    case X86_REG_R9B: return r9b;

    case X86_REG_R10:  return r10;
    case X86_REG_R10D: return r10d;
    case X86_REG_R10W: return r10w;
    case X86_REG_R10B: return r10b;

    case X86_REG_R11:  return r11;
    case X86_REG_R11D: return r11d;
    case X86_REG_R11W: return r11w;
    case X86_REG_R11B: return r11b;

    case X86_REG_R12:  return r12;
    case X86_REG_R12D: return r12d;
    case X86_REG_R12W: return r12w;
    case X86_REG_R12B: return r12b;

    case X86_REG_R13:  return r13;
    case X86_REG_R13D: return r13d;
    case X86_REG_R13W: return r13w;
    case X86_REG_R13B: return r13b;

    case X86_REG_R14:  return r14;
    case X86_REG_R14D: return r14d;
    case X86_REG_R14W: return r14w;
    case X86_REG_R14B: return r14b;

    case X86_REG_R15:  return r15;
    case X86_REG_R15D: return r15d;
    case X86_REG_R15W: return r15w;
    case X86_REG_R15B: return r15b;

    default:
        throw std::runtime_error("Unsupported register");
    }
}

//thanks chatgpt
x86::Inst::Id converter::MapInstruction(const u32 id)
{
    switch (id) {

        // Data Movement
    case X86_INS_MOV: return x86::Inst::kIdMov;
    case X86_INS_MOVZX: return x86::Inst::kIdMovzx;
    case X86_INS_MOVSX: return x86::Inst::kIdMovsx;
    case X86_INS_MOVSXD: return x86::Inst::kIdMovsxd;
    case X86_INS_LEA: return x86::Inst::kIdLea;
    case X86_INS_XCHG: return x86::Inst::kIdXchg;
    case X86_INS_CMOVAE: return x86::Inst::kIdCmovae;
    case X86_INS_CMOVA: return x86::Inst::kIdCmova;
    case X86_INS_CMOVBE: return x86::Inst::kIdCmovbe;
    case X86_INS_CMOVB: return x86::Inst::kIdCmovb;
    case X86_INS_CMOVE: return x86::Inst::kIdCmove;
    case X86_INS_CMOVG: return x86::Inst::kIdCmovg;
    case X86_INS_CMOVGE: return x86::Inst::kIdCmovge;
    case X86_INS_CMOVL: return x86::Inst::kIdCmovl;
    case X86_INS_CMOVLE: return x86::Inst::kIdCmovle;
    case X86_INS_CMOVNE: return x86::Inst::kIdCmovne;
    case X86_INS_CMOVNO: return x86::Inst::kIdCmovno;
    case X86_INS_CMOVNP: return x86::Inst::kIdCmovnp;
    case X86_INS_CMOVNS: return x86::Inst::kIdCmovns;
    case X86_INS_CMOVO: return x86::Inst::kIdCmovo;
    case X86_INS_CMOVP: return x86::Inst::kIdCmovp;
    case X86_INS_CMOVS: return x86::Inst::kIdCmovs;
    case X86_INS_BSWAP: return x86::Inst::kIdBswap;
    case X86_INS_MOVABS: return x86::Inst::kIdMovabs;
    case X86_INS_MOVBE: return x86::Inst::kIdMovbe;
    case X86_INS_XLATB: return x86::Inst::kIdXlatb;

        // Arithmetic
    case X86_INS_ADD: return x86::Inst::kIdAdd;
    case X86_INS_ADC: return x86::Inst::kIdAdc;
    case X86_INS_SUB: return x86::Inst::kIdSub;
    case X86_INS_SBB: return x86::Inst::kIdSbb;
    case X86_INS_MUL: return x86::Inst::kIdMul;
    case X86_INS_IMUL: return x86::Inst::kIdImul;
    case X86_INS_DIV: return x86::Inst::kIdDiv;
    case X86_INS_IDIV: return x86::Inst::kIdIdiv;
    case X86_INS_INC: return x86::Inst::kIdInc;
    case X86_INS_DEC: return x86::Inst::kIdDec;
    case X86_INS_NEG: return x86::Inst::kIdNeg;
    case X86_INS_CMP: return x86::Inst::kIdCmp;
    case X86_INS_ADCX: return x86::Inst::kIdAdcx;
    case X86_INS_ADOX: return x86::Inst::kIdAdox;

        // Logical
    case X86_INS_AND: return x86::Inst::kIdAnd;
    case X86_INS_OR:  return x86::Inst::kIdOr;
    case X86_INS_XOR: return x86::Inst::kIdXor;
    case X86_INS_NOT: return x86::Inst::kIdNot;
    case X86_INS_TEST: return x86::Inst::kIdTest;

        // Shifts & Rotates
    case X86_INS_SHL: return x86::Inst::kIdShl;
    case X86_INS_SHR: return x86::Inst::kIdShr;
    case X86_INS_SAL: return x86::Inst::kIdSal;
    case X86_INS_SAR: return x86::Inst::kIdSar;
    case X86_INS_ROL: return x86::Inst::kIdRol;
    case X86_INS_ROR: return x86::Inst::kIdRor;
    case X86_INS_RCL: return x86::Inst::kIdRcl;
    case X86_INS_RCR: return x86::Inst::kIdRcr;
    case X86_INS_SHLD: return x86::Inst::kIdShld;
    case X86_INS_SHRD: return x86::Inst::kIdShrd;

        // Bit Manipulation
    case X86_INS_BT: return x86::Inst::kIdBt;
    case X86_INS_BTC: return x86::Inst::kIdBtc;
    case X86_INS_BTR: return x86::Inst::kIdBtr;
    case X86_INS_BTS: return x86::Inst::kIdBts;
    case X86_INS_BSF: return x86::Inst::kIdBsf;
    case X86_INS_BSR: return x86::Inst::kIdBsr;
    case X86_INS_TZCNT: return x86::Inst::kIdTzcnt;
    case X86_INS_LZCNT: return x86::Inst::kIdLzcnt;
    case X86_INS_POPCNT: return x86::Inst::kIdPopcnt;
    case X86_INS_BEXTR: return x86::Inst::kIdBextr;
    case X86_INS_BLSI: return x86::Inst::kIdBlsi;
    case X86_INS_BLSMSK: return x86::Inst::kIdBlsmsk;
    case X86_INS_BLSR: return x86::Inst::kIdBlsr;
    case X86_INS_ANDN: return x86::Inst::kIdAndn;

        // Control Flow - Unconditional
    case X86_INS_JMP: return x86::Inst::kIdJmp;
    case X86_INS_LJMP: return x86::Inst::kIdLjmp;
    case X86_INS_CALL: return x86::Inst::kIdCall;
    case X86_INS_LCALL: return x86::Inst::kIdLcall;
    case X86_INS_RET: return x86::Inst::kIdRet;
    case X86_INS_RETF: return x86::Inst::kIdRet;
    case X86_INS_IRET: return x86::Inst::kIdIret;
    case X86_INS_IRETD: return x86::Inst::kIdIretd;
    case X86_INS_IRETQ: return x86::Inst::kIdIretq;
    case X86_INS_SYSCALL: return x86::Inst::kIdSyscall;
    case X86_INS_SYSRET: return x86::Inst::kIdSysret;
    case X86_INS_SYSENTER: return x86::Inst::kIdSysenter;
    case X86_INS_SYSEXIT: return x86::Inst::kIdSysexit;

        // Control Flow - Conditional
    case X86_INS_JE:  return x86::Inst::kIdJe;
    case X86_INS_JNE: return x86::Inst::kIdJne;
    case X86_INS_JG:  return x86::Inst::kIdJg;
    case X86_INS_JGE: return x86::Inst::kIdJge;
    case X86_INS_JL:  return x86::Inst::kIdJl;
    case X86_INS_JLE: return x86::Inst::kIdJle;
    case X86_INS_JA:  return x86::Inst::kIdJa;
    case X86_INS_JAE: return x86::Inst::kIdJae;
    case X86_INS_JB:  return x86::Inst::kIdJb;
    case X86_INS_JBE: return x86::Inst::kIdJbe;
    case X86_INS_JO:  return x86::Inst::kIdJo;
    case X86_INS_JNO: return x86::Inst::kIdJno;
    case X86_INS_JS:  return x86::Inst::kIdJs;
    case X86_INS_JNS: return x86::Inst::kIdJns;
    case X86_INS_JP:  return x86::Inst::kIdJp;
    case X86_INS_JNP: return x86::Inst::kIdJnp;
    case X86_INS_JECXZ: return x86::Inst::kIdJecxz;


        // Loop Control
    case X86_INS_LOOP: return x86::Inst::kIdLoop;
    case X86_INS_LOOPE: return x86::Inst::kIdLoope;
    case X86_INS_LOOPNE: return x86::Inst::kIdLoopne;

        // Stack Operations
    case X86_INS_PUSH: return x86::Inst::kIdPush;
    case X86_INS_POP:  return x86::Inst::kIdPop;
    case X86_INS_PUSHF: return x86::Inst::kIdPushf;
    case X86_INS_PUSHFD: return x86::Inst::kIdPushfd;
    case X86_INS_PUSHFQ: return x86::Inst::kIdPushfq;
    case X86_INS_POPF: return x86::Inst::kIdPopf;
    case X86_INS_POPFD: return x86::Inst::kIdPopfd;
    case X86_INS_POPFQ: return x86::Inst::kIdPopfq;
    case X86_INS_ENTER: return x86::Inst::kIdEnter;
    case X86_INS_LEAVE: return x86::Inst::kIdLeave;

        // Flag Operations
    case X86_INS_STC: return x86::Inst::kIdStc;
    case X86_INS_CLC: return x86::Inst::kIdClc;
    case X86_INS_CMC: return x86::Inst::kIdCmc;
    case X86_INS_STD: return x86::Inst::kIdStd;
    case X86_INS_CLD: return x86::Inst::kIdCld;
    case X86_INS_STI: return x86::Inst::kIdSti;
    case X86_INS_CLI: return x86::Inst::kIdCli;
    case X86_INS_SAHF: return x86::Inst::kIdSahf;
    case X86_INS_LAHF: return x86::Inst::kIdLahf;
    case X86_INS_CLAC: return x86::Inst::kIdClac;
    case X86_INS_STAC: return x86::Inst::kIdStac;

        // String Operations
    case X86_INS_MOVSD: return x86::Inst::kIdMovsd;

        // I/O Operations
    case X86_INS_IN: return x86::Inst::kIdIn;
    case X86_INS_OUT: return x86::Inst::kIdOut;

        // Sign/Zero Extension
    case X86_INS_CWDE: return x86::Inst::kIdCwde;
    case X86_INS_CDQE: return x86::Inst::kIdCdqe;
    case X86_INS_CWD: return x86::Inst::kIdCwd;
    case X86_INS_CDQ: return x86::Inst::kIdCdq;
    case X86_INS_CQO: return x86::Inst::kIdCqo;
    case X86_INS_CBW: return x86::Inst::kIdCbw;

        // Decimal Arithmetic (x86 legacy)
    case X86_INS_DAA: return x86::Inst::kIdDaa;
    case X86_INS_DAS: return x86::Inst::kIdDas;
    case X86_INS_AAA: return x86::Inst::kIdAaa;
    case X86_INS_AAS: return x86::Inst::kIdAas;
    case X86_INS_AAM: return x86::Inst::kIdAam;
    case X86_INS_AAD: return x86::Inst::kIdAad;

        // Bound & ARPL
    case X86_INS_BOUND: return x86::Inst::kIdBound;
    case X86_INS_ARPL: return x86::Inst::kIdArpl;

        // Segment Operations
    case X86_INS_LDS: return x86::Inst::kIdLds;
    case X86_INS_LES: return x86::Inst::kIdLes;
    case X86_INS_LFS: return x86::Inst::kIdLfs;
    case X86_INS_LGS: return x86::Inst::kIdLgs;
    case X86_INS_LSS: return x86::Inst::kIdLss;

        // System Instructions
    case X86_INS_CPUID: return x86::Inst::kIdCpuid;
    case X86_INS_RDTSC: return x86::Inst::kIdRdtsc;
    case X86_INS_RDTSCP: return x86::Inst::kIdRdtscp;
    case X86_INS_RDMSR: return x86::Inst::kIdRdmsr;
    case X86_INS_WRMSR: return x86::Inst::kIdWrmsr;
    case X86_INS_RDPMC: return x86::Inst::kIdRdpmc;
    case X86_INS_RDFSBASE: return x86::Inst::kIdRdfsbase;
    case X86_INS_RDGSBASE: return x86::Inst::kIdRdgsbase;
    case X86_INS_WRFSBASE: return x86::Inst::kIdWrfsbase;
    case X86_INS_WRGSBASE: return x86::Inst::kIdWrgsbase;
    case X86_INS_SWAPGS: return x86::Inst::kIdSwapgs;
    case X86_INS_RDPID: return x86::Inst::kIdRdpid;
    case X86_INS_MONITOR: return x86::Inst::kIdMonitor;
    case X86_INS_MWAIT: return x86::Inst::kIdMwait;
    case X86_INS_MONITORX: return x86::Inst::kIdMonitorx;
    case X86_INS_MWAITX: return x86::Inst::kIdMwaitx;
    case X86_INS_CLDEMOTE: return x86::Inst::kIdCldemote;
    case X86_INS_CLFLUSH: return x86::Inst::kIdClflush;
    case X86_INS_CLFLUSHOPT: return x86::Inst::kIdClflushopt;
    case X86_INS_CLWB: return x86::Inst::kIdClwb;
    case X86_INS_CLZERO: return x86::Inst::kIdClzero;
    case X86_INS_LFENCE: return x86::Inst::kIdLfence;
    case X86_INS_SFENCE: return x86::Inst::kIdSfence;
    case X86_INS_MFENCE: return x86::Inst::kIdMfence;
    case X86_INS_LGDT: return x86::Inst::kIdLgdt;
    case X86_INS_SGDT: return x86::Inst::kIdSgdt;
    case X86_INS_LIDT: return x86::Inst::kIdLidt;
    case X86_INS_SIDT: return x86::Inst::kIdSidt;
    case X86_INS_LLDT: return x86::Inst::kIdLldt;
    case X86_INS_SLDT: return x86::Inst::kIdSldt;
    case X86_INS_LTR: return x86::Inst::kIdLtr;
    case X86_INS_STR: return x86::Inst::kIdStr;
    case X86_INS_LMSW: return x86::Inst::kIdLmsw;
    case X86_INS_SMSW: return x86::Inst::kIdSmsw;
    case X86_INS_INVLPG: return x86::Inst::kIdInvlpg;
    case X86_INS_INVPCID: return x86::Inst::kIdInvpcid;
    case X86_INS_INVVPID: return x86::Inst::kIdInvvpid;
    case X86_INS_INVEPT: return x86::Inst::kIdInvept;
    case X86_INS_VMCALL: return x86::Inst::kIdVmcall;
    case X86_INS_VMLAUNCH: return x86::Inst::kIdVmlaunch;
    case X86_INS_VMRESUME: return x86::Inst::kIdVmresume;
    case X86_INS_VMXOFF: return x86::Inst::kIdVmxoff;
    case X86_INS_VMXON: return x86::Inst::kIdVmxon;
    case X86_INS_VMCLEAR: return x86::Inst::kIdVmclear;
    case X86_INS_VMPTRLD: return x86::Inst::kIdVmptrld;
    case X86_INS_VMPTRST: return x86::Inst::kIdVmptrst;
    case X86_INS_VMREAD: return x86::Inst::kIdVmread;
    case X86_INS_VMWRITE: return x86::Inst::kIdVmwrite;
    case X86_INS_SKINIT: return x86::Inst::kIdSkinit;
    case X86_INS_STGI: return x86::Inst::kIdStgi;
    case X86_INS_CLGI: return x86::Inst::kIdClgi;
    case X86_INS_VMLOAD: return x86::Inst::kIdVmload;
    case X86_INS_VMSAVE: return x86::Inst::kIdVmsave;
    case X86_INS_VMMCALL: return x86::Inst::kIdVmmcall;
    case X86_INS_VMRUN: return x86::Inst::kIdVmrun;
    case X86_INS_GETSEC: return x86::Inst::kIdGetsec;
    case X86_INS_TPAUSE: return x86::Inst::kIdTpause;
    case X86_INS_UMONITOR: return x86::Inst::kIdUmonitor;
    case X86_INS_UMWAIT: return x86::Inst::kIdUmwait;
    case X86_INS_SETSSBSY: return x86::Inst::kIdSetssbsy;
    case X86_INS_CLRSSBSY: return x86::Inst::kIdClrssbsy;
    case X86_INS_SAVEPREVSSP: return x86::Inst::kIdSaveprevssp;
    case X86_INS_RSTORSSP: return x86::Inst::kIdRstorssp;
    case X86_INS_INCSSPD: return x86::Inst::kIdIncsspd;
    case X86_INS_INCSSPQ: return x86::Inst::kIdIncsspq;
    case X86_INS_ENDBR32: return x86::Inst::kIdEndbr32;
    case X86_INS_ENDBR64: return x86::Inst::kIdEndbr64;
    case X86_INS_HLT: return x86::Inst::kIdHlt;
    case X86_INS_PAUSE: return x86::Inst::kIdPause;
    case X86_INS_NOP: return x86::Inst::kIdNop;
    case X86_INS_UD2: return x86::Inst::kIdUd2;
    case X86_INS_INT: return x86::Inst::kIdInt;
    case X86_INS_INT3: return x86::Inst::kIdInt3;
    case X86_INS_INTO: return x86::Inst::kIdInto;

        // XSAVE
    case X86_INS_XGETBV: return x86::Inst::kIdXgetbv;
    case X86_INS_XSETBV: return x86::Inst::kIdXsetbv;
    case X86_INS_XSAVE: return x86::Inst::kIdXsave;
    case X86_INS_XSAVE64: return x86::Inst::kIdXsave64;
    case X86_INS_XRSTOR: return x86::Inst::kIdXrstor;
    case X86_INS_XRSTOR64: return x86::Inst::kIdXrstor64;
    case X86_INS_XSAVEOPT: return x86::Inst::kIdXsaveopt;
    case X86_INS_XSAVEOPT64: return x86::Inst::kIdXsaveopt64;
    case X86_INS_XSAVES: return x86::Inst::kIdXsaves;
    case X86_INS_XSAVES64: return x86::Inst::kIdXsaves64;
    case X86_INS_XRSTORS: return x86::Inst::kIdXrstors;
    case X86_INS_XRSTORS64: return x86::Inst::kIdXrstors64;
    case X86_INS_XSAVEC: return x86::Inst::kIdXsavec;
    case X86_INS_XSAVEC64: return x86::Inst::kIdXsavec64;

        // FXSAVE/FXRSTOR
    case X86_INS_FXSAVE: return x86::Inst::kIdFxsave;
    case X86_INS_FXSAVE64: return x86::Inst::kIdFxsave64;
    case X86_INS_FXRSTOR: return x86::Inst::kIdFxrstor;
    case X86_INS_FXRSTOR64: return x86::Inst::kIdFxrstor64;

        // CRC32
    case X86_INS_CRC32: return x86::Inst::kIdCrc32;

        // CMPXCHG
    case X86_INS_CMPXCHG: return x86::Inst::kIdCmpxchg;
    case X86_INS_CMPXCHG8B: return x86::Inst::kIdCmpxchg8b;
    case X86_INS_CMPXCHG16B: return x86::Inst::kIdCmpxchg16b;

        // XADD
    case X86_INS_XADD: return x86::Inst::kIdXadd;


        // LAR/LSL
    case X86_INS_LAR: return x86::Inst::kIdLar;
    case X86_INS_LSL: return x86::Inst::kIdLsl;
    case X86_INS_VERW: return x86::Inst::kIdVerw;
    case X86_INS_VERR: return x86::Inst::kIdVerr;

        // LDMXCSR/STMXCSR
    case X86_INS_LDMXCSR: return x86::Inst::kIdLdmxcsr;
    case X86_INS_STMXCSR: return x86::Inst::kIdStmxcsr;

        // MOVNT (Non-temporal moves)
    case X86_INS_MOVNTI: return x86::Inst::kIdMovnti;
    case X86_INS_MOVNTDQA: return x86::Inst::kIdMovntdqa;
    case X86_INS_MOVNTQ: return x86::Inst::kIdMovntq;

        // MOVDIR
    case X86_INS_MOVDIRI: return x86::Inst::kIdMovdiri;
    case X86_INS_MOVDIR64B: return x86::Inst::kIdMovdir64b;


        // PTWRITE
    case X86_INS_PTWRITE: return x86::Inst::kIdPtwrite;

        // PREFETCH
    case X86_INS_PREFETCHNTA: return x86::Inst::kIdPrefetchnta;
    case X86_INS_PREFETCHT0: return x86::Inst::kIdPrefetcht0;
    case X86_INS_PREFETCHT1: return x86::Inst::kIdPrefetcht1;
    case X86_INS_PREFETCHT2: return x86::Inst::kIdPrefetcht2;
    case X86_INS_PREFETCHW: return x86::Inst::kIdPrefetchw;
    case X86_INS_PREFETCHWT1: return x86::Inst::kIdPrefetchwt1;

        // TSX (Transactional Synchronization Extensions)
    case X86_INS_XABORT: return x86::Inst::kIdXabort;
    case X86_INS_XBEGIN: return x86::Inst::kIdXbegin;
    case X86_INS_XEND: return x86::Inst::kIdXend;
    case X86_INS_XTEST: return x86::Inst::kIdXtest;




        // AVX-512 BITALG
    case X86_INS_VPOPCNTB: return x86::Inst::kIdVpopcntb;
    case X86_INS_VPOPCNTW: return x86::Inst::kIdVpopcntw;
    case X86_INS_VPOPCNTD: return x86::Inst::kIdVpopcntd;
    case X86_INS_VPOPCNTQ: return x86::Inst::kIdVpopcntq;

        // AVX-512 VBMI
    case X86_INS_VPERMB: return x86::Inst::kIdVpermb;
    case X86_INS_VPERMW: return x86::Inst::kIdVpermw;
    case X86_INS_VPERMT2B: return x86::Inst::kIdVpermt2b;
    case X86_INS_VPERMT2W: return x86::Inst::kIdVpermt2w;
    case X86_INS_VPMULTISHIFTQB: return x86::Inst::kIdVpmultishiftqb;

        // AVX-512 VBMI2
    case X86_INS_VPCOMPRESSB: return x86::Inst::kIdVpcompressb;
    case X86_INS_VPCOMPRESSW: return x86::Inst::kIdVpcompressw;
    case X86_INS_VPEXPANDB: return x86::Inst::kIdVpexpandb;
    case X86_INS_VPEXPANDW: return x86::Inst::kIdVpexpandw;
    case X86_INS_VPSHLD: return x86::Inst::kIdVpshld;

        // AVX-512 VNNI
    case X86_INS_VPDPBUSD: return x86::Inst::kIdVpdpbusd;
    case X86_INS_VPDPBUSDS: return x86::Inst::kIdVpdpbusds;
    case X86_INS_VPDPWSSD: return x86::Inst::kIdVpdpwssd;
    case X86_INS_VPDPWSSDS: return x86::Inst::kIdVpdpwssds;

        // AVX-512 IFMA
    case X86_INS_VPMADD52HUQ: return x86::Inst::kIdVpmadd52huq;
    case X86_INS_VPMADD52LUQ: return x86::Inst::kIdVpmadd52luq;



        // AVX-512 4FMAPS/4VNNIW
    case X86_INS_V4FMADDPS: return x86::Inst::kIdV4fmaddps;
    case X86_INS_V4FMADDSS: return x86::Inst::kIdV4fmaddss;
    case X86_INS_V4FNMADDPS: return x86::Inst::kIdV4fnmaddps;
    case X86_INS_V4FNMADDSS: return x86::Inst::kIdV4fnmaddss;


    case X86_INS_VCVTPH2PS: return x86::Inst::kIdVcvtph2ps;

    case X86_INS_VCVTPS2PH: return x86::Inst::kIdVcvtps2ph;

    case X86_INS_VFRCZPD: return x86::Inst::kIdVfrczpd;
    case X86_INS_VFRCZPS: return x86::Inst::kIdVfrczps;
    case X86_INS_VFRCZSD: return x86::Inst::kIdVfrczsd;
    case X86_INS_VFRCZSS: return x86::Inst::kIdVfrczss;


        // GFNI (Galois Field New Instructions)
    case X86_INS_GF2P8AFFINEINVQB: return x86::Inst::kIdGf2p8affineinvqb;
    case X86_INS_GF2P8AFFINEQB: return x86::Inst::kIdGf2p8affineqb;
    case X86_INS_GF2P8MULB: return x86::Inst::kIdGf2p8mulb;
    case X86_INS_VGF2P8AFFINEINVQB: return x86::Inst::kIdVgf2p8affineinvqb;
    case X86_INS_VGF2P8AFFINEQB: return x86::Inst::kIdVgf2p8affineqb;
    case X86_INS_VGF2P8MULB: return x86::Inst::kIdVgf2p8mulb;

        // VAES (Vector AES)
    case X86_INS_VAESDEC: return x86::Inst::kIdVaesdec;
    case X86_INS_VAESDECLAST: return x86::Inst::kIdVaesdeclast;
    case X86_INS_VAESENC: return x86::Inst::kIdVaesenc;
    case X86_INS_VAESENCLAST: return x86::Inst::kIdVaesenclast;
    case X86_INS_VAESIMC: return x86::Inst::kIdVaesimc;
    case X86_INS_VAESKEYGENASSIST: return x86::Inst::kIdVaeskeygenassist;

        // VPCLMULQDQ (Vector Carry-less Multiplication)
    case X86_INS_VPCLMULQDQ: return x86::Inst::kIdVpclmulqdq;

        // SHA Extensions
    case X86_INS_SHA1MSG1: return x86::Inst::kIdSha1msg1;
    case X86_INS_SHA1MSG2: return x86::Inst::kIdSha1msg2;
    case X86_INS_SHA1NEXTE: return x86::Inst::kIdSha1nexte;
    case X86_INS_SHA1RNDS4: return x86::Inst::kIdSha1rnds4;
    case X86_INS_SHA256MSG1: return x86::Inst::kIdSha256msg1;
    case X86_INS_SHA256MSG2: return x86::Inst::kIdSha256msg2;
    case X86_INS_SHA256RNDS2: return x86::Inst::kIdSha256rnds2;

        // FMA (Fused Multiply-Add)
    case X86_INS_VFMADD132PD: return x86::Inst::kIdVfmadd132pd;
    case X86_INS_VFMADD132PS: return x86::Inst::kIdVfmadd132ps;
    case X86_INS_VFMADD132SD: return x86::Inst::kIdVfmadd132sd;
    case X86_INS_VFMADD132SS: return x86::Inst::kIdVfmadd132ss;
    case X86_INS_VFMADD213PD: return x86::Inst::kIdVfmadd213pd;
    case X86_INS_VFMADD213PS: return x86::Inst::kIdVfmadd213ps;
    case X86_INS_VFMADD213SD: return x86::Inst::kIdVfmadd213sd;
    case X86_INS_VFMADD213SS: return x86::Inst::kIdVfmadd213ss;
    case X86_INS_VFMADD231PD: return x86::Inst::kIdVfmadd231pd;
    case X86_INS_VFMADD231PS: return x86::Inst::kIdVfmadd231ps;
    case X86_INS_VFMADD231SD: return x86::Inst::kIdVfmadd231sd;
    case X86_INS_VFMADD231SS: return x86::Inst::kIdVfmadd231ss;
    case X86_INS_VFMADDSUB132PD: return x86::Inst::kIdVfmaddsub132pd;
    case X86_INS_VFMADDSUB132PS: return x86::Inst::kIdVfmaddsub132ps;
    case X86_INS_VFMADDSUB213PD: return x86::Inst::kIdVfmaddsub213pd;
    case X86_INS_VFMADDSUB213PS: return x86::Inst::kIdVfmaddsub213ps;
    case X86_INS_VFMADDSUB231PD: return x86::Inst::kIdVfmaddsub231pd;
    case X86_INS_VFMADDSUB231PS: return x86::Inst::kIdVfmaddsub231ps;
    case X86_INS_VFMSUBADD132PD: return x86::Inst::kIdVfmsubadd132pd;
    case X86_INS_VFMSUBADD132PS: return x86::Inst::kIdVfmsubadd132ps;
    case X86_INS_VFMSUBADD213PD: return x86::Inst::kIdVfmsubadd213pd;
    case X86_INS_VFMSUBADD213PS: return x86::Inst::kIdVfmsubadd213ps;
    case X86_INS_VFMSUBADD231PD: return x86::Inst::kIdVfmsubadd231pd;
    case X86_INS_VFMSUBADD231PS: return x86::Inst::kIdVfmsubadd231ps;
    case X86_INS_VFMSUB132PD: return x86::Inst::kIdVfmsub132pd;
    case X86_INS_VFMSUB132PS: return x86::Inst::kIdVfmsub132ps;
    case X86_INS_VFMSUB132SD: return x86::Inst::kIdVfmsub132sd;
    case X86_INS_VFMSUB132SS: return x86::Inst::kIdVfmsub132ss;
    case X86_INS_VFMSUB213PD: return x86::Inst::kIdVfmsub213pd;
    case X86_INS_VFMSUB213PS: return x86::Inst::kIdVfmsub213ps;
    case X86_INS_VFMSUB213SD: return x86::Inst::kIdVfmsub213sd;
    case X86_INS_VFMSUB213SS: return x86::Inst::kIdVfmsub213ss;
    case X86_INS_VFMSUB231PD: return x86::Inst::kIdVfmsub231pd;
    case X86_INS_VFMSUB231PS: return x86::Inst::kIdVfmsub231ps;
    case X86_INS_VFMSUB231SD: return x86::Inst::kIdVfmsub231sd;
    case X86_INS_VFMSUB231SS: return x86::Inst::kIdVfmsub231ss;
    case X86_INS_VFNMADD132PD: return x86::Inst::kIdVfnmadd132pd;
    case X86_INS_VFNMADD132PS: return x86::Inst::kIdVfnmadd132ps;
    case X86_INS_VFNMADD132SD: return x86::Inst::kIdVfnmadd132sd;
    case X86_INS_VFNMADD132SS: return x86::Inst::kIdVfnmadd132ss;
    case X86_INS_VFNMADD213PD: return x86::Inst::kIdVfnmadd213pd;
    case X86_INS_VFNMADD213PS: return x86::Inst::kIdVfnmadd213ps;
    case X86_INS_VFNMADD213SD: return x86::Inst::kIdVfnmadd213sd;
    case X86_INS_VFNMADD213SS: return x86::Inst::kIdVfnmadd213ss;
    case X86_INS_VFNMADD231PD: return x86::Inst::kIdVfnmadd231pd;
    case X86_INS_VFNMADD231PS: return x86::Inst::kIdVfnmadd231ps;
    case X86_INS_VFNMADD231SD: return x86::Inst::kIdVfnmadd231sd;
    case X86_INS_VFNMADD231SS: return x86::Inst::kIdVfnmadd231ss;
    case X86_INS_VFNMSUB132PD: return x86::Inst::kIdVfnmsub132pd;
    case X86_INS_VFNMSUB132PS: return x86::Inst::kIdVfnmsub132ps;
    case X86_INS_VFNMSUB132SD: return x86::Inst::kIdVfnmsub132sd;
    case X86_INS_VFNMSUB132SS: return x86::Inst::kIdVfnmsub132ss;
    case X86_INS_VFNMSUB213PD: return x86::Inst::kIdVfnmsub213pd;
    case X86_INS_VFNMSUB213PS: return x86::Inst::kIdVfnmsub213ps;
    case X86_INS_VFNMSUB213SD: return x86::Inst::kIdVfnmsub213sd;
    case X86_INS_VFNMSUB213SS: return x86::Inst::kIdVfnmsub213ss;
    case X86_INS_VFNMSUB231PD: return x86::Inst::kIdVfnmsub231pd;
    case X86_INS_VFNMSUB231PS: return x86::Inst::kIdVfnmsub231ps;
    case X86_INS_VFNMSUB231SD: return x86::Inst::kIdVfnmsub231sd;
    case X86_INS_VFNMSUB231SS: return x86::Inst::kIdVfnmsub231ss;
    

    default:
        return x86::Inst::kIdNone;

    }
}


bool converter::IsJcc(const x86::Inst::Id id)
{
    switch (id)
    {
    case x86::Inst::kIdJz: 
    case x86::Inst::kIdJnz: 
    case x86::Inst::kIdJa:  
    case x86::Inst::kIdJb:  
    case x86::Inst::kIdJg:  
    case x86::Inst::kIdJl:  
    case x86::Inst::kIdJne:  
    case x86::Inst::kIdJmp:  return true;
        // add others as needed

    default:
        return false;
    }
}

x86::Gp converter::GetRandomRegister64()
{
    using namespace asmjit::x86;

    static constexpr Gp regs[] = { rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11 };

    const size_t idx = GenRandom<i8>() % std::size(regs);

    return regs[idx];
}

