#include "define.h"


int main() {

	GameTree game;
	while (true) {
		cout << "_________________________" << endl;
		cout << "1. Insert game" << endl << "2. Create Game Tree" << endl << "3. Print Out" << endl << "4. Delete game" << endl << "5. Exit" << endl;
		cout << "-------------------------" << endl;
		cout << "Select an option: ";
		int option;
		cin >> option;
		switch (option) {
		case 1: LoadGame(game); break;
		case 2: MakeTree(game); break;
		case 3: Print(game); break;
		case 4: Delete(game); break;
		case 5: exists(game)?Delete(game):exit(0); exit(0); break;


		default: cout << "Invalid option!" << endl;
			break;
		}
	}


}