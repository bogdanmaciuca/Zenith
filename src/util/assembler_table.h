#pragma once

#define ASM_REG_EAX32 0xB8
#define ASM_REG_ECX32 0xB9
#define ASM_REG_EDX32 0xBA
#define ASM_REG_EBX32 0xBB

// TODO: is this the right byte order? should it be an array instead of a number or a prefix?
#define ASM_REG_RAX32 0xB848
#define ASM_REG_RCX32 0xB948
#define ASM_REG_RDX32 0xBA48
#define ASM_REG_RBX32 0xBB48

#define ASM_MOV_IMM32_REG(val, reg) // TODO

