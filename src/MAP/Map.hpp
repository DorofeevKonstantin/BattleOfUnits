#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <UNITS/Unit.hpp>

namespace sw::map
{
    class Map
    {
    private:
        uint32_t _width;
        uint32_t _height;
        std::vector<std::vector<uint32_t>> _field;

    public:
        Map(uint32_t width, uint32_t height) : _width(width), _height(height)
        {
            _field.resize(_height);
            for (uint32_t i = 0; i < _height; ++i)
            {
                _field[i].resize(_width);
                for (uint32_t j = 0; j < _width; ++j)
                    _field[i][j] = 0;
            }
        };
        void clearCell(uint32_t targetX, uint32_t targetY)
        {
            _field[targetY][targetX] = 0;
        }
        bool placeUnit(std::shared_ptr<units::Unit> unit, uint32_t targetX, uint32_t targetY)
        {
            bool placed = false;
            if (_field[targetY][targetX] == 0)
            {
                uint32_t currentX = unit->getX();
                uint32_t currentY = unit->getY();
                _field[targetY][targetX] = unit->getId();
                unit->setX(targetX);
                unit->setY(targetY);
                if (currentX != targetX || currentY != targetY)
                    _field[currentY][currentX] = 0;
                placed = true;
            }
            return placed;
        }
        void printMap()
        {
            for (uint32_t i = 0; i < _height; ++i)
            {
                for (uint32_t j = 0; j < _width; ++j)
                {
                    std::cout << _field[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    };
}
