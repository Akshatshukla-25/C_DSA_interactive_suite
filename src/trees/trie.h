#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stddef.h>

// For Trie (Prefix Tree)
#define TRIE_ALPHA_SIZE 26

typedef struct TrieNode
{
    struct TrieNode* children[TRIE_ALPHA_SIZE];
    int is_end;
} TrieNode;

TrieNode* trie_create_node(void);
bool trie_insert(TrieNode* root, const char* word);
int trie_search(TrieNode* root, const char* word);
int trie_starts_with_prefix(TrieNode* root, const char* prefix);
void trie_delete(TrieNode* root, const char* word);
void trie_free(TrieNode* node);
void trie_demo(void);

#endif // TRIE_H
