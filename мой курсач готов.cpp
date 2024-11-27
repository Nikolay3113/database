#include <algorithm> // for transform
#include <cctype>    // for toupper
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iomanip>
using namespace std;

//Структура, представляющая информацию об игроке
struct Player {
	string firstName;
	string lastName;
	string number;
	string position;
	string height;
	string weight;
};

// Структура узла двусвязного списка
struct Node {
	Player data;
	Node* next;
	Node* prev;
};

// Структура двусвязного списка игроков
struct DoublyLinkedList {
	Node* head;

	DoublyLinkedList() {
		head = nullptr;
	}

	bool isValidNumber(const string& number) {
		if (number.empty()) {
			return false;
		}
		if (number.length() > 2) {
			return false;
		}
		for (char c : number) {
			if (c < '0' || c > '9') {
				return false;
			}
		}

		return true;
	}


	// Функция для проверки корректности роста
	bool isValidHeight(const string& height) {
  if (height.empty()) {
    return false;
  }

  for (char c : height) {
    if (c < '0' || c > '9') {
      return false;
    }
  }

  int heightValue = 0;
  for (char c : height) {
    heightValue = heightValue * 10 + (c - '0');
  }

  return (heightValue >= 160 && heightValue <= 220);
}


	bool isValidWeight(const string& weight) {
		if (weight.empty()) {
			return false;
		}

		int weightValue = 0;
		for (char c : weight) {
			if (c < '0' || c > '9') {
				return false;
			}
			weightValue = weightValue * 10 + (c - '0');
		}

		return (weightValue >= 50 && weightValue <= 120);
	}

	bool isValidName(const string& name) {
		if (name.length() > 15) {
			return false;
		}

		for (char ch : name) {
			if (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z')) {
				return false;
			}
		}

		return true;
	}

	bool isValidPosition(const string& position) {
		if (position.length() > 3) {
			return false;
		}

		for (char ch : position) {
			if (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z')) {
				return false;
			}
		}

		return true;
	}

	// Функция для создания нового игрока
	void createPlayer(Player& player) {
		string input;
		string temp;
	type_firstName:
		cout << "Введите имя игрока: ";
		cin >> input;
		temp = "";
		while (!isValidName(input)) {
			cout << "Некорректное имя. Пожалуйста, введите имя заново: ";
			goto type_firstName;
		}
		for (char ch : input)
		{
			ch = tolower(ch);
			temp += ch;
		}
		input = temp;
		input[0] = toupper(input[0]);
		player.firstName = input;


	type_lastName:
		cout << "Введите фамилию игрока: ";
		cin.ignore();
		cin >> input;
		temp = "";
		if (!isValidName(input)) {
			cout << "Некорректная фамилия. Пожалуйста, введите фамилию заново: ";
			goto type_lastName;
		}
		for (char ch : input)
		{
			ch = tolower(ch);
			temp += ch;
		}
		input = temp;
		input[0] = toupper(input[0]);
		player.lastName = input;

	type_number:
		cout << "Введите номер игрока: ";
		cin.ignore();
		cin >> input;
		if (!isValidNumber(input)) {
			cout << "Некорректный номер. Пожалуйста, введите номер заново: ";
			goto type_number;
		}
		player.number = input;
	type_position:
		cout << "Введите позицию игрока: ";
		cin.ignore();
		cin >> input;
		temp = "";
		if (!isValidPosition(input)) {
			cout << "Некорректная позиция. Пожалуйста, введите позицию заново: ";
			goto type_position;
		}
		for (char ch : input)
		{
			ch = toupper(ch);
			temp += ch;
		}
		player.position = temp;

		cout << "Введите рост игрока (в см): ";
		cin.ignore();
		cin >> player.height;
		while (!isValidHeight(player.height)) {
			cout << "Некорректный рост. Рост должен быть от 160 до 220 см. Пожалуйста, введите рост заново: ";
			cin >> player.height;
		}

		cout << "Введите вес игрока (в кг): ";
		cin.ignore();
		cin >> player.weight;
		while (!isValidWeight(player.weight)) {
			cout << "Некорректный вес. Вес должен быть от 50 до 120 кг. Пожалуйста, введите вес заново: ";
			cin >> player.weight;
		}
	}

	// Функция для создания списка игроков
	void createList() {
		int count = 0;
		char ch;
		cout << "Введите количество записей: ";
		string num;
		bool validinput = false;

		while (!validinput) {
			cin >> num;
			bool invalidChar = false;

			for (int i = 0; i < num.size(); i++) {
				ch = num[i];
				if (ch < '0' || ch > '9') {
					invalidChar = true;
					break;
				}
			}

			if (invalidChar || num.empty()) {
				cout << "Некорректный ввод! Пожалуйста, введите число: ";
			}
			else {
				validinput = true;
			}
		}

		cin.ignore();

		for (int i = 0; i < stoi(num); ++i) {
			// start Player creation
			Player entry;
			createPlayer(entry);
			// new player in "entry"

			Node* newNode = new Node();
			newNode->data = entry;
			if (head == nullptr) {
				head = newNode;
				head->next = nullptr;
				head->prev = nullptr;
			}
			else {
				Node* curr = head;
				while (curr->next != nullptr) {
					curr = curr->next;
				}
				curr->next = newNode;
				newNode->prev = curr;
				newNode->next = nullptr;
			}
		}
	}

	// Функция для печати списка игроков
	void printList() {
		if (head == nullptr) {
			cout << "Список пуст" << endl;
			return;
		}

		Node* curr = head;
		while (curr != nullptr) {


			cout << "Имя: " << curr->data.firstName << endl;
			cout << "Фамилия: " << curr->data.lastName << endl;
			cout << "Номер: " << curr->data.number << endl;
			cout << "Позиция: " << curr->data.position << endl;
			cout << "Рост: " << curr->data.height << " см" << endl;
			cout << "Вес: " << curr->data.weight << " кг" << endl;
			cout << endl;
			curr = curr->next;
		}
	}

	// Функция для удаления списка игроков
	void deleteList() {
		if (head == nullptr) {
			cout << "Список пуст" << endl;
			return;
		}

		Node* curr = head;
		Node* next;
		while (curr != nullptr) {
			next = curr->next;
			delete curr;
			curr = next;
		}

		head = nullptr;
		cout << "Список удален." << endl;
	}

	void addAfter(Player data, int index) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно добавить элемент." << endl;
			return;
		}

		Node* curr = head;
		int count = 1;
		while (curr != nullptr && count < index) {
			curr = curr->next;
			count++;
		}

		if (curr == nullptr) {
			cout << "Нет элемента с таким номером." << endl;
			return;
	
		}

		Player newPlayer;
		createPlayer(newPlayer);

		Node* newNode = new Node();
		newNode->data = newPlayer;
		newNode->next = curr->next;
		newNode->prev = curr;
		if (curr->next != nullptr) {
			curr->next->prev = newNode;
		}
		curr->next = newNode;
	}

	void deleteAtIndex(int index) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно удалить элемент." << endl;
			return;
		}

		Node* curr = head;
		int count = 1;
		while (curr != nullptr && count < index) {
			curr = curr->next;
			count++;
		}

		if (curr == head && curr->next == nullptr) {
			cout << "Невозможно удалить единственный элемент." << endl;
			return;
		}

		if (curr == nullptr || curr->next == nullptr) {
			cout << "Нет элемента с таким номером." << endl;
			return;
		}

		Node* nodeToDelete = curr->next;
		curr->next = nodeToDelete->next;
		if (nodeToDelete->next != nullptr) {
			nodeToDelete->next->prev = curr;
		}

		delete nodeToDelete;
	}

	void bubbleSortByHeight() {
		if (head == nullptr) {
			cout << "Список пуст" << endl;
			return;
		}

		bool swapped;
		do {
			Node* ptr = head;
			swapped = false;

			do {
				if (stoi(ptr->data.height) > stoi(ptr->next->data.height)) {
					Player temp = ptr->data;
					ptr->data = ptr->next->data;
					ptr->next->data = temp;
					swapped = true;
				}
				ptr = ptr->next;
			} while (ptr->next != nullptr);
		} while (swapped);

		cout << "Список отсортирован методом пузырька по росту." << endl;
	}

	void bubbleSortByName() {
		if (head == nullptr) {
			cout << "Список пуст" << endl;
			return;
		}

		bool swapped;
		do {
			Node* ptr = head;
			swapped = false;

			do {
				if (ptr->data.firstName > ptr->next->data.firstName) {
					Player temp = ptr->data;
					ptr->data = ptr->next->data;
					ptr->next->data = temp;
					swapped = true;
				}
				ptr = ptr->next;
			} while (ptr->next != nullptr);
		} while (swapped);

		cout << "Список отсортирован методом пузырька по имени." << endl;
	}

	void bubbleSortByLastName() {
		if (head == nullptr) {
			cout << "Список пуст" << endl;
			return;
		}

		bool swapped;
		do {
			Node* ptr = head;
			swapped = false;

			do {
				if (ptr->data.lastName > ptr->next->data.lastName) {
					Player temp = ptr->data;
					ptr->data = ptr->next->data;
					ptr->next->data = temp;
					swapped = true;
				}
				ptr = ptr->next;
			} while (ptr->next != nullptr);
		} while (swapped);

		cout << "Список отсортирован методом пузырька по фамилии." << endl;
	}

	void bubbleSortByNumber() {
		if (head == nullptr) {
			cout << "Список пуст" << endl;
			return;
		}

		bool swapped;
		do {
			Node* ptr = head;
			swapped = false;

			do {
				if (stoi(ptr->data.number) > stoi(ptr->next->data.number)) {
					Player temp = ptr->data;
					ptr->data = ptr->next->data;
					ptr->next->data = temp;
					swapped = true;
				}
				ptr = ptr->next;
			} while (ptr->next != nullptr);
		} while (swapped);

		cout << "Список отсортирован методом пузырька по номеру." << endl;
	}

	Node* partition(Node* l, Node* h) {
		int x = stoi(h->data.weight);
		Node* i = l->prev;

		for (Node* j = l; j != h; j = j->next) {
			if (stoi(j->data.weight) <= x) {
				i = (i == nullptr) ? l : i->next;
				swap(i->data, j->data);
			}
		}
		i = (i == nullptr) ? l : i->next;
		swap(i->data, h->data);
		return i;
	}

	void _quickSort(Node* l, Node* h) {
		if (h != nullptr && l != h && l != h->next) {
			Node* p = partition(l, h);
			_quickSort(l, p->prev);
			_quickSort(p->next, h);
		}
	}

	void quickSortByWeight() {
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		_quickSort(head, temp);
	}

	void swapPlayers(int index1, int index2) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно поменять местами игроков." << endl;
			return;
		}

		Node* curr1 = head;
		Node* curr2 = head;
		int count = 1;
		while (curr1 != nullptr && count < index1) {
			curr1 = curr1->next;
			count++;
		}
		count = 1;
		while (curr2 != nullptr && count < index2) {
			curr2 = curr2->next;
			count++;
		}

		if (curr1 == nullptr || curr2 == nullptr) {
			cout << "Некорректные индексы. Невозможно поменять местами игроков." << endl;
			return;
		}

		swap(curr1->data, curr2->data);
		cout << "Игроки успешно поменяли местами." << endl;
	}

	void searchByHeight(int height) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно найти игрока." << endl;
		}

		Node* curr = head;
		while (curr != nullptr) {
			if (stoi(curr->data.height) == height) {
				cout << "Игрок найден:" << endl;
				cout << "Имя: " << curr->data.firstName << endl;
				cout << "Фамилия: " << curr->data.lastName << endl;
				cout << "Номер: " << curr->data.number << endl;
				cout << "Позиция: " << curr->data.position << endl;
				cout << "Рост: " << curr->data.height << " см" << endl;
				cout << "Вес: " << curr->data.weight << " кг" << endl;
				cout << endl;
			}
			curr = curr->next;
		}

		cout << "Игрок с ростом " << height << " не найден." << endl;
	}

	void searchByWeight(int weight) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно найти игрока." << endl;
		}

		Node* curr = head;
		while (curr != nullptr) {
			if (stoi(curr->data.weight) == weight) {
				cout << "Игрок найден:" << endl;
				cout << "Имя: " << curr->data.firstName << endl;
				cout << "Фамилия: " << curr->data.lastName << endl;
				cout << "Номер: " << curr->data.number << endl;
				cout << "Позиция: " << curr->data.position << endl;
				cout << "Рост: " << curr->data.height << " см" << endl;
				cout << "Вес: " << curr->data.weight << " кг" << endl;
				cout << endl;
			}
			curr = curr->next;
		}

		cout << "Игрок с ростом: " << weight << " не найден." << endl;
	}

	void searchByfirstName(string firstName) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно найти игрока." << endl;
		}

		int flag = 0;

		Node* curr = head;
		while (curr != nullptr) {
			string formattedFirstName = curr->data.firstName;
			formattedFirstName[0] = toupper(formattedFirstName[0]);

			string formattedSearchName = firstName;
			formattedSearchName[0] = toupper(formattedSearchName[0]);

			if (formattedFirstName == formattedSearchName) {
				flag = 1; // если нашли игрока, то меняем на 1, останется 0, если никого не нашли
				cout << "Игрок найден:" << endl;
				cout << "Имя: " << curr->data.firstName << endl;
				cout << "Фамилия: " << curr->data.lastName << endl;
				cout << "Номер: " << curr->data.number << endl;
				cout << "Позиция: " << curr->data.position << endl;
				cout << "Рост: " << curr->data.height << " см" << endl;
				cout << "Вес: " << curr->data.weight << " кг" << endl;
				cout << endl;
			}
			curr = curr->next;
		}

		if (flag == 0) { // 0, если никого не нашли
			cout << "Игрок с именем: " << firstName << " не найден." << endl;
		}
	}

	void searchBylastName(string lastName) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно найти игрока." << endl;
		}

		int flag = 0;

		Node* curr = head;
		while (curr != nullptr) {
			string formattedLastName = curr->data.lastName;
			formattedLastName[0] = toupper(formattedLastName[0]);

			string formattedSearchLastName = lastName;
			formattedSearchLastName[0] = toupper(formattedSearchLastName[0]);

			if (formattedLastName == formattedSearchLastName) {
				flag = 1; // если нашли игрока, то меняем на 1, останется 0, если никого не нашли
				cout << "Игрок найден:" << endl;
				cout << "Имя: " << curr->data.firstName << endl;
				cout << "Фамилия: " << curr->data.lastName << endl;
				cout << "Номер: " << curr->data.number << endl;
				cout << "Позиция: " << curr->data.position << endl;
				cout << "Рост: " << curr->data.height << " см" << endl;
				cout << "Вес: " << curr->data.weight << " кг" << endl;
				cout << endl;
			}
			curr = curr->next;
		}

		if (flag == 0) { // 0, если никого не нашли
			cout << "Игрок с фамилией: " << lastName << " не найден." << endl;
		}
	}

	Node* searchByNumber(int number) {
		if (head == nullptr) {
			cout << "Список пуст. Невозможно найти игрока." << endl;
			return nullptr;
		}

		Node* curr = head;
		while (curr != nullptr) {
			if (stoi(curr->data.number) == number) {
				return curr;
			}
			curr = curr->next;
		}

		cout << "Игрок с номером " << number << " не найден." << endl;
		return nullptr;
	}

	void outputtablet() {
		if (head == nullptr) {
			cout << "Список пуст" << endl << endl;
			system("pause");
			system("cls");
			return;
		}

		int max_firstName = 20, max_lastName = 20, max_number = 10, max_position = 15, max_height = 5, max_weight = 5;
		int u = 1;

		for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
			// Определение максимальных значений для каждого столбца на текущей итерации
			if (ptr->data.firstName.size() > max_firstName)
				max_firstName = ptr->data.firstName.size();

			if (ptr->data.lastName.size() > max_lastName)
				max_lastName = ptr->data.lastName.size();

			if (ptr->data.number.size() > max_number)
				max_number = ptr->data.number.size();

			if (ptr->data.position.size() > max_position)
				max_position = ptr->data.position.size();

			if (ptr->data.height.size() > max_height)
				max_height = ptr->data.height.size();

			if (ptr->data.weight.size() > max_weight)
				max_weight = ptr->data.weight.size();
		}




		int totalWidth = max_number + max_firstName + max_lastName + max_position + max_height + max_weight + 16;

		cout << '+' << string(totalWidth, '-') << '+' << endl;
		cout << '|' << setw(max_number) << "Номер" << '|' << setw(max_firstName) << "Имя" << '|'
			<< setw(max_lastName) << "Фамилия" << '|'
			<< setw(max_number) << "Номер" << '|'
			<< setw(max_position) << "Позиция" << '|'
			<< setw(max_height) << "Рост" << '|'
			<< setw(max_weight) << "Вес" << '|' << endl;
		cout << '+' << string(totalWidth, '-') << '+' << endl;

		for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
			cout << '|' << setw(max_number) << u << '|'
				<< setw(max_firstName) << ptr->data.firstName << '|'
				<< setw(max_lastName) << ptr->data.lastName << '|'
				<< setw(max_number) << ptr->data.number << '|'
				<< setw(max_position) << ptr->data.position << '|'
				<< setw(max_height) << ptr->data.height << '|'
				<< setw(max_weight) << ptr->data.weight << '|' << endl;
			cout << '+' << string(totalWidth, '-') << '+' << endl;
			u++;
		}

		system("pause");
		system("cls");
	}

	// Function to create a new database file
	ofstream new_DB(const string& filename) {
		ofstream file(filename);
		if (!file.is_open()) {
			cerr << "Ошибка: Не удалось создать файл базы данных." << endl;
		}
		return file;
	}

	// Function to remove a database file
	void remove_DB(const string& filename) {
		if (remove(filename.c_str()) != 0) {
			cerr << "Ошибка: Не удалось удалить файл базы данных." << endl;
		}
		else {
			cout << "Файл базы данных успешно удален." << endl;
		}
	}

	// Function to save the sorted list to a file
	void save_DB(const string& filename, DoublyLinkedList& list) {
		ofstream file(filename);
		if (!file.is_open()) {
			cerr << "Ошибка: Не удалось открыть файл базы данных для сохранения." << endl;
			return;
		}

		Node* curr = list.head;
		while (curr != nullptr) {
			file << "Имя: " << curr->data.firstName << endl;
			file << "Фамилия: " << curr->data.lastName << endl;
			file << "Номер: " << curr->data.number << endl;
			file << "Позиция: " << curr->data.position << endl;
			file << "Рост: " << curr->data.height << " см" << endl;
			file << "Вес: " << curr->data.weight << " кг" << endl;
			file << endl;
			curr = curr->next;
		}

		cout << "Список успешно сохранен в файл базы данных." << endl;
	}

	int getListSize(const DoublyLinkedList* list) {
		int size = 0;
		Node* currentNode = list->head;
		while (currentNode != nullptr) {
			size++;
			currentNode = currentNode->next;
		}
		return size;
	}

	// Функция для проверки, является ли строка числом
	bool isNumeric(const string& str) {
		for (char c : str) {
			if (!isdigit(c)) {
				return false;
			}
		}
		return true;
	}





	// Функция для проверки корректности позиции в списке внутри функции modifyField
	bool isValidPositionInModifyfield(int position, int listSize) {
		return position >= 0 && position < listSize;
	}
	// Функция для проверки корректности номера поля
	bool isValidFieldNum(int fieldNum) {
		return fieldNum >= 1 && fieldNum <= 6;
	}
	// Функция для изменения поля в элементе списка
	void modifyField(DoublyLinkedList* list, int index, int fieldNum, const string& newValue) {
		index--; // Уменьшаем индекс на 1, так как индексация начинается с 0

		// Находим узел с указанным индексом
		Node* currentNode = list->head;
		for (int i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}

		// Проверяем наличие узла
		if (currentNode == nullptr) {
			cout << "Ошибка. Неверные данные" << endl;
			return;
		}

		// Получаем ссылку на данные в текущем узле
		Player* data = &(currentNode->data);

		// В зависимости от номера поля изменяем его значение
		bool isValueValid = false;
		string validValue;
		switch (fieldNum) {
		case 1:
			if (isValidName(newValue)) {
				data->firstName = formatName(newValue);
				isValueValid = true;
			}
			else {
				cout << "Ошибка. Некорректное имя. Введите корректное имя: ";
				cin >> validValue;
				if (isValidName(validValue)) {
					data->firstName = formatName(validValue);
					isValueValid = true;
				}
				else {
					cout << "Ошибка. Некорректное имя." << endl;
				}
			}
			break;
		case 2:
			if (isValidName(newValue)) {
				data->lastName = formatName(newValue);
				isValueValid = true;
			}
			else {
				cout << "Ошибка. Некорректная фамилия. Введите корректную фамилию: ";
				cin >> validValue;
				if (isValidName(validValue)) {
					data->lastName = formatName(validValue);
					isValueValid = true;
				}
				else {
					cout << "Ошибка. Некорректная фамилия." << endl;
				}
			}
			break;
		case 3:
			// Проверяем, что newValue является корректным числом
			try {
				int numberValue = stoi(newValue);
				if (numberValue >= 0) {
					data->number = newValue;
					isValueValid = true;
				}
				else {
					cout << "Ошибка. Номер должен быть положительным числом. Введите корректный номер: ";
					cin >> validValue;
					numberValue = stoi(validValue);
					if (numberValue >= 0) {
						data->number = validValue;
						isValueValid = true;
					}
					else {
						cout << "Ошибка. Некорректный номер." << endl;
					}
				}
			}
			catch (const std::invalid_argument&) {
				cout << "Ошибка. Некорректный номер. Введите корректный номер: ";
				cin >> validValue;
				try {
					int numberValue = stoi(validValue);
					if (numberValue >= 0) {
						data->number = validValue;
						isValueValid = true;
					}
					else {
						cout << "Ошибка. Номер должен быть положительным числом." << endl;
					}
				}
				catch (const std::invalid_argument&) {
					cout << "Ошибка. Некорректный номер." << endl;
				}
			}
			break;

		case 4:
			if (isValidPosition(newValue)) {
				data->position = formatPosition(newValue);
				isValueValid = true;
			}
			else {
				cout << "Ошибка. Некорректная позиция. Введите корректную позицию: ";
				cin >> validValue;
				if (isValidPosition(validValue)) {
					data->position = formatPosition(validValue);
					isValueValid = true;
				}
				else {
					cout << "Ошибка. Некорректная позиция." << endl;
				}
			}
			break;
		case 5:
			if (isValidHeight(newValue)) {
				data->height = newValue;
				isValueValid = true;
			}
			else {
				

				cout << "Ошибка. Некорректный рост. Введите корректный рост: ";
				cin >> validValue;
				if (isValidHeight(validValue)) {
					data->height = validValue;
					isValueValid = true;
				}
				else {
					cout << "Ошибка. Некорректный рост." << endl;
				}
			}
			break;
		case 6:
			if (isValidWeight(newValue)) {
				data->weight = newValue;
				isValueValid = true;
			}
			else {
				cout << "Ошибка. Некорректный вес. Введите корректный вес: ";
				cin >> validValue;
				if (isValidWeight(validValue)) {
					data->weight = validValue;
					isValueValid = true;
				}
				else {
					cout << "Ошибка. Некорректный вес." << endl;
				}
			}
			break;
		default:
			cout << "Ошибка. Некорректный номер поля." << endl;
			return;
		}

		if (isValueValid) {
			cout << "Поле успешно изменено." << endl;
		}
	}

	// Вспомогательная функция для форматирования имени и фамилии
	string formatName(const string& name) {
		if (name.empty()) {
			return "";
		}

		string formattedName;
		formattedName += toupper(name[0]);
		for (size_t i = 1; i < name.length(); i++) {
			formattedName += tolower(name[i]);
		}

		return formattedName;
	}

	// Вспомогательная функция для форматирования позиции
	string formatPosition(const string& position) {

		string formattedPosition;
		for (char c : position) {
			formattedPosition += toupper(c);
		}
		return formattedPosition;
	}

	//bool isStringSizeCorrect(string input, int size) // input - Твоя переменная с введенными данными, size - максимальный размер этой строки. Если превышает - FALSE
	//{
	//	if (input.length() > size)
	//	{
	//		cout << "Ошибка!!! Введенное значение превышает ограничения!";
	//		system("pause");
	//		return false;
	//	}
	//	return true;
	//}






	// Function to load the list of players from a file
	void load_DB(const string& filename, DoublyLinkedList& list) {
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Ошибка: Не удалось открыть файл базы данных для чтения." << endl;
			return;
		}

		list.deleteList(); // Clear the existing list before loading

		Player player;
		string line;
		while (getline(file, line)) {
			if (line.find("Имя:") != string::npos) {
				player.firstName = line.substr(5); // Trim "Имя: " from the line
			}
			else if (line.find("Фамилия:") != string::npos) {
				player.lastName = line.substr(9); // Trim "Фамилия: " from the line
			}
			else if (line.find("Номер:") != string::npos) {
				player.number = line.substr(7); // Trim "Номер: " from the line
			}
			else if (line.find("Позиция:") != string::npos) {
				player.position = line.substr(9); // Trim "Позиция: " from the line
			}
			else if (line.find("Рост:") != string::npos) {
				player.height = line.substr(6, line.find("см") - 7); // Extract height from the line
			}
			else if (line.find("Вес:") != string::npos) {
				player.weight = line.substr(5, line.find("кг") - 6); // Extract weight from the line

				Node* newNode = new Node();
				newNode->data = player;
				newNode->next = nullptr;
				newNode->prev = nullptr;

				if (list.head == nullptr) {
					list.head = newNode;
				}
				else {
					Node* curr = list.head;
					while (curr->next != nullptr) {
						curr = curr->next;
					}
					curr->next = newNode;
					newNode->prev = curr;
				}
			}
		}

		cout << "Список успешно загружен из файла базы данных." << endl;
	}

	// Function to clear the dynamically allocated memory for the database
	void clear(DoublyLinkedList& list) {
		list.deleteList();
		cout << "Динамическая память, выделенная для структур базы данных, очищена." << endl;
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	DoublyLinkedList list;
	bool check = false;
	string choice;

	while (!check) {
		cout << "____________$$$$$$$$$$$$$  \n";
		cout << "________$$$$$$$ ________ $$$\n";
		cout << "_____$$$$$$$$$ ___________ $$$$\n";
		cout << "____$$_$$$____$$ ________ $___$$\n";
		cout << "___$___$________$ ______ $______$$\n";
		cout << "__$___$ _________ $$$$$$$$_______$$\n";
		cout << "_$___$$ ________ $$$$$$$$$________$\n";
		cout << "$$___$ _________ $$$$$$$$$$________$\n";
		cout << "$___$$ _______ $$$$$$$$$$$$________$\n";
		cout << "$__$$$$$ __ $$$___$$$$$$$__$$$$___$$\n";
		cout << "$$$$$$$$$$$ _______ $$$________$$$$$\n";
		cout << "$_$$$$$$$ __________ $__________$$$$\n";
		cout << "$_$$$$$$$ __________ $__________$$$$\n";
		cout << "_$_$$$$$$ _________ $$__________$$$\n";
		cout << "__$_$$__$$ ________ $_________$$_$$\n";
		cout << "___$$_____$$$ ___ $$$$$____$$$___$\n";
		cout << "____$$ _____ $$$$$$$$$$$$$$$___$$\n";
		cout << "_____$$$ _____ $$$$$$$$$$____$$\n";
		cout << "_______$$$$ __ $$$$$$$$$__$$$\n";
		cout << "__________$$$$$ _____ $$$$\n\n";
		cout << "1. Меню для работы со списком\n";
		cout << "2. Меню сортировок\n";
		cout << "3. Меня поиска\n";
		cout << "4. Меню для работы с файлом:\n";
		cout << "0. Выйти\n";


		getline(cin, choice);

		if (choice == "1") {
			// Сортировка по росту
			while (true) {
				system("cls");
				cout << "Меню работы со списками:" << endl;
				cout << "1. Создание списка" << endl;
				cout << "2. Добавление элемента" << endl;
				cout << "3. Печать данных" << endl;
				cout << "4. Печать в табличном формате" << endl;
				cout << "5. Удаление игрока по индексу" << endl;
				cout << "6. Смена игроков местами" << endl;
				cout << "7. Очистка списка" << endl;
				cout << "8. Изменение записи" << endl;
				cout << "0. Выход в главное меню" << endl;
				cout << "Выберите опцию: ";

				string listChoice;
				cin >> listChoice;

				if (listChoice == "1") {
					system("cls");
					list.createList();
					system("cls");
					continue;
				}
				else if (listChoice == "2") {
					system("cls");

					Player newPlayer;

					string indexStr;
					cout << "Введите индекс элемента, после которого нужно добавить новый элемент: ";
					cin >> indexStr;
					int index = stoi(indexStr);

					list.addAfter(newPlayer, index);

					system("cls");
					continue;
				}
				else if (listChoice == "3") {
					system("cls");
					list.printList();
					cout << endl << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (listChoice == "4") {
					system("cls");
					list.outputtablet();
					system("cls");
					continue;
				}
				else if (listChoice == "5") {
					system("cls");
					string indexStr;
					cout << "Введите индекс элемента, который нужно удалить: ";
					cin >> indexStr;
					int indexToDel = stoi(indexStr);

					list.deleteAtIndex(indexToDel);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (listChoice == "6") {
					system("cls");
					int index1, index2;
					cout << "Введите индекс первого игрока: ";
					cin >> index1;
					cout << "Введите индекс второго игрока: ";
					cin >> index2;

					list.swapPlayers(index1, index2);
					cout << "Игроки успешно поменялись местами." << endl;
					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (listChoice == "7") {
					system("cls");
					list.deleteList();
					cout << "Список очищен." << endl;
					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (listChoice == "8") {
					system("cls");

					int index;
					cout << "Введите номер элемента, который нужно изменить: ";
					while (!(cin >> index))
					{
						cout << "Ошибка:\n";
						cin.clear();
						cin.ignore();
						cout << "Введите номер элемента, который нужно изменить: ";
					}

					int fieldNum;
					cout << "Введите номер поля, которое нужно изменить (1 - firstName, 2 - lastName, 3 - number, 4 - position, 5 - height, 6 - weight): ";
					while (!(cin >> fieldNum))
					{
						cout << "Ошибка:\n";
						cin.clear();
						cin.ignore();
						cout << "Введите номер поля, которое нужно изменить (1 - firstName, 2 - lastName, 3 - number, 4 - position, 5 - height, 6 - weight): ";
					}
					

					string newValue;
					cout << "Введите новое значение: ";
					cin >> newValue;

					list.modifyField(&list, index, fieldNum, newValue);

					system("pause");
					system("cls");
					continue;
				}

				else if (listChoice == "0") {

					break;
				}
				else {
					cout << "Некорректный ввод. Попробуйте снова." << endl;
				}
			}
			system("cls");
			continue;
		}



			else if (choice == "2") {
				// Сортировка по росту
				while (true) {
					system("cls");
					cout << "Меню сортировки:" << endl;
					cout << "1. Сортировка по росту" << endl;
					cout << "2. Сортировка по весу" << endl;
					cout << "3. Сортировка по имени" << endl;
					cout << "4. Сортировка по фамилии" << endl;
					cout << "5. Сортировка по номеру" << endl;
					cout << "0. Вернуться в предыдущее меню" << endl;
					cout << "Выберите опцию: ";
					
					string sortChoice;
					cin >> sortChoice;
					// Проверка на ввод чисел от 0 до 5 без пробелов
					if (sortChoice.length() != 1 || sortChoice[0] < '0' || sortChoice[0] > '5') {
						cout << "Некорректный ввод. Попробуйте снова." << endl;
						break;
					}
					else if (sortChoice == "1") {
						system("cls");
						list.bubbleSortByHeight();
						list.outputtablet();
						cout << "Список отсортирован по росту методом пузырьковой сортировки." << endl;
						cout << "Чтобы продолжить введите любое число: ";
						string num;
						cin >> num;
						continue;
					}
					else if (sortChoice == "2") {
						system("cls");
						list.quickSortByWeight();
						list.outputtablet();
						cout << "Список отсортирован по весу методом пузырьковой сортировки." << endl;
						cout << "Чтобы продолжить введите любое число: ";
						string num;
						cin >> num;
						system("cls");

						continue;
					}
					else if (sortChoice == "3") {
						system("cls");
						list.bubbleSortByName();
						list.outputtablet();
						cout << "Список отсортирован по имени методом пузырьковой сортировки." << endl;
						cout << "Чтобы продолжить введите любое число: ";
						string num;
						cin >> num;
						system("cls");
						continue;
					}
					else if (sortChoice == "4") {
						system("cls");
						list.bubbleSortByLastName();
						list.outputtablet();
						cout << "Список отсортирован по фамилии методом пузырьковой сортировки." << endl;
						cout << "Чтобы продолжить введите любое число: ";
						string num;
						cin >> num;
						system("cls");
						continue;
					}
					else if (sortChoice == "5") {
						system("cls");
						list.bubbleSortByNumber();
						list.outputtablet();
						cout << "Список отсортирован по номеру." << endl;
						cout << "Чтобы продолжить введите любое число: ";
						string num;
						cin >> num;
						system("cls");
						continue;
					}
					else if (sortChoice == "0") {
						break;
					}
					else {
						cout << "Некорректный ввод. Попробуйте снова." << endl;
					}
				}
				system("cls");
				continue;
			}



		else if (choice == "3") {
			// Сортировка по росту
			while (true) {
				system("cls");
				cout << "Меню поиска:" << endl;
				cout << "1. Поиск по росту" << endl;
				cout << "2. Поиск по весу" << endl;
				cout << "3. Поиск по имени" << endl;
				cout << "4. Поиск по фамилии" << endl;
				cout << "5. Поиск по номеру" << endl;
				cout << "0. Вернуться в предыдущее меню" << endl;
				cout << "Выберите опцию: ";

				string searchChoice;
				cin >> searchChoice;
				if (searchChoice.length() != 1 || searchChoice[0] < '0' || searchChoice[0] > '5') {
					cout << "Некорректный ввод. Попробуйте снова." << endl;
					break;
				}
				else if  (searchChoice == "5") {
					system("cls");
					int number;
					cout << "Введите номер игрока для поиска: ";
					cin >> number;

					Node* found = list.searchByNumber(number);
					if (found != nullptr) {
						cout << "Игрок найден:" << endl;
						cout << "Имя: " << found->data.firstName << endl;
						cout << "Фамилия: " << found->data.lastName << endl;
						cout << "Номер: " << found->data.number << endl;
						cout << "Позиция: " << found->data.position << endl;
						cout << "Рост: " << found->data.height << " см" << endl;
						cout << "Вес: " << found->data.weight << " кг" << endl;
					}
					else {
						cout << "Игрок не найден." << endl;
					}
					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (searchChoice == "1") {
					system("cls");
					int height;
					cout << "Введите рост игрока для поиска: ";
					cin >> height;

					list.searchByHeight(height);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (searchChoice == "3") {
					system("cls");
					string firstName;
					cout << "Введите имя игрока для поиска: ";
					cin >> firstName;

					list.searchByfirstName(firstName);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (searchChoice == "4") {
					system("cls");
					string lastName;
					cout << "Введите фамилию игрока для поиска: ";
					cin >> lastName;

					list.searchBylastName(lastName);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (searchChoice == "2") {
					system("cls");
					int weight;
					cout << "Введите вес игрока для поиска: ";
					cin >> weight;

					list.searchByWeight(weight);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (searchChoice == "0") {
					break;
				}
				else {
					cout << "Некорректный ввод. Попробуйте снова." << endl;
				}
					
			}
			system("cls");
			continue;
		}




		else if (choice == "4") {
			// Сортировка по росту
			while (true) {
				system("cls");
				cout << "Меню для работы с файлом:" << endl;
				cout << "1. Создание файла" << endl;
				cout << "2. Удаление файла" << endl;
				cout << "3. Сохранение файла" << endl;
				cout << "4. Выгрузка данных из файла" << endl;
				cout << "5. Очистка файла" << endl;
				cout << "0. Вернуться в предыдущее меню" << endl;
				cout << "Выберите опцию: ";

				string fileChoice;
				cin >> fileChoice;

				if (fileChoice == "1") {
					system("cls");
					string filename;
					cout << "Введите название нового файла базы данных: ";
					cin.ignore();
					getline(cin, filename);

					ofstream newFile = list.new_DB(filename);
					newFile.close();

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (fileChoice == "2") {
					system("cls");
					string filename;
					cout << "Введите название файла базы данных для удаления: ";
					cin.ignore();
					getline(cin, filename);

					list.remove_DB(filename);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (fileChoice == "3") {
					system("cls");
					string filename;
					cout << "Введите название файла базы данных для сохранения: ";
					cin.ignore();
					getline(cin, filename);

					list.quickSortByWeight();
					list.save_DB(filename, list);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (fileChoice == "4") {
					system("cls");
					string filename;
					cout << "Введите название файла базы данных для загрузки: ";
					cin.ignore();
					getline(cin, filename);

					list.load_DB(filename, list);

					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}
				else if (fileChoice == "5") {
					system("cls");
					string filename;
					cout << "Введите название файла базы данных для очистки: ";
					cin.ignore();
					getline(cin, filename);

					ofstream clearFile(filename, ios::trunc); // Open the file in trunc mode to clear it
					clearFile.close();

					cout << "Файл базы данных успешно очищен." << endl;
					cout << "Чтобы продолжить введите любое число: ";
					string num;
					cin >> num;
					system("cls");
					continue;
				}

				else if (fileChoice == "0") {
					break;
				}
				else {
					cout << "Некорректный ввод. Попробуйте снова." << endl;
				}

				
			}
			system("cls");
			continue;
		}

		else if (choice == "0") {
			cout << "Выход..." << endl;
			check = true;
		}
		else {
			cout << "Такой вариант отсутствует." << endl;
			system("pause");
			system("cls"); // Очищаем экран перед выводом нового меню
			continue; // Продолжаем цикл, чтобы обновить меню
		}
		return 0;
	}
}
