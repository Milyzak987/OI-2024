#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long a, b;
    cin >> a >> b;

    long long dif = b - a, res;
    if(dif % 4 == 0 || dif % 4 == 2){
        res = dif;
    } else if(dif % 4 == 1){
        res = dif - 1;
    } else{
        res = dif + 1;
    }

    cout << res;

    return 0;
}
