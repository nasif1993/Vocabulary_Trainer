/*
Task: H3
Family Name: Mannan
Given Name: Nasif
Matriculation number: 3055949
Uni-Email: nasif.mannan@stud.uni-due.de
Course of Studies: ISE CSE
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Entry {
	string key;
	int hashedKey;
	string value;
};

Entry *hashTable;
int collcount;
int prime;

void init() {
	cout << "please input value for (prime) number p : ";
	cin >> prime;
	hashTable = new Entry[prime];
	for (int i = 0; i < prime; i ++) {
		hashTable[i].hashedKey = -1;
	}
	collcount = 0;
}

int gethashedKey(string str) {
	int hKey = 0;
	for (int i = 0; i < str.length(); i++) {
		hKey = (hKey * 128 + str[i]) % prime;
	}
	return hKey;
}

void insert(const string key, string value) {
	int hKey = gethashedKey(key);
	if (hashTable[hKey].hashedKey != -1) {
		while (hashTable[hKey].hashedKey != -1) {
			hKey = (hKey + 1) % prime;
			collcount++;
		}
	}
	hashTable[hKey].key = key;
	hashTable[hKey].hashedKey = hKey;
	hashTable[hKey].value = value;
	cout << "insert: " << key << " -> " << value << " at index: " << hKey << endl;
}

bool find(const string key) {
	int hKey = gethashedKey(key);
	if (hashTable[hKey].hashedKey == -1) {
		cerr << "Element does not exist for " << key << endl;
		return false;
	}
	while (hashTable[hKey].hashedKey != -1)	{
		if (hashTable[hKey].key == key)
			break;
		hKey = (hKey + 1) % prime;
	}
	cout << hashTable[hKey].key << " -> " << hashTable[hKey].value << endl;
	return true;
}

void listhashtable() {
	int cnt = 0;
	for (int i = 0; i < prime; i++) {
		if (hashTable[i].hashedKey != -1) {
			cout << i << " : " << hashTable[i].key << " -> " << hashTable[i].value << endl;
			cnt++;
		}
	}
	cout << cnt << " entries in array" << endl;
}

bool inputbyfile(string filename) {
	string line, key, value;
	int pos;
	ifstream infile(filename);
	if (!infile.is_open()) {
		cerr << "Error occured while opening file..." << endl;
		return false;
	}
	cout << filename << " opened..." << endl;
	while (getline(infile, line)) {
		pos = line.find(';', 0);
		key = line.substr(0, pos);
		value = line.substr(pos + 1, line.length() - pos - 1);
		insert(key, value);
	}
	infile.close();
	cout << filename << " closed..." << endl;
	cout << collcount << " collision(s) during insert" << endl;
	return true;
}

void destroy() {
	delete[] hashTable;
}

int main() {
	init();
	if (!inputbyfile("tiere_animals.txt"))
		return 1;
	listhashtable();
	string key;
	do {
		cout << "translate (0 for end): ";
		cin >> key;
		if (key == "0")
			break;
		find(key);
	} while (1);
	destroy();
	return 0;
}
