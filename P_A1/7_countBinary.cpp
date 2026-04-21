#include <iostream>
using namespace std;

int countBinary(int n) {
    if (n == 1) return 2;
    if (n == 2) return 3;
    return countBinary(n - 1) + countBinary(n - 2);
}

int main() {
    int n;
    cin >> n;

    cout << countBinary(n) << '\n';
    return 0;
}


