#ifndef LSOF_WRAPPER_H
#define LSOF_WRAPPER_H

#include "lsof.h"

#ifdef __cplusplus
extern "C" {
#endif

// Wrapper function to run lsof with given arguments
lsof_result_t* lsof_run(const char* args);

// Function to free the result
void lsof_free_result(lsof_result_t* result);

// Function to get entry count
int lsof_get_entry_count(lsof_result_t* result);

// Function to get a specific entry
lsof_entry_t* lsof_get_entry(lsof_result_t* result, int index);

#ifdef __cplusplus
}
#endif

#endif // LSOF_WRAPPER_H 