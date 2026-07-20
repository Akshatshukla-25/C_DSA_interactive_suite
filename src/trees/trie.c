#include "safe_input.h"
#include "trees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode* trie_create_node(void)
{
    TrieNode* node = malloc(sizeof(TrieNode));
    if (node == NULL)
        return NULL;
    memset(node, 0, sizeof(TrieNode));
    return node;
}

bool trie_insert(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL)
        return false;
    TrieNode* curr = root;

    TrieNode* first_new_node = NULL;
    TrieNode* first_new_node_parent = NULL;
    int first_new_node_idx = -1;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = word[i] - 'a';
        if (idx < 0 || idx >= TRIE_ALPHA_SIZE)
        {
            if (first_new_node != NULL)
            {
                trie_free(first_new_node);
                first_new_node_parent->children[first_new_node_idx] = NULL;
            }
            return false;
        }
        if (curr->children[idx] == NULL)
        {
            TrieNode* new_node = trie_create_node();
            if (new_node == NULL)
            {
                if (first_new_node != NULL)
                {
                    trie_free(first_new_node);
                    first_new_node_parent->children[first_new_node_idx] = NULL;
                }
                return false;
            }
            curr->children[idx] = new_node;
            if (first_new_node == NULL)
            {
                first_new_node = new_node;
                first_new_node_parent = curr;
                first_new_node_idx = idx;
            }
        }
        curr = curr->children[idx];
    }
    curr->is_end = 1;
    return true;
}

int trie_search(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL)
        return 0;
    TrieNode* curr = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = word[i] - 'a';
        if (idx < 0 || idx >= TRIE_ALPHA_SIZE)
            return 0;
        if (curr->children[idx] == NULL)
            return 0;
        curr = curr->children[idx];
    }
    return curr->is_end;
}

int trie_starts_with_prefix(TrieNode* root, const char* prefix)
{
    if (root == NULL || prefix == NULL)
        return 0;
    TrieNode* curr = root;
    for (int i = 0; prefix[i] != '\0'; i++)
    {
        int idx = prefix[i] - 'a';
        if (idx < 0 || idx >= TRIE_ALPHA_SIZE)
            return 0;
        if (curr->children[idx] == NULL)
            return 0;
        curr = curr->children[idx];
    }
    return 1;
}

/* Returns 1 if the node has no children and can be freed */
static int trie_delete_helper(TrieNode* node, const char* word, int depth)
{
    if (node == NULL)
        return 0;
    if (word[depth] == '\0')
    {
        if (!node->is_end)
            return 0;
        node->is_end = 0;
        for (int i = 0; i < TRIE_ALPHA_SIZE; i++)
            if (node->children[i] != NULL)
                return 0;
        return 1;
    }
    int idx = word[depth] - 'a';
    if (idx < 0 || idx >= TRIE_ALPHA_SIZE)
        return 0;
    if (!trie_delete_helper(node->children[idx], word, depth + 1))
        return 0;
    free(node->children[idx]);
    node->children[idx] = NULL;
    if (node->is_end)
        return 0;
    for (int i = 0; i < TRIE_ALPHA_SIZE; i++)
        if (node->children[i] != NULL)
            return 0;
    return 1;
}

void trie_delete(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL)
        return;
    trie_delete_helper(root, word, 0);
}

void trie_free(TrieNode* node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < TRIE_ALPHA_SIZE; i++)
        trie_free(node->children[i]);
    free(node);
}
