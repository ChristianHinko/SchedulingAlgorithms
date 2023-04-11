# SchedulingAlgorithms

This project demonstrates the different scheduling algorithms that an operating system's task processor may perform.

The user provides a task schedule file pathname along with the scheduling algorithm name. This file contains the tasks to run which have names, priorities, and burst times. The scheduling algorithms implemented are First Come First Serve, Shortest Job First, Priority, Round Robin, and Priority Round Robin.

## Design

Extensibility was a major focus for this project. It is trivial to implement custom scheduling algorithms for this program.

Scheduling algorithms are registered to the GScheduleAlgorithms map statically via the G_REGISTER_SCHEDULE_ALGORITHM() macro. This allows the main program loop code to be generic and be concerned solely with the contents of the GScheduleAlgorithms map without hardcoding algorithm names.

The generic multicast delegate system allows benchmarking code to run without cluttering the scheduling algorithm implementations. The benchmarker simply binds its static functions to the task processing delegates and records timings.
