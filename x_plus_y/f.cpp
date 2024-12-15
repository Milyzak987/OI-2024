#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Funkcja pomocnicza do obliczenia największego prostokąta w histogramie
int largestRectangleInHistogram(const vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        int h = (i < n) ? heights[i] : 0; // Dodajemy "0" na końcu histogramu
        while (!s.empty() && heights[s.top()] >= h) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        s.push(i);
    }

    return maxArea;
}

// Funkcja główna do znajdowania największego prostokąta w macierzy
int largestRectangleInMatrix(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;

    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> heights(m, 0);
    int maxArea = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 0) {
                heights[j] += 1;
            } else {
                heights[j] = 0;
            }
        }
        maxArea = max(maxArea, largestRectangleInHistogram(heights));
    }

    return maxArea;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << largestRectangleInMatrix(matrix) << endl;

    return 0;
}