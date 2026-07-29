#include "bst.h"
#include "display_header.h"
#include "graph_traversals.h"
#include "safe_input.h"
#include "serialization.h"
#include "trees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void run_tree_serialization_demo(void)
{
    display_header("BST & AVL Tree Serialization");

    printf("Building sample Binary Search Tree (BST)...\n");
    bstNode* root = NULL;
    bst_insert(&root, 50);
    bst_insert(&root, 30);
    bst_insert(&root, 70);
    bst_insert(&root, 20);
    bst_insert(&root, 40);

    const char* bst_filename = "bst_serialized_demo.txt";
    printf("Serializing BST to '%s'...\n", bst_filename);
    bool bst_ok = serialize_bst_to_file(root, bst_filename);
    printf(" -> BST Serialization: %s\n", bst_ok ? "SUCCESS" : "FAILED");

    printf("\nDeserializing BST from '%s'...\n", bst_filename);
    bstNode* restored_root = deserialize_bst_from_file(bst_filename);
    printf(" -> Deserialized BST Root Value: %d\n", restored_root ? restored_root->data : -1);

    destroy_bst(root);
    destroy_bst(restored_root);
}

static void run_graph_serialization_demo(void)
{
    display_header("Graph & Weighted Graph Serialization");

    printf("Creating sample Graph (V = 4)...\n");
    Graph* g = create_graph(4);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 3);

    const char* graph_filename = "graph_serialized_demo.txt";
    printf("Serializing Graph to '%s'...\n", graph_filename);
    bool graph_ok = serialize_graph_to_file(g, graph_filename);
    printf(" -> Graph Serialization: %s\n", graph_ok ? "SUCCESS" : "FAILED");

    printf("\nDeserializing Graph from '%s'...\n", graph_filename);
    Graph* restored_g = deserialize_graph_from_file(graph_filename);
    printf(" -> Deserialized Graph Vertices: %d\n", restored_g ? restored_g->V : -1);

    free_graph(g);
    free_graph(restored_g);
}

static void inspect_serialization_files(void)
{
    display_header("Inspect Serialized File Payloads");

    const char* filenames[] = {"bst_serialized_demo.txt", "graph_serialized_demo.txt"};
    for (size_t i = 0; i < 2; i++)
    {
        printf("--- File: %s ---\n", filenames[i]);
        FILE* fp = fopen(filenames[i], "r");
        if (!fp)
        {
            printf("(File not found. Run serialization demo first.)\n\n");
            continue;
        }

        char buffer[256];
        size_t lines = 0;
        while (fgets(buffer, sizeof(buffer), fp) && lines < 10)
        {
            printf("  %s", buffer);
            lines++;
        }
        fclose(fp);
        printf("\n");
    }
}

void serialization_demo(void)
{
    while (1)
    {
        display_header("State Serialization & Deserialization Engine");
        printf("1. BST & AVL Tree Serialization / Deserialization Demo\n");
        printf("2. Graph Serialization / Deserialization Demo\n");
        printf("3. Inspect Serialized File Payloads & Integrity\n");
        printf("-1. Return to Main Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 3);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Serialization Engine...\n");
            return;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                run_tree_serialization_demo();
                break;
            case 2:
                run_graph_serialization_demo();
                break;
            case 3:
                inspect_serialization_files();
                break;
        }
    }
}
