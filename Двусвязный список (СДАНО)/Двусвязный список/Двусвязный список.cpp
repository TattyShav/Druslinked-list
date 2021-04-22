#include <iostream> // �������� ������������ � ��������� ��������� ����������� ���������� �����-������
#include <clocale> // ����������� ������������ ���� ��� ������� setlocale

using namespace std; // ������������ ���

struct Node {
	int d;
	Node *next; // ��������� �����
	Node *prev; // ���������� �����
};


void add(Node *&begin, int d); // �������� 
Node* find(Node * begin, int i); // ������� 
bool insert(Node * begin, int key, int d); // �������� 
void print(Node * begin); // ������
bool remove(Node *&begin, int key);
void printend(Node *Node);


int main() // ��������� ������ �������
{
	int n, a, b;
	setlocale(LC_ALL, "Russian"); // ��������, ��������������� ������� ������
	Node* begin = nullptr;
	int e;
	do {
		cout << "�������� ��������: " << endl;
		cout << "1. ��������� � ������� ��������������� ������: " << endl;
		cout << "2. ������� ������� �� ������: " << endl;
		cout << "3. ������� ������ � �������� �������: " << endl;
		cout << "4. �������� ������� ����� ��������� �����: " << endl;
		cout << "5. ����� �����: " << endl;
		cin >> e;
		switch (e)
		{
		case 1: { for (int i = 1; i < 6; i++) add(begin, i); // ���������� � ������ ��������� 1, 2, 3, 4 � 5:
			print(begin);
		} 
				cout << '\n';
				break;
		case 2: {
			cout << " ";
			cin >> n;
			cout << '\n';
			if (!remove(begin, n)) cout << "�������� �� ���������" << endl;
			print(begin);
			cout << '\n';
		};
			break;
		case 3: 
		{
			printend(begin);
			cout << '\n';
		};
		break;
		case 4: {
			cout << "������� �����, ����� �������� ������ �������� ������ �����: ";
			cin >> a;
			cout << "������� �����, ������� ������ ��������: ";
			cin >> b;
			insert(begin, a, b);
			print(begin);
			cout << '\n';
		}; break;
		case 5: {
			cout << "������� �����, � �������� ����� ����� ����: ";
			cin >> a;
			cout << find(begin, a);
			cout << '\n';
			print(begin);
			cout << '\n';
		}; break;
		default:cout << "����� ������ ������� �� 1 �� 5 " << endl;
			break;
		}
	}
	while (e != 6);
	system("Pause"); // �������, ������� ��� ������ �����, ����� ���������� ����, ������� �� ����� �����������
	return 0; // ����� ������� �������
}

// ���������� � ����� ������
void add(Node *&begin, int d) { // *& ������ �� ���������
	Node *cur = new Node;
	cur->d = d; // -> ���������� ����� ������ � ������� ��� ���� �������
	cur->next = nullptr; // ���������� �� ����������
	if (!begin) { begin = cur; cur->prev = nullptr; } // begin - ������ ��������, ������� �� ������� ������� � �������, ��� ��� �����
	else {
		Node * temp = begin; // ��������� ������ ����������, ���������� - ���������
		while (temp->next) 
			temp = temp->next;
		temp->next = cur;
		cur->prev = temp;
	}
}

// ����� �������� �� �����
// ���� - ����� ��������
Node * find(Node * begin, int d) {
	Node *cur = begin;
	while (cur) {
		if (cur->d == d)
			break;
		cur = cur->next; 
	}
	return cur;
}

// ������� �������� ����� ���������
bool insert(Node * begin, int key, int d) {
	Node *pkey = find(begin, key);
	if (!pkey) return false;
	Node *cur = new Node;
	cur->d = d;
	// 1 - ������������ ����� ������ ���� � �����������:
	cur->next = pkey->next;
	// 2 - ������������ ����� ������ ���� � ����������:
	cur->prev = pkey;
	// 3 - ������������ ����� ����������� ���� � �����:
	pkey->next = cur;
	// 4 - ������������ ����� ������������ ���� � �����:
	if (cur->next != nullptr) (cur->next)->prev = cur;
	return true;
}

// ����� ������ �� �����
void print(Node * begin) {
	Node* cur = begin;
	while (cur) {
		cout << cur->d << ' ';
		cur = cur->next;
	}
}

// �������� ��������
bool remove(Node *&begin, int key) {
	Node *cur = find(begin, key); // ��������� ������ ��� ��������� ��������� cur, �������� ������������� ��������� ���������� ������� find 
	// (������� ��������� �������� �� �����)
	// ������� find ���������� ��������� �� ������� � ������ ��������� ������ � nullptr, ���� �������� � ����� ������ � ������ ��� 
	// (� ���� ������ ������� ������, � ����������� ����� �� ������� remove �� ��������� false)
	if (!cur) return false;
	// ���� ������� �������� � ������ ������, �� ��������� begin �� ������ ������ ���������� �� ��������� �������
	if (cur == begin) {
		begin = begin->next; // ����� �������� ��������� � ���� next ������� ��������
		begin->prev = nullptr; // ����� ��������� ������� ������ ������ ����� � ����� ���� ��������� �� ���������� ������� nullptr
	}
	else { // ���� �������� ���������� �� �������� ������, ������������ ����������� ���� ����������� � ������������ ���������
		(cur->prev)->next = cur->next;
		if (cur->next != nullptr) (cur->next)->prev = cur->prev; // �������� �������, ��������� ������� ������ �������� ���������� �������� ������
	}
	delete cur; // ������������ ������ ��-��� �������� 
	return true; // ������� ���������� �������� true
	}

// ����� ��������� ������ �� �����
void printend(Node *Node)
{
	if (Node) {
		printend(Node->next);
		cout << (Node->d) << ' '; // ���� ��������� �� ����� ���������, �������
	}
}