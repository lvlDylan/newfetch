//
// Created by dylan on 1/15/26.
//

#include "system.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024

void get_cpu_name(sys_config_t *config) {

    char line[MAX_BUFFER_SIZE];

    // Open File and handle error that might happen
    FILE *fp = NULL;
    if ((fp = fopen("/proc/cpuinfo", "r")) == NULL) { // Testing if /proc/cpuinfo can be read.
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
                model_name ++;
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
    const char *start_ptr = line + 9; // Start of line without MemTotal

    long mem_val = strtol(start_ptr, NULL, 10); // Convert str to long

    mem_val = mem_val / 1024;
    if (strcmp(type, "TotalRam") == 0) {
        snprintf(config->total_ram, MAX_BUFFER_SIZE,"%ld MiB", mem_val);
    } else if (strcmp(type, "FreeRam") == 0) {
        snprintf(config->free_ram, MAX_BUFFER_SIZE,"%ld MiB", mem_val);
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
