#ifndef TREES_H
#define TREES_H

#include "memory_inspector.h"
#include <stdbool.h>
#include <stddef.h>

/*
 * TREES MODULE AGGREGATE HEADER
 *
 * This header aggregates all tree-based data structure definitions.
 * It is maintained for backward compatibility and for modules (like main.c or tui.c)
 * that need to import all trees at once.
 *
 * Individual files should prefer including their specific headers (e.g. "bst.h").
 */

#include "avl.h"
#include "bplus_tree.h"
#include "bst.h"
#include "btree.h"
#include "fenwick_tree.h"
#include "red_black_tree.h"
#include "segment_tree.h"
#include "splay_tree.h"
#include "tbt.h"
#include "trie.h"

/* Top-level demo dispatcher - called from main menu (option 8) */
void trees_demo(void);

#endif // TREES_H
