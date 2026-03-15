# Doubly Linked List Serialization/Deserialization


## Task Description
Implementation of a program for serializing and deserializing a doubly linked list from a file of a given format with an additional `rand` pointer that points to an arbitrary element of the list.


### Node Structure (ListNode)
- `prev` — pointer to the previous element
- `next` — pointer to the next element
- `rand` — pointer to an arbitrary list element
- `data` — string data (up to 1000 characters, UTF-8)


## Input File Format (inlet.in)
Text file where each line contains:
<data>;<rand_index>
where `rand_index` is the index of the node for the `rand` pointer, or -1 if `rand == nullptr`.


Example:

apple;2
banana;-1
carrot;1


## Requirements
- Maximum number of nodes: 1,000,000
- Data string length: up to 1000 characters
- UTF-8 support


## Build and Run


### Compilation
```bash
g++ -std=c++17 -Wall -Wextra -o list_program src/main.cpp src/List.cpp
```


### Run
./list_program


### Input/Output Files
- inlet.in — input text file (must be in the project root directory)
- outlet.out — output binary file (created by the program)