#include "advanced_heaps.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Allocates and initializes a new Fibonacci Heap node */
FibonacciNode* create_fibonacci_node(int key, int value)
{
    FibonacciNode* node = (FibonacciNode*)malloc(sizeof(FibonacciNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;  /* Point to itself to form a circular list */
    node->right = node; /* Point to itself to form a circular list */
    return node;
}

/* Helper to insert node x into a circular doubly linked list containing node min */
static void list_insert(FibonacciNode* min, FibonacciNode* x)
{
    x->left = min;
    x->right = min->right;
    min->right->left = x;
    min->right = x;
}

/* Helper to remove node x from a circular doubly linked list */
static void list_remove(FibonacciNode* x)
{
    x->left->right = x->right;
    x->right->left = x->left;
}

/* Inserts a new key-value pair into the Fibonacci Heap */
FibonacciNode* fib_heap_insert(FibonacciNode* min_node, int key, int value)
{
    FibonacciNode* node = create_fibonacci_node(key, value);
    if (node == NULL)
    {
        return min_node;
    }

    if (min_node == NULL)
    {
        return node;
    }

    list_insert(min_node, node);
    if (node->key < min_node->key)
    {
        min_node = node;
    }
    return min_node;
}

/* Combines two Fibonacci Heaps by merging their root lists */
FibonacciNode* fib_heap_union(FibonacciNode* min1, FibonacciNode* min2)
{
    if (min1 == NULL)
        return min2;
    if (min2 == NULL)
        return min1;

    /* Merge circular list of min2 into min1 */
    FibonacciNode* min1_next = min1->right;
    FibonacciNode* min2_prev = min2->left;

    min1->right = min2;
    min2->left = min1;
    min1_next->left = min2_prev;
    min2_prev->right = min1_next;

    /* Return the node with the smaller key */
    if (min1->key < min2->key)
    {
        return min1;
    }
    else
    {
        return min2;
    }
}

/* Links node y as a child of node x */
static void fib_heap_link(FibonacciNode* y, FibonacciNode* x)
{
    /* Remove y from the root list */
    list_remove(y);

    /* Make y a child of x */
    y->parent = x;
    if (x->child == NULL)
    {
        x->child = y;
        y->left = y;
        y->right = y;
    }
    else
    {
        list_insert(x->child, y);
    }
    x->degree++;
    y->mark = false;
}

/* Consolidates the root list by combining trees of equal degree */
static FibonacciNode* fib_heap_consolidate(FibonacciNode* min_node)
{
    if (min_node == NULL)
    {
        return NULL;
    }

    /* Max degree for any node in Fibonacci heap of size n is bounded by O(log n) */
    /* An array of size 64 is more than enough for up to 2^60 elements */
    FibonacciNode* arr[64];
    for (int i = 0; i < 64; i++)
    {
        arr[i] = NULL;
    }

    /* Count number of roots in the list to avoid infinite loops during updates */
    int num_roots = 0;
    FibonacciNode* x = min_node;
    if (x != NULL)
    {
        do
        {
            num_roots++;
            x = x->right;
        } while (x != min_node);
    }

    /* Allocate roots array to iterate safely */
    FibonacciNode** roots = (FibonacciNode**)malloc(num_roots * sizeof(FibonacciNode*));
    x = min_node;
    for (int i = 0; i < num_roots; i++)
    {
        roots[i] = x;
        x = x->right;
    }

    for (int i = 0; i < num_roots; i++)
    {
        x = roots[i];
        int d = x->degree;
        while (arr[d] != NULL)
        {
            FibonacciNode* y = arr[d];
            if (x->key > y->key)
            {
                /* Swap x and y */
                FibonacciNode* temp = x;
                x = y;
                y = temp;
            }
            fib_heap_link(y, x);
            arr[d] = NULL;
            d++;
        }
        arr[d] = x;
    }

    free(roots);

    /* Reconstruct the root list from the array of consolidated trees */
    FibonacciNode* new_min = NULL;
    for (int i = 0; i < 64; i++)
    {
        if (arr[i] != NULL)
        {
            arr[i]->left = arr[i];
            arr[i]->right = arr[i];
            if (new_min == NULL)
            {
                new_min = arr[i];
            }
            else
            {
                list_insert(new_min, arr[i]);
                if (arr[i]->key < new_min->key)
                {
                    new_min = arr[i];
                }
            }
        }
    }

    return new_min;
}

/* Extracts the minimum element and consolidates the heap */
FibonacciNode* fib_heap_extract_min(FibonacciNode* min_node, int* min_key, int* min_val)
{
    FibonacciNode* z = min_node;
    if (z == NULL)
    {
        return NULL;
    }

    if (min_key)
        *min_key = z->key;
    if (min_val)
        *min_val = z->value;

    /* Add all children of z to the root list of the heap */
    if (z->child != NULL)
    {
        FibonacciNode* child = z->child;
        FibonacciNode* curr = child;
        /* First, count children */
        int count = 0;
        do
        {
            count++;
            curr = curr->right;
        } while (curr != child);

        /* Collect children pointers to update parent references safely */
        FibonacciNode** children_arr = (FibonacciNode**)malloc(count * sizeof(FibonacciNode*));
        curr = child;
        for (int i = 0; i < count; i++)
        {
            children_arr[i] = curr;
            curr = curr->right;
        }

        for (int i = 0; i < count; i++)
        {
            FibonacciNode* c = children_arr[i];
            list_insert(z, c);
            c->parent = NULL;
        }
        free(children_arr);
    }

    /* Remove z from the root list */
    if (z->right == z)
    {
        /* z was the only node in the root list */
        free(z);
        return NULL;
    }

    FibonacciNode* next_min = z->right;
    list_remove(z);
    free(z);

    /* Consolidate the root list */
    return fib_heap_consolidate(next_min);
}

/* Recursively frees a tree in the Fibonacci Heap */
static void free_fib_tree(FibonacciNode* node)
{
    if (node == NULL)
    {
        return;
    }

    /* We need to free all nodes in the children circular list */
    if (node->child != NULL)
    {
        FibonacciNode* curr = node->child;
        FibonacciNode* start = node->child;
        int count = 0;
        do
        {
            count++;
            curr = curr->right;
        } while (curr != start);

        FibonacciNode** children = (FibonacciNode**)malloc(count * sizeof(FibonacciNode*));
        curr = start;
        for (int i = 0; i < count; i++)
        {
            children[i] = curr;
            curr = curr->right;
        }

        for (int i = 0; i < count; i++)
        {
            free_fib_tree(children[i]);
        }
        free(children);
    }
    free(node);
}

/* Destroys the entire Fibonacci Heap */
void destroy_fibonacci_heap(FibonacciNode* min_node)
{
    if (min_node == NULL)
    {
        return;
    }

    /* Count roots in root list */
    FibonacciNode* curr = min_node;
    int count = 0;
    do
    {
        count++;
        curr = curr->right;
    } while (curr != min_node);

    FibonacciNode** roots = (FibonacciNode**)malloc(count * sizeof(FibonacciNode*));
    curr = min_node;
    for (int i = 0; i < count; i++)
    {
        roots[i] = curr;
        curr = curr->right;
    }

    for (int i = 0; i < count; i++)
    {
        free_fib_tree(roots[i]);
    }
    free(roots);
}
