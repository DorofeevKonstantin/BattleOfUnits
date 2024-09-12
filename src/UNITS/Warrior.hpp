#pragma once

#include <UNITS/Unit.hpp>

namespace sw::units
{
    class Warrior : public Unit
    {
    protected:
        uint32_t _strength;
        bool meleeAttack(std::shared_ptr<Unit> target)
        {
            bool result = false;
            if (this->targetLocatedInRadius(target, 1))
            {
                target->getDamage(this->_strength);
                result = true;
            }
            return result;
        }

    public:
        Warrior(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) : Unit(unitId, x, y, hp), _strength(strength) {};
        std::string getType() override
        {
            return "Warrior";
        }
        bool attack(std::shared_ptr<Unit> target) override
        {
            return meleeAttack(target);
        }
    };
}
