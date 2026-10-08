#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

void inputKeyMatrix(vector<vector<int>>& key, int n) {
    cout << "Enter the " << n * n << " numbers for the " << n << "x" << n << " key matrix row by row:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < n; j++) {
            cin >> key[i][j];
        }
    }
}

void displayMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < (int)matrix.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)matrix[i].size(); j++) {
            cout << matrix[i][j];
            if (j != (int)matrix[i].size() - 1) cout << " ";
        }
        cout << "]" << endl;
    }
}

vector<vector<int>> multiplyKeyVector(const vector<vector<int>>& key, const vector<vector<int>>& vec, int n) {
    vector<vector<int>> result(n, vector<int>(1, 0));
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += key[i][j] * vec[j][0];
        }
        result[i][0] = sum % 26;
        if (result[i][0] < 0) result[i][0] += 26;
    }
    return result;
}

int main() {
    int n;
    string msg;

    cout << "Enter the dimension of the square key matrix: ";
    cin >> n;

    vector<vector<int>> key(n, vector<int>(n));
    inputKeyMatrix(key, n);

    cout << "\nKey Matrix:" << endl;
    displayMatrix(key);

    cin.ignore();
    cout << "\nEnter Plaintext: ";
    getline(cin, msg);

    string cleanMsg = "";
    for (char c : msg) {
        if (c != ' ') {
            cleanMsg += static_cast<char>(toupper(static_cast<unsigned char>(c)));
        }
    }
    msg = cleanMsg;

    int remainder = msg.length() % n;
    if (remainder != 0) {
        for (int i = 0; i < n - remainder; i++) {
            msg += 'X';
        }
    }

    cout << "Processed Plaintext: " << msg << endl;

    vector<int> nums;
    for (char c : msg) {
        nums.push_back(c - 'A');
    }

    cout << "Numerical values: [";
    for (int i = 0; i < (int)nums.size(); i++) {
        cout << nums[i];
        if (i != (int)nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    string finalCipher = "";
    for (int i = 0; i < (int)nums.size(); i += n) {
        vector<vector<int>> vec(n, vector<int>(1));
        for (int j = 0; j < n; j++) {
            vec[j][0] = nums[i + j];
        }

        cout << "\nBlock '" << msg.substr(i, n) << "' Vector:" << endl;
        displayMatrix(vec);

        vector<vector<int>> result = multiplyKeyVector(key, vec, n);

        cout << "Result (Key * Vector) mod 26:" << endl;
        displayMatrix(result);

        for (int j = 0; j < n; j++) {
            finalCipher += static_cast<char>(result[j][0] + 'A');
        }
    }

    cout << "\nEncrypted Text: " << finalCipher << endl;

    return 0;
}

