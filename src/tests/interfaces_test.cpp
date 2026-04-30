#include <gtest/gtest.h>

#include "interfaces/i_order_book.hpp"

using namespace mt;

TEST(OrderBookInterface, ConceptCheck)
{
    // This test will fail to compile if the concept requirements are not met
    struct MockOrderBook : IOrderBook
    {
        void addOrder(const Order& order) override
        {
        }
        bool cancelOrder(OrderId orderId) override
        {
            return true;
        }
        BookSnapshot snapshot(int depth = 10) const override
        {
            return {};
        }
        std::optional<Price> bestBid() const override
        {
            return std::nullopt;
        }
    };

    MockOrderBook book;
    EXPECT_TRUE((OrderBook<MockOrderBook>));
}