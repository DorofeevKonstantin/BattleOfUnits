#include "Unit.hpp"

namespace sw::units
{

    bool Unit::targetLocatedInRadius(std::shared_ptr<units::Unit> target, uint32_t radius)
    {
        bool result = false;
        uint32_t distanceX = (this->getX() > target->getX()) ? this->getX() - target->getX() : target->getX() - this->getX();
        uint32_t distanceY = (this->getY() > target->getY()) ? this->getY() - target->getY() : target->getY() - this->getY();
        if ((distanceX <= radius) && (distanceY <= radius))
            result = true;
        return result;
    }
    void Unit::getDamage(uint32_t damage)
    {
        if (damage > _hp)
            _hp = 0;
        else
            _hp -= damage;
    }
}
