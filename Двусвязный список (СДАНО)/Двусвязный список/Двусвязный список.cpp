#include <iostream> // Описания используемых в программе элементов стандартной библиотеки ввода-вывода
#include <clocale> // Стандартный заголовочный файл для функции setlocale

using namespace std; // Пространство имён

struct Node {
	int d;
	Node *next; // Следующее число
	Node *prev; // Предыдущее число
};


void add(Node *&begin, int d); // Создание 
Node* find(Node * begin, int i); // Первого 
bool insert(Node * begin, int key, int d); // Элемента 
void print(Node * begin); // Списка
bool remove(Node *&begin, int key);
void printend(Node *Node);


int main() // Заголовок гавной функции
{
	int n, a, b;
	setlocale(LC_ALL, "Russian"); // Оператор, устанавливающий русскую локаль
	Node* begin = nullptr;
	int e;
	do {
		cout << "Выберите действие: " << endl;
		cout << "1. Заполнить и вывести двунаправленный список: " << endl;
		cout << "2. Удалить элемент из списка: " << endl;
		cout << "3. Вывести список в обратном порядке: " << endl;
		cout << "4. Вставить элемент после заданного числа: " << endl;
		cout << "5. Поиск ключа: " << endl;
		cin >> e;
		switch (e)
		{
		case 1: { for (int i = 1; i < 6; i++) add(begin, i); // Добавление в список элементов 1, 2, 3, 4 и 5:
			print(begin);
		} 
				cout << '\n';
				break;
		case 2: {
			cout << " ";
			cin >> n;
			cout << '\n';
			if (!remove(begin, n)) cout << "Удаление не выполнено" << endl;
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
			cout << "ВВедите число, после которого хотите вставить другое число: ";
			cin >> a;
			cout << "ВВедите число, которое хотите вставить: ";
			cin >> b;
			insert(begin, a, b);
			print(begin);
			cout << '\n';
		}; break;
		case 5: {
			cout << "ВВедите число, у которого нужно найти ключ: ";
			cin >> a;
			cout << find(begin, a);
			cout << '\n';
			print(begin);
			cout << '\n';
		}; break;
		default:cout << "Нужно нажать клавишу от 1 до 5 " << endl;
			break;
		}
	}
	while (e != 6);
	system("Pause"); // Команда, которая ждёт любого ввода, чтобы консольное окно, которое не сразу закрывалось
	return 0; // Конец текущей функции
}

// Добавление в конец списка
void add(Node *&begin, int d) { // *& ссылка на указатель
	Node *cur = new Node;
	cur->d = d; // -> показывает часть ячейки в которую нам надо попасть
	cur->next = nullptr; // Следующего не существует
	if (!begin) { begin = cur; cur->prev = nullptr; } // begin - первое значение, доходит до первого знаения и говорит, что там пусто
	else {
		Node * temp = begin; // следующее делает предыдущим, предыдущее - следующим
		while (temp->next) 
			temp = temp->next;
		temp->next = cur;
		cur->prev = temp;
	}
}

// Поиск элемента по ключу
// Ключ - номер элемента
Node * find(Node * begin, int d) {
	Node *cur = begin;
	while (cur) {
		if (cur->d == d)
			break;
		cur = cur->next; 
	}
	return cur;
}

// Вставка элемента после заданного
bool insert(Node * begin, int key, int d) {
	Node *pkey = find(begin, key);
	if (!pkey) return false;
	Node *cur = new Node;
	cur->d = d;
	// 1 - установление связи нового узла с последующим:
	cur->next = pkey->next;
	// 2 - установление связи нового узла с предыдущим:
	cur->prev = pkey;
	// 3 - установление связи предыдущего узла с новым:
	pkey->next = cur;
	// 4 - установление связи последующего узла с новым:
	if (cur->next != nullptr) (cur->next)->prev = cur;
	return true;
}

// Вывод списка на экран
void print(Node * begin) {
	Node* cur = begin;
	while (cur) {
		cout << cur->d << ' ';
		cur = cur->next;
	}
}

// Удаление элемента
bool remove(Node *&begin, int key) {
	Node *cur = find(begin, key); // Выделение памяти под локальный указатель cur, которому присваивается результат выполнения функции find 
	// (функция находения элемента по ключу)
	// Функция find возвращает указатель на элемент в случае успешного поиска и nullptr, если элемента с таким ключом в списке нет 
	// (в этом случае удалять нечего, и выполняется выход из функции remove со значением false)
	if (!cur) return false;
	// Если элемент находитс в начале списка, то указатель begin на начало списка сдвигается на следующий элемент
	if (cur == begin) {
		begin = begin->next; // Адрес которого находится в поле next первого элемента
		begin->prev = nullptr; // Новый начальный элемент списка должен иметь в своем поле указателя на предыдущий элемент nullptr
	}
	else { // Если удаление происходит из середины списка, обеспечиваем двусторонюю свзь предыдущего и последующего элементов
		(cur->prev)->next = cur->next;
		if (cur->next != nullptr) (cur->next)->prev = cur->prev; // Проверка условия, обработка особого случая удаления последнего элемента списка
	}
	delete cur; // Освобождение памяти из-под элемента 
	return true; // Функция возвращает значение true
	}

// Вывод обратного списка на экран
void printend(Node *Node)
{
	if (Node) {
		printend(Node->next);
		cout << (Node->d) << ' '; // Пока последний не будет следующим, выводим
	}
}