#include "dll.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void* a, const void* b)
{
    return *(const int*)a - *(const int*)b;
}

/* Helper: build list */
static doubly_ll_Node* build_list(int arr[], int n)
{
    doubly_ll_Node* head = NULL;
    for (int i = 0; i < n; i++)
    {
        int* val = malloc(sizeof(int));
        assert(val != NULL);
        *val = arr[i];
        assert(dll_insertAtEnd(&head, val) == 1);
    }
    return head;
}

/* Helper: list -> array */
static int list_to_array(doubly_ll_Node* head, int arr[], int max)
{
    int i = 0;
    while (head != NULL && i < max)
    {
        arr[i++] = *(int*)(head->data);
        head = head->next;
    }
    return i;
}

/* Insert tests */
void test_insert()
{
    doubly_ll_Node* head = NULL;

    int* val10 = malloc(sizeof(int));
    *val10 = 10;
    assert(dll_insertAtBeginning(&head, val10) == 1);
    assert(*(int*)(head->data) == 10);

    int* val5 = malloc(sizeof(int));
    *val5 = 5;
    assert(dll_insertAtBeginning(&head, val5) == 1);
    assert(*(int*)(head->data) == 5);

    int* val20 = malloc(sizeof(int));
    *val20 = 20;
    assert(dll_insertAtEnd(&head, val20) == 1);

    int out[3];
    int n = list_to_array(head, out, 3);

    assert(n == 3);
    assert(out[0] == 5 && out[1] == 10 && out[2] == 20);

    delete_dll(head, free);

    printf("DLL insert tests passed\n");
}

/* Delete at beginning */
void test_delete_begin()
{
    int arr[] = {1, 2, 3};
    doubly_ll_Node* head = build_list(arr, 3);

    assert(dll_deleteAtBeginning(&head, free) == 1);

    int out[3];
    int n = list_to_array(head, out, 3);

    assert(n == 2);
    assert(out[0] == 2 && out[1] == 3);

    delete_dll(head, free);

    printf("DLL delete beginning tests passed\n");
}

/* Delete at end */
void test_delete_end()
{
    int arr[] = {1, 2, 3};
    doubly_ll_Node* head = build_list(arr, 3);

    assert(dll_deleteAtEnd(&head, free) == 1);

    int out[3];
    int n = list_to_array(head, out, 3);

    assert(n == 2);
    assert(out[0] == 1 && out[1] == 2);

    delete_dll(head, free);

    printf("DLL delete end tests passed\n");
}

/* Delete by value */
void test_delete_by_value()
{
    int arr[] = {1, 2, 3, 4};
    doubly_ll_Node* head = build_list(arr, 4);

    int key = 4;
    assert(dll_deleteByValue(&head, &key, compare_ints, free) == 1);

    int out[4];
    int n = list_to_array(head, out, 4);

    assert(n == 3);
    assert(out[0] == 1 && out[1] == 2 && out[2] == 3);

    delete_dll(head, free);

    printf("DLL delete by value tests passed\n");
}

/* Search test */
void test_search()
{
    int arr[] = {5, 10, 15};
    doubly_ll_Node* head = build_list(arr, 3);

    int key5 = 5;
    int key15 = 15;
    int key99 = 99;

    assert(dll_search(head, &key5, compare_ints) == 0);
    assert(dll_search(head, &key15, compare_ints) == 2);
    assert(dll_search(head, &key99, compare_ints) == -1);

    delete_dll(head, free);

    printf("DLL search tests passed\n");
}

/* Reverse test */
void test_reverse()
{
    int arr[] = {1, 2, 5};
    doubly_ll_Node* head = build_list(arr, 3);

    dll_reverselist(&head);

    int out[3];
    int n = list_to_array(head, out, 3);

    assert(n == 3);
    assert(out[0] == 5 && out[1] == 2 && out[2] == 1);

    delete_dll(head, free);

    printf("DLL reverse tests passed\n");
}

/* Test insert at position */
void test_insert_at_position()
{
    doubly_ll_Node* head = NULL;

    /* Insert at position 0 in empty list */
    int* val10 = malloc(sizeof(int));
    *val10 = 10;
    assert(dll_insertAtPosition(&head, val10, 0) == 1);
    assert(*(int*)(head->data) == 10);

    /* Insert at position 1 (end) */
    int* val20 = malloc(sizeof(int));
    *val20 = 20;
    assert(dll_insertAtPosition(&head, val20, 1) == 1);
    assert(*(int*)(head->next->data) == 20);
    assert(*(int*)(head->next->prev->data) == 10);

    /* Insert at position 1 (middle) */
    int* val15 = malloc(sizeof(int));
    *val15 = 15;
    assert(dll_insertAtPosition(&head, val15, 1) == 1);

    int out[3];
    int n = list_to_array(head, out, 3);
    assert(n == 3);
    assert(out[0] == 10 && out[1] == 15 && out[2] == 20);

    /* Test invalid position */
    int* val99 = malloc(sizeof(int));
    *val99 = 99;
    assert(dll_insertAtPosition(&head, val99, 10) == -2);
    assert(dll_insertAtPosition(&head, val99, -1) == -2);
    free(val99);

    delete_dll(head, free);
    printf("DLL insert at position tests passed\n");
}

/* Test delete at position */
void test_delete_at_position()
{
    int arr[] = {1, 2, 3, 4};
    doubly_ll_Node* head = build_list(arr, 4);

    /* Delete at position 0 */
    assert(dll_deleteAtPosition(&head, 0, free) == 1);

    int out[3];
    int n = list_to_array(head, out, 3);
    assert(n == 3);
    assert(out[0] == 2 && out[1] == 3 && out[2] == 4);

    /* Delete at position 1 (middle) */
    assert(dll_deleteAtPosition(&head, 1, free) == 1);

    n = list_to_array(head, out, 3);
    assert(n == 2);
    assert(out[0] == 2 && out[1] == 4);

    /* Test invalid position */
    assert(dll_deleteAtPosition(&head, 10, free) == -2);
    assert(dll_deleteAtPosition(&head, -1, free) == -2);

    delete_dll(head, free);
    printf("DLL delete at position tests passed\n");
}

/* Edge cases */
void test_edge_cases()
{
    doubly_ll_Node* head = NULL;

    assert(dll_deleteAtBeginning(&head, free) == -1);
    assert(dll_deleteAtEnd(&head, free) == -1);

    int* val42 = malloc(sizeof(int));
    *val42 = 42;
    assert(dll_insertAtEnd(&head, val42) == 1);

    dll_reverselist(&head); // single node

    delete_dll(head, free);

    printf("DLL edge case tests passed\n");
}

int main()
{
    test_insert();
    test_delete_begin();
    test_delete_end();
    test_delete_by_value();
    test_search();
    test_reverse();
    test_insert_at_position();
    test_delete_at_position();
    test_edge_cases();

    printf("All DLL tests passed\n");

    return 0;
}