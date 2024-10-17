#include <iostream>

using namespace std;

string n;
int res = 0;

void add_one() {
    int i = n.length() - 1;
    while (i >= 0 && n[i] == '9') {
        n[i] = '0';
        i--;
    }
    if (i >= 0) {
        n[i]++;
    } else {
        n = '1' + n;
    }
    res++;
    // cout << "Add one\n";
}

void move() {
    char x = n[0];
    n.erase(n.begin());
    n += x;
    while (n[0] == '0') {
        n.erase(n.begin());
    }
    res++;
    // cout << "Move\n";
}

bool allNine() {
    return (n == string(n.length(), '9'));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    while (n != "1") {
        int i = n.length() - 1;
        int x = n[i] - '0';
        if (allNine()) {
            add_one();
            move();
        } else if (x == 0 || x == 9) {
            move();
        } else {
            while (n[i] != '9') {
                add_one();
            }
        }
    }

    cout << res;

    return 0;
}