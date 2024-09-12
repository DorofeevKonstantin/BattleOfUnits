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
            _field.resize(_width);
            for (uint32_t i = 0; i < _width; ++i)
            {
                _field[i].resize(_height);
                for (uint32_t j = 0; j < _height; ++j)
                    _field[i][j] = 0;
            }
        };
        bool placeUnit(uint32_t unitId, uint32_t x, uint32_t y)
        {
            bool placed = true;
            if (_field[x][y] == 0)
                _field[x][y] = unitId;
            else
                placed = false;
            return placed;
        }
        void checkMap()
        {
            for (uint32_t i = 0; i < _width; ++i)
            {
                for (uint32_t j = 0; j < _height; ++j)
                {
                    std::cout<<_field[i][j]<<" ";
                }
                std::cout<<std::endl;
            }
        }
    };
}
