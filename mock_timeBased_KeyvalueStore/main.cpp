#include <tb.hpp>

int main() {
    TimeMap tm;

    tm.set("AAPL", "100", 1);
    tm.set("AAPL", "105", 3);
    tm.set("AAPL", "110", 5);

    cout << tm.get("AAPL", 0) << "\n"; // ""
    cout << tm.get("AAPL", 1) << "\n"; // 100
    cout << tm.get("AAPL", 4) << "\n"; // 105
    cout << tm.get("AAPL", 5) << "\n"; // 110
}