/*C. To develop a C program that performs encryption and decryption of text using the Caesar Cipher algorithm by reading plaintext from a file, applying a specified key for encryption/decryption, and storing the resulting output in separate files using file handling operations.*/

#include <iostream>
#include <fstream>
using namespace std;
 
char encryptChar(char ch, int key) {
    if (ch >= 'a' && ch <= 'z')
        return (char)(((ch - 'a' + key) % 26 + 26) % 26 + 'a');
    else if (ch >= 'A' && ch <= 'Z')
        return (char)(((ch - 'A' + key) % 26 + 26) % 26 + 'A');
    return ch;
}
 
char decryptChar(char ch, int key) {
    if (ch >= 'a' && ch <= 'z')
        return (char)(((ch - 'a' - key) % 26 + 26) % 26 + 'a');
    else if (ch >= 'A' && ch <= 'Z')
        return (char)(((ch - 'A' - key) % 26 + 26) % 26 + 'A');
    return ch;
}
 
int main() {
    int key;
    char ch;
 
    cout << "Enter key (shift value): ";
    cin >> key;
 
    // ---------- ENCRYPTION ----------
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Error: input.txt not found. Please create it first." << endl;
        return 1;
    }
    ofstream fout("encrypted.txt");
 
    while (fin.get(ch)) {
        fout.put(encryptChar(ch, key));
    }
    fin.close();
    fout.close();
    cout << "Encryption complete. See encrypted.txt" << endl;
 
    // ---------- DECRYPTION ----------
    ifstream fin2("encrypted.txt");
    ofstream fout2("decrypted.txt");
 
    while (fin2.get(ch)) {
        fout2.put(decryptChar(ch, key));
    }
    fin2.close();
    fout2.close();
    cout << "Decryption complete. See decrypted.txt" << endl;
 
    return 0;
} 
