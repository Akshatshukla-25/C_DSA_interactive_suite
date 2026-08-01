#ifndef MEMORY_INSPECTOR_H
#define MEMORY_INSPECTOR_H

#include <stddef.h>
#include <stdlib.h>

#define MAX_STRUCT_FIELDS 16
#define MAX_TRACKED_BLOCKS 64

typedef enum
{
    BLOCK_STATE_FREE = 0,
    BLOCK_STATE_ACTIVE = 1,
    BLOCK_STATE_LEAK = 2
} BlockState;

typedef struct AllocatedBlock
{
    void* address;
    size_t size;
    const char* label;
    BlockState state;
} AllocatedBlock;

typedef struct StructField
{
    const char* name;
    size_t offset;
    size_t size;
    size_t padding_after;
} StructField;

typedef struct StructLayout
{
    const char* struct_name;
    size_t total_size;
    size_t payload_size;
    size_t total_padding;
    size_t alignment;
    size_t field_count;
    StructField fields[MAX_STRUCT_FIELDS];
} StructLayout;

/* ── Custom Allocation Wrappers & Live Heap Map API ────────── */
void* dsa_malloc(size_t size, const char* label);
void dsa_free(void* ptr);
void* dsa_realloc(void* ptr, size_t size, const char* label);

void memory_inspector_clear_blocks(void);
int memory_inspector_get_active_block_count(void);
size_t memory_inspector_get_total_allocated_bytes(void);
void memory_inspector_draw_heap_map(void);

/**
 * Print a classic hex dump of a memory block to standard output.
 */
void print_hexdump(const void* ptr, size_t size);

/**
 * Format a hex dump of a memory block into a user-provided string buffer.
 */
size_t format_hexdump(const void* ptr, size_t size, char* out_buf, size_t buf_size);

/**
 * Print a detailed memory layout report of a structure including field offsets.
 */
void print_struct_layout_report(const StructLayout* layout, const void* instance_ptr);

/**
 * Calculate total padding bytes and internal efficiency ratio for a struct layout.
 */
void finalize_struct_layout(StructLayout* layout);

/**
 * Inspect memory layout, alignment, and raw bytes of a Singly Linked List Node (Node).
 */
void inspect_sll_node_memory(const void* node_ptr);

/**
 * Inspect memory layout, alignment, and raw bytes of a Doubly Linked List Node (doubly_ll_Node).
 */
void inspect_dll_node_memory(const void* node_ptr);

/**
 * Inspect memory layout, alignment, and raw bytes of a Binary Search Tree Node (bstNode).
 */
void inspect_bst_node_memory(const void* node_ptr);

/**
 * Interactive memory inspector and raw hexdump visualizer demo suite.
 */
void memory_inspector_demo(void);

/* Intercept memory calls in target files */
#ifndef IN_MEMORY_INSPECTOR_C
#define malloc(size) dsa_malloc((size), "Dynamic Node")
#define free(ptr) dsa_free((ptr))
#define realloc(ptr, size) dsa_realloc((ptr), (size), "Dynamic Node Realloc")
#endif

#endif /* MEMORY_INSPECTOR_H */
