#pragma once

#include "interfaces/i_order_book.hpp"

#include "domain/order.hpp"
#include "domain/trade.hpp"

#include <deque>
#include <map>

namespace mt
{
    class OrderBook : public IOrderBook
    {
        void addOrder(const Order& order) override;
        bool cancelOrder(OrderId orderId) override;
        BookSnapshot snapshot(int depth = 10) const override;
        std::optional<Price> bestBid() const override;

        std::vector<Trade> match(const Order& incoming_order);

    private:
        std::map<Price, std::deque<Order, std::greater<Price>>> _bids;
        std::map<Price, std::deque<Order>> _asks;

        bool removeOrder(OrderId orderId);
    };

} // namespace mt