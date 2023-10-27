#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;

    int arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + N);

    int maxFrequency = 1;
    int currentFrequency = 1;
    int distinctElementsWithMaxFrequency = 1;

    for (int i = 1; i < N; i++) {
        if (arr[i] == arr[i - 1]) {
            currentFrequency++;
        } else {
            if (currentFrequency > maxFrequency) {
                maxFrequency = currentFrequency;
                distinctElementsWithMaxFrequency = 1;
            } else if (currentFrequency == maxFrequency) {
                distinctElementsWithMaxFrequency++;
            }
            currentFrequency = 1;
        }
    }

    if (currentFrequency > maxFrequency) {
        maxFrequency = currentFrequency;
        distinctElementsWithMaxFrequency = 1;
    } else if (currentFrequency == maxFrequency) {
        distinctElementsWithMaxFrequency++;
    }

    cout << maxFrequency << " " << distinctElementsWithMaxFrequency << endl;

    return 0;
}

