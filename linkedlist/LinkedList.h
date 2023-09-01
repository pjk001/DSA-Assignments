#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

typedef std::string ItemType;
struct Node {
	ItemType value;
	Node* next;
};
class LinkedList {
private:
	Node* head;
public:

	LinkedList();

	LinkedList(const LinkedList& rhs);

	~LinkedList();

	void insertToFront(const ItemType& val);

	bool get(int i, ItemType& item) const;

	int size() const;

	void printReverse() const;

	void printList() const;

	void reverseList();

	void append(const LinkedList& other);

	void swap(LinkedList& other);

	const LinkedList& operator=(const LinkedList& rhs);

};

#endif
