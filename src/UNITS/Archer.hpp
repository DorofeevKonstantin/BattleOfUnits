#pragma once

#include <UNITS/Unit.hpp>
#include <UNITS/Warrior.hpp>

namespace sw::units
{
    class Archer : public Warrior
    {
    protected:
        uint32_t _agility;
        uint32_t _range;
        uint32_t rangeAttack(std::shared_ptr<Unit> target);

    public:
        Archer(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range) : Warrior(unitId, x, y, hp, strength), _agility(agility), _range(range) {};
        std::string getType() override;
        uint32_t attack(std::shared_ptr<Unit> target) override;
    };
}
