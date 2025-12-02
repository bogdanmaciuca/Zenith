#include "assembler.h"
#include "common.h"
#include "byte_builder.h"

#define ASSEMBLER__DEFAULT_CAPACITY 1024

AssemeblerCreateError assembler_create(Assembler* const assembler) {
  ByteBuilderCreateError err = byte_builder_create(
    &assembler->builder, ASSEMBLER__DEFAULT_CAPACITY);
  if (FAILED(err))
    return ASSEMBLER_CREATE_ERROR_BUILDER_FAIL;

#ifdef ZN_DEBUG
  err = byte_builder_create(
    &assembler->debug_builder, ASSEMBLER__DEFAULT_CAPACITY);
  if (FAILED(err))
    return ASSEMBLER_CREATE_ERROR_BUILDER_FAIL;
#endif // ZN_DEBUG

  return ASSEMBLER_CREATE_ERROR_SUCCESS;
}

void assembler_free(Assembler* const assembler) {
  byte_builder_free(&assembler->builder);
}

void assembler_mov_u32_reg(Assembler* const assembler, u32 val, AssemblerRegister reg) {
  u8 instr = 0xB8 + reg;
  byte_builder_append(&assembler->builder, &instr, sizeof(instr));
  byte_builder_append(&assembler->builder, &val, sizeof(val));

#ifdef ZN_DEBUG
  u8 length = sizeof(u8) + sizeof(u32);
  byte_builder_append(&assembler->debug_builder, &length, sizeof(length));
  byte_builder_append(&assembler->debug_builder, &instr, sizeof(instr));
  byte_builder_append(&assembler->debug_builder, &val, sizeof(val));
#endif // ZN_DEBUG
}

void assembler_mov_i32_reg(Assembler* const assembler, i32 val, AssemblerRegister reg) {
  u8 instr = 0xB8 + reg;
  byte_builder_append(&assembler->builder, &instr, sizeof(instr));
  byte_builder_append(&assembler->builder, &val, sizeof(val));

#ifdef ZN_DEBUG
  u8 length = sizeof(u8) + sizeof(i32);
  byte_builder_append(&assembler->debug_builder, &length, sizeof(length));
  byte_builder_append(&assembler->debug_builder, &instr, sizeof(instr));
  byte_builder_append(&assembler->debug_builder, &val, sizeof(val));
#endif // ZN_DEBUG
}

void assembler_mov_u64_reg(Assembler* const assembler, u64 val, AssemblerRegister reg) {
  u8 prefix = 0x48;
  u8 instr = 0xB8 + reg;
  byte_builder_append(&assembler->builder, &prefix, sizeof(prefix));
  byte_builder_append(&assembler->builder, &instr, sizeof(instr));
  byte_builder_append(&assembler->builder, &val, sizeof(val));

#ifdef ZN_DEBUG
  u8 length = sizeof(u8) + sizeof(u8) + sizeof(u64);
  byte_builder_append(&assembler->debug_builder, &length, sizeof(length));
  byte_builder_append(&assembler->debug_builder, &prefix, sizeof(prefix));
  byte_builder_append(&assembler->debug_builder, &instr, sizeof(instr));
  byte_builder_append(&assembler->debug_builder, &val, sizeof(val));
#endif // ZN_DEBUG
}

void assembler_syscall(Assembler* const assembler) {
  byte_builder_append_cstring(&assembler->builder, "\x0F\x05");
#ifdef ZN_DEBUG
  u8 length = 2;
  byte_builder_append(&assembler->debug_builder, &length, sizeof(length));
  byte_builder_append_cstring(&assembler->debug_builder, "\x0F\x05");
#endif // ZN_DEBUG
}

void assembler_print_code(Assembler* const assembler) {
  usize offset = 0;
  for (usize i = 0; i < assembler->debug_builder.size; i++) {
    u8 instr_len = ((u8*)assembler->debug_builder.ptr)[i];
    printf("%*zu: ", 5, offset);
    usize start = i;
    for (u8 j = 1; j <= instr_len; j++, i++) {
      printf("%*x ", 3, ((u8*)assembler->debug_builder.ptr)[start + j]);
    }
    printf("\n");
    offset += instr_len;
  }
}
