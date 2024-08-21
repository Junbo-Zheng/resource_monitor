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

#include <stdio.h>
#include <stdlib.h>

#include "monitor.h"

static void* mymalloc(size_t size)
{
    char* handle = malloc(size);
    if (handle == NULL) {
        printf("malloc fail\n");
        return NULL;
    }

    allocate_monitor(handle);
    return handle;
}

static void myfree(void* handle)
{
    if (handle == NULL) {
        printf("free fail\n");
        return;
    }

    if (handle) {
        free(handle);
        release_monitor(handle);
    }
}

int main(void)
{
    char* handle1 = mymalloc(100);
    char* handle2 = mymalloc(200);
    char* handle3 = mymalloc(300);

    // Print allocated monitor before releasing
    print_monitor();

    myfree(handle1);
    myfree(handle2);

    // Print allocated monitor after some releases
    print_monitor();

    // Cleanup any remaining monitor
    cleanup_monitor();

    // Free the last handle3
    myfree(handle3);

    return 0;
}
