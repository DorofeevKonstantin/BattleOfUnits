#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include <iostream>

#include <UNITS/Unit.hpp>

namespace sw::map
{
    class Map
    {
    protected:
        uint32_t _width;
        uint32_t _height;
        std::vector<std::vector<uint32_t>> _field;

    public:
        Map(uint32_t width, uint32_t height);
        void clearCell(uint32_t targetX, uint32_t targetY)
        {
            _field[targetY][targetX] = 0;
        }
        virtual bool placeUnit(std::shared_ptr<units::Unit> unit, uint32_t targetX, uint32_t targetY) = 0;
        virtual std::pair<uint32_t, uint32_t> findWay(std::shared_ptr<units::Unit> attacker, std::shared_ptr<units::Unit> target) = 0;
        void printMap();
        virtual ~Map() {};
    };
}
