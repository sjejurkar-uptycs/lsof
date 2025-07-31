#ifndef LSOF_STRUCTURED_H
#define LSOF_STRUCTURED_H

#include "lsof.h"

#ifdef __cplusplus
extern "C" {
#endif

// Structured result function prototypes
extern void init_lsof_result(void);
extern void add_lsof_entry(const char *command, int pid, int parent_pid, const char *user, 
                          const char *fd, const char *type, const char *device,
                          const char *size_off, const char *node, const char *name,
                          const char *tcp_tpi_info);
extern void free_lsof_result(void);
extern lsof_result_t* get_lsof_result(void);

#ifdef __cplusplus
}
#endif

#endif // LSOF_STRUCTURED_H 