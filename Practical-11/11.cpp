#include <iostream>
using namespace std;

// Calculate (base ^ exp) mod n using a simple loop
long long power(long long base, long long exp, long long n) {
    long long result = 1;
    for (long long i = 1; i <= exp; i++) {
        result = (result * base) % n;
    }
    return result;
}

// Calculate gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int p, q, e, d, M;

    // Step 1: Select two prime numbers
    cout << "Enter prime number p: ";
    cin >> p;
    cout << "Enter prime number q: ";
    cin >> q;

    // Step 2: Calculate n
    int n = p * q;

    // Step 3: Calculate Euler's Totient
    int phi = (p - 1) * (q - 1);

    // Step 4: Select public exponent e  (1 < e < phi and gcd(e, phi) = 1)
    cout << "Enter public exponent e: ";
    cin >> e;
    if (e <= 1 || e >= phi || gcd(e, phi) != 1) {
        cout << "Invalid e! It must satisfy 1 < e < phi and gcd(e, phi) = 1." << endl;
        return 0;
    }

    // Step 5: Calculate private exponent d  (e * d mod phi = 1)
    for (d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            break;
    }

    cout << "\nn = " << n << endl;
    cout << "phi(n) = " << phi << endl;
    cout << "Public Key  = (" << e << ", " << n << ")" << endl;
    cout << "Private Key = (" << d << ", " << n << ")" << endl;

    // Step 6: Encryption  C = M^e mod n
    cout << "\nEnter message M (number less than " << n << "): ";
    cin >> M;
    long long C = power(M, e, n);
    cout << "Encrypted Message C = " << C << endl;

    // Step 7: Decryption  M = C^d mod n
    long long decrypted = power(C, d, n);
    cout << "Decrypted Message M = " << decrypted << endl;

    return 0;
}