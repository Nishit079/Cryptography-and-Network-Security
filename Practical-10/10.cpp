#include <iostream>
using namespace std;
int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {            // base case: remainder is zero
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extendedGCD(b, a % b, x1, y1);   // recursive call
    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}
int main() {
    int a, m, x, y;

    cout << "Enter a: ";
    cin >> a;
    cout << "Enter m: ";
    cin >> m;

    int g = extendedGCD(a, m, x, y);

    cout << "\nGCD(" << a << ", " << m << ") = " << g << endl;
    cout << "x = " << x << ", y = " << y << endl;
    cout << "Verify: " << a << " * " << x << " + " << m << " * " << y
         << " = " << a * x + m * y << endl;
    if (g == 1) {
        int inverse = (x % m + m) % m;       // make x positive
        cout << "Modular inverse of " << a << " modulo " << m
             << " = " << inverse << endl;
    } else {
        cout << "Modular inverse does not exist (gcd is not 1)." << endl;
    }

    return 0;
}


