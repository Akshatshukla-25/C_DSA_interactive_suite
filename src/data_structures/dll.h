#ifndef DLL_H
#define DLL_H

typedef struct doubly_ll_Node
{
    void* data;
    struct doubly_ll_Node* prev;
    struct doubly_ll_Node* next;
} doubly_ll_Node;

// Insert a value at the beginning of a doubly linked list. Returns 1 on success, -1 on allocation
// failure.
int dll_insertAtBeginning(doubly_ll_Node** head_ref, void* value);

// Insert a value at the end of a doubly linked list. Returns 1 on success, -1 on allocation
// failure.
int dll_insertAtEnd(doubly_ll_Node** head_ref, void* value);

// Print the elements of a doubly linked list.
void dll_printlist(const doubly_ll_Node* head, void (*print_element)(const void*));

// Search for a key in a doubly linked list. Returns The index of the key or -1 if not found.
int dll_search(const doubly_ll_Node* head, const void* key, int (*compare)(const void*, const void*));

// Delete the first element from a doubly linked list. Returns 1 on success, -1 if the list is
// empty.
int dll_deleteAtBeginning(doubly_ll_Node** head_ref, void (*free_data)(void*));

// Delete the last element from a doubly linked list. Returns 1 on success, -1 if the list is empty.
int dll_deleteAtEnd(doubly_ll_Node** head_ref, void (*free_data)(void*));

// Delete the first occurrence of a key from a doubly linked list. Returns 1 on success, -1 if not
// found, -2 if empty list.
int dll_deleteByValue(doubly_ll_Node** head_ref, const void* key, int (*compare)(const void*, const void*), void (*free_data)(void*));

// Free all nodes in a doubly linked list.
void delete_dll(doubly_ll_Node* head, void (*free_data)(void*));

// Run the doubly linked list demonstration module.
void dll_demo(void);

// Reverse a doubly linked list in place. Returns 1 on success, -1 on failure.
int dll_reverselist(doubly_ll_Node** head_ref);

// Get the number of nodes in a doubly linked list. Returns The number of nodes in the list.
int dll_getLength(const doubly_ll_Node* head);

// Insert a value at a specific position in a doubly linked list. Returns 1 on success, -1 on
// allocation failure, -2 on invalid position.
int dll_insertAtPosition(doubly_ll_Node** head_ref, void* value, int position);

// Delete a node at a specific position in a doubly linked list. Returns 1 on success, -1 if the
// list is empty, -2 on invalid position.
int dll_deleteAtPosition(doubly_ll_Node** head_ref, int position, void (*free_data)(void*));

#endif
