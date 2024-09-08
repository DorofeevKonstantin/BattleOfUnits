#pragma once

#include <string>

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
        uint32_t getId() { return _unitId; }
        uint32_t getX() { return _x; }
        uint32_t getY() { return _y; }
        std::string virtual getType() = 0;
        Unit(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp) : _unitId(unitId), _x(x), _y(y), _hp(hp) {

                                                                     };
    };
}