#pragma once

#include "domain/order.hpp"
#include "i_order_book.hpp"

namespace mt
{
    template <OrderBook TBook> class IMatchingEngine
    {
    public:
        explicit IMatchingEngine(TBook& book) : _book(book)
        {
        }
        virtual ~IMatchingEngine() = default;
        virtual void submitOrder(const Order& order) = 0;

    private:
        TBook& _book;
    };
} // namespace mt