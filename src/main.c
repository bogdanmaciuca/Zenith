// TODO:
// - debug data dump of the assembly code
// - moving immediates
// - recreating the test program with the assembly
// - add underscore between module name and typename

#include "util/common.h"
#include "util/assembler.h"
#include "util/elf.h"
#include "util/debug.h"

int main() {
  void* elf;
  usize elf_size;

  char data[] = {
    0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0xa, // Hello!\n
  };

  char text[] = {
    0xb8,                                    // mov rax (32bit)
    1, 0, 0, 0,                              // write syscall 1
    0xbf,                                    // mov rdi (32 bit)
    1, 0, 0, 0,                              // stdout
    0x48, 0xbe,                              // mov rsi, 64 bit pointer
    0xb0, 0x10, 0x40, 0, 0, 0, 0, 0,         // Hello strings address in virtual memory
    0xba,                                    // mov rdx (32bit)
    7, 0, 0, 0,                              // number of bytes in Hello!\n
    0xf, 0x5,                                // syscall
    0xb8,                                    // mov rax (32 bit)
    0x3c, 0, 0, 0,                           // 60 = exit syscall
    0x48, 0x31, 0xff,                        // xor rdi, rdi
    0xf, 0x5                                 // syscall
  };

  Assembler assembler;
  ASSERT(
    SUCCEEDED(assembler_create(&assembler)),
    "Could not initialize asasembler!"
  );
  assembler_mov_u32_reg(&assembler, 1, REG_RAX);        // syscall write
  assembler_mov_u32_reg(&assembler, 1, REG_RDI);        // stdout
  assembler_mov_u64_reg(&assembler, 0x4010b0, REG_RSI); // address of "Hello!\n"
  assembler_mov_u32_reg(&assembler, 7, REG_RDX);        // size of "Hello!\n"
  assembler_syscall(&assembler);                        // write(stdout, addr, size);
  assembler_mov_u32_reg(&assembler, 0x3c, REG_RAX);     // syscall exit
  assembler_mov_u32_reg(&assembler, 0, REG_RDI);        // exit with 0
  assembler_syscall(&assembler);                        // exit(0);

  //assembler_print_code(&assembler);
  //exit(0);

  //ElfData elf_data = {
  //  .type = ELF_EXECUTABLE,
  //  .text = &text, .text_size = sizeof(text),
  //  .data = &data, .data_size = sizeof(data)
  //};

  ElfData elf_data = {
    .type = ELF_EXECUTABLE,
    .text = assembler.builder.ptr, .text_size = assembler.builder.size,
    .data = &data, .data_size = sizeof(data)
  };

  elf_create(&elf, &elf_size, &elf_data);

  ASSERT(
    SUCCEEDED(io_write_binary("../test_elf", elf, elf_size)),
    "Could not write ELF to file!"
  );

  elf_free(elf);
  return 0;
}

