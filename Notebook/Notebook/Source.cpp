#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Person {
private:
	static const int number = 7;
	string data[number];
	/*
	0 - имя
	1 - фамилия
	2 - отчество
	3 - номер телефона
	4 - адрес элестронной почты
	5 - дата рождения
	6 - город проживания*/

public:
	Person() {
		for (int i = 0; i < number; i++) {
			data[i] = "-";
		}
	}

	void conversion(string currentLine) {
		string currentWord;
		int j = 0;
		for (int i = 0; i < number; i++) {
			currentWord = "";
			while (currentLine[j] != ' ') {
				currentWord += currentLine[j];
				j++;
				if ((j + 1) > currentLine.length()) {
					break;
				}
			}
			data[i] = currentWord;
			j++;
		}
	}

	string compound() {
		string currentLine = data[0];
		for (int i = 1; i < number; i++) {
			currentLine += " " + data[i];
		}
		return currentLine;
	}

	bool compare(const Person sample) {
		bool trigger = true;

		for (int i = 0; i < number; i++) {
			if (!((sample.data[i] == data[i]) || (sample.data[i] == "-") || (data[i] == "-"))) {
				trigger = false;
				break;
			}
		}
		return trigger;
	}

	Person& operator= (const Person &person) {
		for (int i = 0; i < number; i++) {
			data[i] = person.data[i];
		}

		return *this;
	}

	void print() {
		for (int i = 0; i < number; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
	}
};

void chooseCommand(const string command, bool &keepOn);

void read(vector<Person> &dataList, int &length);
void write(vector<Person> &dataList, const int &length);
void readData(vector<Person> &data, int &length);
void writeData(vector<Person> &data, const int &length, const bool trigger);

void add();
void search();
void destroy();
void clear();

int main() {
	bool keepOn = true;
	string command;

	cout << "Commands:" << endl;
	cout << "add - saves new contacts from file 'input.txt'." << endl << "    Warning! Data should be recorded in the following order: name, surname," << endl << "    patronymic, phone number, e-mail address, date of birth, city of residence." << endl << "    They should be separated by the symbol ' '. Other use of the ' ' symbol is not allowed." << endl << "    The data for each new person starts with a new line." << endl << "    In case certain data are unknown, they should be replaced with a '-' symbol." << endl;
	cout << "search - looks for any matching records with the samples." << endl << "    The samples is written by all rules in the 'input.txt' file." << endl << "    The result is output to the 'output.txt' file." << endl;
	cout << "delete - deletes all data matching the samples." << endl << "    The samples is written by all rules in the 'input.txt' file." << endl;
	cout << "clear - erases all recorded data." << endl;
	cout << "exit - gets out of the program." << endl << endl;

	while (keepOn) {
		cout << "Enter a command: ";
		cin >> command;

		chooseCommand(command, keepOn);
	}

	return 0;
}

void chooseCommand(const string command, bool &keepOn) {
	if (command == "add") {
		add();
	}
	else if (command == "search") {
		search();
	}
	else if (command == "delete") {
		destroy();
	}
	else if (command == "clear") {
		clear();
	}
	else if (command == "exit") {
		keepOn = false;
	}
	else {
		cout << "The command entered does not exist." << endl << endl;
	}
}

void read(vector<Person> &dataList, int &length) {
	string currentLine;
	ifstream in;
	length = 0;

	in.open("input.txt");

	while (getline(in, currentLine)) {
		dataList[length].conversion(currentLine);
		length++;
	}

	in.close();
}

void write(vector<Person> &dataList, const int &length) {
	string currentLine;
	ofstream out;

	out.open("output.txt");

	for (int i = 0; i < length; i++) {
		currentLine = dataList[i].compound();
		out << currentLine << endl;
	}

	out.close();
}

void readData(vector<Person> &data, int &length) {
	string currentLine;
	ifstream in;
	length = 0;

	in.open("data.txt");
	
	while (getline(in, currentLine)) {
		data[length].conversion(currentLine);
		length++;
	}

	in.close();
}

void writeData(vector<Person> &data, const int &length, const bool trigger) {
	string currentLine;
	ofstream out;

	if (trigger) {
		out.open("data.txt", ios::app);
	}
	else {
		out.open("data.txt");
	}

	for (int i = 0; i < length; i++) {
		currentLine = data[i].compound();
		out << currentLine << endl;
	}

	out.close();
}

void add() {
	vector<Person> dataList(10);
	int lengthData;

	read(dataList, lengthData);

	writeData(dataList, lengthData, true);

	cout << "Completed!" << endl << endl;
}

void search() {
	vector<Person> dataList(10);
	int lengthData;
	vector<Person> data(10);
	int length;
	vector<Person> newData(10);
	int newLength = 0;

	read(dataList, lengthData);
	readData(data, length);

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < lengthData; j++) {
			if (data[i].compare(dataList[j])) {
				newData[newLength] = data[i];
				newLength++;
			}
		}
	}

	write(newData, newLength);

	cout << "Completed!" << endl << endl;
}

void destroy() {
	vector<Person> dataList(10);
	int lengthData;
	vector<Person> data(10);
	int length;
	vector<Person> newData(10);
	int newLength = 0;

	read(dataList, lengthData);
	readData(data, length);

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < lengthData; j++) {
			if (!(data[i].compare(dataList[j]))) {
				newData[newLength] = data[i];
				newLength++;
			}
		}
	}

	writeData(newData, newLength, false);

	cout << "Completed!" << endl << endl;
}

void clear() {
	ofstream out;
	out.open("data.txt", ios::trunc);
	out.close();

	cout << "Completed!" << endl << endl;
}