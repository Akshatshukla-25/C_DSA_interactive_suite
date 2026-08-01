#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_process_synchronization_menu(void)
{
    display_header("Help - Process Synchronization");

    printf("--- OVERVIEW & FUNDAMENTALS ---\n\n");
    printf("WHAT IS PROCESS SYNCHRONIZATION?\n");
    printf("    Process Synchronization is the mechanism of coordinating the execution\n");
    printf("    of multiple concurrent processes or threads sharing system resources\n");
    printf("    (such as global memory, variables, files, or devices) to ensure data\n");
    printf("    consistency and prevent chaotic execution order.\n\n");
    printf("WHY IT MATTERS:\n");
    printf("    In multi-threaded or multi-process systems, threads execute concurrently\n");
    printf("    and may be interrupted at any assembly instruction. Without proper\n");
    printf("    synchronization, simultaneous memory writes or interleaved reads\n");
    printf("    cause corrupted data, program crashes, and non-deterministic bugs.\n\n");
    printf("CORE CONCEPTS:\n");
    printf("    • Race Condition: A scenario where the final result of concurrent operations\n");
    printf("      depends strictly on the relative timing or order of thread execution.\n");
    printf("    • Critical Section: The code segment that accesses shared resources that\n");
    printf("      must NOT be concurrently accessed by more than one thread at a time.\n");
    printf("    • Mutual Exclusion: Guaranteeing that if Process A is executing in its\n");
    printf("      critical section, no other process can enter its critical section.\n");
    printf("    • Progress: If no process is in its critical section and some processes\n");
    printf("      wish to enter, only processes not in their remainder section can participate\n");
    printf("      in deciding who enters next (no indefinite postponement).\n");
    printf("    • Bounded Waiting: A limit on the number of times other processes can enter\n"
           "      their critical sections after a process requests entry, preventing\n"
           "      starvation.\n\n");

    printf("--- PRODUCER-CONSUMER (BOUNDED BUFFER) ---\n\n");
    printf("PROBLEM STATEMENT:\n");
    printf("    The Producer-Consumer problem models two processes sharing a fixed-size\n");
    printf("    (bounded) circular buffer. The Producer generates data items and inserts\n");
    printf("    them into the buffer. The Consumer removes items and processes them.\n");
    printf("    The system must prevent Producer from writing to a full buffer (overflow)\n");
    printf("    and Consumer from reading from an empty buffer (underflow).\n\n");
    printf("WHAT THE SIMULATION MODELS:\n");
    printf("    • Circular Buffer: Fixed array of size 5 slots.\n");
    printf("    • mutex Semaphore (Binary, Initial = 1):\n");
    printf("      Provides mutual exclusion for updating buffer indices ('in' and 'out').\n");
    printf("    • empty_sem Semaphore (Counting, Initial = 5):\n");
    printf("      Tracks the count of available empty buffer slots for the Producer.\n");
    printf("    • full_sem Semaphore (Counting, Initial = 0):\n");
    printf("      Tracks the count of filled item slots available for the Consumer.\n\n");
    printf("WHAT TO OBSERVE IN THE DEMO:\n");
    printf("    • Producer Blocking: When buffer fills (empty_sem = 0), Producer becomes\n");
    printf("      BLOCKED until Consumer consumes an item and signals empty_sem.\n");
    printf("    • Consumer Blocking: When buffer is empty (full_sem = 0), Consumer becomes\n");
    printf("      BLOCKED until Producer produces an item and signals full_sem.\n");
    printf("    • Lock Acquisition: Mutex decreases to 0 while inserting/removing items,\n");
    printf("      ensuring thread-safe index manipulation.\n\n");

    printf("--- DINING PHILOSOPHERS PROBLEM ---\n\n");
    printf("PROBLEM STATEMENT:\n");
    printf("    5 philosophers sit around a circular table. Each philosopher alternates\n");
    printf("    between THINKING, HUNGRY, and EATING. 5 chopsticks are placed on the table,\n");
    printf("    one between each pair of adjacent philosophers. A philosopher needs BOTH\n");
    printf("    left and right chopsticks to eat. The challenge is allocating limited shared\n");
    printf("    resources without causing Deadlock or Starvation.\n\n");
    printf("WHAT THE SIMULATION MODELS:\n");
    printf("    • 5 Philosophers (P0..P4) and 5 Chopsticks (C0..C4).\n");
    printf("    • 3 Solvers / Strategies:\n");
    printf("      1. Naive Strategy (Deadlock-Prone):\n");
    printf("         Every philosopher attempts to grab Left chopstick, then Right chopstick.\n");
    printf("         If all 5 grab Left simultaneously, all wait forever for Right => DEADLOCK.\n");
    printf("      2. Asymmetric Strategy (Symmetry Breaking):\n");
    printf("         Odd-numbered philosophers pick Right first, then Left.\n");
    printf("         Even-numbered philosophers pick Left first, then Right.\n");
    printf("         Breaks circular wait condition, guaranteeing deadlock-free execution.\n");
    printf("      3. Arbitrator / State-Check Strategy (Monitor Approach):\n");
    printf("         A philosopher can pick chopsticks ONLY if neither neighbor is EATING.\n");
    printf("         Prevents both Deadlock and Starvation through state inspection.\n\n");
    printf("WHAT TO OBSERVE IN THE DEMO:\n");
    printf("    • Circular Wait Deadlock: Observe Naive strategy freeze when all chopsticks\n");
    printf("      are held simultaneously.\n");
    printf("    • Resolution via Asymmetric Pickup: Observe smooth execution when chopstick\n");
    printf("      pickup order is broken.\n");
    printf("    • State Visualizer: Live ANSI layout of Table, Chopstick ownership, and Logs.\n\n");

    printf("--- PETERSON'S ALGORITHM ---\n\n");
    printf("PROBLEM STATEMENT:\n");
    printf("    Peterson's Algorithm is a classic software-based solution to the Critical\n");
    printf("    Section problem for exactly TWO processes (P0 / Process A and P1 / Process B).\n");
    printf("    It guarantees Mutual Exclusion without requiring special hardware atomic\n");
    printf("    instructions (like Test-And-Set or Compare-And-Swap).\n\n");
    printf("WHAT THE SIMULATION MODELS:\n");
    printf("    • Shared Variables:\n");
    printf("      - flag[2]: flag[i] = true indicates Process i wants to enter CS.\n");
    printf("      - turn: Specifies which process gets priority if both want to enter.\n");
    printf("    • Stepped Execution:\n");
    printf("      - Process 0 steps: l1 (Non-CS) -> l2 (readyA=true) -> l3 (turn=B) ->\n"
           "        l4 (await !readyB || turn==A) -> l5 (Critical Section) ->\n"
           "        l6 (readyA=false).\n");
    printf("      - Process 1 steps: m1 (Non-CS) -> m2 (readyB=true) -> m3 (turn=A) ->\n"
           "        m4 (await !readyA || turn==B) -> m5 (Critical Section) ->\n"
           "        m6 (readyB=false).\n\n");
    printf("WHAT TO OBSERVE IN THE DEMO:\n");
    printf("    • Mutual Exclusion: P0 and P1 can NEVER be in CS (l5 and m5) simultaneously.\n");
    printf("    • Politeness Principle: When P0 wants to enter, it sets turn = B (yielding\n"
           "      to P1). If P1 also wants to enter, turn determines the winner.\n");
    printf("    • Busy-Waiting Spinlock: Step l4/m4 shows busy-waiting until lock opens.\n\n");

    printf("--- DEADLOCK & STARVATION THEORY ---\n\n");
    printf("DEADLOCK THEORY:\n");
    printf("    A Deadlock occurs when two or more processes are permanently blocked\n");
    printf("    because each process holds a resource that another process needs, and\n");
    printf("    waits for a resource held by the next process.\n\n");
    printf("THE 4 COFFMAN CONDITIONS (Must ALL hold simultaneously for Deadlock):\n");
    printf("    1. Mutual Exclusion: At least one resource is held in a non-shareable mode.\n");
    printf("    2. Hold and Wait: A process holds at least one resource while waiting to\n");
    printf("       acquire additional resources held by other processes.\n");
    printf("    3. No Preemption: Resources cannot be forcibly taken from a process; they\n");
    printf("       can only be released voluntarily after the process completes its task.\n");
    printf("    4. Circular Wait: A closed chain of processes exists such that P0 waits for\n");
    printf("       a resource held by P1, P1 waits for P2, ..., and Pn waits for P0.\n\n");
    printf("STARVATION THEORY:\n");
    printf("    Starvation (Indefinite Postponement) occurs when a runnable process is\n"
           "    perpetually denied necessary resources by the scheduler or greedier processes,\n"
           "    even though no deadlock exists in the system.\n\n");
    printf("HOW DEADLOCK AND STARVATION ARE AVOIDED:\n");
    printf("    • Deadlock Prevention: Eliminate at least one Coffman condition.\n");
    printf("      - Break Circular Wait: Resource ordering (e.g. asymmetric chopsticks).\n");
    printf("      - Eliminate Hold & Wait: Request all resources simultaneously upfront.\n");
    printf("    • Deadlock Avoidance: Dynamic state checking (e.g. Banker's Algorithm).\n");
    printf("      Allocates resources only if system remains in a SAFE state.\n");
    printf("    • Starvation Avoidance: Aging (gradually increasing process priority as it\n"
           "      waits) and Fair FIFO Request Queues for semaphores/locks.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
