#pragma once

#include <UNITS/Unit.hpp>

namespace sw::units
{
    class Archer : public Unit
    {
        private:
            uint32_t _agility;
            uint32_t _strength;
            uint32_t _range;

        public:
            Archer(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range) :
            Unit(unitId, x, y, hp), _agility(agility), _strength(strength), _range(range)
            {

            };
    };
}