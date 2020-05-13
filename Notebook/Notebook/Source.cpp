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
};

int main() {
	bool keepOn = true;
	int number;
	string command;
	string currentLine;
	ifstream in;
	ofstream out;

	cout << "Commands:" << endl;
	cout << "add - write new contacts from file add.txt." << endl << "    Warning! Data should be recorded in the following order: name, surname," << endl << "    patronymic, phone number, e-mail address, date of birth, city of residence." << endl << "    They should be separated by the symbol ' '. Other use of the ' ' symbol is not allowed." << endl << "    The data for each new person starts with a new line." << endl << "    In case certain data are unknown, they should be replaced with a '-' symbol." << endl;
	cout << "exit - get out of the program." << endl << endl;

	while (keepOn) {
		cout << "Enter a command:" << endl;
		cin >> command;

		if (command == "add") {
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
			dataList.clear();
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