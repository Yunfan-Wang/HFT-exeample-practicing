#include "lru.hpp"

int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cout << cache.get(1) << "\n"; // getting 10

    cache.put(3, 30);             // now evicts key 2

    cout << cache.get(2) << "\n"; // -1?
    cout << cache.get(3) << "\n"; // 30?
}