#ifndef _DEFINE_H
#define _DEFINE_H

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

struct Node {
	char table[5][5];
	char currPlayer;
	bool end;
	int result;
	Node *parent, *son[5];
	Node(const Node& n);
	Node() = default;
};

class Stack {
	struct Elem {
		Node *n;
		Elem *next;
		Elem(Node *_n, Elem *p = nullptr) : n(_n), next(p) {}
	};
	Elem *s = nullptr;
public:
	void Push(Node *n);
	Node* Pop();
	bool Empty() const;
};

class Queue {
public:
	struct Elem {
		Node *n;
		Elem *next;
		Elem(Node *_n, Elem* p = nullptr) : n(_n), next(p) {}
	};
private:
	Elem * front, *rear;
public:
	Queue();
	void Insert(Node* n);
	bool Empty();
	Node* Delete();
	Elem* Front() const;
	Elem* Rear() const;
	~Queue();
};


class GameTree {
	Node *root;
	char first = 'x';
public:
	GameTree() = default;
	friend void LoadGame(GameTree&);
	friend void MakeTree(GameTree&);
	friend void Delete(GameTree&);
	friend void Print(GameTree&);
	friend bool exists(GameTree&);
};


#endif
