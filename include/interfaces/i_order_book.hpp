#pragma once

#include <concepts>
#include <optional>
#include <vector>

#include "domain/order.hpp"

namespace mt
{
    struct Level
    {
        Price price;
        Quantity quantity;
        int order_count;
    };

    struct BookSnapshot
    {
        std::vector<Level> bids;
        std::vector<Level> asks;
    };

    class IOrderBook
    {
    public:
        virtual ~IOrderBook() = default;
        virtual void addOrder(const Order& order) = 0;
        virtual bool cancelOrder(OrderId orderId) = 0;
        virtual BookSnapshot snapshot(int depth = 10) const = 0;
        virtual std::optional<Price> bestBid() const = 0;
    };

    template <typename T>
    concept OrderBook = requires(T book, Order order, OrderId orderId) {
        { book.addOrder(order) } -> std::same_as<void>;
        { book.cancelOrder(orderId) } -> std::same_as<bool>;
        { book.snapshot(10) } -> std::same_as<BookSnapshot>;
        { book.bestBid() } -> std::same_as<std::optional<Price>>;
    };

} // namespace mt