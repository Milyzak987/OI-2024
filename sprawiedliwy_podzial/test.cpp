#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> bajtyna(n);
    vector<int> bitek(n);

    for (int i = 0; i < n; ++i) {
        cin >> bajtyna[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> bitek[i];
    }

    vector<int> bajtyna2 = {0};
    vector<int> bitek2 = {0};
    vector<int> answer;

    for (int i = 0; i < n; ++i) {
        int sumBajtyna2 = accumulate(bajtyna2.begin(), bajtyna2.end(), 0);
        int sumBitek2 = accumulate(bitek2.begin(), bitek2.end(), 0);

        if (sumBajtyna2 < sumBitek2) {
            answer.push_back(0);
            bajtyna2.push_back(bajtyna[i]);
        } else {
            answer.push_back(1);
            bitek2.push_back(bitek[i]);
        }
    }

    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i] << " ";
    }
    cout << endl;

    return 0;
}
