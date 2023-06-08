#include <iostream>
#include <string>
using namespace std;
class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};
class CircularLinkedList {
private:
	Node* LAST;
public:
	CircularLinkedList() {
		LAST = NULL;
	}

	void addNode();
	bool search(int rollno, Node** salsabila, Node** novita);
	bool listEmpty();
	bool delNode();
	void traverse();
};
void CircularLinkedList::addNode() { //write your answer here
	Node* newNode = new Node(); //alokasikan memori untuk node baru
	cout << "|Masukan nomor baru :|"; //tetapkan nilai ke bidang data node baru
	cin >> newNode->rollNumber;
	cout << "|Masukan nama baru:|";
	cin >> newNode->name;

	if (listEmpty()) {
		newNode->next = newNode; //buat bidang berikutnya dari titik simpul baru kepenerus last
		LAST = newNode; //buat field dari last ke node baru
	}
	else {
		cout << "Masukan node baru di (d)epan, (t)engah, or (b)elakang :" << endl;
		char position;
		cin >> position;

		if (position == 'd') {
			newNode->next = LAST->next;
			LAST->next = newNode;
		}
		else if (position == 't') {
			int rollno;
			cout << "Masukan node baru setelah nomor:" << endl;
			cin >> rollno;
			
			Node* salsabila,* novita;
			bool found = search(rollno, &salsabila, &novita);

			if (!found) {
				cout << "Tidak Ditemukan" << endl;
				delete newNode;
				return;
			}
			newNode->next = novita->next;
			novita->next = newNode;
		}
		else if (position == 'b') {
			newNode->next = LAST->next;
			LAST->next = newNode;
			LAST = newNode;
		}
		else {
			cout << "Posisi salah" << endl;
			delete newNode;
			return;
		}
		cout << "Berhasil menambah node baru" << endl;
	}

}
bool CircularLinkedList::search(int rollno, Node** salsabila, Node** novita) {
	*salsabila = LAST->next;
	*novita = LAST->next;
	while (*novita != LAST) {
		if (rollno == (*novita)->rollNumber) {
			return true;
		}
		*salsabila = *novita;
		*novita = (*novita)->next;
	}
	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}
bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}
bool CircularLinkedList::delNode() { //write your answer here
	if (listEmpty()) {
		cout << "List Kosong." << endl;
		return false;
	}

	cout << "Masukkan nomor yang ingin dihapus: ";
	int rollno;
	cin >> rollno;

	Node* salsabila, * novita;
	bool found = search(rollno, &salsabila, &novita);

	if (!found) {
		cout << "Nomor Tidak Ditemukan." << endl;
		return false;
	}
	if (novita == LAST) { // Deleting the last node
		if (novita == LAST) { // Only one node in the list
			LAST = NULL;
		}
		else {
			LAST = salsabila;
		}
	}

	salsabila->next = novita->next;
	delete novita;
	cout << "Sukses Menghapus Node." << endl;
	return true;
}

void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* novitaNode = LAST->next;
		while (novitaNode != LAST) {
			cout << novitaNode->rollNumber << " " << novitaNode->name << endl;
			novitaNode = novitaNode->next;
		}
		cout << LAST->rollNumber << " " << LAST->name << endl;
	}
}
int main() {
	CircularLinkedList obj;
	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-5): ";
			char ch;
			cin >> ch;
			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break; 
			}
			case '3': {
				obj.traverse();
				break;
			}
			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}