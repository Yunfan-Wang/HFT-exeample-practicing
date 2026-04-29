#pragma once

#include <map>
#include <queue>
#include <memory>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

struct Order {
    int id;
    bool isBuy;
    int price;
    int qty;
    bool active = true;
};

class matchingEngine {
private:
    map<int, queue<shared_ptr<Order>>, greater<int>> buys;
    map<int, queue<shared_ptr<Order>>> sells;
    unordered_map<int, shared_ptr<Order>> orders;

    long long totalVolume = 0;

    template <typename Book>
    void cleanTop(Book& book) {
        while (!book.empty()) {
            auto& q = book.begin()->second;
            while (!q.empty() && (!q.front()->active || q.front()->qty==0)){
                q.pop();
            }
            if (q.empty()) {
                book.erase(book.begin());
            } else {
                break;
            }
        }
    }

public:
    void addBuy(int id, int price, int qty) {
        auto incoming = make_shared<Order> (
            Order{id, true, price, qty, true}
        );
        while (incoming->qty > 0) {
            cleanTop(sells);
            if (sells.empty()) break;

            auto bestIt = sells.begin();
            int bestSellPrice = bestIt->first;
            if (bestSellPrice > price) break;

            auto resting = bestIt->second.front();
            int traded = min(incoming->qty, resting->qty);
            incoming->qty -= traded;
            resting->qty -= traded;
            totalVolume += traded;
            if (resting->qty == 0) {
                resting->active = false;
                bestIt->second.pop();
            }

        }
        if (incoming->qty > 0) {
            orders[id] = incoming;
            buys[price].push(incoming);
        }
    }
    void addSell(int id, int price, int qty) {
        auto incoming = make_shared<Order> (
            Order{id, false, price, qty, true}
        );

        while (incoming->qty > 0) {
            cleanTop(buys);

            if (buys.empty()) break;

            auto bestIt = buys.begin();
            int bestBuyPrice = bestIt->first;

            if (bestBuyPrice < price) break;

            auto resting = bestIt->second.front();

            int traded = min(incoming->qty, resting->qty);
            incoming->qty -= traded;
            resting->qty -= traded;
            totalVolume += traded;

            if (resting->qty == 0) {
                resting->active = false;
                bestIt->second.pop();
            }
        }

        if (incoming->qty > 0) {
            orders[id] = incoming;
            sells[price].push(incoming);
        }
    }

    void cancel(int id) {
        auto it = orders.find(id);
        if (it == orders.end()) return;

        it->second->active = false;
        orders.erase(it);
    }

    long long getTotalVolume() const {
        return totalVolume;
    }

    int bestBid() {
        cleanTop(buys);
        if (buys.empty()) return -1;
        return buys.begin()->first;
    }

    int bestAsk() {
        cleanTop(sells);
        if (sells.empty()) return -1;
        return sells.begin()->first;
    }

};
