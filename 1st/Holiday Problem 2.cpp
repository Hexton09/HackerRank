#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std; // Added this line

long long minConsecutiveDays(long long n, vector<long long>& temperatures) {
    set<long long> uniqueTemperatures(temperatures.begin(), temperatures.end());
    long long numUniqueTemperatures = uniqueTemperatures.size();

    unordered_map<long long, long long> frequency;
    long long left = 0;
    long long minDays = n;

    for (long long right = 0; right < n; ++right) {
        long long temp = temperatures[right];
        frequency[temp]++;

        while (frequency.size() == static_cast<size_t>(numUniqueTemperatures)) {
            minDays = min(minDays, right - left + 1);
            frequency[temperatures[left]]--;

            if (frequency[temperatures[left]] == 0) {
                frequency.erase(temperatures[left]);
            }

            left++;
        }
    }

    return minDays;
}

int main() {
    long long n;
    cin >> n;
    vector<long long> temperatures(n);

    for (long long i = 0; i < n; ++i) {
        cin >> temperatures[i];
    }

    long long result = minConsecutiveDays(n, temperatures);
    cout << result << endl;

return 0;
}
