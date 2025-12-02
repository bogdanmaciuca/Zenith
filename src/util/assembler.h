/*
* mov semantics (order in function names):
* - mov X `into` Y
*/
#pragma once
#include "common.h"
#include "byte_builder.h"

typedef enum {
  REG_RAX = 0,
  REG_RCX = 1,
  REG_RDX = 2,
  REG_RBX = 3,
  REG_RSP = 4,
  REG_RBP = 5,
  REG_RSI = 6,
  REG_RDI = 7
} AssemblerRegister;

typedef struct {
  ByteBuilder builder;
  ByteBuilder debug_builder; // Appends the length of each instruction before the instruction
} Assembler;

typedef enum {
  ASSEMBLER_CREATE_ERROR_SUCCESS,
  ASSEMBLER_CREATE_ERROR_BUILDER_FAIL,
} AssemeblerCreateError;

AssemeblerCreateError assembler_create(Assembler* const assembler);
void assembler_free(Assembler* const assembler);

void assembler_create_reg_u32(Assembler* const assembler);
void assembler_create_reg_i32(Assembler* const assembler);
void assembler_create_reg_u64(Assembler* const assembler);
void assembler_create_reg_i64(Assembler* const assembler);
void assembler_mov_i32_reg(Assembler* const assembler, i32 val, AssemblerRegister reg);
void assembler_mov_u32_reg(Assembler* const assembler, u32 val, AssemblerRegister reg);
void assembler_mov_i64_reg(Assembler* const assembler, i64 val, AssemblerRegister reg);
void assembler_mov_u64_reg(Assembler* const assembler, u64 val, AssemblerRegister reg);
void assembler_syscall(Assembler* const assembler);

#define assembler_mov_imm_reg(assembler, val, reg)          \
  _Generic((val),                                           \
           i32: assembler_mov_i32_reg(assembler, val, reg), \
           u32: assembler_mov_u32_reg(assembler, val, reg), \
           i64: assembler_mov_i64_reg(assembler, val, reg), \
           u64: assembler_mov_i64_reg(assembler, val, reg), \
  )

void assembler_print_code(Assembler* const assembler);
