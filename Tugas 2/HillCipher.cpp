/*
Nama        : Maritza Ratnamaya N
NPM         : 140810230076
Deskripsi   : Program enkripsi, dekripsi, dan mencari kunci Hill Cripher
*/

#include <iostream>
#include <cstring>
using namespace std;

int determinan(int key[2][2]) {
    return (key[0][0]*key[1][1] - key[0][1]*key[1][0]) % 26;
}

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; 
}

bool inverseKey(int key[2][2], int invKey[2][2]) {
    int det = determinan(key);
    det = (det + 26) % 26;
    if (gcd(det, 26) != 1) {
        return false;
    }
    int detInv = inverse(det, 26);

    invKey[0][0] = ( key[1][1] * detInv) % 26;
    invKey[1][1] = ( key[0][0] * detInv) % 26;
    invKey[0][1] = (-key[0][1] * detInv) % 26;
    invKey[1][0] = (-key[1][0] * detInv) % 26;

    for (int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            if (invKey[i][j] < 0) invKey[i][j] += 26;
        }
    }
    return true;
}

void multiply(int a[2][2], int b[2][2], int res[2][2]) {
    for (int i=0;i<2;i++) {
        for (int j=0;j<2;j++) {
            res[i][j] = 0;
            for (int k=0;k<2;k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
            res[i][j] %= 26;
        }
    }
}

void enkripsi(int key[2][2], int input[2], int output[2]) {
    for (int i=0; i<2; i++) {
        output[i] = (key[i][0]*input[0] + key[i][1]*input[1]) % 26;
    }
}

void dekripsi(int invKey[2][2], int input[2], int output[2]) {
    for (int i=0; i<2; i++) {
        output[i] = (invKey[i][0]*input[0] + invKey[i][1]*input[1]) % 26;
    }
}

int main() {
    int key[2][2], invKey[2][2];
    int pilihan;
    char text[100];

    cout << " -------------------------------" << endl;
    cout << "|------ Hill Cipher (2x2) ------|" << endl;
    cout << " -------------------------------" << endl;

    do {
        cout << "Menu:\n";
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "3. Mencari kunci\n";
        cout << "0. Keluar\n";
        cout << "=> ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "Matriks key 2x2 :\n";
            cin >> key[0][0] >> key[0][1] >> key[1][0] >> key[1][1];
            cin.ignore();
            cout << "Plaintext (kapital A-Z): ";
            cin.getline(text, 100);

            int n = strlen(text);
            if (n % 2 != 0) strcat(text, "X");

            char cipher[100]; int idx = 0;
            for (int i=0; i<n; i+=2) {
                int p[2] = { text[i]-'A', text[i+1]-'A' };
                int c[2];
                enkripsi(key, p, c);
                cipher[idx++] = c[0] + 'A';
                cipher[idx++] = c[1] + 'A';
            }
            cipher[idx] = '\0';
            cout << "Ciphertext: " << cipher << endl;
            cout << "--------------------------------" << endl;
        } else if (pilihan == 2) {
            cout << "Matriks key 2x2 :\n";
            cin >> key[0][0] >> key[0][1] >> key[1][0] >> key[1][1];
            cin.ignore();
            cout << "Ciphertext (kapital A-Z): ";
            cin.getline(text, 100);

            if (!inverseKey(key, invKey)) {
                cout << "Tidak ditemukan.\n";
                continue;
            }

            int n = strlen(text);
            char plain[100]; int idx = 0;
            for (int i=0; i<n; i+=2) {
                int c[2] = { text[i]-'A', text[i+1]-'A' };
                int p[2];
                dekripsi(invKey, c, p);
                plain[idx++] = p[0] + 'A';
                plain[idx++] = p[1] + 'A';
            }
            plain[idx] = '\0';
            cout << "Plaintext: " << plain << endl;
            cout << "--------------------------------" << endl;
        } else if (pilihan == 3) {
            char plain[10], cipher[10];
            cout << "Plaintext 4 huruf (kapital A-Z): ";
            cin.getline(plain, 10);
            cout << "Ciphertext 4 huruf (kapital A-Z): ";
            cin.getline(cipher, 10);

            int P[2][2], C[2][2];
            P[0][0] = plain[0]-'A'; P[1][0] = plain[1]-'A';
            P[0][1] = plain[2]-'A'; P[1][1] = plain[3]-'A';

            C[0][0] = cipher[0]-'A'; C[1][0] = cipher[1]-'A';
            C[0][1] = cipher[2]-'A'; C[1][1] = cipher[3]-'A';

            int Pinv[2][2], K[2][2];
            if (!inverseKey(P, Pinv)) {
                cout << "Tidak ditemukan.\n";
                continue;
            }
            multiply(C, Pinv, K);

            cout << "Matriks kunci Hill Cipher :\n";
            cout << K[0][0] << " " << K[0][1] << endl;
            cout << K[1][0] << " " << K[1][1] << endl;
            cout << "--------------------------------" << endl;
        }

    } while (pilihan != 0);

}
