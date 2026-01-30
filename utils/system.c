//
// Created by dylan on 1/15/26.
//

#include "system.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_BUFFER_SIZE 1024

void get_cpu_name(sys_config_t *config) {
    char line[MAX_BUFFER_SIZE];

    // Open File and handle error that might happen
    FILE *fp = NULL;
    if ((fp = fopen("/proc/cpuinfo", "r")) == NULL) {
        // Testing if /proc/cpuinfo can be read.
        strncpy(config->cpu_name, "Unknown", STR_SIZE_MAX - 1); // If not, put unknown
        return;
    }

    /*
     * While a line can be read and found is not set to 1
     * Search model name in the buffer line, search ' : ' in line
     * tmp++ because we want to skip ':'
     *  Remove blanks or tabulation
     *  Copy it in our struct
     */

    while (fgets(line, MAX_BUFFER_SIZE, fp) != NULL) {
        if (strncmp(line, "model name", 10) == 0) {
            char *model_name = strchr(line, ':');
            if (model_name != NULL) {
                model_name++;
                while (*model_name == ' ' || *model_name == '\t') {
                    model_name++;
                }

                strncpy(config->cpu_name, model_name, STR_SIZE_MAX - 1);

                config->cpu_name[STR_SIZE_MAX - 1] = '\0';
                char *p = strchr(config->cpu_name, '\n');
                if (p != NULL) {
                    *p = '\0';
                }

                break;
            }
        }
    }

    fclose(fp);
}

static void parse_meminfo(const char *line, const char *type, sys_config_t *config) {
    const char *start_ptr = strchr(line, ':') + 1; // Start of line without Mem***:

    long mem_val = strtol(start_ptr, NULL, 10); // Convert str to long

    mem_val = mem_val / 1024;
    if (strcmp(type, "TotalRam") == 0) {
        snprintf(config->total_ram, STR_SIZE_MAX - 1, "%ld MiB", mem_val);
    } else if (strcmp(type, "FreeRam") == 0) {
        snprintf(config->free_ram, STR_SIZE_MAX - 1, "%ld MiB", mem_val);
    }
}

void get_ram_info(sys_config_t *config) {
    FILE *fp = NULL;
    if ((fp = fopen("/proc/meminfo", "r")) == NULL) {
        strncpy(config->total_ram, "Unknown", STR_SIZE_MAX - 1);
        strncpy(config->free_ram, "Unknown", STR_SIZE_MAX - 1);
        return;
    }

    char line[MAX_BUFFER_SIZE];

    while (fgets(line, MAX_BUFFER_SIZE, fp) != NULL) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            parse_meminfo(line, "TotalRam", config);
        } else if (strncmp(line, "MemFree:", 8) == 0) {
            parse_meminfo(line, "FreeRam", config);
        }
    }

    fclose(fp);
}

void get_os_name(sys_config_t *config) {
    FILE *fp = NULL;
    if ((fp = fopen("/etc/os-release", "r")) == NULL) {
        strncpy(config->os_name, "Linux (Unknown)", STR_SIZE_MAX - 1);
        return;
    }

    char line[MAX_BUFFER_SIZE];
    while (fgets(line, MAX_BUFFER_SIZE, fp) != NULL) {
        if (strncmp(line, "PRETTY_NAME", 11) == 0) {
            strtok(line, "=");
            char *os_name = strtok(NULL, "=\"\n");
            strncpy(config->os_name, os_name, STR_SIZE_MAX - 1);
            break;
        }
    }

    fclose(fp);
}

void get_kernel_version(sys_config_t *config) {
    FILE *fp = NULL;
    if ((fp = fopen("/proc/version", "r")) == NULL) {
        strncpy(config->kernel_name, "Unknown", STR_SIZE_MAX - 1);
        return;
    }

    char line[MAX_BUFFER_SIZE];
    while (fgets(line, MAX_BUFFER_SIZE, fp) != NULL) {
        strtok(line, " ");
        strtok(NULL, " ");
        const char *kernel_version = strtok(NULL, " ");

        if (kernel_version == NULL) {
            strncpy(config->kernel_name, "Unknown", STR_SIZE_MAX - 1);
            return;
        }

        strncpy(config->kernel_name, kernel_version, STR_SIZE_MAX - 1);
        break;
    }

    fclose(fp);
}

void get_uptime(sys_config_t *config) {
    FILE *fp = NULL;
    if ((fp = fopen("/proc/uptime", "r")) == NULL) {
        strncpy(config->uptime, "Unknown", STR_SIZE_MAX - 1);
        return;
    }

    char line[MAX_BUFFER_SIZE];
    while (fgets(line, MAX_BUFFER_SIZE, fp) != NULL) {
        char *buffer = strtok(line, " ");
        char tmp[128];

        long uptime = strtol(buffer, NULL, 10);

        long hours = (uptime / 3600) % 24;
        long minutes = (uptime / 60) % 60;
        long seconds = uptime % 60;
        long days = uptime / 86400;

        int pos = 0;

        if (days >= 1) {
            if (days == 1) {
                pos += sprintf(tmp + pos, "%ldd, ", days);
            } else {
                pos += sprintf(tmp + pos, "%ld days, ", days);
            }
        }

        if (hours >= 1) {
            if (hours == 1) {
                pos += sprintf(tmp + pos, "%ld hour, ", hours);
            } else {
                pos += sprintf(tmp + pos, "%ld hours, ", hours);
            }
        }

        if (minutes >= 1) {
            if (minutes == 1) {
                pos += sprintf(tmp + pos, "%ld minute, ", minutes);
            } else {
                pos += sprintf(tmp + pos, "%ld minutes, ", minutes);
            }
        }

        if (minutes >= 1) {
            if (minutes == 1) {
                sprintf(tmp + pos, "%ld seconde", seconds);
            } else {
                sprintf(tmp + pos, "%ld secondes", seconds);
            }
        }

        strncpy(config->uptime, tmp, STR_SIZE_MAX - 1);
    }
}

void get_hostname(sys_config_t *config) {
    FILE *fp = NULL;
    if ((fp = fopen("/etc/hostname", "r")) == NULL) {
        strncpy(config->hostname, "Unknown", HOST_SIZE_MAX - 1);
        return;
    }

    char line[MAX_BUFFER_SIZE];
    if (fgets(line, HOST_SIZE_MAX, fp) != NULL) {
        strncpy(config->hostname, line, HOST_SIZE_MAX - 1);
    }

    config->hostname[HOST_SIZE_MAX - 1] = '\0';
    char *p = strchr(config->hostname, '\n');
    if (p != NULL) {
        *p = '\0';
    }

    fclose(fp);
}

void get_username(sys_config_t *config) {
    strncpy(config->user, getlogin(), HOST_SIZE_MAX - 1);
}

void get_shell_name(sys_config_t *config) {
    pid_t parent = getppid();
    char path[64];
    snprintf(path, 64, "/proc/%d/cmdline", parent);

    FILE *fp = NULL;
    if ((fp = fopen(path, "r")) == NULL) {
        strncpy(config->shell_name, "Unknown", STR_SIZE_MAX - 1);
        return;
    }

    char line[STR_SIZE_MAX];
    if (fgets(line, STR_SIZE_MAX, fp) != NULL) {
        strncpy(config->shell_name, line, STR_SIZE_MAX - 1);
    }

    config->shell_name[HOST_SIZE_MAX - 1] = '\0';
    char *p = strchr(config->shell_name, '\n');
    if (p != NULL) {
        *p = '\0';
    }

    fclose(fp);
}