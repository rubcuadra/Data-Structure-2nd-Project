/*
   Gilberto Echeverria

   Implementation of the Doubly Linked list
*/

#include <iostream>
#include "DoubleNode.h"

template <class T>
class DoubleLinkedList {
    protected:
        DoubleNode<T> * head = nullptr;
        DoubleNode<T> * tail = nullptr;
        DoubleNode<T> * current = nullptr;
        int length = 0;
    public:
        // Constructors
        DoubleLinkedList () {}
        DoubleLinkedList (DoubleNode<T> * item) { head = item; }
        // Destructor
        ~DoubleLinkedList ();

        // Return the current length of the list
        int getLength() { return this->length; }
        // Get the position in the list of a given item
        int getPositionOf(DoubleNode<T> * item);
        // Get a reference to items in the list
        DoubleNode<T> * getHead() { return this->head; }
        DoubleNode<T> * getTail() { return this->tail; }
        DoubleNode<T> * getCurrent() { return this->current; }
        DoubleNode<T> * getItemAt(int position);
        // Add new items to the list
        void insertOrdered(DoubleNode<T> * new_item);
        void insertOrdered(const T & data);
        void insertAtPosition(DoubleNode<T> * new_item, int position);
        void insertAtPosition(const T & data, int position);
        void insertHead(DoubleNode<T> * new_item);
        void insertHead(const T & data);
        void insertTail(DoubleNode<T> * new_item);
        void insertTail(const T & data);
        // Remove items from the list
        DoubleNode<T> * removeItemAt(int position);
        DoubleNode<T> * removeHead();
        DoubleNode<T> * removeTail();
        void removeNode(DoubleNode<T> item);
        // Search within the list
        bool searchFor(const T & data);
        // Print the contents of a list
        void printList();
        // Remove all nodes
        void clear();
};

// Destructor
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    // Simply call the function to delete all nodes in the list
    this->clear();
}

// Add items to the list
template <class T>
void DoubleLinkedList<T>::insertTail(DoubleNode<T> * new_item)
{
    // Make sure to stop the pointer in the list
    new_item->setNext(nullptr);

    // If the list is empty, this node is the new head
    if (this->head == nullptr)
    {
        this->head = new_item;
        this->tail = new_item;
    }
    else
    {
        this->tail->setNext(new_item);
		new_item->setPrevious(this->tail);
        this->tail = new_item;
    }
    // Increment the size of the list
    this->length++;
}


template <class T>
void DoubleLinkedList<T>::insertTail(const T & data)
{
    DoubleNode<T> * item = new DoubleNode<T>(data);
    this->insertTail(item);
}

template <class T>
void DoubleLinkedList<T>::insertHead(DoubleNode<T> * new_item)
{
    // If the list was empty
    if (this->head == nullptr)
        this->tail = new_item;
    else
    // Make the previous head point to the new one
        this->head->setPrevious(new_item);

    // Make this node point to the previous head
	new_item->setNext(this->head);
    // The node becomes the head of the list
    this->head = new_item;
    // Increment the size of the list
    this->length++;
}

template <class T>
void DoubleLinkedList<T>::insertHead(const T & data)
{
    DoubleNode<T> * item = new DoubleNode<T>(data);
    this->insertHead(item);
}

/*
    Inserts node elements in their corresponding place, in increasing order of exponent
*/
template <class T>
void DoubleLinkedList<T>::insertOrdered(DoubleNode<T> * new_item)
{
    // Special case when the list is empty
    //  or the new item is the smallest
    if ( this->head == nullptr || new_item->getData() < this->head->getData() )
    {
        // Update the tail when necessary
        if (this->head == nullptr)
        {
            this->tail = new_item;
            // Update the current node
            this->current = new_item;
        }
        else
        {
            // Link the previous head to the new item
            this->head->setPrevious(new_item);
        }
        // Make the new item point to the current head
        new_item->setNext(this->head);
        // Update the head
        this->head = new_item;
    }
    // Check if the item should be inserted last
    else if (new_item->getData() >= this->tail->getData())
    {
        this->tail->setNext(new_item);
        new_item->setPrevious(this->tail);
        this->tail = new_item; 
    }
    else
    {
        DoubleNode<T> * previous = this->head;
        DoubleNode<T> * item = static_cast<DoubleNode<T>*>(previous->getNext());
        // Loop to search for the item
        while (item != nullptr && new_item->getData() > item->getData())
        {
            previous = item;
            item = static_cast<DoubleNode<T>*>(item->getNext());
        }
        // Update the connections in the list
        new_item->setPrevious(previous);
        new_item->setNext(item);
        previous->setNext(new_item);
        if (item != nullptr)
            item->setPrevious(new_item);
    }
    // Increase the length of the list
    this->length++;
}

/* 
   Inserts new terms in the polynomial list, in increasing order of exponent
*/
template <class T>
void DoubleLinkedList<T>::insertOrdered(const T & data)
{
    DoubleNode<T> * item = new DoubleNode<T>(data);
    this->insertOrdered(item);
}

template <class T>
void DoubleLinkedList<T>::insertAtPosition(DoubleNode<T> * new_item, int position)
{
    int index = 1;
    DoubleNode<T> * item = this->head;

    // Return nothing for invalid positions
    if (position > this->length || position < 0)
    {
        return;
    }
    // Position is the last item in the list
    if (position == this->length)
    {
        this->tail = new_item;
    }
    // Special case when adding at position 0
    if (position == 0)
    {
        // Make the new item point to the current head
        new_item->setNext(this->head);
        // Make the previous head point to the new one
        this->head->setPrevious(new_item);
        // Update the head
        this->head = new_item;
    }
    else
    {
        // Loop to search for the item
        while (index < position)
        {
            item = item->getNext();
            index++;
        }
        // Update the connections in the list
        new_item->setNext(item->getNext());
        new_item->setPrevious(item);
        item->getNext()->setPrevious(new_item);
        item->setNext(new_item);
    }
    // Increase the length of the list
    this->length++;
}


template <class T>
void DoubleLinkedList<T>::insertAtPosition(const T & data, int position)
{
    DoubleNode<T> * item = new DoubleNode<T>(data);
    this->insertAtPosition(item, position);
}

template <class T>
int DoubleLinkedList<T>::getPositionOf(DoubleNode<T> * search_item)
{
    int index = 0;
    DoubleNode<T> * item = this->head;

    while ( item != nullptr && search_item->getData() != item->getData() )
    {
		item = item->getNext();
        index++;
    }
    if (index == this->length)
        return -1;
    return index;
}

template <class T>
DoubleNode<T> * DoubleLinkedList<T>::getItemAt(int position)
{
    int index = 0;
    DoubleNode<T> * item = this->head;

    // Return nothing for invalid positions
    if (position > this->length || position < 0)
    {
        return nullptr;
    }
    // Loop to search for the item
    while (index < position && item != nullptr)
    {
        item = item->getNext();
        index++;
    }
    return item;
}

template <class T>
DoubleNode<T> * DoubleLinkedList<T>::removeHead()
{
    DoubleNode<T> * item = this->head;

    // Clear the tail also when the head is the only item in the list
    if (this->head == this->tail)
    {
        this->tail = nullptr;
    }
    // Check that the list is not empty
    if (this->head != nullptr)
    {
        // Make the head point to the second item
        this->head = item->getNext();
        // Make the item point to nothing
        item->setNext(nullptr);
        // Clear the previous of the new head
        this->head->setPrevious(nullptr);
        // Reduce the length of the list
        this->length--;
    }

    return item;
}

template <class T>
DoubleNode<T> * DoubleLinkedList<T>::removeTail()
{
    DoubleNode<T> * tail = this->tail;
    DoubleNode<T> * previous;

    // If the list is empty, return nothing
    if (this->head == nullptr)
    {
        return nullptr;
    }
    // If there is only one item in the list, return that one
    if (tail->getPrevious() == nullptr)
    {
        // Mark the list as empty
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
        // Set previous to be the new tail
        previous = tail->getPrevious();
        previous->setNext(nullptr);
        this->tail = previous;
    }
    // Make the item point to nothing
    tail->setPrevious(nullptr);
    // Reduce the length of the list
    this->length--;

    return tail;
}


template <class T>
DoubleNode<T> * DoubleLinkedList<T>::removeItemAt(int position)
{
    int index = 1;
    DoubleNode<T> * previous = this->head;
    DoubleNode<T> * item;

    // Return nothing for invalid positions
    if (position > this->length || position < 0)
    {
        return nullptr;
    }
    // If removing the last item, change the tail
    if (position == this->length-1)
    {
        this->tail = this->tail->getPrevious();
    }
    // Special case when removing the first item
    if (position == 0)
    {
        // Prepare the item to return
        item = previous;
        // Update the head
        this->head = item->getNext();
    }
    else
    {
        // Keep the previous item before the tail
        item = previous->getNext();
        // Loop to search for the item
        while (index < position)
        {
            previous = item;
            item = item->getNext();
            index++;
        }
        // Update the connections in the list
        previous->setNext(item->getNext());
        item->getNext()->setPrevious(previous);
    }
    // Make the item point to nothing
    item->setNext(nullptr);
    item->setPrevious(nullptr);

    // Reduce the length of the list
    this->length--;

    return item;
}

template <class T>
void DoubleLinkedList<T>::removeNode(DoubleNode<T> item)
{
    DoubleNode<T> * list_item = this->head;
    int index = 0;

    if (list_item == nullptr)
        return;
    // Loop to search for the item
    while (list_item->getData() != item.getData())
    {
        list_item = list_item->getNext();
        index++;
    }
    // If the item was found before the end of the list, remove it
    if (index < getLength())
        removeItemAt(index); 
}

/*
Base function to search for an intem in an ordered double linked list
*/
template <class T>
bool DoubleLinkedList<T>::searchFor(const T & search_data)
{
    int count = 0;

    // Special case for empty list
    if (this->head == nullptr)
        return false;
    // Initialize the current pointer if it has not been set
    if (this->current == nullptr)
        this->current = this->head;
    // If we are alrady pointing to the item, we have found it
    if (search_data == this->current->getData())
        return true;
    // Test to identify which way to search
    else if (search_data > this->current->getData())
    {
        std::cout << "Searching forward" << std::endl;
        while (this->current != nullptr)
        {
            if (search_data == this->current->getData())
            {
                std::cout << "Found after " << count << " checks." << std::endl;
                return true;
            }
            this->current = static_cast<DoubleNode<T>*>(this->current->getNext());
            count++;
        }
        if (this->current == nullptr)
        {
            this->current = this->tail;
        }
    }
    else if (search_data < this->current->getData())
    {
        std::cout << "Searching backwards" << std::endl;
        while (this->current != nullptr)
        {
            if (search_data == this->current->getData())
            {
                std::cout << "Found after " << count << " checks." << std::endl;
                return true;
            }
            this->current = this->current->getPrevious();
            count++;
        }
        if (this->current == nullptr)
        {
            this->current = this->head;
        }
    }

    return false;
}

/*
Simple function to print the contents of the list
*/
template <class T>
void DoubleLinkedList<T>::printList()
{
    DoubleNode<T> * item;
    int counter = 0;

    item = this->head;
    while (item != nullptr)
    {
        std::cout << "Item " << counter++ << " = " << item->getData() << std::endl;
        item = static_cast<DoubleNode<T>*>(item->getNext());
    }
}

/*
Empty the list, and free the memory for all nodes
*/
template <class T>
void DoubleLinkedList<T>::clear()
{
    DoubleNode<T> * item;

    item = this->head;
    while (item != nullptr)
    {
        std::cout << "Deleting item " << item->getData() << std::endl;
        this->head = static_cast<DoubleNode<T>*>(item->getNext());
        delete item;
        item = this->head;
    }
    this->length = 0;
    this->head = nullptr;
}
