#pragma once

#include <UNITS/Unit.hpp>

namespace sw::units
{
    class Warrior : public Unit
    {
    protected:
        uint32_t _strength;
        uint32_t meleeAttack(std::shared_ptr<Unit> target);

    public:
        Warrior(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) : Unit(unitId, x, y, hp), _strength(strength) {};
        std::string getType() override;
        uint32_t attack(std::shared_ptr<Unit> target) override;
    };
}
