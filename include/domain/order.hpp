#pragma once

#include "types.hpp"

#include <string>

namespace mt
{
    struct Instrument
    {
        std::string symbol;
    };

    struct Order
    {
        OrderId id;
        Instrument instrument;
        Side side;
        Price price;
        Quantity quantity;
        Quantity filled_quantity{Quantity(0)};
        Timestamp timestamp;
    };

} // namespace mt