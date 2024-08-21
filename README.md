## Resource Monitor

It can be used to monitor whether resources are used in pairs. Usually, it is used to monitor whether subscribers or unsubscribers are matched. It can also be expanded to monitor whether memory usage and release are used in pairs.

- Generic resource management: Create a generic resource management system that can track any type of resource. This system can handle memory, file handles, network connections, etc.

- Generic API: Provide a set of generic APIs to manage these resources, including allocation, release, and status inspection.

- Resource tracking: Record allocation information and backtrace for each resource so that it can be inspected and debugged when needed.
