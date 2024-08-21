/*
 * Copyright (C) 2024 Junbo Zheng. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monitor.h"

static monitor_t* head = NULL;

static void print_backtrace(void* backtrace[], int size)
{
    char** symbols = backtrace_symbols(backtrace, size);
    if (symbols != NULL) {
        for (int i = 0; i < size; i++) {
            printf("%s\n", symbols[i]);
        }
        free(symbols);
    }
}

// Function to allocate a new monitor
monitor_t* allocate_monitor(void* handle)
{
    // Allocate and initialize monitor structure
    monitor_t* res = (monitor_t*)malloc(sizeof(monitor_t));
    if (!res) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    res->handle = handle;
    res->backtrace_size = backtrace(res->backtrace, MAX_BACKTRACE);
    res->next = head;
    head = res;

    // Print the backtrace for debugging purposes
    printf("Allocated monitor with handle %p:\n", res->handle);
    print_backtrace(res->backtrace, res->backtrace_size);

    return res;
}

// Function to release a monitor by handle
void release_monitor(void* handle)
{
    monitor_t** indirect = &head;
    while (*indirect) {
        monitor_t* res = *indirect;
        if (res->handle == handle) {
            // Print backtrace of the monitor being released
            printf("Releasing monitor with handle %p:\n", res->handle);
            print_backtrace(res->backtrace, res->backtrace_size);

            // Remove monitor from the list
            *indirect = res->next;
            free(res);
            return;
        }
        indirect = &res->next;
    }
    fprintf(stderr, "monitor handle %p not found.\n", handle);
}

// Function to print all allocated but not released monitors
void print_monitor(void)
{
    monitor_t* current = head;
    if (current == NULL) {
        printf("No allocated monitor.\n");
        return;
    }

    printf("Allocated monitor:\n");
    while (current) {
        printf("monitor handle %p:\n", current->handle);
        print_backtrace(current->backtrace, current->backtrace_size);
        current = current->next;
    }
}

// Clean up all remaining monitor
void cleanup_monitor(void)
{
    monitor_t* current = head;
    while (current) {
        monitor_t* next = current->next;
        printf("Cleanup monitor with handle %p:\n", current->handle);
        print_backtrace(current->backtrace, current->backtrace_size);
        free(current);
        current = next;
    }
    head = NULL;
}
