#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

    int count_even = 0;
    int count_odd = 0;

    vector<int> even, odd;

    for_each(vec.begin(), vec.end(), [&](int x) {
        if (x % 2 == 0) {
            count_even++;
            even.push_back(x);
        } else {
            count_odd++;
            odd.push_back(x);
        }
    });

    cout << "So luong chan: " << count_even << endl;
    for (auto item : even) {
        cout << item << " ";
    }
    cout << endl;

    cout << "So luong le: " << count_odd << endl;
    for (auto item : odd) {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}

