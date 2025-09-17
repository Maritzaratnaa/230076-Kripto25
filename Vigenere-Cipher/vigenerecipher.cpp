/*
Nama        : Maritza Ratnamaya N
NPM         : 140810230076
Deskripsi   : Program enkripsi dan dekripsi menggunakan algoritma Vigenere Cipher
*/

#include <iostream>
#include <string>
using namespace std;

string enkripsi(const string &pt, const string &key) {
    string ct = "";
    int keyLength = key.length();
    int keyIndex = 0;

    for (char c : pt) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[keyIndex % keyLength]) - 'A';
            char enkrip = ( (c - base + k) % 26 ) + base;
            ct += enkrip;
            keyIndex++;
        } 
    }
    return ct;
}

string dekripsi(const string &ct, const string &key) {
    string pt = "";
    int keyLength = key.length();
    int keyIndex = 0;

    for (char c : ct) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[keyIndex % keyLength]) - 'A';
            char dec = ( (c - base - k + 26) % 26 ) + base;
            pt += dec;
            keyIndex++;
        }
    }
    return pt;
}

int main() {
    int pilihan;
    string text, key;

    while (true) {
        cout << "\n------ Vigenere Cipher ------\n";
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "0. Keluar\n";
        cout << "=> ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "\n--- Enkripsi ---\n";
            cout << "Plaintext  : ";
            getline(cin, text);
            cout << "Key        : ";
            getline(cin, key);
            string cipher = enkripsi(text, key);
            cout << "Ciphertext : " << cipher << endl;
        } 
        else if (pilihan == 2) {
            cout << "\n--- Dekripsi ---\n";
            cout << "Ciphertext : ";
            getline(cin, text);
            cout << "Key        : ";
            getline(cin, key);
            string plain = dekripsi(text, key);
            cout << "Plaintext  : " << plain << endl;
        } 
        else if (pilihan == 0) {
            break;
        } 
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}
