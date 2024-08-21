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

#ifndef _MONITOR_H_
#define _MONITOR_H_

#ifdef CONFIG_MAX_BACKTRACE
#define MAX_BACKTRACE CONFIG_MAX_BACKTRACE
#else
#define MAX_BACKTRACE 20
#endif

/* clang-format off */
typedef struct monitor {
    void*  handle;
    void*  backtrace[MAX_BACKTRACE];
    int    backtrace_size;
    struct monitor* next;
} monitor_t;
/* clang-format on */

void cleanup_monitor(void);

void print_monitor(void);

void release_monitor(void* handle);

monitor_t* allocate_monitor(void* handle);

#endif /* _MONITOR_H_ */
