#pragma once

#include <variant>

#include "order.hpp"
#include "trade.hpp"

namespace mt
{

    struct OrderRequest
    {
        Order order;
    };

    struct CancelRequest
    {
        OrderId order_id;
        Instrument instrument;
    };

    struct FillEvent
    {
        Trade trade;
    };

    using Message = std::variant<OrderRequest, CancelRequest, FillEvent>;

} // namespace mt