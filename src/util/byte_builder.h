#pragma once
#include "common.h"
#include "debug.h"

typedef struct {
  void* ptr;
  usize size;
  usize capacity;
} ByteBuilder;

typedef struct {
  void* ptr;
  usize size;
} ByteData;

typedef enum {
  BYTE_BUILDER_CREATE_SUCCESS,
  BYTE_BUILDER_CREATE_ALLOC_FAIL
} ByteBuilderCreateError;

ByteBuilderCreateError byte_builder_create(ByteBuilder* builder, usize capacity);
void byte_builder_free(const ByteBuilder* const builder);

void byte_builder_append(ByteBuilder* const builder, void* data, usize size);
void byte_builder_append_cstring(ByteBuilder* const builder, const char* str);


