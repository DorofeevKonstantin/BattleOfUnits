#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <UNITS/Unit.hpp>
#include <MAP/Map.hpp>

namespace sw::map
{
    class MapWithoutBarriers : public Map
    {
    public:
        MapWithoutBarriers(uint32_t width, uint32_t height) : Map(width, height) {};
        bool placeUnit(std::shared_ptr<units::Unit> unit, uint32_t targetX, uint32_t targetY) override;
        std::pair<uint32_t, uint32_t> findWay(std::shared_ptr<units::Unit> attacker, std::shared_ptr<units::Unit> target) override;
    };
}
