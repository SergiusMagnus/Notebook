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
			if (!((sample.data[i] == data[i]) || (sample.data[i] == "%"))) {
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

	string getValue(int index) {
		return data[index];
	}
};

void readData(string dataAddress, vector<Person> &data, int &lengthData);
void writeData(string dataAddress, vector<Person> &data, int lengthData, bool flag);
bool checkInput(string fileAddress);
bool checkString(string String);
void sortData(vector<Person> &data, int lengthData, string flag);
int getIndex(string flag);
bool compareString(string String1, string String2);

void addString(string dataAddress, string stringToAdd);
void addFile(string dataAddress, string fileToAdd);
void searchString(string dataAddress, string stringToSearch, string outputFile, string outputOrder);
void searchFile(string dataAddress, string fileToSearch, string outputFile, string outputOrder);
void replaceString(string dataAddress, string stringToSearch, string newString);
void replaceFile(string dataAddress, string fileToSearch, string newFile);
void deleteString(string dataAddress, string stringToDelete);
void deleteFile(string dataAddress, string fileToDelete);

const int originalSize = 10;

int main(int argc, char *argv[]) {
	if (argc > 2) {
		string dataAddress = argv[1];
		string flag = argv[2];

		if (flag == "0") {
			string stringToAdd = argv[3];

			addString(dataAddress, stringToAdd);
		}
		else if (flag == "1") {
			string fileToAdd = argv[3];

			addFile(dataAddress, fileToAdd);
		}
		else if (flag == "2") {
			string stringToSearch = argv[3];
			string outputFile = argv[4];
			string outputOrder = argv[5];

			searchString(dataAddress, stringToSearch, outputFile, outputOrder);
		}
		else if (flag == "3") {
			string fileToSearch = argv[3];
			string outputFile = argv[4];
			string outputOrder = argv[5];

			searchFile(dataAddress, fileToSearch, outputFile, outputOrder);
		}
		else if (flag == "4") {
			string stringToSearch = argv[3];
			string newString = argv[4];

			replaceString(dataAddress, stringToSearch, newString);
		}
		else if (flag == "5") {
			string fileToSearch = argv[3];
			string newFile = argv[4];

			replaceFile(dataAddress, fileToSearch, newFile);
		}
		else if (flag == "6") {
			string stringToDelete = argv[3];

			deleteString(dataAddress, stringToDelete);
		}
		else if (flag == "7") {
			string fileToDelete = argv[3];

			deleteFile(dataAddress, fileToDelete);
		}
	}
	//system("pause");
	return 0;
}

void readData(string dataAddress, vector<Person> &data, int &lengthData) {
	string currentLine;
	ifstream in;
	lengthData = 0;

	in.open(dataAddress);
	
	while (getline(in, currentLine)) {
		if (lengthData == data.size()) {
			data.resize(lengthData * 2);
		}
		data[lengthData].conversion(currentLine);
		lengthData++;
	}

	in.close();
}

void writeData(string dataAddress, vector<Person> &data, int lengthData, bool flag) {
	string currentLine;
	ofstream out;

	if (flag) {
		out.open(dataAddress, ios::app);
	}
	else {
		out.open(dataAddress);
	}

	for (int i = 0; i < lengthData; i++) {
		currentLine = data[i].compound();
		out << currentLine << endl;
	}

	out.close();
}

bool checkInput(string fileAddress) {
	string currentLine;
	ifstream in;
	Person inputDatum;
	int indexLine;
	int countLetter;
	int countSpace;
	int countLine = 0;
	bool trigger = true;

	in.open(fileAddress);

	while (getline(in, currentLine)) {
		indexLine = 0;
		countLetter = 0;
		countSpace = 0;
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

bool checkString(string String) {
	int indexLine;
	int countLetter;
	int countSpace;
	Person inputDatum;
	bool trigger = true;

	indexLine = 0;
	countLetter = 0;
	countSpace = 0;
	while (indexLine < String.size()) {
		if (String[indexLine] != ' ') {
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
	if (countSpace != inputDatum.getNumber() - 1) {
		trigger = false;
	}

	return trigger;
}

void sortData(vector<Person> &data, int lengthData, string flag) {
	int index = getIndex(flag);
	string String1;
	string String2;
	Person tmp;

	//if (index != 5) {
		for (int i = 0; i < lengthData; i++) {
			for (int j = 1; j < lengthData; j++) {

				String1 = data[j - 1].getValue(index);
				String2 = data[j].getValue(index);

				if (!(compareString(String1, String2))) {
					tmp = data[j - 1];
					data[j - 1] = data[j];
					data[j] = tmp;
				}
			}
		}
	//}
}

int getIndex(string flag) {
	int index;

	if (flag == "0") {
		index = 0;
	}
	else if (flag == "1") {
		index = 1;
	}
	else if (flag == "2") {
		index = 2;
	}
	else if (flag == "3") {
		index = 3;
	}
	else if (flag == "4") {
		index = 4;
	}
	else if (flag == "5") {
		index = 5;
	}
	else if (flag == "6") {
		index = 6;
	}

	return index;
}

bool compareString(string String1, string String2) {
	bool trigger = true;

	int lengthString1 = String1.size();
	int lengthString2 = String2.size();
	int minLength;

	if (lengthString1 <= lengthString2) {
		minLength = lengthString1;
	}
	else {
		minLength = lengthString2;
	}

	for (int index = 0; index < minLength; index++) {
		if (!(String1[index] <= String2[index])) {
			trigger = false;
			break;
		}
		if (String1[index] < String2[index]) {
			break;
		}
	}

	return trigger;
}


void addString(string dataAddress, string stringToAdd) {
	if (checkString(stringToAdd)) {
		vector<Person> inputData(1);
		int lengthInputData = 1;

		inputData[0].conversion(stringToAdd);

		writeData(dataAddress, inputData, lengthInputData, true);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void addFile(string dataAddress, string fileToAdd) {
	if (checkInput(fileToAdd)) {
		vector<Person> inputData(originalSize);
		int lengthInputData;

		readData(fileToAdd, inputData, lengthInputData);

		writeData(dataAddress, inputData, lengthInputData, true);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void searchString(string dataAddress, string stringToSearch, string outputFile, string outputOrder) {
	if (checkString(stringToSearch)) {
		vector<Person> inputData(1);
		int lengthInputData = 1;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> outputData(originalSize);
		int outputLengthData = 0;

		inputData[0].conversion(stringToSearch);
		readData(dataAddress, data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			if (data[i].compare(inputData[0])) {
				if (outputLengthData == outputData.size()) {
					outputData.resize(outputLengthData * 2);
				}
				outputData[outputLengthData] = data[i];
				outputLengthData++;
			}
		}

		sortData(outputData, outputLengthData, outputOrder);

		writeData(outputFile, outputData, outputLengthData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void searchFile(string dataAddress, string fileToSearch, string outputFile, string outputOrder) {
	if (checkInput(fileToSearch)) {
		vector<Person> inputData(originalSize);
		int lengthInputData;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> outputData(originalSize);
		int outputLengthData = 0;

		readData(fileToSearch, inputData, lengthInputData);
		readData(dataAddress, data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			for (int j = 0; j < lengthInputData; j++) {
				if (data[i].compare(inputData[j])) {
					if (outputLengthData == outputData.size()) {
						outputData.resize(outputLengthData * 2);
					}
					outputData[outputLengthData] = data[i];
					outputLengthData++;
				}
			}
		}

		sortData(outputData, outputLengthData, outputOrder);

		writeData(outputFile, outputData, outputLengthData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void replaceString(string dataAddress, string stringToSearch, string newString) {
	if ((checkString(stringToSearch)) && (checkString(newString))) {
		vector<Person> dataToSearch(1);
		int lengthInputData = 1;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> dataToReplace(1);
		int outputLengthData = 1;

		dataToSearch[0].conversion(stringToSearch);
		dataToReplace[0].conversion(newString);
		readData(dataAddress, data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			if (data[i].compare(dataToSearch[0])) {
				data[i] = dataToReplace[0];
			}
		}

		writeData(dataAddress, data, lengthData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void replaceFile(string dataAddress, string fileToSearch, string newFile) {
	if ((checkInput(fileToSearch)) && (checkInput(newFile))) {
		vector<Person> dataToSearch(originalSize);
		int lengthInputData;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> newData(originalSize);
		int lengthNewData;
		vector<Person> dataToReplace(originalSize);
		int outputLengthData;

		readData(fileToSearch, dataToSearch, lengthInputData);
		readData(dataAddress, data, lengthData);
		readData(dataAddress, newData, lengthNewData);
		readData(newFile, dataToReplace, outputLengthData);

		for (int i = 0; i < lengthData; i++) {
			for (int j = 0; j < lengthInputData; j++) {
				if (data[i].compare(dataToSearch[j])) {
					newData[i] = dataToReplace[j];
				}
			}
		}

		writeData(dataAddress, newData, lengthNewData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void deleteString(string dataAddress, string stringToDelete) {
	if (checkInput(stringToDelete)) {
		bool trigger;
		vector<Person> inputData(1);
		int lengthInputData = 1;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> newData(originalSize);
		int newLengthData = 0;

		inputData[0].conversion(stringToDelete);
		readData(dataAddress, data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			trigger = true;
			if (data[i].compare(inputData[0])) {
				trigger = false;
			}
			if (trigger) {
				if (newLengthData == newData.size()) {
					newData.resize(newLengthData * 2);
				}
				newData[newLengthData] = data[i];
				newLengthData++;
			}
		}

		writeData(dataAddress, newData, newLengthData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}

void deleteFile(string dataAddress, string fileToDelete) {
	if (checkInput(fileToDelete)) {
		bool trigger;
		vector<Person> inputData(originalSize);
		int lengthInputData;
		vector<Person> data(originalSize);
		int lengthData;
		vector<Person> newData(originalSize);
		int newLengthData = 0;

		readData(fileToDelete, inputData, lengthInputData);
		readData(dataAddress, data, lengthData);

		for (int i = 0; i < lengthData; i++) {
			trigger = true;
			for (int j = 0; j < lengthInputData; j++) {
				if (data[i].compare(inputData[j])) {
					trigger = false;
				}
			}
			if (trigger) {
				if (newLengthData == newData.size()) {
					newData.resize(newLengthData * 2);
				}
				newData[newLengthData] = data[i];
				newLengthData++;
			}
		}

		writeData(dataAddress, newData, newLengthData, false);

		cout << "Completed!" << endl << endl;
	}
	else {
		cout << "The data was entered incorrectly." << endl << endl;
	}
}
