#pragma once

#include <UNITS/Unit.hpp>

namespace sw::units
{
    class Warrior : public Unit
    {
    protected:
        uint32_t _strength;
        uint32_t meleeAttack(std::shared_ptr<Unit> target)
        {
            uint32_t result = 0;
            if (this->targetLocatedInRadius(target, 1))
            {
                target->getDamage(this->_strength);
                result = this->_strength;
            }
            return result;
        }

    public:
        Warrior(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) : Unit(unitId, x, y, hp), _strength(strength) {};
        std::string getType() override
        {
            return "Warrior";
        }
        uint32_t attack(std::shared_ptr<Unit> target) override
        {
            return meleeAttack(target);
        }
    };
}
