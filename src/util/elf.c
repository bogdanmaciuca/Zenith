// TODO:
// clean up
// find out why we need the headers in entry point
#include "elf.h"
#include "pch.h"
#include "common.h"
#include "debug.h"

#define ELF__SEGMENT_NUM 2
#define ELF__SECTION_NUM 0

#define ELF__EHDR_SIZE sizeof(Elf64_Ehdr)
#define ELF__PHDR_SIZE sizeof(Elf64_Phdr)
#define ELF__SHDR_SIZE sizeof(Elf64_Shdr)

u16 elf__get_type(ElfType type);

typedef struct {
  void* elf;
  usize size;
  usize text_size;
  usize data_size;
} ElfBuilder;

void        elf_builder__create(ElfBuilder* builder, const ElfData* const elf_data);
void        elf_builder__free(ElfBuilder* builder);
Elf64_Ehdr* elf_builder__ehdr(const ElfBuilder* const builder);
Elf64_Phdr* elf_builder__phdr(const ElfBuilder* const builder);
void*       elf_builder__text(const ElfBuilder* const builder);
void*       elf_builder__data(const ElfBuilder* const builder);
Elf64_Shdr* elf_builder__shdr(const ElfBuilder* const builder);
usize       elf_builder__phdr_offset(const ElfBuilder* const builder);
usize       elf_builder__text_offset(const ElfBuilder* const builder);
usize       elf_builder__data_offset(const ElfBuilder* const builder);
usize       elf_builder__shdr_offset(const ElfBuilder* const builder);

ElfCreateError elf_create(void** elf, usize* const elf_size, const ElfData* const elf_data) {
  ElfBuilder builder;
  elf_builder__create(&builder, elf_data);

  // ELF header
  Elf64_Ehdr* ehdr = elf_builder__ehdr(&builder);
  ehdr->e_ident[EI_MAG0]    = ELFMAG0;
  ehdr->e_ident[EI_MAG1]    = ELFMAG1;
  ehdr->e_ident[EI_MAG2]    = ELFMAG2;
  ehdr->e_ident[EI_MAG3]    = ELFMAG3;
  ehdr->e_ident[EI_CLASS]   = ELFCLASS64;
  ehdr->e_ident[EI_DATA]    = ELFDATA2LSB;
  ehdr->e_ident[EI_VERSION] = EV_CURRENT;
  ehdr->e_ident[EI_OSABI]   = ELFOSABI_LINUX;
  ehdr->e_type      = elf__get_type(elf_data->type);                 // Binary type
  ehdr->e_machine   = EM_X86_64;                                     // Architecture
  ehdr->e_version   = EV_CURRENT;                                    // File version
  ehdr->e_entry     = 0x400000 + elf_builder__text_offset(&builder); // Virtual adress to which the system transfers control
  ehdr->e_phoff     = elf_builder__phdr_offset(&builder);            // Program header table offset
  ehdr->e_shoff     = elf_builder__shdr_offset(&builder);            // Section header table offset
  ehdr->e_flags     = 0;                                             // Processor specific flags
  ehdr->e_ehsize    = ELF__EHDR_SIZE;                                // ELF header size
  ehdr->e_phentsize = ELF__PHDR_SIZE;                                // Program header size
  ehdr->e_phnum     = ELF__SEGMENT_NUM;                              // Number of program headers
  ehdr->e_shentsize = sizeof(Elf64_Shdr);                            // Section header entry size
  ehdr->e_shnum     = ELF__SECTION_NUM;                              // Number of entries in the section header table
  ehdr->e_shstrndx  = SHN_UNDEF;                                     // Section header table index of the section name string table

  Elf64_Phdr* phdr_text = &elf_builder__phdr(&builder)[0];
  phdr_text->p_type   = PT_LOAD;
  phdr_text->p_offset = 0;
  phdr_text->p_vaddr  = 0x400000;
  phdr_text->p_paddr  = 0x400000;
  phdr_text->p_filesz = elf_builder__text_offset(&builder) + builder.text_size;
  phdr_text->p_memsz  = elf_builder__text_offset(&builder) + builder.text_size;
  phdr_text->p_flags  = PF_R | PF_X;
  phdr_text->p_align  = 0x1000;

  // Data segment header
  Elf64_Phdr* phdr_data = &elf_builder__phdr(&builder)[1];
  phdr_data->p_type   = PT_LOAD;
  phdr_data->p_offset = elf_builder__data_offset(&builder);
  phdr_data->p_vaddr  = 0x400000 + elf_builder__data_offset(&builder);
  phdr_data->p_paddr  = 0x400000 + elf_builder__data_offset(&builder);
  phdr_data->p_filesz = builder.data_size;
  phdr_data->p_memsz  = builder.data_size;
  phdr_data->p_flags  = PF_R | PF_W;
  phdr_data->p_align  = 0x1000;

  memcpy(builder.elf + elf_builder__text_offset(&builder), elf_data->text, elf_data->text_size);
  memcpy(builder.elf + elf_builder__data_offset(&builder), elf_data->data, elf_data->data_size);

  // Text segment header
  *elf      = builder.elf;
  *elf_size = builder.size;

  return ELF_CREATE_SUCCESS;
}

void elf_free(void* elf) {
  free(elf);
}

u16 elf__get_type(ElfType type) {
  switch (type) {
    case ELF_EXECUTABLE: return ET_EXEC;
    case ELF_SHARED: return ET_DYN;
    case ELF_RELOCATABLE: return ET_REL;
    default: ASSERT(false, "Unreachable");
  }
}

usize elf__calculate_data_offset(usize code_size) {
  usize headers_size = sizeof(Elf64_Ehdr) + (ELF__SEGMENT_NUM * sizeof(Elf64_Phdr));
  usize text_segment_end = headers_size + code_size;

  return ALIGN_UP(text_segment_end, 0x1000);
}

void elf_builder__create(ElfBuilder* builder, const ElfData* const elf_data) {
  builder->size =
    sizeof(Elf64_Ehdr) +
    sizeof(Elf64_Phdr) * ELF__SEGMENT_NUM +
    elf_data->text_size +
    ALIGN_UP(elf_data->data_size, 0x1000) +
    sizeof(Elf64_Shdr) * ELF__SECTION_NUM;

  builder->elf = malloc(builder->size);

  builder->data_size = elf_data->data_size;
  builder->text_size = elf_data->text_size;
}

void elf_builder__free(ElfBuilder* builder) {
  free(builder->elf);
}

Elf64_Ehdr* elf_builder__ehdr(const ElfBuilder* const builder) {
  return builder->elf;
}

Elf64_Phdr* elf_builder__phdr(const ElfBuilder* const builder) {
  return builder->elf + ELF__EHDR_SIZE;
}

void* elf_builder__data(const ElfBuilder* const builder) {
  return builder->elf + ELF__EHDR_SIZE + ELF__PHDR_SIZE * ELF__SEGMENT_NUM;
}

void* elf_builder__text(const ElfBuilder* const builder) {
  return builder->elf + ELF__EHDR_SIZE + ELF__PHDR_SIZE * ELF__SEGMENT_NUM + builder->data_size;
}

Elf64_Shdr* elf_builder__shdr(const ElfBuilder* const builder) {
  return builder->elf + ELF__EHDR_SIZE + ELF__PHDR_SIZE * ELF__SEGMENT_NUM +
  builder->data_size + builder->text_size;
}

usize elf_builder__phdr_offset(const ElfBuilder* const builder) {
  return sizeof(Elf64_Ehdr);
  ((void)builder); // Unused builder warning
}

usize elf_builder__text_offset(const ElfBuilder* const builder) {
  return ELF__EHDR_SIZE + ELF__PHDR_SIZE * ELF__SEGMENT_NUM;
  ((void)builder); // Unused builder warning
}

usize elf_builder__data_offset(const ElfBuilder* const builder) {
  usize offset = ELF__EHDR_SIZE + ELF__PHDR_SIZE * ELF__SEGMENT_NUM + builder->text_size;
  return ALIGN_UP(offset, 0x1000);
}

usize elf_builder__shdr_offset(const ElfBuilder* const builder) {
  return 0;

  return ELF__EHDR_SIZE + ELF__PHDR_SIZE * ELF__SEGMENT_NUM +
  builder->data_size + builder->text_size;
}
