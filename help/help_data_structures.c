#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_data_structures_menu(void)
{
    display_header("Help - Data Structures");

    printf("--- SINGLY LINKED LIST (SLL) ---\n\n");
    printf("CONCEPT:\n");
    printf("    A Singly Linked List is a linear data structure where each element (node)\n");
    printf("    contains a data field and a pointer (next) to the next node in line.\n\n");
    printf("OPERATIONS:\n");
    printf("    • Insert (Beginning, Middle, End)\n");
    printf("    • Delete (Beginning, Middle, End)\n");
    printf("    • Search & Traverse\n\n");

    printf("--- DOUBLY LINKED LIST (DLL) ---\n\n");
    printf("CONCEPT:\n");
    printf("    A Doubly Linked List node has three parts: a next pointer, a prev pointer,\n");
    printf("    and a data pointer referencing the element itself. This structure allows\n");
    printf("    for seamless bi-directional traversal (forward and backward).\n\n");
    printf("HOW WE ACHIEVE GENERIC DESIGN (Storing any type of data):\n");
    printf("    In standard C, structures usually hold a specific type of data (like 'int').\n");
    printf("    To make this DLL capable of holding anything (integers, strings, custom\n"
           "    structs), we use:\n\n");
    printf("    1. Void Pointers (void* data):\n");
    printf("       A void pointer is a generic pointer. It acts as an envelope that can store\n");
    printf("       the memory address of any variable type.\n\n");
    printf("    2. Callback Functions:\n");
    printf("       Since the list doesn't know what data it is holding, the programmer must\n");
    printf("       pass small helper functions (callbacks) to describe how to perform\n"
           "       operations:\n");
    printf("       • Printer Callback: Tells the list how to print the items on screen.\n");
    printf("       • Compare Callback: Tells the list how to check if two items are equal\n");
    printf("         when searching or deleting nodes.\n");
    printf("       • Destructor Callback: Tells the list how to free the item's memory\n");
    printf("         so we don't cause memory leaks.\n\n");
    printf("OPERATIONS:\n");
    printf("    • Insertion & Deletion at arbitrary positions\n");
    printf("    • Reverse Traversal\n\n");

    printf("--- CIRCULAR LINKED LISTS ---\n\n");
    printf("CONCEPT:\n");
    printf("    In Circular Linked Lists, the last node links back to the first node\n");
    printf("    instead of pointing to NULL.\n");
    printf("    • Singly Circular (SCLL): Single link pointing forward, looping last to first.\n");
    printf("    • Doubly Circular (DCLL): Predecessor and successor links form a full\n"
           "      circular loop.\n\n");
    printf("HOW WE ACHIEVE GENERIC DESIGN (Storing any type of data):\n");
    printf("    Both our SCLL and DCLL implementations are fully generic using void pointers\n"
           "    (void* data). This allows the circular lists to hold integers, strings, or\n"
           "    custom structures.\n");
    printf("    Just like the DLL, you pass helper callbacks for printing, searching, and\n"
           "    freeing memory.\n\n");

    printf("--- STACKS & QUEUES ---\n\n");
    printf("STACK (LIFO - Last In First Out):\n");
    printf("    Supports Push (insert) and Pop (remove) operations. Only the top is\n"
           "    accessible.\n\n");
    printf("QUEUE (FIFO - First In First Out):\n");
    printf("    Supports Enqueue (insert at rear) and Dequeue (remove from front) operations.\n\n");
    printf("CIRCULAR QUEUE:\n");
    printf("    A queue where the last position is connected back to the first\n");
    printf("    position to make a circle, resolving the linear queue \"false overflow\"\n");
    printf("    issue by wrapping indices modulo N.\n\n");
    printf("DOUBLE-ENDED QUEUE (DEQUE):\n");
    printf("    An extension of a queue that supports insertion and deletion at\n");
    printf("    both the front and rear ends.\n\n");
    printf("RELATIONSHIPS & COMPARISONS:\n");
    printf("    • Simple Queue vs. Circular Queue:\n");
    printf("      - Simple Queue suffers from false overflow where unused front space is\n"
           "        wasted.\n");
    printf("      - Circular Queue wrapping prevents false overflow, allowing continuous reuse\n"
           "        of empty slots.\n");
    printf("    • Deque vs. Stack & Queue:\n");
    printf("      - Deque acts as a double-ended generalization, enabling both LIFO (Stack)\n"
           "        and FIFO (Queue) operations on either side depending on the restricted\n"
           "        operations.\n\n");
    printf("WHEN TO USE WHAT & REAL-WORLD USE CASES:\n");
    printf("    • Use Stacks for depth-first searches, compiler parsing/syntax checks, and\n"
           "      recursion backtracking.\n");
    printf("    • Use Circular Queues for streaming buffers (e.g. audio playback), network\n"
           "      packet ring buffers, and scheduling processes.\n");
    printf("    • Use Deques for undo/redo browser history trackers, and work-stealing job\n"
           "      processor queues.\n\n");

    printf("--- ARRAYS & PRIORITY QUEUES ---\n\n");
    printf("ARRAYS:\n");
    printf("    Fixed-size sequential collections of elements. Operations include search,\n"
           "    insertion, and deletion.\n\n");
    printf("PRIORITY QUEUE:\n");
    printf("    A queue where each element has a priority. Implemented here using a Binary\n"
           "    Heap structure.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
