#include "define.h"

void Stack::Push(Node *n) {
	Elem *p = new Elem(n);
	p->next = s;
	s = p;
}

Node* Stack::Pop() {
	Elem *el = s;
	s = s->next;
	Node *n = el->n;
	el->n = nullptr;
	el->next = nullptr;
	delete el;
	return n;
}
	
bool Stack::Empty() const {
	return s ? false : true;
}
