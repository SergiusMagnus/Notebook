#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Person {
private:
	const int number = 7;
	string name;
	string surname;
	string patronymic;
	string phoneNumber;
	string emailAddress;
	string birthday;
	string city;

public:
	Person() {
		name = "-";
		surname = "-";
		patronymic = "-";
		phoneNumber = "-";
		emailAddress = "-";
		birthday = "-";
		city = "-";
	}

	void record(int currentNumber, string currentWord) {
		if (currentNumber == 0) {
			name = currentWord;
		}
		else if (currentNumber == 1) {
			surname = currentWord;
		}
		else if (currentNumber == 2) {
			patronymic = currentWord;
		}
		else if (currentNumber == 3) {
			phoneNumber = currentWord;
		}
		else if (currentNumber == 4) {
			emailAddress = currentWord;
		}
		else if (currentNumber == 5) {
			birthday = currentWord;
		}
		else if (currentNumber == 6) {
			city = currentWord;
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
				if (j + 1 > currentLine.length()) {
					break;
				}
			}
			record(i, currentWord);
			j++;
		}
	}

	string compound() {
		string currentLine;
		currentLine = name + ' ' + surname + ' ' + patronymic + ' ' + phoneNumber + ' ' + emailAddress + ' ' + birthday + ' ' + city;
		return currentLine;
	}

	bool compare(Person sample) {
		bool trigger = true;
		if (!((sample.name == name) || (name == "-") || (sample.name == "-"))) {
			trigger = false;
		}
		if (!((sample.surname == surname) || (surname == "-") || (sample.surname == "-"))) {
			trigger = false;
		}
		if (!((sample.patronymic == patronymic) || (patronymic == "-") || (sample.patronymic == "-"))) {
			trigger = false;
		}
		if (!((sample.phoneNumber == phoneNumber) || (phoneNumber == "-") || (sample.phoneNumber == "-"))) {
			trigger = false;
		}
		if (!((sample.emailAddress == emailAddress) || (emailAddress == "-") || (sample.emailAddress == "-"))) {
			trigger = false;
		}
		if (!((sample.birthday == birthday) || (birthday == "-") || (sample.birthday == "-"))) {
			trigger = false;
		}
		if (!((sample.city == city) || (city == "-") || (sample.city == "-"))) {
			trigger = false;
		}
		if (trigger) {
			return true;
		}
		else {
			return false;
		}
	}
};

void add();
void search();

int main() {
	bool keepOn = true;
	string command;

	cout << "Commands:" << endl;
	cout << "add - write new contacts from file add.txt." << endl << "    Warning! Data should be recorded in the following order: name, surname," << endl << "    patronymic, phone number, e-mail address, date of birth, city of residence." << endl << "    They should be separated by the symbol ' '. Other use of the ' ' symbol is not allowed." << endl << "    The data for each new person starts with a new line." << endl << "    In case certain data are unknown, they should be replaced with a '-' symbol." << endl;
	cout << "search - to look for any matching records with the sample." << endl << "    The sample is written by all rules into the 'data to search.txt' file." << endl << "    The result is output to the 'search results.txt' file." << endl;
	cout << "exit - get out of the program." << endl << endl;

	while (keepOn) {
		cout << "Enter a command: ";
		cin >> command;

		if (command == "add") {
			add();
		}
		else if (command == "search") {
			search();
		}
		else if (command == "exit") {
			keepOn = false;
		}
		else {
			cout << "The command entered does not exist." << endl << endl;
		}
	}

	return 0;
}

void add() {
	int number;
	string currentLine;
	ifstream in;
	ofstream out;

	in.open("add.txt");
	vector<Person> dataList(10);
	number = 0;

	while (getline(in, currentLine)) {
		dataList[number].conversion(currentLine);
		number++;
	}

	in.close();

	out.open("data.txt", ios::app);

	for (int i = 0; i < number; i++) {
		currentLine = dataList[i].compound();
		out << currentLine << endl;
	}

	out.close();

	cout << "Completed!" << endl << endl;
}

void search() {
	int number;
	string currentLine;
	ifstream in;
	ofstream out;

	in.open("data to search.txt");
	vector<Person> dataList(10);
	number = 0;
	Person sample;

	getline(in, currentLine);
	sample.conversion(currentLine);

	in.close();

	in.open("data.txt");

	while (getline(in, currentLine)) {
		dataList[number].conversion(currentLine);
		number++;
	}

	in.close();

	out.open("search results.txt");
	for (int i = 0; i < number; i++) {
		if (dataList[i].compare(sample)) {
			currentLine = dataList[i].compound();
			out << currentLine << endl;
		}
	}

	out.close();

	cout << "Completed!" << endl << endl;
}