#include "byte_builder.h"
#include "debug.h"

void byte_builder__ensure_capacity(ByteBuilder* const builder, usize capacity);

ByteBuilderCreateError byte_builder_create(ByteBuilder* builder, usize capacity) {
  ASSERT(capacity != 0, "Capacity must not be 0!");

  builder->ptr = malloc(capacity);
  builder->size = 0;
  builder->capacity = capacity;
  
  if (builder->ptr == 0)
    return BYTE_BUILDER_CREATE_ALLOC_FAIL;

  return BYTE_BUILDER_CREATE_SUCCESS;
}

void byte_builder_free(const ByteBuilder* const builder) {
  free(builder->ptr);
}

void byte_builder_append(ByteBuilder* const builder, void* data, usize data_size) {
  byte_builder__ensure_capacity(builder, builder->size + data_size);

  memcpy(builder->ptr + builder->size, data, data_size);
  builder->size += data_size;
}

void byte_builder_append_cstring(ByteBuilder* const builder, const char* str) {
  usize data_size = strlen(str);
  byte_builder__ensure_capacity(builder, builder->size + data_size);

  memcpy(builder->ptr + builder->size, str, data_size);
  builder->size += data_size;
}

void byte_builder__ensure_capacity(ByteBuilder* const builder, usize capacity) {
  if (builder->capacity > capacity) {
    usize new_capacity = capacity * 2;
    builder->ptr = realloc(builder->ptr, new_capacity);
    builder->capacity = new_capacity;
  }
}

