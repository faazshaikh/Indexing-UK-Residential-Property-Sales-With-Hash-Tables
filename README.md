Hash Table Indexing for Large Datasets

This project demonstrates an efficient way to index and search large datasets using hash tables in C. It loads CSV data into memory, creates an index on a specific column (for example, street name), and compares the performance of linear search versus hash-based lookup.

Overview

When handling large datasets, linear searching can be extremely slow. This project uses a hash-based index to speed up lookups by mapping keys (like street names) to memory addresses.

Features:

Dynamic memory allocation for scalable data loading

Hash table construction with collision handling (linked lists)

Search performance comparison between indexed and non-indexed methods

Load factor analysis to measure efficiency and memory usage

How to Build and Run
make
./main


Example output:

Total records appended: 666013
Total records appended: 1500230
Hash index on street created.
Time (Linear Search): 0.046075 seconds
Time (Hash Index): 0.000176 seconds
Unused hash slots: 11504 out of 100000 (11.50% unused)
Hash table load factor: 0.885

Core Components
File	Description
myDSlib.c	Core implementation: file reading, hashing, and search functions
myDSlib.h	Structures, constants, and function prototypes
main.c	Entry point and test runner
Makefile	Build automation
Report.pdf	Documentation of build, usage, and analysis
.gitignore	Ignores CSVs, binaries, and object files
Key Functions

read_file() – Loads CSV data into dynamically allocated memory

createIndexOnStreet() – Builds the hash table index

searchStreetLinear() – Performs full linear scan

searchStreet() – Performs constant-time indexed lookup

count_unused_slots() – Evaluates load factor and slot usage

Insights

Performance: Hash indexing drastically reduces lookup times.

Memory Use: Dynamic fields minimize waste compared to static arrays.

Efficiency: Optimal load factors (around 0.8) balance speed and collisions.

Technologies Used

Language: C

Concepts: Hash Tables, Linked Lists, Memory Management, Caching

Tools: GCC, Make, GDB

Author

Faaz Shaikh Waheed Shaikh (Big 808)