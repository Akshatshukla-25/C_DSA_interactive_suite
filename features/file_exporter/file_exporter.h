#ifndef FILE_EXPORTER_H
#define FILE_EXPORTER_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Recursively search for a target filename starting from `base_dir` using DFS algorithm.
 * Skips `.git`, `build`, `object_files`, `test_binaries`, and hidden directories.
 *
 * @param base_dir Directory path to start search from (e.g. ".").
 * @param target_filename Exact name of file to find (e.g. "sll.c").
 * @param found_path_out Output buffer to store full path if found (min 512 bytes).
 * @return True if file found, false otherwise.
 */
bool dfs_search_file(const char* base_dir, const char* target_filename, char* found_path_out);

/**
 * Copy entire contents of source file to destination file path.
 * Creates parent directory if it does not exist.
 *
 * @param src_path Source file path.
 * @param dest_path Target destination file path.
 * @return True on successful copy, false on failure.
 */
bool copy_file_contents(const char* src_path, const char* dest_path);

/**
 * Find `<base_filename>.c` and `<base_filename>.h` via recursive DFS from `root_dir`
 * and export both files into `dest_dir`.
 *
 * @param root_dir Project root directory to start DFS search from.
 * @param base_filename Base file name without extension (e.g. "sll", "dll", "queue", "stack").
 * @param header_basename Base header file name without extension (e.g. "sll", "trees", "queue",
 * "stack").
 * @param dest_dir User-specified destination directory path.
 * @param exported_c_path Output buffer for exported .c file path (optional, can be NULL).
 * @param exported_h_path Output buffer for exported .h file path (optional, can be NULL).
 * @return True if both source and header files were found and exported successfully.
 */
bool export_file_pair(const char* root_dir, const char* base_filename, const char* header_basename,
                      const char* dest_dir, char* exported_c_path, char* exported_h_path);

// Core Data Structure Exporters
bool export_sll(const char* root_dir, const char* dest_dir);
bool export_dll(const char* root_dir, const char* dest_dir);
bool export_bst(const char* root_dir, const char* dest_dir);
bool export_circular_queue(const char* root_dir, const char* dest_dir);
bool export_stack(const char* root_dir, const char* dest_dir);

// Advanced Structure & Algorithm Exporters
bool export_avl(const char* root_dir, const char* dest_dir);
bool export_graph(const char* root_dir, const char* dest_dir);
bool export_hash(const char* root_dir, const char* dest_dir);
bool export_heaps(const char* root_dir, const char* dest_dir);

#endif /* FILE_EXPORTER_H */
