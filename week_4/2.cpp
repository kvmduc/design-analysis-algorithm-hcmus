#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;


string rotateleft(string bin) {
	char temp = bin[0];
	string result = "";
	for (int i = 1; i < bin.size(); i++) {
		result += bin[i];
	}
	result += temp;
	return result;
}

struct Node {
	int index;
	int flag = 1;
	Node* next;
};

struct List {
	Node* head;
	Node* tail;
};

void createlist(List& list) {
	list.head = list.tail = NULL;
}

Node* createnode(int x) {
	Node* p = new Node;
	if (p != NULL) {
		p->index = x;
		p->next = NULL;
	}
	return p;
}

void insert(List & list, int x) {
	Node * p = createnode(x);
	if (p == NULL) {
		return;
	}
	if (list.head == NULL && list.tail == NULL) {
		list.head = list.tail = p;
	}
	else {
		//list.head->prev = p;
		//p->next = list.head;
		//list.head = p;
		list.tail->next = p;
		list.tail = p;
	}
}

void lastmember(string binary) {
	cout << endl << std::bitset<32>(binary).to_ulong();
}

void Josephus(unsigned int n) {
	string binary = bitset<32>(n).to_string();
	binary = binary.substr(binary.find_first_not_of("0"));
	binary = rotateleft(binary);
	
	List list;
	createlist(list);
	for (int i = 1; i <= n; i++) {
		insert(list, i);
	}
	list.tail->next = list.head;

	for (Node* temp1 = list.head;; temp1 = temp1->next) {
		if (temp1->flag == 0) {
			continue;
		}
		for (Node* temp2 = temp1->next;; temp2 = temp2->next) {
			if (temp2->index == temp1->index) {
				lastmember(binary);
				return;
			}
			if (temp2->flag == 0) {
				continue;
			}
			else if(temp2->flag == 1) {
				cout << temp2->index << " ";
				temp1->next = temp2->next;
				break;
			}
		}
	}

	
}


void main() {
	ifstream input("input_2.txt");
	unsigned int n;
	input >> n;
	Josephus(n);
}