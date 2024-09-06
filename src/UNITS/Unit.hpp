#pragma once

namespace sw::units
{
    class Unit
    {
    protected:
        uint32_t _unitId{};
        uint32_t _x{};
        uint32_t _y{};
        uint32_t _hp{};

    public:
        Unit(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp) : _unitId(unitId), _x(x), _y(y), _hp(hp) {

                                                                     };
    };
}