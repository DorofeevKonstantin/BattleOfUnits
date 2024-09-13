#include "Warrior.hpp"

namespace sw::units
{
    uint32_t Warrior::meleeAttack(std::shared_ptr<Unit> target)
    {
        uint32_t result = 0;
        if (this->targetLocatedInRadius(target, 1))
        {
            target->getDamage(this->_strength);
            result = this->_strength;
        }
        return result;
    }
    std::string Warrior::getType()
    {
        return "Warrior";
    }
    uint32_t Warrior::attack(std::shared_ptr<Unit> target)
    {
        return meleeAttack(target);
    }
}
