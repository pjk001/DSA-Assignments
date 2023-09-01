#include "LinkedList.h"

using namespace std;
#include <iostream>


LinkedList::LinkedList() {
	head = nullptr;
}


// copy constructor
LinkedList::LinkedList(const LinkedList & rhs) {

	if (rhs.head == nullptr) {
		return;
	}

	head = new Node;

	head->value = rhs.head->value;
	head->next = rhs.head->next;

	Node* copyList = rhs.head;
	Node* currentList = head;


	while (copyList->next != nullptr) {
		currentList->next = new Node;
		currentList = currentList->next;
		copyList = copyList->next;
		currentList->value = copyList->value;
	}
	currentList->next = nullptr;
}



// Destroys all the dynamically allocated memory
// in the list.
LinkedList::~LinkedList() {
	Node* p = head;

	while (p != nullptr) {
		Node* n = p->next;
		delete p;
		p = n;
	}
}


// assignment operator
const LinkedList& LinkedList::operator=(const LinkedList & rhs) {
	if (&rhs == this) {
		return *this;
	}
	else {
		LinkedList temp(rhs);
		swap(temp);
	}
	return *this;

}



// Inserts val at the front of the list
void LinkedList::insertToFront(const ItemType & val) {
	Node* p = new Node;
	p->value = val;
	p->next = head;

	head = p;

}

// Prints the LinkedList
void LinkedList::printList() const {
	if (head == nullptr) {
		return;
	}

	Node* p = head;

	while (p != nullptr) {
		cout << p->value << " ";

		p = p->next;
	}
	cout << endl;
}


// Sets item to the value at position i in this
// LinkedList and return true, returns false if
// there is no element i
bool LinkedList::get(int i, ItemType & item) const {
	if (head == nullptr) {
		return false;
	}


	Node* p = head;
	for (int k = 1; k <= i; k++) {
		p = p->next;
	}

	if (p == nullptr) {		//make sure that get() function properly returns false if accessing non-existent element
		return false;
	} else {
		item = p->value;
		return true;
	}
}



// Reverses the LinkedList
void LinkedList::reverseList() {
	if (head == nullptr) {
		return;
	}

	Node* temp = NULL;
	Node* temp2 = NULL;

	while (head != nullptr) {
		temp2 = head->next;
		head->next = temp;
		temp = head;
		head = temp2;
	}
	head = temp;

}



// Prints the LinkedList in reverse order
void LinkedList::printReverse() const {
	if (head == nullptr) {
		return;
	}


	int sizeOfList = 0;
	Node* temp = head;

	while (temp != nullptr) {
		sizeOfList++;
		temp = temp->next;
	}

	string* array = new string[sizeOfList];

	Node* p = head;
	for (int i = 0; p != nullptr; i++) {
		array[i] = p->value;
		p = p->next;
	}

	for (int k = sizeOfList - 1; k >= 0; k--) {
		cout << array[k] << " ";
	}
	cout << endl;

	delete[] array;


	/*
	LinkedList reverse(*this);
	reverse.reverseList();

	reverse.printList();
	*/
}


// Appends the values of other onto the end of this
// LinkedList.

//if head is equal to nullptr use assignment operator to copy the values of the other list to the already existing empty list.
void LinkedList::append(const LinkedList & other) {
	if (other.head == nullptr) {
		return;
	}
	else if (head == nullptr) {
		*this = other;
	}
	else if (this == &other) {
		Node* iterateToTail = head;
		Node* iterateForValue = head;

		while (iterateToTail->next != nullptr) {
			iterateToTail = iterateToTail->next;
		}

		Node* node = new Node;
		Node* nodeHead = node;
		node->value = iterateForValue->value;

		iterateForValue = iterateForValue->next;
		while (iterateForValue != nullptr) {
			node->next = new Node;
			node = node->next;
			node->value = iterateForValue->value;

			iterateForValue = iterateForValue->next;
		}
		node->next = nullptr;
		iterateToTail->next = nodeHead;
	}
	else {
		Node* currentList = head;
		Node* otherList = other.head;

		while (currentList->next != nullptr) {
			currentList = currentList->next;
		}

		while (otherList != nullptr) {
			currentList->next = new Node;
			currentList = currentList->next;

			currentList->value = otherList->value;
			otherList = otherList->next;
		}
		currentList->next = nullptr;

	}
}



// Exchange the contents of this LinkedList with the other
// one.
void LinkedList::swap(LinkedList & other) {			//related to assignment operator
	Node* temp = head;
	head = other.head;
	other.head = temp;
}


// Returns the number of items in the Linked List.
int LinkedList::size() const {
	Node* p = head;
	int count = 0;

	while (p != nullptr) {
		count++;
		p = p->next;
	}
	return count;
}
