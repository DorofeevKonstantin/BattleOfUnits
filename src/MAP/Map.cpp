#include "Map.hpp"

namespace sw::map
{
    Map::Map(uint32_t width, uint32_t height) : _width(width), _height(height)
    {
        _field.resize(_height);
        for (uint32_t i = 0; i < _height; ++i)
        {
            _field[i].resize(_width);
            for (uint32_t j = 0; j < _width; ++j)
                _field[i][j] = 0;
        }
    };
    void Map::printMap()
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
}
