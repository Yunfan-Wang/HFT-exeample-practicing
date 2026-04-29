#include <bits/stdc++.h>
using namespace std;

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> store;

public:
    void set(string key, string value, int timestamp) {
        store[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (store.find(key) == store.end()) {
            return "";
        }

        auto& arr = store[key];

        int l = 0;
        int r = arr.size() - 1;

        string ans = "";

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (arr[mid].first <= timestamp) {
                ans = arr[mid].second;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return ans;
    }
};