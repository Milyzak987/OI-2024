#include <iostream>
using namespace std;

const int R = 1 << 18;
int tree[2 * R];

void update(int a, int b, int x) {
    a += R - 1;
    b += R + 1;
    while (a / 2 != b / 2) {
        if (a % 2 == 0)
            tree[a + 1] += x;
        if (b % 2 == 1)
            tree[b - 1] += x;
        a /= 2;
        b /= 2;
    }
}

int query(int i) {
    int res = 0;
    i += R;
    while (i) {
        res += tree[i];
        i /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        int a, b;
        cin >> a >> b;

        if (a == 0) {
            int c, d;
            cin >> c >> d;
            update(b, c, d);
        } else {
            cout << query(b) << "\n";
        }
    }

    return 0;
}