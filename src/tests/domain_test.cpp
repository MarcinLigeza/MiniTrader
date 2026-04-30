#include <gtest/gtest.h>

#include "domain/messages.hpp"
#include "domain/order.hpp"
#include "domain/trade.hpp"

using namespace mt;

TEST(DomainTypes, PriceComparison)
{
    Price p1(100);
    Price p2(100.1);

    EXPECT_EQ(p1, p2);

    p2 = Price(99);
    EXPECT_GT(p1, p2);
}

TEST(DomainTypes, OrderCreation)
{
    Order order{OrderId(1), {"AAPL"}, Side::Buy, Price(150), Quantity(100), Quantity(50), Timestamp(1234567890)};

    EXPECT_EQ(order.id, OrderId(1));
    EXPECT_EQ(order.instrument.symbol, "AAPL");
    EXPECT_EQ(order.side, Side::Buy);
    EXPECT_EQ(order.price, Price(150));
    EXPECT_EQ(order.quantity, Quantity(100));
    EXPECT_EQ(order.filled_quantity, Quantity(50));
    EXPECT_EQ(order.timestamp, Timestamp(1234567890));
}

TEST(DomainTypes, TradeCreation)
{
    Trade trade{OrderId(1), OrderId(2), {"AAPL"}, Price(150), Quantity(100), Timestamp(1234567890)};

    EXPECT_EQ(trade.buy_order_id, OrderId(1));
    EXPECT_EQ(trade.sell_order_id, OrderId(2));
    EXPECT_EQ(trade.instrument.symbol, "AAPL");
    EXPECT_EQ(trade.price, Price(150));
    EXPECT_EQ(trade.qty, Quantity(100));
    EXPECT_EQ(trade.ts, Timestamp(1234567890));
}

TEST(DomainTypes, MessageVariant)
{
    Order order{OrderId(1), {"AAPL"}, Side::Buy, Price(150), Quantity(100), Quantity(50), Timestamp(1234567890)};

    OrderRequest order_request{order};
    Message msg = order_request;

    ASSERT_TRUE(std::holds_alternative<OrderRequest>(msg));
    EXPECT_EQ(std::get<OrderRequest>(msg).order.id, OrderId(1));
}
