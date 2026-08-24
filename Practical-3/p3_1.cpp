#include<bits/stdc++.h>
using namespace std;


string generateKey(string plaintext, string keyword){
    string key = "";
    int j =0;

    for(int i = 0;i<plaintext.length(); i++){
        if(plaintext[i] == ' '){
            key += ' ';
        }else{
            key += toupper(keyword[j % keyword.length()]);
            j++;
        }
    }
    return key;
}

string encrypt(string plaintext,string key){
    string ciphertext = "";

    for(int i = 0; i < plaintext.length();i++){
        if(plaintext[i] == ' '){
            ciphertext +=' ';
            continue;   
        }

        int plainValue = plaintext[i] - 'A';
        int keyValue = key[i] - 'A';

        int cipherValue = (plainValue + keyValue) %26;
        char cipherChar = cipherValue + 'A';

        ciphertext += cipherChar;

    }

    return ciphertext;
}

string decrypt(string ciphertext, string key) {
    string decrypted = "";

    for (int i = 0; i < ciphertext.length(); i++) {
        if (ciphertext[i] == ' ') {
            decrypted += ' ';
            continue;
        }

        int cipherValue = ciphertext[i] - 'A';  
        int keyValue = key[i] - 'A';            

        int plainValue = (cipherValue - keyValue + 26) % 26;  
        char plainChar = plainValue + 'A';

        decrypted += plainChar;
    }

    return decrypted;
}


int main() {
    string plaintext, keyword;

    cout << "Enter Plaintext: ";
    getline(cin, plaintext);

    cout << "Enter Keyword: ";
    getline(cin, keyword);

    for (int i = 0; i < plaintext.length(); i++) {
        plaintext[i] = toupper(plaintext[i]);
    }

    string key = generateKey(plaintext, keyword);
    cout << "\nGenerated Key: " << key << endl;

    string ciphertext = encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}