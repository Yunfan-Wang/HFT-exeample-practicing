#include "match.hpp"


int main() {
    matchingEngine engine;

    engine.addBuy(1, 100, 10);
    engine.addBuy(2, 101, 5);
    engine.addSell(3, 99, 8);

    cout << "Volume: " << engine.getTotalVolume() << "\n";
    cout << "Best bid: " << engine.bestBid() << "\n";
    cout << "Best ask: " << engine.bestAsk() << "\n";
}