#include "define.h"



Node::Node(const Node& n) {
	for (int i = 0; i < 5; i++) {
		son[i] = new Node(*n.son[i]);
		for (int j = 0; j < 5; j++)
			table[i][j] = n.table[i][j];
	}
	currPlayer = n.currPlayer;
	end = n.end;
	result = n.result;
	parent = n.parent;
}

void AddToCol(Node *n, const char &cur_player, const int &col, const char &first_player) {

	int i, j, x, y;
	int ins_y;

	// Insert coin
	for (i = 4; i >= 0; i--)
		if (n->table[i][col] == 'x') break;
	ins_y = i;
	n->table[ins_y][col] = cur_player;

	// Vertical Check
	x = 1;
	for (i = ins_y; i < 4; i++) {
		if ((n->table[i][col] == n->table[i + 1][col])) x++;
		else x = 1;

		if (x >= 3) {
			n->end = true;
			if (n->table[i][col] == first_player) n->result = 1;
			else n->result = -1;
			break;
		}
	}

	// Horisontal Check
	x = 1;
	for (j = 0; j < 4; j++) {
		if (n->table[ins_y][j] != 'x' && (n->table[ins_y][j] == n->table[ins_y][j + 1])) x++;
		else x = 1;

		if (x >= 3) {
			n->end = true;
			if (n->table[ins_y][j] == first_player) n->result = 1;
			else n->result = -1;
			break;
		}
	}

	// Diagonal Check '\'
	for (y = 3; y >= 0; --y) {
		x = 1;
		for (i = y, j = 0; i < 4; ++i, ++j) {
			if (n->table[i][j] != 'x' && (n->table[i][j] == n->table[i + 1][j + 1])) ++x;
			else x = 1;

			if (x >= 3) {
				n->end = true;
				if (n->table[i][j] == first_player) n->result = 1;
				else n->result = -1;
			}
		}
	}

	for (y = 1; y < 3; ++y) {
		x = 1;
		for (i = 0, j = y; j < 4; ++i, ++j) {
			if (n->table[i][j] != 'x' && (n->table[i][j] == n->table[i + 1][j + 1])) ++x;
			else x = 1;

			if (x >= 3) {
				n->end = true;
				if (n->table[i][j] == first_player) n->result = 1;
				else n->result = -1;
			}
		}
	}

	// Diagonal Check '/'

	for (y = 2; y >= 0; y--) {
		x = 1;
		for (i = y, j = 4; i < 4; i++, j--) {
			if (n->table[i][j] != 'x' && (n->table[i][j] == n->table[i + 1][j - 1])) x++;
			else x = 1;

			if (x >= 3) {
				n->end = true;
				if (n->table[i][j] == first_player) n->result = 1;
				else n->result = -1;
			}
		}
	}

	for (y = 3; y > 1; --y) {
		x = 1;
		for (i = 0, j = y; j >= 1; i++, j--) {
			if (n->table[i][j] != 'x' && (n->table[i][j] == n->table[i + 1][j - 1])) x++;
			else x = 1;

			if (x >= 3) {
				n->end = true;
				if (n->table[i][j] == first_player) n->result = 1;
				else n->result = -1;
			}
		}
	}

	// 0 check
	if (!n->end && n->table[0][0] != 'x' && n->table[0][1] != 'x' && n->table[0][2] != 'x' && n->table[0][3] != 'x' && n->table[0][4] != 'x') {
		n->end = true;
		n->result = 0;
	}
	
}
void CreateSon(Node &n1, Node &n2) {
	n1.currPlayer = (n2.currPlayer == 'r' ? 'b' : 'r');
	n1.end = false;
	n1.parent = &n2;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; n1.table[i][j++] = n2.table[i][j]);
}

bool HasSon(Node *n) {
	for (int i = 0; i < 5; i++) 
		if (n->son[i]) return true;
	return false;
}
int min(Node *n) {
	int min;
	bool first = true;
	for (int i = 0; i < 5; i++) {
		if (n->son[i]) {
			if (first) {
				first = false;
				min = n->son[i]->result;
				continue;
			}
			if (n->son[i]->result < min) min = n->son[i]->result;
		}
	}
	return min;
}
int max(Node *n) {
	int min;
	bool first = true;
	for (int i = 0; i < 5; i++) {
		if (n->son[i]) {
			if (first) {
				first = false;
				min = n->son[i]->result;
				continue;
			}
			if (n->son[i]->result > min) min = n->son[i]->result;
		}
	}
	return min;
}

void MakeTree(GameTree &game) {

	if (game.first == 'x') {
		cout << "Insert game first!" << endl;
		return;
	}

	int Counter = 0;
	Queue q;
	Stack s;
	int i = 0;
	Node *node = game.root;
	q.Insert(node);
	while (!q.Empty()) {

		node = q.Delete();
		s.Push(node);
		Counter++;

		if (!node->end) {
			// Adding children
			for (i = 0; i < 5; i++) {
				if (node->table[0][i] != 'x') {
					node->son[i] = nullptr;
					continue;
				}
				node->son[i] = new Node;
				CreateSon(*node->son[i], *node);
				AddToCol(node->son[i], node->currPlayer, i, game.first);
				q.Insert(node->son[i]);
			}
		}
		else 
			for (i = 0; i < 5; node->son[i++] = nullptr);
		
	}
	cout << "Number of nodes: " << Counter << endl;
	while (!s.Empty()) {
		node = s.Pop();
		if (HasSon(node)) {
			if (node->currPlayer == game.first) node->result = max(node);
			else node->result = min(node);
		}
	}
}
void LoadGame(GameTree &game) {
	cout << "Type in current game state as matrix (no spaces)" << endl;
	cout << "x - empty; r - red; b - blue" << endl;
	cout << "Example of a row: xbxrb" << endl;

	game.root = new Node;
	for (int i = 0; i < 5; game.root->son[i++] = nullptr)
		for (int j = 0; j < 5; j++)
			cin >> game.root->table[i][j];
	game.root->parent = nullptr;
	game.root->end = false;
	
	//srand(time(NULL));
	//game.first = (rand() % 2 ? 'r' : 'b');
	cout << "Who's playing next (r|b): ";
	cin >> game.first;
	game.root->currPlayer = game.first;
	//cout << "First player: " << game.first << endl;
}
bool exists(GameTree &game) {
	return game.first != 'x';
}

void Delete(GameTree &game) {


	if (game.first == 'x') {
		cout << "Insert game first!" << endl;
		return;
	}

	Queue Q;
	Node *node;
	Q.Insert(game.root);
	while (!Q.Empty()) {
		node = Q.Delete();
		for (int i = 0; i < 5; i++) {
			if (!node->son[i]) continue;
			Q.Insert(node->son[i]);
		}
		delete node;
	}


	cout << "Game Tree is deleted!" << endl;
	game.root = nullptr;
	game.first = 'x';
}


void Print(GameTree &game) {
	if (game.first == 'x') {
		cout << "Insert game first!" << endl;
		return;
	}
	bool ready = false;
	for (int i = 0; i < 5; i++)
		if (game.root->son[i]) ready = true;
	if (!ready) {
		cout << "Create Game Tree first!" << endl;
		return;
	}
	Node *node = game.root;
	cout << "___________________________________" << endl << "Initial state: " << endl;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; cout << node->table[x][y++]);
		cout << endl;
	}
	cout << "-------------------------" << endl;
	while (!node->end) {
		for (int i = 0; i < 5; i++) {
			if (node->son[i] && (node->son[i]->result == node->result)) {
				for (int x = 0; x < 5; x++) {
					for (int y = 0; y < 5; cout << node->son[i]->table[x][y++]);
					cout << endl;
				}

				cout << "-------------------------" << endl;
				node = node->son[i];
				break;
			}
		}
	} 
	switch (game.root->result) {
	case -1: cout << "The winner is: " << (('r' == game.first) ? 'b' : 'r') << endl; break;
	case 0: cout << "It's Draw!" << endl; break;
	case 1: cout << "The winner is: " << (('r' == game.first) ? 'r' : 'b') << endl; break;
	}

}

