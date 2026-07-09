#include <iostream>
#include <string>
using namespace std;
 
string modEncrypt(string text) {
    for (char &ch : text) {
        if (ch >= 'a' && ch <= 'z') {
            int idx = ch - 'a';
            idx = (idx % 2 == 0) ? (idx + 1) % 26 : (idx - 1 + 26) % 26;
            ch = (char)(idx + 'a');
        } else if (ch >= 'A' && ch <= 'Z') {
            int idx = ch - 'A';
            idx = (idx % 2 == 0) ? (idx + 1) % 26 : (idx - 1 + 26) % 26;
            ch = (char)(idx + 'A');
        }
    }
    return text;
}
 
string modDecrypt(string text) {
    for (char &ch : text) {
        if (ch >= 'a' && ch <= 'z') {
            int idx = ch - 'a';
            idx = (idx % 2 != 0) ? (idx - 1 + 26) % 26 : (idx + 1) % 26;
            ch = (char)(idx + 'a');
        } else if (ch >= 'A' && ch <= 'Z') {
            int idx = ch - 'A';
            idx = (idx % 2 != 0) ? (idx - 1 + 26) % 26 : (idx + 1) % 26;
            ch = (char)(idx + 'A');
        }
    }
    return text;
}
 
int main() {
    string plaintext;
 
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
 
    string cipher = modEncrypt(plaintext);
    cout << "\nEncrypted text: " << cipher << endl;
 
    string decrypted = modDecrypt(cipher);
    cout << "Decrypted text: " << decrypted << endl;
 
    return 0;
}
