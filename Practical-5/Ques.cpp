#include <iostream>
#include <string>
using namespace std;
 
// ---------- ENCRYPTION ----------
string encrypt(string text, int rails) {
    // Remove spaces from the plaintext
    string plain = "";
    for (char c : text)
        if (c != ' ')
            plain += c;
 
    int n = plain.length();
 
    // Create a 2D grid of size rails x n, filled with '\n' (empty marker)
    char fence[rails][n];
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < n; j++)
            fence[i][j] = '\n';
 
    int row = 0;
    int dir = 1; // 1 = moving down, -1 = moving up
 
    // Place each character in its zig-zag position
    for (int i = 0; i < n; i++) {
        fence[row][i] = plain[i];
 
        if (row == 0) dir = 1;
        else if (row == rails - 1) dir = -1;
 
        row += dir;
    }
 
    // Read the grid row by row to build the ciphertext
    string cipher = "";
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < n; j++)
            if (fence[i][j] != '\n')
                cipher += fence[i][j];
 
    return cipher;
}
 
// ---------- DECRYPTION ----------
string decrypt(string cipher, int rails) {
    int n = cipher.length();
 
    // Step 1: mark the zig-zag pattern with a placeholder ('*')
    char fence[rails][n];
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < n; j++)
            fence[i][j] = '\n';
 
    int row = 0;
    int dir = 1;
    for (int i = 0; i < n; i++) {
        fence[row][i] = '*';
 
        if (row == 0) dir = 1;
        else if (row == rails - 1) dir = -1;
 
        row += dir;
    }
 
    // Step 2: fill the '*' positions with ciphertext characters, row by row
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < n; j++) {
            if (fence[i][j] == '*' && index < n) {
                fence[i][j] = cipher[index++];
            }
        }
    }
 
    // Step 3: read the grid in zig-zag order to recover the plaintext
    string plain = "";
    row = 0;
    dir = 1;
    for (int i = 0; i < n; i++) {
        plain += fence[row][i];
 
        if (row == 0) dir = 1;
        else if (row == rails - 1) dir = -1;
 
        row += dir;
    }
 
    return plain;
}
 
// ---------- MAIN ----------
int main() {
    int choice, rails;
    string text;
 
    cout << "1. Encrypt\n2. Decrypt\nEnter your choice: ";
    cin >> choice;
    cin.ignore(); // clear newline before getline
 
    cout << "Enter number of rails: ";
    cin >> rails;
    cin.ignore();
 
    if (choice == 1) {
        cout << "Enter plaintext: ";
        getline(cin, text);
        cout << "Ciphertext: " << encrypt(text, rails) << endl;
    } else if (choice == 2) {
        cout << "Enter ciphertext: ";
        getline(cin, text);
        cout << "Plaintext: " << decrypt(text, rails) << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
 
    return 0;
}
 