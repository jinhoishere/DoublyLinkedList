// CS 3100 project 3 by Jinho Nam
// There must be "sequence.h" file in the same directory to run this file.
// "test.cpp" is the main file.

#include "sequence.h"
#include <iostream>

// Default Constructor
Sequence::Sequence(size_type sz)
{
    // assign local variable sz to numElts
    numElts = sz;
    // If sz is 0,
    // Set head and tail pointers to nullptr
    if (sz == 0)    {
        head = nullptr;
        tail = nullptr;
    }
    // Else sz is NOT 0
    else {
        // Create a new node that will be the head
        head = new SequenceNode();
        tail = head;

        // Create a new node at the last which will be the tail
        for (int i = 0; i < (sz - 1); i++) {
            tail -> next = new SequenceNode();
            tail -> next -> prev = tail; // set a new prev pointer
            tail = tail -> next; // set a new tail
        }
    }
}

// Copy Constructor
Sequence::Sequence(const Sequence& s)
{
    // Set private fields to default like default constructor
    head = nullptr;
    tail = nullptr;
    numElts = 0;

    SequenceNode *current = s.head;
    // While loop to copy nodes one by one
    while (current != nullptr) {
        this->push_back(current -> elt);
        current = current -> next;
    }
}

// Destructor
Sequence::~Sequence()
{
    SequenceNode * current = head;

    // Delete current node until current is nullptr
    while (current != nullptr) {
        SequenceNode *killThisNext = (current -> next);
        delete current;
        current = killThisNext;
        numElts -= 1;   
    }
}

// -------------------------------------------------------------
// Sequence::opearator=: create a new sequence that is exactly
//                       same as the parameter one.
// Returns: *this (Sequence&)
// Parameters:
//       s (const Sequence&)
// -------------------------------------------------------------
Sequence& Sequence::operator=(const Sequence& s)
{
    // Clear the current sequence first
    clear();

    // Copy the &s to the current sequence
    SequenceNode *current = s.head;
        // While loop to go through the sequence
        while (current != nullptr) {
            // Add a new node at the end of the sequence
            this->push_back(current -> elt);
            current = current -> next;
        }
    return *this;
}

// -------------------------------------------------------------
// Sequence::operator[]: return an item with the corresponding 
//                       position(index) in the sequence
// Returns: item (value_type&)
// Parameters: 
//          position (size_type)
// -------------------------------------------------------------
Sequence::value_type& Sequence::operator[](size_type position)
{
    SequenceNode *current = head;
    // for-loop to move to the node that its index is position-1.
    for (int i = 0; i < position; i++) {
        // If the position is out of sequence boundary
        if (current == nullptr) {
            throw exception();
        }
        current = current -> next;
    }

    // If current node is not valid, throw exception
    if (current == nullptr) {
        throw exception();
    }

    // Else return a reference to item at index position of the sequence
    else {
        value_type& selectedItem = current -> elt;
        return selectedItem;
    }
}
// -------------------------------------------------------------
// Sequence::push_back: add a new node with the given value 
//                      to the end of the sequence
// Returns: -
// Parameters:
//          value (const value_tye&)
// -------------------------------------------------------------
void Sequence::push_back(const value_type& value)
{
    // If the sequence is empty
    if (!head) {
        head = new SequenceNode(value);
        tail = head;
        numElts += 1;
    }
    // Else the sequence is NOT empty
    else {
        // create a new node after the tail
        tail -> next = new SequenceNode(value);
        // set a prev pointer from the new node
        tail -> next -> prev = tail;
        // change the tail to the new node
        tail = tail -> next;
        numElts += 1;
    }
}

// -------------------------------------------------------------
// Sequence::pop_back: remove the last node of the sequence
// Returns: -
// Paramters: -
// -------------------------------------------------------------
void Sequence::pop_back()
{
    // If the sequence is empty
    if (!head) {
        throw exception();
    }
    // Else the sequence is NOT empty
    else {
        // If the sequence has only one node
        if (head == tail) {
            SequenceNode *killThis = tail;
            delete killThis;
            // Set the pointers null to prevent memory leak
            tail = nullptr;
            head = nullptr;
            numElts -= 1;
        }
        // If the sequence has more than one node
        else {
            SequenceNode *killThis = tail;
            // Set a new tail pointer to the second last node
            tail = tail -> prev;
            tail -> next = nullptr;
            // After setting pointers, kill the node
            delete killThis;
            numElts -= 1;
        }
    }
}
// -------------------------------------------------------------
// Sequence::insert: add a new node with the given value
//                   at the given position(index) of the sequence
// Returns: -
// Parameters:
//          position (size_type)
//          value (value_type)
// -------------------------------------------------------------
void Sequence::insert(size_type position, value_type value)
{
    // If the given position is invalid index
    if (position < 0 || position >= numElts) {
        throw exception();
    }
    // Else the given position is valid index
    else {
        // If the sequence is empty, a "insertThis" node will be head and tail
        if (numElts == 0) {
            SequenceNode *insertThis = new SequenceNode(value);
            head == insertThis;
            tail == insertThis;
            numElts += 1;
        }

        // Else the sequence is NOT empty
        else {
            // If new node is the first node
            if (position == 0) {
                // assign a new value to a new node
                SequenceNode *insertThis = new SequenceNode(value);

                // create a "current" node which will be "insertThis -> next" node
                SequenceNode *current = head;

                // the new node will be the head
                head = nullptr;
                head = insertThis;

                // set "insertThis -> next" as "current" node
                insertThis -> next = current;

                // set "current -> prev" as "insertThis" node
                current -> prev = insertThis;
                numElts += 1;
            }

            // Else the new node will be NOT the first node,
            // the new node will be inserted between "previous" and "current" node
            else {    
                // assign a new value to a new node
                SequenceNode *insertThis = new SequenceNode(value);

                // move on to the target index
                SequenceNode *current = head;
                for (int i = 0; i < position; i++) {
                    current = current -> next;
                }

                // "previous" is a node which comes right before "insertThis" node
                SequenceNode *previous = current -> prev;

                // set prev and next pointers to null before assigning them to the new addresses
                previous -> next = nullptr;
                current -> prev = nullptr;

                // set the new prev and next pointers to 
                // each other, "previous" node and "insertThis" node.
                previous -> next = insertThis;
                insertThis -> prev = previous;
                insertThis -> next = current;
                current -> prev = insertThis;
                numElts += 1;
            }
        }  
    }
}

// -------------------------------------------------------------
// const Sequence::front(): returns the first item in the sequence
// Returns: firstItem (value_type&)
// Parameters: -
// -------------------------------------------------------------
const Sequence::value_type& Sequence::front() const
{
    // If the size of sequence is greater than zero,
    // return a reference to the first item in the sequence
    if (size() > 0) {
        SequenceNode *firstNode = head;
        value_type& firstItem = firstNode -> elt;
        return firstItem;
        
    }
    // else the sequence is empty, throws an exception
    else {
        throw exception();
    }
}

// -------------------------------------------------------------
// const Sequence::back: returns the last item in the sequence
// Returns: lastItem (value_type&)
// Parameters: -
// -------------------------------------------------------------
const Sequence::value_type& Sequence::back() const
{
    // If the size of sequence is greater than zero,
    // return a reference to the last item in the sequence
    if (numElts > 0) {
        SequenceNode *lastNode = tail;
        value_type& lastItem = lastNode -> elt;
        return lastItem;
    }
    // Else throws an exception
    else {
        throw exception();
    }
}

// -------------------------------------------------------------
// Sequence::empty: check if the sequence is empty or not
// Returns: true (bool)
//          false (bool)
// Parameters: -
// -------------------------------------------------------------
bool Sequence::empty() const
{
    // Returns true if the sequence is empty
    if (numElts == 0) {
        return true;
    }
    // Returns false if the sequnce is NOT empty
    else {
        return false;
    }
}

// -------------------------------------------------------------
// Sequence::size(): return numElts of the sequence
// Returns: numElts (size_type)
// Parameters: -
// -------------------------------------------------------------
Sequence::size_type Sequence::size() const
{
    return numElts;
}

// -------------------------------------------------------------
// Sequence::clear: delete all items in the sequence 
//                  and release the memory
// Returns: -
// Parameters: -
// -------------------------------------------------------------
void Sequence::clear()
{
    SequenceNode * current = head;
    // while loop to delete nodes   
    while (current != nullptr) {
        SequenceNode *nextKillThis = (current -> next);
        // cout << "Deleting " << (current -> elt) << endl;
        delete current;
        current = nextKillThis;
        numElts -= 1;   
    }
    // Set tail and head to nullptr like default constructor
    tail = nullptr;
    head = nullptr;
}

// -------------------------------------------------------------
// Sequence::erase: delete nodes of the sequence
//                  from (position) to (position + count - 1)
// Returns: -
// Parameters: 
//          positions (size_type)
//          count (size_type)
// -------------------------------------------------------------
void Sequence::erase(size_type position, size_type count)
{
    // If both given position and count are invalid
    if ((position < 0) || ((position + count) > numElts)) {
        throw exception();
    }
    // Else the position and count are valid
    else { 
        // Move "position" times to get the "startNode"
        SequenceNode *startNode = head;
        for (int i = 0; i < position; i++) {
            startNode = startNode -> next;
        }
        // // Move "count - 1" times to get the "endNode"
        SequenceNode *endNode = startNode;
        for (int i = 0; i < (count - 1); i++) {
            endNode = endNode -> next;
        }

        // If there's only one node in the sequence
        if (head == tail) {
            clear();
            return;
        }
        // Else there's more than one node in the sequence
        else {
            // If startNode is head and endNode is tail,
            // delete all nodes in the sequence
            if (startNode == head && endNode == tail) {
                clear();
                return;
            }

            // Else if startNode is head,
            // Set a new head and delete startNode to endNode
            else if (startNode == head) {
                head = endNode -> next;
                head -> prev = nullptr; 
            }

            // Else if endNode is tail
            // Set a new tail and delete startNode to endNode 
            else if (endNode == tail) {
                tail = startNode -> prev;
                tail -> next = nullptr;
            }
            
            // Else all of other cases,
            // Set the next and prev pointers between
            // startNode -> prev and endNode -> next
            else {
                startNode -> prev -> next = endNode -> next;
                endNode -> next -> prev = startNode -> prev;
            }

            // for-loop to delete from startNode to endNode
            SequenceNode *killThis = startNode;
            for (int i = 0; i < count; i++) {
                SequenceNode *nextKillThis = killThis -> next;
                delete killThis;
                killThis = nextKillThis;
                numElts -= 1;
            }         
        }
    }
}

// -------------------------------------------------------------
// Sequence::print: display all items in the sequence
// Returns: -
// Parameters: os (ostream&) 
// -------------------------------------------------------------
void Sequence::print(ostream& os) const
{
    os << "<";
    SequenceNode *current = head;
    // while loop to print item within each node
    while (current) {
        os << (current -> elt);
        current = current -> next;
        if (current) {
            os << ", ";
        }
        else {
            break;
        }
    }
    os << ">" << endl;
}

// Don't modify, do the output in the print() method
ostream& operator<<(ostream& os, const Sequence& s)
{
    s.print(os);
    return os;
}

