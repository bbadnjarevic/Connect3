#include "define.h"


	
Queue::Queue() {
	front = rear = nullptr;
}
void Queue::Insert(Node *n) {
	rear = (rear ? rear->next : front) = new Elem(n);
}
bool Queue::Empty() {
	return rear ? false : true;
}
Node* Queue::Delete() {
	if (!front) {
		cout << "UNDERFLOW!" << endl;
		exit(1);
	}
	Node *n = front->n;
	Elem *q = front;
	front = front->next;
	q->n = nullptr;
	q->next = nullptr;
	delete q;
	if (!front) rear = nullptr;
	return n;
}
Queue::Elem* Queue::Front() const { return front; }
Queue::Elem* Queue::Rear() const { return rear; }

Queue::~Queue() {
	while (front) {
		rear = front;
		front = front->next;
		delete rear;
	}
}