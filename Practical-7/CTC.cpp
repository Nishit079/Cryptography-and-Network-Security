#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Remove spaces and convert to UPPERCASE
string cleanText(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c))
            result += toupper(c);
    }
    return result;
}

// ---------------- ENCRYPTION ----------------
string encrypt(string plain, string key) {
    int cols = key.length();
    int rows = (plain.length() + cols - 1) / cols;   // round up

    // Pad extra cells with 'X'
    while (plain.length() < rows * cols)
        plain += 'X';

    // Step 1: write plain text row by row
    char grid[20][20];
    int index = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r][c] = plain[index++];

    // Step 2: read column by column in the order of key (1,2,3...)
    string cipher = "";
    for (int k = 1; k <= cols; k++) {
        for (int c = 0; c < cols; c++) {
            if (key[c] - '0' == k) {          // find column having this key number
                for (int r = 0; r < rows; r++)
                    cipher += grid[r][c];
            }
        }
    }
    return cipher;
}

// ---------------- DECRYPTION ----------------
string decrypt(string cipher, string key) {
    int cols = key.length();
    int rows = cipher.length() / cols;           // e.g. 28 / 7 = 4

    // Step 1: fill cipher text column by column in the order of key
    char grid[20][20];
    int index = 0;
    for (int k = 1; k <= cols; k++) {
        for (int c = 0; c < cols; c++) {
            if (key[c] - '0' == k) {
                for (int r = 0; r < rows; r++)
                    grid[r][c] = cipher[index++];
            }
        }
    }

    // Step 2: read row by row to get plain text
    string plain = "";
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            plain += grid[r][c];

    return plain;
}

int main() {
    string text, key;
    int choice;

    cout << "1. Encryption\n2. Decryption\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter text: ";
    getline(cin, text);
    text = cleanText(text);

    cout << "Enter key (e.g. 4312567): ";
    cin >> key;

    if (choice == 1)
        cout << "Cipher Text: " << encrypt(text, key) << endl;
    else
        cout << "Plain Text : " << decrypt(text, key) << endl;

    return 0;
}