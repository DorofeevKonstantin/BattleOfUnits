#pragma once

#include <vector>
#include <memory>

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
        bool placeUnit(uint32_t unitId, uint32_t x, uint32_t y)
        {
            bool placed = true;
            if (_field[y][x] == 0)
                _field[y][x] = unitId;
            else
                placed = false;
            return placed;
        }
    };
}
