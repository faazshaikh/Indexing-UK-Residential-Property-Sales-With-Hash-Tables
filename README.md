Indexing Large Datasets with Hash Tables

This project implements an in-memory hash table index for large CSV datasets to demonstrate how indexing improves lookup speed and memory efficiency.
It’s based on the UK Land Registry Price Paid Data and explores concepts of hashing, dynamic memory, and cache performance.

📘 Overview

When dealing with millions of records, searching linearly through data is slow.
This assignment compares:

Linear Search (O(n)) — scanning each record sequentially

Hash Index Search (O(1)) — direct lookup using a hash table

By indexing only the street column, the program drastically reduces search time and improves efficiency.

🧩 Features

Dynamically loads CSV files into memory (read_file())

Builds a hash table index on the street field (createIndexOnStreet())

Performs both linear and indexed searches (searchStreetLinear() / searchStreet())

Analyzes load factor and unused slots to assess index performance

Includes a Makefile for easy compilation and cleanup

⚙️ How to Build and Run
# Compile the program
make

# Run the executable
./main


If successful, you’ll see output similar to:

Total records appended: 666013
Total records appended: 1500230
Hash index on street created.
Time (Linear Search): 0.046075 seconds
Time (Hash Index): 0.000176 seconds
Unused hash slots: 11504 out of 100000 (11.50% unused)
Hash table load factor: 0.885

📊 Discussion Summary

Memory efficiency: dynamically allocated fields (like district) save space compared to fixed arrays (street).

Performance gap: caching and memory layout reduce the theoretical gap between O(1) and O(n) searches.

Optimal load factor: between 0.5–0.9 for balance between speed and memory use.

🧮 File Structure
📂 COMPSCI1XC3_Assignment4
├── myDSlib.c          # Implementation (your main logic)
├── myDSlib.h          # Header file (structs, constants, prototypes)
├── main.c             # Provided driver (do not modify)
├── Makefile           # Build automation
├── Report.pdf         # Documentation & appendix
├── .gitignore         # Ignore object files and datasets
└── README.md          # This file

🚫 Excluded Files

Do not upload:

Large CSV files (e.g., pp-2024.csv, pp-2023.csv)

Object files or executables (*.o, a.out, etc.)

🧰 Technologies

Language: C

Concepts: Hash Tables, Dynamic Memory Allocation, Linked Lists, Caching

Tools: GCC, Makefile, GDB

🧑‍💻 Author

Faaz Shaikh Waheed Shaikh 
McMaster University 
