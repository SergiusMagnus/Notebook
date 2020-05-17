#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class Person {
private:
	static const int number = 7;
	string data[number];
	/*
	0 - имя(name)
	1 - фамилия(surname)
	2 - отчество(patronymic)
	3 - номер телефона(phone number)
	4 - адрес элестронной почты(e-male)
	5 - дата рождения(date of birth)
	6 - город проживания(city)*/

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

	int getNumber() {
		return number;
	}
};

void chooseCommand(const string command, bool &keepOn);

void readInput(vector<Person> &dataList, int &length);
void writeOutput(vector<Person> &dataList, const int length);
void readData(vector<Person> &data, int &length);
void writeData(vector<Person> &data, const int length, const bool trigger);
bool checkInput();

void add();
void search();
void destroy();
void clear();

const int originalSize = 10;

int main() {
	bool keepOn = true;
	string command;

	cout << "Data recording rules:" << endl;
	cout << "    The input data must be written to the 'input.txt' file." << endl;
	cout << "    The data must be written in the following order: first name, last name," << endl;
	cout << "    patronymic, phone number, e-mail address, date of birth, city of residence." << endl;
	cout << "    There must be a symbol ' ' between each cell. No other use of this symbol is allowed." << endl;
	cout << "    Unknown cells must be replaced by a '-'. Information about each new character must begin with a new line." << endl;
	cout << "    The maximum length of one cell is 50 characters. The minimum is 1." << endl;
	cout << "    The result of the operation is written to the 'output.txt' file." << endl;

	cout << "Commands:" << endl;
	cout << "    add     -  saves new contacts from file 'input.txt'." << endl; 
	cout << "    search  -  looks for any matching records with the samples." << endl; 
	cout << "    delete  -  deletes all data matching the samples." << endl; 
	cout << "    clear   -  erases all recorded data." << endl;
	cout << "    exit    -  gets out of the program." << endl << endl;

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

void readInput(vector<Person> &inputData, int &lengthInputData) {
	string currentLine;
	ifstream in;
	lengthInputData = 0;

	in.open("input.txt");

	while (getline(in, currentLine)) {
		if (lengthInputData == inputData.size()) {
			inputData.resize(lengthInputData + ceil(lengthInputData / 2.0));
		}
		inputData[lengthInputData].conversion(currentLine);
		lengthInputData++;
	}

	in.close();
}

void writeOutput(vector<Person> &outputData, const int lengthOutputData) {
	string currentLine;
	ofstream out;

	out.open("output.txt");

	for (int i = 0; i < lengthOutputData; i++) {
		currentLine = outputData[i].compound();
		out << currentLine << endl;
	}

	out.close();
}

void readData(vector<Person> &data, int &lengthData) {
	string currentLine;
	ifstream in;
	lengthData = 0;

	in.open("data.txt");
	
	while (getline(in, currentLine)) {
		if (lengthData == data.size()) {
			data.resize(lengthData + ceil(lengthData / 2.0));
		}
		data[lengthData].conversion(currentLine);
		lengthData++;
	}

	in.close();
}

void writeData(vector<Person> &data, const int lengthData, const bool trigger) {
	string currentLine;
	ofstream out;

	if (trigger) {
		out.open("data.txt", ios::app);
	}
	else {
		out.open("data.txt");
	}

	for (int i = 0; i < lengthData; i++) {
		currentLine = data[i].compound();
		out << currentLine << endl;
	}

	out.close();
}

bool checkInput() {
	string currentLine;
	ifstream in;
	Person inputDatum;
	int indexLine;
	int countLetter;
	int countSpace;
	int countLine = 0;
	bool trigger = true;

	in.open("input.txt");

	while (getline(in, currentLine)) {
		indexLine = 0;
		int countLetter = 0;
		int countSpace = 0;
		while (indexLine < currentLine.size()) {
			if (currentLine[indexLine] != ' ') {
				countLetter++;
			}
			else {
				countSpace++;
				if ((countLetter == 0) || (countLetter > 50)) {
					trigger = false;
					break;
				}
				countLetter = 0;
			}
			indexLine++;
		}
		countLine++;
		if (countSpace != inputDatum.getNumber() - 1) {
			trigger = false;
		}
		if (countLine > 30000) {
			trigger = false;
		}
		if (!trigger) {
			break;
		}
	}

	in.close();

	return trigger;
}

void add() {
	if (checkInput()) {
		vector<Person> inputData(originalSize);
		int lengthInputData;

		readInput(inputData, lengthInputData);

		writeData(inputData, lengthInputData, true);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void search() {
	if (checkInput()) {
		vector<Person> inputData(originalSize);
		int lengthInputData;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> newData(originalSize);
		int newLengthData = 0;

		readInput(inputData, lengthInputData);
		readData(data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			for (int j = 0; j < lengthInputData; j++) {
				if (data[i].compare(inputData[j])) {
					if (newLengthData == newData.size()) {
						newData.resize(newLengthData + ceil(newLengthData / 2.0));
					}
					newData[newLengthData] = data[i];
					newLengthData++;
				}
			}
		}

		writeOutput(newData, newLengthData);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void destroy() {
	if (checkInput()) {
		bool trigger;
		vector<Person> inputData(originalSize);
		int lengthInputData;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> newData(originalSize);
		int newLengthData = 0;

		readInput(inputData, lengthInputData);
		readData(data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			trigger = true;
			for (int j = 0; j < lengthInputData; j++) {
				if (data[i].compare(inputData[j])) {
					trigger = false;
				}
			}
			if (trigger) {
				if (newLengthData == newData.size()) {
					newData.resize(newLengthData + ceil(newLengthData / 2.0));
				}
				newData[newLengthData] = data[i];
				newLengthData++;
			}
		}

		writeData(newData, newLengthData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void clear() {
	ofstream out;
	out.open("data.txt", ios::trunc);
	out.close();

	cout << "Completed!" << endl << endl;
}