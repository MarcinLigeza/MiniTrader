// include/minitrader/trade.hpp
#pragma once
#include "types.hpp"

namespace mt {

    struct Trade
    {
        OrderId buy_order_id;
        OrderId sell_order_id;
        Instrument instrument;
        Price price;
        Quantity qty;
        Timestamp ts;
    };

} // namespace mt