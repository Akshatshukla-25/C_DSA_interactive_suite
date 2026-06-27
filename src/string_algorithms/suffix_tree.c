#include "../utils/config.h"
#include "clear_screen.h"
#include "history_logger.h"
#include "safe_input.h"
#include "string_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CHAR 256

typedef struct SuffixTreeNode {
    struct SuffixTreeNode* children[MAX_CHAR];
    struct SuffixTreeNode* suffixLink;
    int start;
    int end_val;
    int is_leaf;
    int suffixIndex;
} SuffixTreeNode;

static SuffixTreeNode* root = NULL;
static SuffixTreeNode* lastNewNode = NULL;
static SuffixTreeNode* activeNode = NULL;
static int activeEdge = -1;
static int activeLength = 0;
static int remainingSuffixCount = 0;
static int leafEnd = -1;

static SuffixTreeNode* new_suffix_tree_node(int start, int end_val, int is_leaf)
{
    SuffixTreeNode* node = (SuffixTreeNode*)malloc(sizeof(SuffixTreeNode));
    if (node)
    {
        for (int i = 0; i < MAX_CHAR; i++)
            node->children[i] = NULL;
        node->suffixLink = root;
        node->start = start;
        node->end_val = end_val;
        node->is_leaf = is_leaf;
        node->suffixIndex = -1;
    }
    return node;
}

static int get_node_end(SuffixTreeNode* n, int global_leaf_end)
{
    if (n->is_leaf)
        return global_leaf_end;
    return n->end_val;
}

static int edge_length(SuffixTreeNode* n, int global_leaf_end)
{
    if (n == root)
        return 0;
    return get_node_end(n, global_leaf_end) - n->start + 1;
}

static int walk_down(SuffixTreeNode* currNode, int global_leaf_end)
{
    int elen = edge_length(currNode, global_leaf_end);
    if (activeLength >= elen)
    {
        activeEdge += elen;
        activeLength -= elen;
        activeNode = currNode;
        return 1;
    }
    return 0;
}

static void extend_suffix_tree(char* text, int pos, int global_leaf_end)
{
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;

    while (remainingSuffixCount > 0)
    {
        if (activeLength == 0)
            activeEdge = pos;

        unsigned char active_char = text[activeEdge];
        if (activeNode->children[active_char] == NULL)
        {
            activeNode->children[active_char] = new_suffix_tree_node(pos, -1, 1);
            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        else
        {
            SuffixTreeNode* next = activeNode->children[active_char];
            if (walk_down(next, global_leaf_end))
                continue;

            if (text[next->start + activeLength] == text[pos])
            {
                if (lastNewNode != NULL && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
                activeLength++;
                break;
            }

            int splitEnd = next->start + activeLength - 1;
            SuffixTreeNode* split = new_suffix_tree_node(next->start, splitEnd, 0);
            activeNode->children[active_char] = split;

            split->children[(unsigned char)text[pos]] = new_suffix_tree_node(pos, -1, 1);
            next->start += activeLength;
            split->children[(unsigned char)text[next->start]] = next;

            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = split;
            }
            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

static void set_suffix_indices(SuffixTreeNode* n, int labelHeight, int global_leaf_end)
{
    if (n == NULL)
        return;

    int is_leaf = 1;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            is_leaf = 0;
            set_suffix_indices(n->children[i], labelHeight + edge_length(n->children[i], global_leaf_end), global_leaf_end);
        }
    }
    if (is_leaf)
    {
        n->suffixIndex = global_leaf_end + 1 - labelHeight;
    }
}

SuffixTreeNode* build_suffix_tree(char* text, int n)
{
    root = new_suffix_tree_node(-1, -1, 0);
    activeNode = root;
    activeEdge = -1;
    activeLength = 0;
    remainingSuffixCount = 0;
    leafEnd = -1;

    for (int i = 0; i < n; i++)
    {
        extend_suffix_tree(text, i, i);
    }

    set_suffix_indices(root, 0, n - 1);
    return root;
}

void free_suffix_tree(SuffixTreeNode* n)
{
    if (n == NULL)
        return;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
            free_suffix_tree(n->children[i]);
    }
    free(n);
}

static void traverse_and_collect_leaves(SuffixTreeNode* n, int* found)
{
    if (n == NULL)
        return;
    if (n->is_leaf)
    {
        printf("Pattern found at index %d\n", n->suffixIndex);
        (*found)++;
    }
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
            traverse_and_collect_leaves(n->children[i], found);
    }
}

void suffix_tree_search(char* text, char* pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    if (n == 0 || m == 0)
    {
        printf("Pattern not found in the text.\n");
        return;
    }

    char* text_with_sentinel = (char*)malloc((n + 2) * sizeof(char));
    if (!text_with_sentinel)
        return;
    strcpy(text_with_sentinel, text);
    text_with_sentinel[n] = '$';
    text_with_sentinel[n + 1] = '\0';
    int n_sentinel = n + 1;

    SuffixTreeNode* tree_root = build_suffix_tree(text_with_sentinel, n_sentinel);

    SuffixTreeNode* curr = tree_root;
    int idx = 0;
    int matched = 1;

    while (idx < m)
    {
        unsigned char c = pattern[idx];
        if (curr->children[c] == NULL)
        {
            matched = 0;
            break;
        }

        SuffixTreeNode* child = curr->children[c];
        int edge_len = edge_length(child, n_sentinel - 1);
        int j = 0;
        while (j < edge_len && idx < m)
        {
            if (text_with_sentinel[child->start + j] != pattern[idx])
            {
                matched = 0;
                break;
            }
            idx++;
            j++;
        }
        if (!matched)
            break;
        curr = child;
    }

    int found = 0;
    if (matched)
    {
        traverse_and_collect_leaves(curr, &found);
    }

    free_suffix_tree(tree_root);
    free(text_with_sentinel);

    if (found == 0)
    {
        printf("Pattern not found in the text.\n");
    }
    else
    {
        printf("Total occurrences found: %d\n", found);
    }
}

static void print_tree_structure(SuffixTreeNode* n, char* text, int depth, int global_leaf_end)
{
    if (n == NULL)
        return;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            SuffixTreeNode* child = n->children[i];
            for (int d = 0; d < depth; d++)
                printf("  ");
            printf("+- ");
            int end = get_node_end(child, global_leaf_end);
            for (int k = child->start; k <= end; k++)
            {
                printf("%c", text[k]);
            }
            if (child->is_leaf)
            {
                printf(" (suffix index %d)", child->suffixIndex);
            }
            printf("\n");
            print_tree_structure(child, text, depth + 1, global_leaf_end);
        }
    }
}

void suffix_tree_visualization(char* text, char* pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    if (n == 0 || m == 0)
    {
        printf("Pattern not found in the text.\n");
        return;
    }

    char* text_with_sentinel = (char*)malloc((n + 2) * sizeof(char));
    if (!text_with_sentinel)
        return;
    strcpy(text_with_sentinel, text);
    text_with_sentinel[n] = '$';
    text_with_sentinel[n + 1] = '\0';
    int n_sentinel = n + 1;

    SuffixTreeNode* tree_root = build_suffix_tree(text_with_sentinel, n_sentinel);

    if (!is_instant())
    {
        clear_screen();
    }

    printf("\nUkkonen's Suffix Tree Structure (text + sentinel '$'):\n");
    print_tree_structure(tree_root, text_with_sentinel, 0, n_sentinel - 1);
    dynamic_sleep();

    printf("\nSearching for pattern '%s'...\n", pattern);

    SuffixTreeNode* curr = tree_root;
    int idx = 0;
    int matched = 1;

    while (idx < m)
    {
        unsigned char c = pattern[idx];
        if (curr->children[c] == NULL)
        {
            matched = 0;
            printf("Character '%c' mismatch: no transition edge from state %p\n", c, (void*)curr);
            break;
        }

        SuffixTreeNode* child = curr->children[c];
        int edge_len = edge_length(child, n_sentinel - 1);
        printf("Matched transition character '%c': scanning edge labeled [", c);
        int end = get_node_end(child, n_sentinel - 1);
        for (int k = child->start; k <= end; k++)
            printf("%c", text_with_sentinel[k]);
        printf("]\n");

        int j = 0;
        while (j < edge_len && idx < m)
        {
            if (text_with_sentinel[child->start + j] != pattern[idx])
            {
                matched = 0;
                printf("Mismatch on edge: expected '%c', found '%c'\n", pattern[idx], text_with_sentinel[child->start + j]);
                break;
            }
            idx++;
            j++;
        }
        if (!matched)
            break;
        curr = child;
        dynamic_sleep();
    }

    int found = 0;
    if (matched)
    {
        printf("\nPattern matched successfully! Collecting suffix indices under subtree:\n");
        traverse_and_collect_leaves(curr, &found);
    }

    free_suffix_tree(tree_root);
    free(text_with_sentinel);

    printf("\n-----------------------------------\n");
    if (found == 0)
    {
        printf("Pattern not found in the text.\n");
    }
    else
    {
        printf("Total occurrences found: %d\n", found);
    }
}

void suffix_tree_demo(void)
{
    while (1)
    {
        char text[100];
        char pattern[100];

        printf("\nSuffix Tree Search Demo (Ukkonen's Algorithm)\n");

        int status_T =
            safe_input_string(text, "Enter text (no spaces, max 99 chars), or 'X' to exit: ");
        if (status_T == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting demo...\n");
            return;
        }

        int status_P =
            safe_input_string(pattern, "Enter pattern (no spaces, max 99 chars), or 'X' to exit: ");
        if (status_P == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting demo...\n");
            return;
        }

        clock_t start_t = clock();
        suffix_tree_visualization(text, pattern);
        clock_t end_t = clock();
        double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("Total CPU time taken: %f seconds\n", total_t);

        add_to_history("Suffix Tree Search", strlen(text), total_t);
    }
}
