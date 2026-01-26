//
// Created by dylan on 1/14/26.
//

#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "colors.h"

void display_fetch(sys_config_t *config) {

    const char *arch_logo[] = {
        "                   -                ",
        "                  .o+`               ",
        "                 `ooo/               ",
        "                `+oooo:              ",
        "               `+oooooo:             ",
        "               -+oooooo+:            ",
        "             `/:-:++oooo+:           ",
        "            `/++++/+++++++:          ",
        "           `/++++++++++++++:         ",
        "          `/+++ooooooooooooo/`       ",
        "         ./ooosssso++osssssso+`      ",
        "        .oossssso-````/ossssss+`     ",
        "       -osssssso.      :ssssssso.    ",
        "       :osssssss/        osssso+++.   ",
        "     /ossssssss/        +ssssooo/-   ",
        "   `/ossssso+/:-        -:/+osssso+- ",
        "  `+sso+:-`                `.-/+oso: ",
        " `++:.                           `-/+/",
        " .`                                 `%"
    };

    for (int i = 0; i<19; i++) {
        switch (i) {
            case 2:
                printf(CYAN BOLD "%-35s" COLOR_RESET BOLD "---------------" COLOR_RESET "\n", arch_logo[i]);
                break;
            case 3:
                printf(CYAN "%-35s" "OS: " COLOR_RESET BOLD "%s" COLOR_RESET "\n", arch_logo[i], config->os_name);
                break;
            case 4:
                printf(CYAN "%-35s" "Kernel: " COLOR_RESET BOLD "%s" COLOR_RESET "\n", arch_logo[i], config->kernel_name);
                break;
            case 5:
                printf(CYAN "%-35s" "Uptime: " COLOR_RESET BOLD "%s" COLOR_RESET "\n", arch_logo[i], config->uptime);
                break;
            case 6:
                printf(CYAN "%-35s" "Memory: " COLOR_RESET BOLD "%s/%s" COLOR_RESET "\n", arch_logo[i], config->free_ram, config->total_ram);
                break;
            case 7:
                printf(CYAN "%-35s" "CPU: " COLOR_RESET BOLD "%s" COLOR_RESET "\n", arch_logo[i], config->cpu_name);
                break;
            default:
                printf(CYAN "%-35s" COLOR_RESET "\n", arch_logo[i]);
                break;
        }
    }
};

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
    get_uptime(config);

    display_fetch(config);
    free(config);
}