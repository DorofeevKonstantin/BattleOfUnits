#include "Archer.hpp"

namespace sw::units
{
    uint32_t Archer::rangeAttack(std::shared_ptr<Unit> target)
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
    std::string Archer::getType()
    {
        return "Archer";
    }
    uint32_t Archer::attack(std::shared_ptr<Unit> target)
    {
        uint32_t result = rangeAttack(target);
        if (result == 0)
            result = meleeAttack(target);
        return result;
    }
}
