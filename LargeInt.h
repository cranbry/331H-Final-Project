#ifndef LARGEINT_H
#define LARGEINT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "doublyLinkedList.h"

using namespace std;

class LargeInt {
private:
    DoublyLinkedList<int> digits; // nodes have single digit
public:
    // Default constructor
    LargeInt() {
    }

    // Constructor from a string
    LargeInt(const string &numberStr) {
        for (int i = 0; i < numberStr.length(); ++i) {
            if (!isdigit(numberStr[i])) {
                throw invalid_argument("Only numeric characters are allowed.");
            }
            digits.insertFront(numberStr[i] - '0'); // adding digits to list from left to right
        }
        // removing leading zeros
        while (digits.getLength() > 1 && *(digits.begin()) == 0) {
            digits.removeFront();
        }
    }

    // Overload assignment operator
    LargeInt &operator=(const LargeInt &other) {
        if (this != &other) {
            digits = other.digits;
        }
        while (digits.getLength() > 1 && *(digits.begin()) == 0) {
            digits.removeFront();  // removing leading zeros
        }
        return *this;
    }

    // Overload << for printing
    friend ostream &operator<<(ostream &out, const LargeInt &num) {
        if (num.digits.isEmpty()) {
            out << "0";
            return out;
        }

        auto it = num.digits.rbegin(); // Reverse iterator
        while (it != num.digits.rend()) {
            out << *it;
            ++it;
        }
        return out;
    }

    // Overload >> for input
    friend istream &operator>>(istream &in, LargeInt &num) {
        string input;
        in >> input;

        // clearing existing digits
        num.digits.Clear();

        // adding digits to list from most significant digit
        for (int i = 0; i < input.length(); ++i) {
            char digit = input[i];
            if (isdigit(digit)) {
                num.digits.insertFront(digit - '0');  // storing most significant digit first
            } else {
                throw invalid_argument("Only numeric characters are allowed.");
            }
        }
        
        // Remove leading zeros
        while (num.digits.getLength() > 1 && *(num.digits.begin()) == 0) {
            num.digits.removeFront();
        }
        
        return in;
    }

    // Equality operator
    bool operator==(const LargeInt &other) const {
        if (digits.getLength() != other.digits.getLength()) {
            return false;
        }

        auto thisIt = digits.begin();
        auto otherIt = other.digits.begin();
        
        while (thisIt != digits.end() && otherIt != other.digits.end()) {
            if (*thisIt != *otherIt) {
                return false;
            }
            ++thisIt;
            ++otherIt;
        }
        return true;
    }

    // Less than operator
    bool operator<(const LargeInt &other) const {
        if (digits.getLength() < other.digits.getLength()) {
            return true;
        }
        else if (digits.getLength() > other.digits.getLength()) {
            return false;
        }

        auto thisIt = digits.begin();
        auto otherIt = other.digits.begin();
        
        while (thisIt != digits.end() && otherIt != other.digits.end()) {
            if (*thisIt < *otherIt) {
                return true;
            }
            else if (*thisIt > *otherIt) {
                return false;
            }
            ++thisIt;
            ++otherIt;
        }
        return false;
    }

    // Less than or equal operator
    bool operator<=(const LargeInt &other) const {
        return (*this < other) || (*this == other);
    }

    // Greater than operator
    bool operator>(const LargeInt &other) const {
        return !(*this <= other);
    }

    // Greater than or equal operator
    bool operator>=(const LargeInt &other) const {
        return !(*this < other);
    }

    // Addition operator
    LargeInt operator+(const LargeInt &other) const {
        LargeInt result;
        int carry = 0;
        
        auto thisIt = digits.rbegin();   // starting at the least significant digit
        auto otherIt = other.digits.rbegin();

        while (thisIt != digits.rend() || otherIt != other.digits.rend() || carry > 0) {
            int sum = carry;

            if (thisIt != digits.rend()) {
                sum += *thisIt;
                ++thisIt;
            }
            
            if (otherIt != other.digits.rend()) {
                sum += *otherIt;
                ++otherIt;
            }
            
            result.digits.insertFront(sum % 10); 
            carry = sum / 10;                   
        }

        return result;
    }

    // Subtraction operator
    LargeInt operator-(const LargeInt &subtrahend) const {
        // hadnling cases where the result is be negative
        if (*this < subtrahend) {
            cout << "Warning: Result would be negative, returning 0" << endl;
            LargeInt zero;
            zero.digits.insertFront(0);
            return zero;
        }

        LargeInt difference;
        int borrow = 0;
        
        auto minuendIt = digits.rbegin();
        auto subtrahendIt = subtrahend.digits.rbegin();

        while (minuendIt != digits.rend() || subtrahendIt != subtrahend.digits.rend()) {
            int minuendDigit = (minuendIt != digits.rend()) ? *minuendIt : 0;
            int subtrahendDigit = (subtrahendIt != subtrahend.digits.rend()) ? *subtrahendIt : 0;
            
            int diff = minuendDigit - subtrahendDigit - borrow;
            
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            difference.digits.insertFront(diff);
            
            if (minuendIt != digits.rend()) ++minuendIt;
            if (subtrahendIt != subtrahend.digits.rend()) ++subtrahendIt;
        }
        
        // removing leading zeros
        while (difference.digits.getLength() > 1 && *(difference.digits.begin()) == 0) {
            difference.digits.removeFront();
        }

        return difference;
    }
    
    // Increment operator (prefix)
    LargeInt& operator++() {
        LargeInt one("1");
        *this = *this + one;
        return *this; 
    }
    
    // Decrement operator (prefix)
    LargeInt& operator--() {
        LargeInt one("1"); 
        *this = *this - one; 

        // checking result is negative
        if (*this < LargeInt("0")) {
            throw runtime_error("Resulting value is negative, which is not supported.");
        }

        return *this;
    }
    
    // Multiplication operator
    LargeInt operator*(const LargeInt &multiplier) const {
        if (digits.isEmpty() || multiplier.digits.isEmpty()) {
            LargeInt zero;
            zero.digits.insertFront(0);
            return zero;
        }
        
        LargeInt product;
        product.digits.insertFront(0);  // initializing with 0
        
        // using more efficient algorithm for multiplication
        auto multiplierIt = multiplier.digits.rbegin();
        int position = 0;
        
        while (multiplierIt != multiplier.digits.rend()) {
            int currentDigit = *multiplierIt;
            LargeInt partialProduct;
            
            // adding zeros based on position
            for (int i = 0; i < position; i++) {
                partialProduct.digits.insertFront(0);
            }
            
            int carry = 0;
            auto thisIt = digits.rbegin();
            
            while (thisIt != digits.rend() || carry > 0) {
                int thisDigit = (thisIt != digits.rend()) ? *thisIt : 0;
                int result = thisDigit * currentDigit + carry;
                
                partialProduct.digits.insertFront(result % 10);
                carry = result / 10;
                
                if (thisIt != digits.rend()) ++thisIt;
            }
            
            product = product + partialProduct;
            ++multiplierIt;
            ++position;
        }
        
        // removing leading zeros
        while (product.digits.getLength() > 1 && *(product.digits.begin()) == 0) {
            product.digits.removeFront();
        }
        
        return product;
    }
    
    // Division operator
    LargeInt operator/(const LargeInt &divisor) const {
        // checking for division by zero
        if (divisor.digits.getLength() == 1 && *(divisor.digits.begin()) == 0) {
            throw runtime_error("Division by zero is not allowed");
        }
        
        if (*this < divisor) {
            LargeInt zero;
            zero.digits.insertFront(0);
            return zero;
        }
        
        // Long division algorithm
        LargeInt quotient;
        LargeInt remainder;
        
        auto dividendIt = digits.begin();
        
        while (dividendIt != digits.end()) {
            // append current digit to remainder
            remainder.digits.insertFront(*dividendIt);
            
            // removing leading zeros from remainder
            while (remainder.digits.getLength() > 1 && *(remainder.digits.begin()) == 0) {
                remainder.digits.removeFront();
            }
            
            // finding how many times divisor goes into current remainder
            int q = 0;
            LargeInt temp = divisor;
            
            while (remainder >= temp) {
                remainder = remainder - temp;
                q++;
            }
            
            quotient.digits.insertBack(q);
            ++dividendIt;
        }
        
        // removing leading zeros from quotient
        while (quotient.digits.getLength() > 1 && *(quotient.digits.begin()) == 0) {
            quotient.digits.removeFront();
        }
        
        return quotient;
    }
    
    // Modulo operator
    LargeInt operator%(const LargeInt &divisor) const {
        // checking for division by zero
        if (divisor.digits.getLength() == 1 && *(divisor.digits.begin()) == 0) {
            throw runtime_error("Modulo by zero is not allowed");
        }
        
        if (*this < divisor) {
            return *this;
        }
        
        // using same algorithm as division but return remainder
        LargeInt remainder;
        
        auto dividendIt = digits.begin();
        
        while (dividendIt != digits.end()) {
            // append current digit to remainder
            remainder.digits.insertFront(*dividendIt);
            
            // remove leading zeros from remainder
            while (remainder.digits.getLength() > 1 && *(remainder.digits.begin()) == 0) {
                remainder.digits.removeFront();
            }
            
            // finding num times divisor goes into current remainder
            LargeInt temp = divisor;
            
            while (remainder >= temp) {
                remainder = remainder - temp;
            }
            
            ++dividendIt;
        }
        
        // handling case where remainder is 0
        if (remainder.digits.isEmpty()) {
            remainder.digits.insertFront(0);
        }
        
        return remainder;
    }
};

#endif // LARGEINT_H