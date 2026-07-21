#include "fuzzer.h"
#include "trees.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run_bst_fuzz(FuzzerState* fuzzer, int ops)
{
    bstNode* root = NULL;
    for (int i = 0; i < ops; i++)
    {
        int val = fuzzer_rand_int(fuzzer, 1, 1000);
        int op = fuzzer_rand_int(fuzzer, 0, 2);
        if (op == 0)
        {
            fuzzer_log_op(fuzzer, "BST insert %d", val);
            bst_insert(&root, val);
        }
        else if (op == 1)
        {
            fuzzer_log_op(fuzzer, "BST delete %d", val);
            root = bst_delete(root, val);
        }
        else
        {
            fuzzer_log_op(fuzzer, "BST height check");
            tree_height(root);
        }
    }
    destroy_bst(root);
}

void run_avl_fuzz(FuzzerState* fuzzer, int ops)
{
    avlNode* root = NULL;
    for (int i = 0; i < ops; i++)
    {
        int val = fuzzer_rand_int(fuzzer, 1, 1000);
        int op = fuzzer_rand_int(fuzzer, 0, 2);
        if (op == 0)
        {
            fuzzer_log_op(fuzzer, "AVL insert %d", val);
            avl_insert(&root, val);
        }
        else if (op == 1)
        {
            fuzzer_log_op(fuzzer, "AVL delete %d", val);
            avl_delete(&root, val);
        }
        else
        {
            fuzzer_log_op(fuzzer, "AVL balance check");
            avl_balance_factor(root);
        }
    }
    destroy_avl(root);
}

void run_trie_fuzz(FuzzerState* fuzzer, int ops)
{
    TrieNode* root = trie_create_node();
    assert(root != NULL);

    char word[12];
    for (int i = 0; i < ops; i++)
    {
        int len = fuzzer_rand_int(fuzzer, 1, 10);
        for (int j = 0; j < len; j++)
        {
            word[j] = 'a' + fuzzer_rand_int(fuzzer, 0, 25);
        }
        word[len] = '\0';

        int op = fuzzer_rand_int(fuzzer, 0, 2);
        if (op == 0)
        {
            fuzzer_log_op(fuzzer, "Trie insert %s", word);
            trie_insert(root, word);
        }
        else if (op == 1)
        {
            fuzzer_log_op(fuzzer, "Trie search %s", word);
            trie_search(root, word);
        }
        else
        {
            fuzzer_log_op(fuzzer, "Trie delete %s", word);
            trie_delete(root, word);
        }
    }
    trie_free(root);
}

int main(void)
{
    unsigned int seed = (unsigned int)time(NULL);
    FuzzerState fuzzer;

    printf("Starting Tree Fuzzing with seed: %u\n", seed);

    // BST
    fuzzer_init(&fuzzer, seed, 5000);
    run_bst_fuzz(&fuzzer, 1000);
    fuzzer_free(&fuzzer);

    // AVL
    fuzzer_init(&fuzzer, seed, 5000);
    run_avl_fuzz(&fuzzer, 1000);
    fuzzer_free(&fuzzer);

    // Trie
    fuzzer_init(&fuzzer, seed, 5000);
    run_trie_fuzz(&fuzzer, 1000);
    fuzzer_free(&fuzzer);

    printf("Tree Fuzzing completed successfully!\n");
    return 0;
}
