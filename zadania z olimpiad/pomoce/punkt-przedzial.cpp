#include <iostream>
using namespace std;

const int R = 1 << 18;
int tree[2 * R];

void update(int i, int x) {
    i += R;
    tree[i] = x;
    i /= 2;
    while (i > 0) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
        i /= 2;
    }
}

int query(int a, int b) {
    int res = 0;
    a += R - 1;
    b += R + 1;
    while (a / 2 != b / 2) {
        if (a % 2 == 0)
            res += tree[a + 1];
        if (b % 2 == 1)
            res += tree[b - 1];
        a /= 2;
        b /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 0) {
            update(b, c);
        } else {
            cout << query(b, c) << "\n";
        }
    }

    return 0;
}
