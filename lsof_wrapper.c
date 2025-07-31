#include "lsof.h"
#include "proto.h"
#include "lsof_structured.h"
#include <string.h>
#include <stdlib.h>

// Global variables to store the current entry being built
static char current_command[256];
static int current_pid;
static int current_parent_pid;
static char current_user[64];
static char current_fd[16];
static char current_type[16];
static char current_device[64];
static char current_size_off[64];
static char current_node[64];
static char current_name[1024];
static char current_tcp_tpi_info[256];

// Function to reset current entry
static void reset_current_entry() {
    memset(current_command, 0, sizeof(current_command));
    current_pid = 0;
    current_parent_pid = 0;
    memset(current_user, 0, sizeof(current_user));
    memset(current_fd, 0, sizeof(current_fd));
    memset(current_type, 0, sizeof(current_type));
    memset(current_device, 0, sizeof(current_device));
    memset(current_size_off, 0, sizeof(current_size_off));
    memset(current_node, 0, sizeof(current_node));
    memset(current_name, 0, sizeof(current_name));
    memset(current_tcp_tpi_info, 0, sizeof(current_tcp_tpi_info));
}

// Function to add current entry to result
static void add_current_entry() {
    if (current_pid > 0) {  // Only add if we have a valid entry
        add_lsof_entry(current_command, current_pid, current_parent_pid, current_user,
                      current_fd, current_type, current_device,
                      current_size_off, current_node, current_name, current_tcp_tpi_info);
    }
    reset_current_entry();
}

// Wrapper function to run lsof with given arguments
lsof_result_t* lsof_run(const char* args) {
    // Initialize the result
    init_lsof_result();
    reset_current_entry();
    
    // Parse arguments and set up lsof options
    // This is a simplified version - you'll need to implement proper argument parsing
    int argc = 1;
    char* argv[10];
    argv[0] = "lsof";
    
    // Parse the args string into argv
    char* args_copy = strdup(args);
    char* token = strtok(args_copy, " ");
    argc = 1;
    while (token && argc < 10) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    
    // Call main2 with the parsed arguments
    int result = main2(argc, argv);
    
    free(args_copy);
    
    // Return the result
    return get_lsof_result();
}

// Function to free the result
void lsof_free_result(lsof_result_t* result) {
    if (result) {
        free_lsof_result();
    }
}

// Function to get entry count
int lsof_get_entry_count(lsof_result_t* result) {
    return result ? result->count : 0;
}

// Function to get a specific entry
lsof_entry_t* lsof_get_entry(lsof_result_t* result, int index) {
    if (!result || index < 0 || index >= result->count) {
        return NULL;
    }
    return &result->entries[index];
} 