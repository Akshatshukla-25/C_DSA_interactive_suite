#ifndef STEP_DEBUGGER_H
#define STEP_DEBUGGER_H

#include <stddef.h>

#define MAX_TELEMETRY_VARIABLES 8
#define MAX_TELEMETRY_ALLOCATIONS 16

typedef struct VariableSnapshot
{
    char name[32];
    char value[64];
} VariableSnapshot;

typedef struct AllocationSnapshot
{
    void* address;
    size_t size;
    char label[32];
    int active; // 1 = active, 0 = freed
} AllocationSnapshot;

typedef struct AlgorithmStateBridge
{
    char algorithm_name[64];
    int step_index;
    int recursion_depth;
    int var_count;
    VariableSnapshot variables[MAX_TELEMETRY_VARIABLES];
    int alloc_count;
    AllocationSnapshot allocations[MAX_TELEMETRY_ALLOCATIONS];
    char status_message[128];
} AlgorithmStateBridge;

void set_step_mode(int active);
int get_step_mode(void);

void set_paused(int paused);
int get_paused(void);

void algorithm_step_hook(const char* event_msg);

void get_recent_events(char events[5][128], int* count);
void clear_recent_events(void);
void print_recent_events_card(void);

/* ── Time-Travel Stepping & State Inspector API ────────────────── */
int debugger_get_history_count(void);
int debugger_get_current_step(void);
void debugger_step_prev(void);
void debugger_step_next(void);
void debugger_step_reset(void);
void debugger_toggle_inspector(void);
int debugger_is_inspector_visible(void);
void print_state_inspector_card(void);

/* ── Unified Interactive Telemetry Bridge API ──────────────────── */
void telemetry_bridge_update(const AlgorithmStateBridge* bridge);
void telemetry_bridge_get(AlgorithmStateBridge* bridge_out);
void telemetry_bridge_reset(const char* algorithm_name);

void debugger_demo(void);

#endif // STEP_DEBUGGER_H
