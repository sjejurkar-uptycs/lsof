#include "lsof.h"
#include "lsof_structured.h"
#include <stdio.h>
#include <stdlib.h>

// Expose run_lsof_core for C++ integration
extern int run_lsof_core(void);

// Simple function to run lsof and return structured result
lsof_result_t* run_lsof(void) {
    // Initialize the structured result
    init_lsof_result();
    printf("DEBUG: run_lsof() - init_lsof_result() called\n");
    
    // Run lsof core function
    printf("DEBUG: run_lsof() - calling run_lsof_core()\n");
    run_lsof_core();
    printf("DEBUG: run_lsof() - run_lsof_core() completed\n");
    
    // Get and return the structured result
    lsof_result_t* result = get_lsof_result();
    printf("DEBUG: run_lsof() - get_lsof_result() returned: %p\n", (void*)result);
    
    if (result) {
        printf("DEBUG: run_lsof() - result->count = %d\n", result->count);
    } else {
        printf("DEBUG: run_lsof() - result is NULL!\n");
    }
    
    return result;
}

// Function to print the lsof result
void print_lsof_result(lsof_result_t* result) {
    if (!result) {
        printf("No structured data collected.\n");
        return;
    }
    
    printf("\n=== STRUCTURED LSOF RESULTS ===\n");
    printf("Total entries collected: %d\n\n", result->count);
    
    // Print all entries
    for (int i = 0; i < result->count; i++) {
        lsof_entry_t* entry = &result->entries[i];
        printf("Entry %d:\n", i);
        printf("  Command: %s\n", entry->command);
        printf("  PID: %d\n", entry->pid);
        printf("  Parent PID: %d\n", entry->parent_pid);
        printf("  User: %s\n", entry->user);
        printf("  FD: %s\n", entry->fd);
        printf("  Type: %s\n", entry->type);
        printf("  Device: %s\n", entry->device);
        printf("  Size/Off: %s\n", entry->size_off);
        printf("  Node: %s\n", entry->node);
        printf("  Name: %s\n", entry->name);
        printf("  TCP/TPI: %s\n", entry->tcp_tpi_info);
        printf("\n");
    }
}

// Function to free the lsof result
void free_lsof_result_wrapper(lsof_result_t* result) {
    if (result) {
        free_lsof_result();
        printf("DEBUG: Structured data freed successfully\n");
    }
}

// Main function for testing
int main(int argc, char *argv[]) {
    printf("=== LSOF Structured Data Test ===\n");
    
    // Run lsof and get structured data
    printf("DEBUG: main() - calling run_lsof()\n");
    lsof_result_t* result = run_lsof();
    printf("DEBUG: main() - run_lsof() returned: %p\n", (void*)result);
    
    // Print the results
    printf("DEBUG: main() - calling print_lsof_result()\n");
    print_lsof_result(result);
    printf("DEBUG: main() - print_lsof_result() completed\n");
    
    // Clean up
    printf("DEBUG: main() - calling free_lsof_result_wrapper()\n");
    free_lsof_result_wrapper(result);
    printf("DEBUG: main() - cleanup completed\n");
    
    return 0;
}