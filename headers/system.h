//
// Created by dylan on 1/15/26.
//

#ifndef NEWFETCH_SYSTEM_H
#define NEWFETCH_SYSTEM_H

#define STR_SIZE_MAX 128
#define HOST_SIZE_MAX 64

typedef struct {
    char user[HOST_SIZE_MAX];
    char hostname[HOST_SIZE_MAX];
    char os_name[STR_SIZE_MAX];
    char total_ram[STR_SIZE_MAX];
    char free_ram[STR_SIZE_MAX];
    char cpu_name[STR_SIZE_MAX];
    char kernel[STR_SIZE_MAX];
} sys_config_t;

void get_cpu_name(sys_config_t *config);
void get_ram_info(sys_config_t *config);

#endif //NEWFETCH_SYSTEM_H