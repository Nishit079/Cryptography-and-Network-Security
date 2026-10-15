#include <iostream>
#include <string>
using namespace std;

// Calculate (base ^ exp) mod n using a simple loop
int power(int base, int exp, int n) {
    int result = 1;
    for (int i = 1; i <= exp; i++) {
        result = (result * base) % n;
    }
    return result;
}

int main() {
    int n, g, a, b;

    // Step 1: agree on n and g
    cout << "Enter prime number (n): ";
    cin >> n;
    cout << "Enter generator (g): ";
    cin >> g;

    // Step 2: Alice
    cout << "Enter Alice's secret number (a): ";
    cin >> a;
    int A = power(g, a, n);          // A = g^a mod n
    cout << "Alice sends A = " << A << endl;

    // Step 3: Bob
    cout << "Enter Bob's secret number (b): ";
    cin >> b;
    int B = power(g, b, n);          // B = g^b mod n
    cout << "Bob sends B = " << B << endl;

    // Step 4 and 5: both compute the shared key
    int K1 = power(B, a, n);         // Alice: K1 = B^a mod n
    int K2 = power(A, b, n);         // Bob:   K2 = A^b mod n

    cout << "Alice's Key K1 = " << K1 << endl;
    cout << "Bob's Key K2   = " << K2 << endl;

    // Caesar cipher
    int key = K1 % 26;
    string text;
    cout << "\nEnter message (UPPERCASE, no spaces): ";
    cin >> text;

    // Encryption
    string cipher = text;
    for (int i = 0; i < text.length(); i++) {
        cipher[i] = (text[i] - 'A' + key) % 26 + 'A';
    }
    cout << "Encrypted Text: " << cipher << endl;

    // Decryption
    string plain = cipher;
    for (int i = 0; i < cipher.length(); i++) {
        plain[i] = (cipher[i] - 'A' - key + 26) % 26 + 'A';
    }
    cout << "Decrypted Text: " << plain << endl;

    return 0;
}