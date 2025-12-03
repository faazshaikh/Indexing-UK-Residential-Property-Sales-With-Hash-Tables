# Hash Table Indexing for Large Datasets

A clean and efficient C program that demonstrates how to index and search large datasets using hash tables for fast lookups and optimized memory performance.

## Features

- **Hash-Based Indexing**: Enables near constant-time lookups using modular hashing  
- **Dynamic Memory Allocation**: Efficiently loads large CSV datasets into memory  
- **Search Comparison**: Benchmarks linear vs. indexed search performance  
- **Load Factor Analysis**: Evaluates hash table usage and collision distribution  
- **Collision Handling**: Implements linked list chaining for hash conflicts  

## Getting Started

### Installation

1. Clone the repository, build, and run:
   ```bash
   git clone <repository-url>
   cd Hash-Table-Indexing
   make
   ./main
   make clean   # optional
   ```

## Example Output

```bash
Total records appended: 666013
Total records appended: 1500230
Hash index on street created.
Time (Linear Search): 0.046075 seconds
Time (Hash Index): 0.000176 seconds
Unused hash slots: 11504 out of 100000 (11.50% unused)
Hash table load factor: 0.885
```

## Project Structure

```bash
project/
├── myDSlib.c        # Core implementation: file reading, hashing, search functions
├── myDSlib.h        # Struct definitions, constants, and function prototypes
├── main.c           # Entry point and test runner
├── Makefile         # Build automation
├── Report.pdf       # Documentation and appendix
└── .gitignore       # Ignores CSVs, binaries, and temp files
```

## Design Features

- **Memory Efficient**: Dynamically allocates and expands dataset memory  
- **Fast Lookup**: Hash-based search achieves O(1) expected performance  
- **Modular Design**: Separation of logic, structures, and compilation rules  
- **Performance Insights**: Tracks runtime differences between methods  
- **Scalable Implementation**: Handles datasets with millions of entries  

## Technologies Used

- C (GCC)  
- Makefile build system  
- GDB debugger  
- Hash tables and linked lists  
- Dynamic memory management (`malloc`, `realloc`, `free`)  

## Author

Faaz Waheed Shaikh 
