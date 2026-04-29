#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int capacity;

    // front = most recently used
    // back  = least recently used
    list<pair<int, int>> cache; // {key, value}

    unordered_map<int, list<pair<int, int>>::iterator> mp;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (mp.find(key) == mp.end()) {
            return -1;
        }

        auto it = mp[key];
        int value = it->second;

        // move this node to front for use
        cache.splice(cache.begin(), cache, it);

        return value;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            auto it = mp[key];
            it->second = value;

            // now we move updated node to front
            cache.splice(cache.begin(), cache, it);
            return;
        }

        if (cache.size() == capacity) {
            auto [oldKey, oldVal] = cache.back();
            mp.erase(oldKey);
            cache.pop_back();
        }

        cache.push_front({key, value});
        mp[key] = cache.begin();
    }
};