#include  <iostream>
#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2
using namespace std;

class cell {
public:
	int key;
	int value;
	int flag;
	cell() {
		key = -1;
		value = -1;
		flag = NOITEM;
	}
};

class linearHashTable {
private:
	cell* hashArr;
	int arrSize;
	int curSize;
public:
	linearHashTable(int size) {
		this->arrSize = size;
		hashArr = new cell[arrSize];
		curSize = 0;
	}
	int hashFunc(int key) {
		return key % arrSize;
	}
	void find(int key) {
		int probing = 1;
		int iniIdx = hashFunc(key) % arrSize;
		int curIdx = hashFunc(key) % arrSize;
		bool firstOpr = true;
		while (hashArr[curIdx].flag == ISITEM || hashArr[curIdx].flag == AVAILABLE) {
			if (hashArr[curIdx].key = key) {
				cout << "find " << key << endl;
				return;
			}
			else if (curIdx == iniIdx && !firstOpr) {
				cout << "loop" << endl;
				return;
			}
			probing += 1;
			firstOpr = false;
			curIdx = (hashFunc(key) + probing - 1) % arrSize;
		}
		cout << "don`t find " << key << endl;
	}
	void put(int key, int value) {
		int probing = 1;
		int iniIdx = hashFunc(key) % arrSize;
		int curIdx = hashFunc(key) % arrSize;
		bool firstOpr = true;
		if (isFull()) cout << "Full" << endl;
		else {
			while (hashArr[curIdx].flag == ISITEM) {
				if (curIdx == iniIdx && !firstOpr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstOpr = false;
				curIdx = (hashFunc(key) + probing - 1) % arrSize;
			}
			hashArr[curIdx].key = key;
			hashArr[curIdx].value = value;
			hashArr[curIdx].flag = ISITEM;
		}
		curSize++;
	}
	void erase(int key) {
		int probing = 1;
		int iniIdx = hashFunc(key) % arrSize;
		int curIdx = hashFunc(key) % arrSize;
		bool firstOpr = true;
		if (isEmpty()) cout << "Empty" << endl;
		else {
			while (hashArr[curIdx].flag == ISITEM || hashArr[curIdx].flag == AVAILABLE) {
				if (hashArr[curIdx].key = key) {
					hashArr[curIdx].flag = AVAILABLE;
					hashArr[curIdx].value = -1;
					hashArr[curIdx].key = -1;
					break;
				}
				else if (curIdx == iniIdx && !firstOpr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstOpr = false;
				curIdx = (hashFunc(key) + probing - 1) % arrSize;
			}
		}
		curSize--;
	}
	bool isFull() {
		return (curSize == arrSize);
	}
	bool isEmpty() {
		return (curSize == 0);
	}
	void print() {
		for (int i = 0; i < arrSize; i++) {
			cout << hashArr[i].value << " ";
		}
	}
};	

int main() {
	int caseNum, size, keyNum, key;
	cin >> caseNum;
	while (caseNum--) {
		cin >> size >> keyNum;
		linearHashTable t(size);
		while (keyNum--) {
			cin >> key;
			t.put(key, key);
		}
		t.print();
	}
}