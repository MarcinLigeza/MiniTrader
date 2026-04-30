#include "order_book.hpp"

#include <algorithm>

using namespace mt;

void OrderBook::addOrder(const Order& order)
{
    if (order.side == Side::Buy)
    {
        auto it = _bids.find(order.price);
        if (auto it = _bids.find(order.price); it == _bids.end())
        {
            _bids.emplace(order.price, std::deque<Order, std::greater<Price>>{order});
        }
        else
        {
            it->second.push_back(order);
        }
    }
    else
    {
        auto it = _asks.find(order.price);
        if (auto it = _asks.find(order.price); it == _asks.end())
        {
            _asks.emplace(order.price, std::deque<Order>{order});
        }
        else
        {
            it->second.push_back(order);
        }
    }
}

bool OrderBook::cancelOrder(OrderId orderId)
{
    for (auto& [price, orders] : _bids)
    {
        auto it = std::find_if(orders.begin(), orders.end(), [&orderId](const Order& o) { return o.id == orderId; });
        if (it != orders.end())
        {
            orders.erase(it);
            if (orders.empty())
            {
                _bids.erase(price);
            }
            return true;
        }
    }

    for (auto& [price, orders] : _asks)
    {
        auto it = std::find_if(orders.begin(), orders.end(), [&orderId](const Order& o) { return o.id == orderId; });
        if (it != orders.end())
        {
            orders.erase(it);
            if (orders.empty())
            {
                _asks.erase(price);
            }
            return true;
        }
    }

    return false;
}

BookSnapshot mt::OrderBook::snapshot(int depth) const
{
    BookSnapshot snapshot;

    for (const auto& [price, orders] : _bids)
    {
        if (snapshot.bids.size() >= depth)
        {
            break;
        }
        snapshot.bids.emplace_back()
    }
}
