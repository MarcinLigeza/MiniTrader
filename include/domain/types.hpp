#pragma once
#include <cstdint>

namespace mt
{

    template <typename T, typename Tag> struct StrongType
    {
        explicit StrongType(T v) : value(v)
        {
        }
        T value;

        bool operator==(const StrongType& other) const
        {
            return value == other.value;
        }
        // bool operator<(const StrongType& other) const
        // {
        //     return value < other.value;
        // }

        auto operator<=>(const StrongType& other) const
        {
            return value <=> other.value;
        }
    };

    using OrderId = StrongType<uint64_t, struct OrderIdTag>;
    using Price = StrongType<int64_t, struct PriceTag>; // price in ticks
    using Quantity = StrongType<int64_t, struct QuantityTag>;
    using Timestamp = StrongType<uint64_t, struct TimestampTag>; // nanoseconds since epoch

    enum class Side : uint8_t
    {
        Buy,
        Sell
    };

} // namespace mt