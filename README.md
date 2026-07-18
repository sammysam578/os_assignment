NovaDrive Operating System Assignment
====================================

Overview:
This project demonstrates operating system concepts including process management,
threading, synchronization, memory management, file system operations, security
mechanisms, and network communication.

The project contains four tasks.

Task 1: Process Management and Threading

Description:
This task demonstrates multithreading, mutex synchronization, race condition
handling, Round Robin scheduling simulation, and deadlock prevention.

Compilation:
Navigate to the Task1_Process_Management folder and run:

gcc novadrive_process.c -o process -pthread

Execution:

./process


Task 2: Memory Management Simulation

Description:
This task implements virtual memory concepts using paging, FIFO and LRU page
replacement algorithms.

Compilation:

gcc novadrive_memory.c -o memory

Execution:

./memory


Task 3: File System Operations and Security

Description:
This task implements a secure file management system with authentication,
permissions, encryption/decryption, and audit logging.

Compilation:

gcc novadrive_filesystem.c -o filesystem

Execution:

./filesystem


Task 4: Network Programming and IPC

Description:
This task demonstrates client-server communication using TCP sockets.

Server Compilation:

gcc novadrive_server.c -o server -pthread

Run Server:

./server


Client Compilation:

gcc novadrive_client.c -o client

Run Client:

./client


Libraries Used:
- Standard C libraries
- POSIX Threads (pthread)
- Linux socket programming libraries


References:
- Linux Manual Pages
- POSIX Thread Documentation
- Standard C Library Documentation
