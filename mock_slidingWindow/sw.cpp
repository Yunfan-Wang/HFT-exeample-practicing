#include <bits/stdc++.h>
using namespace std;

class SlidingMedian {
private:
    multiset<int> low;
    multiset<int> high;

    void rebalance() {
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            high.insert(*it);
            low.erase(it);
        }

        while (low.size() < high.size()) {
            auto it = high.begin();
            low.insert(*it);
            high.erase(it);
        }
    }

public:
    void add(int x) {
        if (low.empty() || x <= *low.rbegin()) {
            low.insert(x);
        } else {
            high.insert(x);
        }

        rebalance();
    }

    void remove(int x) {
        auto itLow = low.find(x);

        if (itLow != low.end()) {
            low.erase(itLow);
        } else {
            auto itHigh = high.find(x);
            if (itHigh != high.end()) {
                high.erase(itHigh);
            }
        }

        rebalance();
    }

    double median(int k) {
        if (k % 2 == 1) {
            return *low.rbegin();
        }

        return ((double)*low.rbegin() + (double)*high.begin()) / 2.0;
    }
};

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    SlidingMedian sm;
    vector<double> ans;
    for (int i = 0; i < nums.size(); i++) {
        sm.add(nums[i]);

        if (i >= k) {
            sm.remove(nums[i - k]);
        }

        if (i >= k - 1) {
            ans.push_back(sm.median(k));
        }
    }

    return ans;
}