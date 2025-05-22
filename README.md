# 📘 LargeInt Class – Arbitrary-Precision Integer Arithmetic

## Overview

This project implements a C++ class called `LargeInt` that allows manipulation of arbitrarily large non-negative integers using a custom **doubly linked list** for internal digit storage. It supports standard arithmetic and comparison operations, enabling use of large integers beyond the native limits of built-in types like `int` or `long long`.

## Features

### ✅ Arithmetic Operators

- `+` Addition  
- `-` Subtraction (result is set to 0 if it would be negative)  
- `*` Multiplication  
- `/` Division  
- `%` Modulo  

### ✅ Relational Operators

- `==` Equality  
- `<` Less than  
- `<=` Less than or equal  
- `>` Greater than  
- `>=` Greater than or equal  

### ✅ Input / Output

- `>>` Input stream operator: Reads a large integer from user input  
- `<<` Output stream operator: Prints the large integer to the console  

## Design Notes

### 🔒 Encapsulation

The `LargeInt` class uses a `DoublyLinkedList<int>` to store individual digits. The digits are stored in **reverse order** (least significant digit first) to simplify arithmetic operations.

### 🚫 No Inheritance from List

The `LargeInt` class is **not derived** from the linked list class. Instead, it **aggregates** the list to maintain strong encapsulation and modularity.

### ♻️ No Dynamic Memory Management

Since the class does not use raw pointers directly (only through the list), there's **no need for a copy constructor or destructor**.

### 📝 Assumptions

All values handled by `LargeInt` are assumed to be **non-negative** (positive or zero only). Negative numbers are not supported.

### ⚙️ Operator Implementation

All arithmetic and comparison operations are implemented manually using digit-wise operations. Only `friend` functions for input/output are used — `LargeInt` is **not** a friend of the linked list.

## How to Compile

Use a **C++11 or newer** compiler:

```bash
g++ main.cpp largeInt.cpp -o largeint
./largeint
