#pragma once

#include <UNITS/Unit.hpp>

namespace sw::units
{
    class Archer : public Warrior
    {
    protected:
        uint32_t _agility;
        uint32_t _range;
        uint32_t rangeAttack(std::shared_ptr<Unit> target)
        {
            uint32_t result = 0;
            if (!this->targetLocatedInRadius(target, 1))
            {
                if (this->targetLocatedInRadius(target, _range))
                {
                    result = this->_agility;
                    target->getDamage(this->_agility);
                }
            }
            return result;
        }

    public:
        Archer(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range) : Warrior(unitId, x, y, hp, strength), _agility(agility), _range(range) {};
        std::string getType() override
        {
            return "Archer";
        }
        uint32_t attack(std::shared_ptr<Unit> target) override
        {
            uint32_t result = rangeAttack(target);
            if (result == 0)
                result = meleeAttack(target);
            return result;
        }
    };
}
