//
// Created by dylan on 1/14/26.
//

#include <stdio.h>
#include <stdlib.h>

#include "system.h"

int main(void)
{
    sys_config_t *config = malloc(sizeof(sys_config_t));
    if (config == NULL) {
        return 1;
    }

    get_cpu_name(config);
    get_ram_info(config);
    get_os_name(config);
    get_kernel_version(config);
    printf("%s - \nMemory: %s / %s\nSystem Name: %s\nKernel: %s", config->cpu_name, config->free_ram, config->total_ram, config->os_name, config->kernel_name);

    free(config);
}