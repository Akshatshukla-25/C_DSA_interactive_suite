#ifndef FILE_EXPORTER_H
#define FILE_EXPORTER_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Recursively search for a target filename starting from `base_dir` using DFS algorithm.
 * Skips `.git`, `build`, `object_files`, `test_binaries`, and hidden directories.
 */
bool dfs_search_file(const char* base_dir, const char* target_filename, char* found_path_out);

/**
 * Copy entire contents of source file to destination file path.
 */
bool copy_file_contents(const char* src_path, const char* dest_path);

/**
 * Find `<base_filename>.c` and `<base_filename>.h` via recursive DFS from `root_dir`
 * and export both files into `dest_dir`.
 */
bool export_file_pair(const char* root_dir, const char* base_filename, const char* header_basename,
                      const char* dest_dir, char* exported_c_path, char* exported_h_path);

// Core Data Structure Exporters
bool export_sll(const char* root_dir, const char* dest_dir);
bool export_dll(const char* root_dir, const char* dest_dir);
bool export_bst(const char* root_dir, const char* dest_dir);
bool export_circular_queue(const char* root_dir, const char* dest_dir);
bool export_stack(const char* root_dir, const char* dest_dir);

// Advanced Data Structure Exporters
bool export_avl(const char* root_dir, const char* dest_dir);
bool export_heaps(const char* root_dir, const char* dest_dir);

/* ── Live State & Data Structure Exporters (TXT, CSV, JSON) ── */
bool export_generic_state(const char* ds_name, const char* format, const char* details);

/* ── Premium Unicode visual UI/UX visualizer styling helpers ── */
void draw_unicode_box_header(const char* title);
void draw_unicode_box_footer(void);

/**
 * Interactive Standalone File Exporter CLI/TUI Dashboard demo suite.
 */
void file_exporter_demo(void);

#endif /* FILE_EXPORTER_H */
