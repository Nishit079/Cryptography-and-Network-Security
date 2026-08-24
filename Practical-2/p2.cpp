#include <iostream>
#include <string>
using namespace std;


string caesarDecrypt(string cipher, int key) {
    string result = "";
    for (char c : cipher) {
        if (isupper(c)) {
            result += char(((c - 'A' - key + 26) % 26) + 'A');
        }
        else if (islower(c)) {
            result += char(((c - 'a' - key + 26) % 26) + 'a');
        }
        else {
            result += c;
        }
    }
    return result;
}

int main() {
    string cipherText;

    cout << "Enter the Cipher Text: ";
    getline(cin, cipherText);

    cout << "\nBrute-Force Attack on Caesar Cipher\n";
    cout << "------------------------------------\n";

    string results[26];
    for (int key = 0; key < 26; key++) {
        results[key] = caesarDecrypt(cipherText, key);
        cout << "Key " << key << " : " << results[key] << endl;
    }

    int chosenKey;
    cout << "\nLook at all 26 results above.\n";
    cout << "Enter the Key number which looks like a normal, logical English sentence: ";
    cin >> chosenKey;

    while (chosenKey < 0 || chosenKey > 25) {
        cout << "Invalid key! Please enter a number between 0 and 25: ";
        cin >> chosenKey;
    }

    cout << "\n------------------------------------\n";
    cout << "FINAL RESULT\n";
    cout << "------------------------------------\n";
    cout << "Cipher Text (Question) : " << cipherText << endl;
    cout << "Key Found               : " << chosenKey << endl;
    cout << "Plain Text (Answer)     : " << results[chosenKey] << endl;
    cout << "------------------------------------\n";

    return 0;
}