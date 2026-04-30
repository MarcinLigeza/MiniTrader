#pragma once

#include "domain/order.hpp"

#include <algorithm>
#include <deque>

namespace mt
{
    struct Level
    {
        void add(const Order& order)
        {
            _orders.push_back(order);
            _total_quantity.value += order.quantity.value;
        }

        bool remove(OrderId orderId)
        {
            auto it = std::find_if(_orders.begin(), _orders.end(), [&](const Order& o) { return o.id == orderId; });
            if (it != _orders.end())
            {
                _total_quantity.value -= it->quantity.value;
                _orders.erase(it);
                return true;
            }
            return false;
        }

        void reduceFront(Quantity quantity)
        {
            if (_orders.empty())
            {
                return;
            }

            auto& front = _orders.front();
            front.quantity.value -= quantity.value;
            front.filled_quantity.value += quantity.value;
            _total_quantity.value -= quantity.value;

            if (front.quantity.value <= 0)
            {
                _orders.pop_front();
            }
        }

        bool empty() const
        {
            return _orders.empty();
        }

    private:
        std::deque<Order> _orders;
        Quantity _total_quantity{0};
    };

} // namespace mt