📘 LargeInt Class – Arbitrary-Precision Integer Arithmetic
Overview
This project implements a C++ class called LargeInt that allows manipulation of arbitrarily large non-negative integers using a custom doubly linked list for internal digit storage. It supports standard arithmetic and comparison operations, enabling use of large integers beyond the native limits of built-in types like int or long long.

Features
The LargeInt class provides the following functionality:

✅ Arithmetic Operators
+ Addition

- Subtraction (result is set to 0 if it would be negative)

* Multiplication

/ Division

% Modulo

✅ Relational Operators
== Equality

< Less than

<= Less than or equal

> Greater than

>= Greater than or equal

✅ Input / Output
>> Input stream operator: Reads a large integer from user input

<< Output stream operator: Prints the large integer to the console

Design Notes
Encapsulation:
The LargeInt class uses a DoublyLinkedList<int> to store individual digits. The digits are stored in reverse order for easier arithmetic operations (least significant digit first).

No Inheritance from List:
The LargeInt class is not derived from the linked list class. Instead, it aggregates a list object internally to maintain strong encapsulation and modularity.

No Dynamic Memory Management:
Since the class does not contain raw pointers (beyond the use of the list), there is no need for a copy constructor or destructor.

Assumptions:
The implementation assumes that all LargeInt values are non-negative (positive or zero only). Negative values are not supported.

Operator Implementation:
Arithmetic and logic are implemented manually using digit-wise operations, mimicking the behavior of hand-written calculations. Friend functions are used only for input/output operations, and no friend access is granted to the linked list class.

How to Compile
Use a C++11 or newer compiler:

g++ main.cpp largeInt.cpp -o largeint
./largeint
Make sure doublyLinkedList.h, largeInt.h, and their corresponding implementations are included in your build.
