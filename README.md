# HashMap & Spam Detector

A C++ implementation of a custom hash table data structure with dynamic resizing capabilities, featuring a practical spam detection application.

## Overview

This project demonstrates advanced C++ programming concepts including template classes, STL-style iterators, move semantics, and custom memory management. It consists of two main components:

### HashMap
A generic, templated hash table implementation with:
- **Dynamic resizing** based on configurable load factors
- **Separate chaining** for collision resolution using `std::vector` buckets
- **STL-compatible iterators** for seamless integration with C++ algorithms
- **Move semantics** for efficient transfers
- **O(1) average-case** lookup, insertion, and deletion

### SpamDetector
A practical application leveraging the HashMap to classify emails as spam or legitimate by:
- Scoring messages based on keyword frequency
- Case-insensitive keyword matching
- Configurable spam thresholds
- Simple CSV-format keyword database

## Features

### HashMap Implementation

| Feature | Description |
|---------|-------------|
| **Generic Templates** | Works with any key-value types supporting `std::hash` |
| **Automatic Resizing** | Doubles capacity when load factor > 0.75, halves when < 0.25 |
| **Efficient Hashing** | Power-of-2 table sizes for bitwise hash computation |
| **Iterator Support** | `begin()`, `end()`, `cbegin()`, `cend()` for range-based loops |
| **Standard Operations** | `insert()`, `erase()`, `at()`, `operator[]`, `containsKey()` |
| **Copy/Move Semantics** | Full support for copy and move constructors/operators |

### Core API

```cpp
// Construction
HashMap<string, int> map;
HashMap<string, int> map(0.5, 0.9);  // Custom load factors

// Insertion
map.insert("hello", 42);
map["world"] = 100;

// Lookup
int value = map.at("hello");
bool exists = map.containsKey("hello");

// Iteration
for (auto it = map.begin(); it != map.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
}

// Metadata
int size = map.size();
int capacity = map.capacity();
double loadFactor = map.getLoadFactor();
```

## Building the Project

### Prerequisites
- C++11 or later
- CMake 3.10+
- A C++ compiler (GCC, Clang, MSVC)

### Build Instructions

```bash
# Clone the repository
git clone <repository-url>
cd Hashmap

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run spam detector
./SpamDetector ../test/1database.txt ../test/1mail.txt 100
```

## Usage

### Spam Detector Application

```bash
./SpamDetector <database_path> <email_path> <threshold>
```

**Parameters:**
- `database_path` - Path to CSV file containing keywords and scores
- `email_path` - Path to email/message file to analyze
- `threshold` - Spam score threshold (integer)

**Example:**
```bash
./SpamDetector test/1database.txt test/1mail.txt 100
```

**Output:**
- `SPAM` - If message score exceeds threshold
- `NOT_SPAM` - If message score is below threshold

### Database Format

The keyword database uses a simple CSV format:
```
keyword1,score1
keyword2,score2
promote,5
winner,10
free,15
```

### How It Works

1. Loads keyword-score pairs from database into HashMap
2. Reads email message line by line
3. Converts text to lowercase for case-insensitive matching
4. Searches for each keyword in the message
5. Calculates total score: sum of (keyword_count × keyword_score)
6. Classifies as SPAM if score > threshold

**Example:**
```
Database:
  free,10
  winner,15

Message: "You are a WINNER! Get it FREE today!"

Score calculation:
  "winner" appears 1 time: 1 × 15 = 15
  "free" appears 1 time: 1 × 10 = 10
  Total score: 25

If threshold = 20, output = SPAM
If threshold = 30, output = NOT_SPAM
```

## Project Structure

```
Hashmap/
├── HashMap.hpp           # Templated hash table implementation
├── SpamDetector.cpp      # Spam detection application
├── CMakeLists.txt        # Build configuration
├── test/                 # Test files
│   ├── 1database.txt     # Sample keyword database
│   ├── 1mail.txt         # Sample email
│   └── ...               # Additional test cases
└── README.md             # This file
```

## Implementation Details

### Hash Function
Uses `std::hash<KeyT>` with bitwise AND masking for efficient modulo operation:
```cpp
int hash = std::hash<KeyT>{}(key) & (capacity - 1);
```

### Collision Resolution
Separate chaining using `std::vector<std::pair<KeyT, ValueT>>` buckets. Each bucket stores multiple key-value pairs.

### Dynamic Resizing
- **Expand:** When `load_factor > upper_threshold` (default 0.75), doubles capacity
- **Shrink:** When `load_factor < lower_threshold` (default 0.25), halves capacity
- Maintains capacity as power of 2 for efficient hashing

### Iterator Design
Custom `const_iterator` class traverses non-empty buckets sequentially, skipping empty ones for efficient iteration over sparse tables.

## Performance Characteristics

| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Insert    | O(1)         | O(n)       |
| Lookup    | O(1)         | O(n)       |
| Delete    | O(1)         | O(n)       |
| Rehash    | O(n)         | O(n)       |

*Worst case occurs with extreme hash collisions. Proper hash functions minimize this.*

## Testing

The project includes 9 test cases in the `test/` directory, each with a database and corresponding email file. Test with different thresholds:

```bash
# Test case 1
./SpamDetector test/1database.txt test/1mail.txt 50
./SpamDetector test/1database.txt test/1mail.txt 100
./SpamDetector test/1database.txt test/1mail.txt 200

# Run all tests
for i in {1..9}; do
    echo "Test $i:"
    ./SpamDetector test/${i}database.txt test/${i}mail.txt 100
done
```

## Technical Highlights

- **Memory Management:** Manual memory management with proper cleanup in destructor
- **Template Metaprogramming:** Generic implementation works with any hashable type
- **C++11 Features:** Move semantics, range-based for loops, lambda expressions
- **Exception Safety:** Throws `std::invalid_argument` and `std::out_of_range` appropriately
- **STL Compatibility:** Custom iterator integrates with STL algorithms

## License

This project is available for educational and portfolio purposes.

## Author

Created as a demonstration of advanced C++ data structures and algorithms.
