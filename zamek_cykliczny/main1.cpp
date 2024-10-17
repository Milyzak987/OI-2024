#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct Result {
    int positionFromEnd;
    int consecutiveNines;
    int dif;
};

string n;
int res = 0;

bool oneZeros() {
    int x = n[1], i = 1;
    while (x == '0') {
        if (i == n.length() - 1) {
            return true;
        }
        i++;
        x = n[i];
    }
    return false;
}

Result findNineAndDetails() {
    int length = n.length();
    int start = (length > 7) ? length - 7 : 0;
    int consecutiveNines = 0;
    int firstNinePos = -1;
    string numbersAfter = "";

    for (int i = length - 1; i >= start; --i) {
        if (n[i] == '9') {
            firstNinePos = i;
            break;
        }
    }

    if (firstNinePos == -1) {
        return {-1, -1, 0};
    }

    int i = firstNinePos;
    while (i >= 0 && n[i] == '9') {
        consecutiveNines++;
        i--;
    }

    if (firstNinePos < length - 1) {
        numbersAfter = n.substr(firstNinePos + 1);
    }

    int positionFromEnd = length - firstNinePos;

    int base = pow(10, positionFromEnd - 1);
    int dif = 0;
    if (numbersAfter != "") {
        dif = base - stoi(numbersAfter) - 1;
    }

    return {positionFromEnd, consecutiveNines, dif};
}

int endNines() {
    int i = n.length() - 2;
    int count = 0;
    while (i >= 0 && n[i] == '9') {
        count++;
        i--;
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    if (n == "1") {
        cout << 0;
        return 0;
    }
    if (n[0] == '1' && oneZeros()) {
        cout << 1;
        return 0;
    }

    Result result = findNineAndDetails();
    if (result.dif < result.consecutiveNines && result.positionFromEnd != 1 && result.positionFromEnd != -1) {
        for(int i = n.length() - 1; i > n.length() - result.positionFromEnd; i--){
            n[i] = '9';
        }
        res += result.dif;
    }
    
    int count = endNines();
    if (n[n.length() - 1] == '0' && n[n.length() - 2] == '9' && count <= 9) {
        res += count;
    }

    int l = n.length() - count;
    int j = n.length() - 1;
    if (n[j] != '0') {
        res += 9 - (n[j] - '0');
    }
    for (int i = 0; i < l - 1; i++) {
        int x = n[i] - '0';
        if (n[i] != '0') {
            res += 10 - x;
        }
    }

    cout << res + 2;

    return 0;
}