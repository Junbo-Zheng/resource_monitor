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

#include "monitor.h"

int main(void)
{
    // Example usage with custom handles
    void* handle1 = (void*)1;    // Example handle
    void* handle2 = (void*)2;    // Example handle
    void* handle3 = (void*)3;    // Example handle

    allocate_monitor(handle1);
    allocate_monitor(handle2);
    allocate_monitor(handle3);

    // Print allocated monitor before releasing
    print_monitor();

    release_monitor(handle1);
    release_monitor(handle2);

    // Print allocated monitor after some releases
    print_monitor();

    // Cleanup any remaining monitor
    cleanup_monitor();

    return 0;
}
