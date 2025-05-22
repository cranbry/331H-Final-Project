#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList {
    private:
        struct Node{
            T info;
            Node* next;
            Node* prev;

            Node() : next(NULL), prev(NULL) {}
            Node (const T& item) : info(item), next(NULL), prev(NULL){}
        };
        Node* first;
        Node* last;
        int length;

    public:
        // Forward Iterator / traversing the list from first to last 
        class Iterator {
            private:
                Node* current; // pointer to current node
                
            public:
                // constructor
                Iterator(Node* node = NULL) : current(node) {}
                
                // dereferencing operator to get access to the value in the current node
                T& operator*() {
                    return current->info;
                }

                // move to next node and return updated iterator
                Iterator& operator++() {
                    if (current != NULL) {
                        current = current->next;
                    }
                    return *this;
                }

                // move to next node and return original position
                Iterator operator++(int) {
                    Iterator temp = *this; // saving original position
                    if (current != NULL) {
                        current = current->next;
                    }
                    return temp;
                }
                
                // check if two iterators point to same node (using it to test)
                bool operator==(const Iterator& other) const {
                    return current == other.current;
                }

                // check if two iterators point to different nodes (using it to test)
                bool operator!=(const Iterator& other) const {
                    return current != other.current;
                }
        };
        
        // Const Forward Iterator for const objects
        class ConstIterator {
            private:
                const Node* current; // pointer to current node
                
            public:
                // constructor
                ConstIterator(const Node* node = NULL) : current(node) {}
                
                // dereferencing operator to get access to the value in the current node
                const T& operator*() const {
                    return current->info;
                }

                // move to next node and return updated iterator
                ConstIterator& operator++() {
                    if (current != NULL) {
                        current = current->next;
                    }
                    return *this;
                }

                // move to next node and return original position
                ConstIterator operator++(int) {
                    ConstIterator temp = *this; // saving original position
                    if (current != NULL) {
                        current = current->next;
                    }
                    return temp;
                }
                
                // check if two iterators point to same node
                bool operator==(const ConstIterator& other) const {
                    return current == other.current;
                }

                // check if two iterators point to different nodes
                bool operator!=(const ConstIterator& other) const {
                    return current != other.current;
                }
        };
        
        // Reverse Iterator / traversing the list from last to first
        class ReverseIterator {
            private:
                Node* current; // pointer to current node
                
            public:
                // constructor to initialize iterator
                ReverseIterator(Node* node = NULL) : current(node) {}
                
                // dereferencing operator to get access to the value in the current node
                T& operator*() {
                    return current->info;
                }
                
                // decrement operator moves backwards through the list
                ReverseIterator& operator++() {
                    if (current != NULL) {
                        current = current->prev;
                    }
                    return *this; // return reference to this iterator
                }
                
                // move backwards through the list but return orginal position
                ReverseIterator operator++(int) {
                    ReverseIterator temp = *this;
                    if (current != NULL) {
                        current = current->prev;
                    }
                    return temp;
                }

                // check if two iterators point to the same node (using it to test)
                bool operator==(const ReverseIterator& other) const {
                    return current == other.current;
                }

                // check if two iterators point to different nodes (using it to test)
                bool operator!=(const ReverseIterator& other) const {
                    return current != other.current;
                }
        };
        
        // Const Reverse Iterator for const objects
        class ConstReverseIterator {
            private:
                const Node* current; // pointer to current node
                
            public:
                // constructor
                ConstReverseIterator(const Node* node = NULL) : current(node) {}
                
                // dereferencing operator to get access to the value in the current node
                const T& operator*() const {
                    return current->info;
                }

                // move backwards and return updated iterator
                ConstReverseIterator& operator++() {
                    if (current != NULL) {
                        current = current->prev;
                    }
                    return *this;
                }

                // move backwards and return original position
                ConstReverseIterator operator++(int) {
                    ConstReverseIterator temp = *this; // saving original position
                    if (current != NULL) {
                        current = current->prev;
                    }
                    return temp;
                }
                
                // check if two iterators point to same node
                bool operator==(const ConstReverseIterator& other) const {
                    return current == other.current;
                }

                // check if two iterators point to different nodes
                bool operator!=(const ConstReverseIterator& other) const {
                    return current != other.current;
                }
        };
        
        // Iterator methods

        // iterator pointing to the first node
        Iterator begin() {
            return Iterator(first);
        }
        
        // const iterator pointing to the first node
        ConstIterator begin() const {
            return ConstIterator(first);
        }
        
        // iterator pointing to after the last node
        Iterator end() {
            return Iterator(NULL);
        }
        
        // const iterator pointing to after the last node
        ConstIterator end() const {
            return ConstIterator(NULL);
        }
        
        // reverse iterator pointing to last node
        ReverseIterator rbegin() {
            return ReverseIterator(last);
        }
        
        // const reverse iterator pointing to last node
        ConstReverseIterator rbegin() const {
            return ConstReverseIterator(last);
        }
        
        // reverse iterator pointing to after the first node
        ReverseIterator rend() {
            return ReverseIterator(NULL);
        }
        
        // const reverse iterator pointing to after the first node
        ConstReverseIterator rend() const {
            return ConstReverseIterator(NULL);
        }

        // default constructor
        DoublyLinkedList() : first(NULL), last(NULL), length(0) {} // CLOSED default constructor 

        // destructor
        ~DoublyLinkedList() {
            Clear();
        } // CLOSED destructor 

        // copy constructor
        DoublyLinkedList(const DoublyLinkedList& other) : first(NULL), last(NULL), length(0) {
            // copying nodes from other list
            Node* current = other.first;
        
            // going thru and copying each node
            while (current != NULL) {
                insertBack(current->info);
                current = current->next;
            }
        } // CLOSED copy constructor

        // checking if list is empty
        bool isEmpty() const {
            return length == 0;
        } // CLOSED isEmpty()
        
        // returning length of the list
        int getLength() const {
            return length;
        } // CLOSED getLength()

        // overloading assignment operator
        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            if (this != &other) {
                // clearing the current list
                Clear();
                
                // copy nodes from the other list
                Node* current = other.first;
                while (current != NULL) {
                    insertBack(current->info);
                    current = current->next;
                }
            }
            return *this;
        } // CLOSED overloading operator=

        // Remove front element
        void removeFront() {
            if (isEmpty()) return;

            Node* temp = first;
            if (first == last) {
                first = last = NULL;
            } else {
                first = first->next;
                first->prev = NULL;
            }
            delete temp;
            length--;
        }

        // deleting item
        bool deleteItem(const T& item) {
            // list is empty
            if (isEmpty()) {
                cout << "List is empty";
                return false;
            }

            // item is in first node
            if (first->info == item) {
                Node* p = first;

                // if we have only 1 node
                if (first == last) {
                    first = last = NULL;
                } 
                // more than one node
                else {
                    first = first->next;
                    first->prev = NULL;
                }

                delete p;
                length--;
                return true;
            }

            // item is in the last node.
            if (last->info == item) {
                Node* p = last;

                last = last->prev;
                last->next = NULL;

                delete p;
                length--;
                return true;
            }

            // item is in the middle
            Node* p = first->next;
            while (p != NULL && p->info != item) {
                p = p->next;
            }
            // checking if item is found
            if (p != NULL) {
                // skipping the node we want to delete
                p->prev->next = p->next;
                p->next->prev = p->prev;

                delete p;
                length--;
                return true;
            }

            return false; // item not found
        } // CLOSED deleteItem()

        // searching for a given item
        bool search(const T& item) const {
            Node* p = first;
            bool found = false;

            while (p != NULL) {
                if (p->info == item) {
                    found = true;
                    break;
                }
                p = p->next;
            }

            return found;
        } // CLOSED search()

        // Insert at front of list
        void insertFront(const T& item) {
            Node* newNode = new Node(item);

            if (isEmpty()) {
                first = last = newNode;
            } else {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            length++;
        } // CLOSED insertFront()

        // Insert at back of list
        void insertBack(const T& item) {
            Node* newNode = new Node(item);

            if (isEmpty()) {
                first = last = newNode;
            } else {
                last->next = newNode;
                newNode->prev = last;
                last = newNode;
            }
            length++;
        }

        // Clear the entire list
        void Clear() {
            Node* p = first;
            Node* q;         // temp save address of next node

            while (p != NULL) {
                q = p->next;
                delete p;
                p = q;
            }

            first = last = NULL;
            length = 0;
        } // CLOSED Clear()

        // Print the list contents
        void print() const {
            Node* p = first;
            if (isEmpty()) {
                cout << "List is empty";
            } else {
                cout << "List contains: ";
                while (p != NULL) {
                    cout << p->info << " ";
                    p = p->next;
                }
                cout << endl;
            }
        }
};

#endif