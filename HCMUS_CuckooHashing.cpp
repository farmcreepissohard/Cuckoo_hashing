#include<iostream>
#include<math.h>
#include<fstream>
#include<iomanip>
#include<Windows.h>
#include<cstdlib>
using namespace std;

struct key_value{
	int key;
	int value;
};

key_value* hash1, * hash2;

// -----------------SUPPORT FUNCTION------------------

int getPrime(int n); // --*-- lay size theo so nguyen to --*--
void initHash(int n); // --*-- khoi tao 2 bang bam --*--
int hash1_func(int key, int n); // --*-- cong thuc bang hash 1 --*--
int hash2_func(int key, int n); // --*-- cong thuc bang hash 2 --*--
int hash2_func(int key, int n); // --*-- cong thuc bang hash 2 --*--
key_value insert_hash1(key_value new_KeyValue, int n); // --*-- them keyvalue vao bang bam 1 --*--
key_value insert_hash2(key_value new_KeyValue, int n); // --*-- them keyvalue vao bang bam 2 --*--
bool checkDuplicate(key_value new_KeyValue, int n); // --*-- kiem tra key cua cap keyvalue moi co bi trung lap hay khong --*--
key_value initKeyValue(); // --*-- khoi tao 1 key value --*--
void removeHash(); // --*-- xoa bang bam --*--
void readfile(const char* inpRoster, key_value*& h, int& n); // --*-- doc file txt --*--
void writefile(const char* inpRoster, key_value* h, int n); // --*-- ghi file txt --*--

//--------------------------------------------

//-----------------CARRY FUNCTION----------------------

int getValue(int key, int n); // --*-- lay Value tu bang bam --*--
bool remove_key_value(int key, int n); // --*-- xoa keyvalue tu bang bam --*--
int insert_key_value(key_value k, int n); // --*-- them keyvalue vao bang bam --*--
void outputHash(int n); // --*-- in ra cac keyvalue trong bang bam --*--

//------------------------------------------------------

// --*-- lay so nguyen to moi --*--
int getPrime(int n) {
	while (1) {
		bool flag = 1;
		if (n <= 3) {
			return n;
		}
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			return n;
		}
		else {
			n++;
		}
	}
}

// --*-- khoi tao 2 bang bam --*--
void initHash(int n) {

	//tao lai size bang so nguyen to moi
	n = getPrime(n + 1);

	//xoa bang bam cu di
	delete[] hash1;
	delete[] hash2;

	//tao lai bang bam moi tu ham co san
	hash1 = new key_value[n];
	hash2 = new key_value[n];

	//khoi tao bang bam rong voi cap gia tri -1 -1
	for (int i = 0; i < n; i++) {
		hash1[i] = { -1,-1 };
	}
	for (int i = 0; i < n; i++) {
		hash2[i] = { -1,-1 };
	}
}

// --*-- cong thuc bang hash 1 --*--
int hash1_func(int key, int n) {
	return key % n;
}

// --*-- cong thuc bang hash 2 --*--
int hash2_func(int key, int n) {
	return (key / n) % n;
}

// --*-- lay Value tu bang bam --*--
int getValue(int key, int n) {
	if (hash1[hash1_func(key, n)].key == key) {//kiem tra bang hash 1
		return hash1[hash1_func(key, n)].value;
	}
	else if (hash2[hash2_func(key, n)].key == key) {//kiem tra bang hash 2
		return hash2[hash2_func(key, n)].value;
	}
	return -1;//neu khong ton tai
}

// --*-- xoa keyvalue tu bang bam --*--
bool remove_key_value(int key, int n) {
	if (n == 0) {//kiem tra ham hash rong
		return 0;
	}
	if (hash1[hash1_func(key, n)].key == key) {//kiem tra bang bam 1
		hash1[hash1_func(key, n)] = { -1,-1 };
		return 1;
	}
	else if (hash2[hash2_func(key, n)].key == key) {//kiem tra bang bam 2
		hash2[hash2_func(key, n)] = { -1,-1 };
		return 1;
	}
	return 0;//khong ton tai gia tri
}

// --*-- them keyvalue vao bang bam 1 --*--
key_value insert_hash1(key_value new_KeyValue, int n) {
	int idx = hash1_func(new_KeyValue.key, n);
	key_value old_KeyValue = hash1[idx];
	hash1[idx] = new_KeyValue;
	if (new_KeyValue.key == old_KeyValue.key) {//truong hop new va old cung key -> thay the bang keyvalue moi
		return { -1,-1 };
	}
	return old_KeyValue;
}

// --*-- them keyvalue vao bang bam 2 --*--
key_value insert_hash2(key_value new_KeyValue, int n) {
	int idx = hash2_func(new_KeyValue.key, n);
	key_value old_KeyValue = hash2[idx];
	hash2[idx] = new_KeyValue;
	if (new_KeyValue.key == old_KeyValue.key) {//truong hop new va old cung key -> thay the bang keyvalue moi
		return { -1,-1 };
	}
	return old_KeyValue;
}

// --*-- kiem tra key cua cap keyvalue moi co bi trung lap hay khong --*--
bool checkDuplicate(key_value new_KeyValue, int n) {
	if (new_KeyValue.key == hash1[hash1_func(new_KeyValue.key, n)].key) {//bi trung o hash1
		insert_hash1(new_KeyValue, n);
		return 1;
	}
	else if (new_KeyValue.key == hash2[hash2_func(new_KeyValue.key, n)].key) {//bi trung o hash2 
		insert_hash2(new_KeyValue, n);
		return 1;
	}
	return 0;
}

// --*-- them keyvalue vao bang bam --*--
int insert_key_value(key_value k, int n) {
	if (n == 0) {//khong du cho chua
		return 0;
	}
	if (checkDuplicate(k, n)) {//kiem tra trung lap
		return -1;
	}
	int key = k.key;
	int cnt = 0;
	int i = 1;
	do {
		if (k.key == key) {
			cnt++;
		}
		if (cnt == 3) {
			return 0;
		}
		if (i & 1) {
			k = insert_hash1(k, n);
		}
		else {
			k = insert_hash2(k, n);
		}
		i++;
	} while (k.key != -1);
	return 1;
}

// --*-- khoi tao 1 key value --*--
key_value initKeyValue() {
	key_value t = { -1,-1 };
	cout << "nhap key: ";
	cin >> t.key;
	cout << "nhap value: ";
	cin >> t.value;
	return t;
}

// --*-- in ra cac keyvalue trong bang bam --*--
void outputHash(int n) {
	for (int i = 0; i < n; i++) {
		if (hash1[i].key != -1) {
			cout << hash1[i].key << " -> " << hash1[i].value << endl;
		}
		if (hash2[i].key != -1) {
			cout << hash2[i].key << " -> " << hash2[i].value << endl;
		}
	}
	cout << endl;
}

// --*-- xoa bang bam --*--
void removeHash() {
	delete[] hash1;
	delete[] hash2;
}

// --*-- doc file txt --*--
void readfile(const char* inpRoster, key_value*& h, int& n_use) {
	fstream f;
	f.open(inpRoster, ios::in);
	if (f >> n_use) {
		h = new key_value[n_use];
		for (int i = 0; i < n_use; i++) {
			f >> h[i].key;
			f >> h[i].value;
		}
	}
	else {
		n_use = 0;
	}
	f.close();
}

// --*-- ghi file txt --*--
void writefile(const char* inpRoster, key_value* h, int n_use) {
	fstream f;
	f.open(inpRoster, ios::out);
	f << n_use << endl;
	for (int i = 0; i < n_use; i++) {
		f << h[i].key << " " << h[i].value << endl;
	}
	f.close();
}

int main() {
	int x;
	//int n = 0;
	//fstream f;
	int cuckoo_n = 0;//size cac thang trong bang bam
	do {
		system("cls");
		cout << "---------CUCKOO HASHING---------" << endl;
		cout << "1. nhap 1 day cac key-value" << endl;
		cout << "2. xuat cac cap key-value trong bang bam" << endl;
		cout << "3. them 1 key-value vao bang bam" << endl;
		cout << "4. xoa 1 key-value ra khoi bang bam" << endl;
		cout << "5. lay value tu key cho truoc" << endl;
		cout << "6. thoat" << endl;
		cout << "nhap lua chon: ";
		cin >> x;
		if (x == 1) {

		}

		else if (x == 2) {// xuat cac keyvalue: outputHash(int n)
			outputHash(cuckoo_n);
			cout << endl << "nhap 0 de quay ve: ";
			cin >> x;
		}

		else if (x == 3) {// them 1 keyvalue: insert
			key_value k = initKeyValue();
			int workdone = insert_key_value(k, cuckoo_n);
			if (workdone == 1) {
				cout << "da them thanh cong" << endl;
				//cong viec doc xuat file
				key_value* h = NULL;
				int n = 0;
				readfile("keyvalue.txt", h, n);
				fstream f;
				f.open("keyvalue.txt", ios::out);
				n += 1;
				f << n << endl;
				for (int i = 0; i < n - 1; i++) {
					f << h[i].key << " " << h[i].value << endl;
				}
				f << k.key << " " << k.value << endl;
				f.close();
				delete[] h;
				//ket thuc doc xuat file
			}
			else if (workdone == -1) {
				cout << "da them thanh cong" << endl;
				//cong viec doc xuat file
				key_value* h = NULL;
				int n = 0;
				readfile("keyvalue.txt", h, n);
				fstream f;
				f.open("keyvalue.txt", ios::out);
				f << n << endl;
				for (int i = 0; i < n; i++) {
					if (h[i].key == k.key) {
						h[i].value = k.value;
					}
					f << h[i].key << " " << h[i].value << endl;
				}
				f.close();
				delete[] h;
				//ket thuc doc xuat file
			}
			else {
				initHash(cuckoo_n);
				//cong viec doc xuat file
				key_value* h = NULL;
				int n = 0;
				readfile("keyvalue.txt", h, n);
				fstream f;
				f.open("keyvalue.txt", ios::out);
				f << n + 1 << endl;
				for (int i = 0; i < n - 1; i++) {
					f << h[i].key << " " << h[i].value << endl;
				}
				f << k.key << " " << k.value << endl;
				f.close();
				//ket thuc doc xuat file
				for (int i = 0; i < n - 1; i++) {
					insert_key_value(h[i], cuckoo_n);
					//tao ham bo sung
				}
			}

			
			cout << endl << "nhap 0 de quay ve: ";
			cin >> x;
		}

		else if (x == 4) {// xoa keyvalue: remove_key_value(int key, int n)
			cout << "key can xoa: ";
			int key;
			cin >> key;
			bool workdone = remove_key_value(key, cuckoo_n);
			if (workdone) {
				cout << "da xoa thanh cong" << endl;
				//cong viec doc xuat file
				key_value* h = NULL;
				int n = 0;
				readfile("keyvalue.txt", h, n);
				fstream f;
				f.open("keyvalue.txt", ios::out);
				f << n - 1 << endl;
				for (int i = 0; i < n; i++) {
					if (h[i].key == key) {
						continue;
					}
					f << h[i].key << " " << h[i].value << endl;
				}
				n--;
				f.close();
				delete[] h;
				//ket thuc doc xuat file
			}
			else {
				cout << "khong ton tai key " << key << " trong bang bam" << endl;
			}
			cout << endl << "nhap 0 de quay ve: ";
			cin >> x;
		}

		else if (x == 5) {// lay keyvalue: getValue(int key, int n) 
			cout << "key can lay value: ";
			int key;
			cin >> key;
			int value = getValue(key, cuckoo_n);
			if (value == -1) {
				cout << "khong ton tai key " << key << " trong bang bam" << endl;
			}
			else {
				cout << "value can tim: " << value << endl;
			}
			cout << endl << "nhap 0 de quay ve: ";
			cin >> x;
		}

		else {//thoat
			removeHash();
			break;
		}
	} while (x <= 5);
	system("cls");
	cout << "cam on ban da su dung cuckoo hashing" << endl;
}