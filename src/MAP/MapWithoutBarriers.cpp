#include "MapWithoutBarriers.hpp"

namespace sw::map
{
    bool MapWithoutBarriers::placeUnit(std::shared_ptr<units::Unit> unit, uint32_t targetX, uint32_t targetY)
    {
        bool placed = false;
        if (_field[targetY][targetX] == 0)
        {
            uint32_t currentX = unit->getX();
            uint32_t currentY = unit->getY();
            _field[targetY][targetX] = unit->getId();
            unit->setX(targetX);
            unit->setY(targetY);
            if (currentX != targetX || currentY != targetY)
                _field[currentY][currentX] = 0;
            placed = true;
        }
        return placed;
    }
    std::pair<uint32_t, uint32_t> MapWithoutBarriers::findWay(std::shared_ptr<units::Unit> attacker, std::shared_ptr<units::Unit> target)
    {
        uint32_t xMove = 0, yMove = 0;
        if (attacker->getY() > target->getY())
            yMove = -1;
        else if (attacker->getX() > target->getX())
            xMove = -1;
        else if (attacker->getY() < target->getY())
            yMove = 1;
        else if (attacker->getX() < target->getX())
            xMove = 1;

        return std::make_pair<uint32_t, uint32_t>(attacker->getX() + xMove, attacker->getY() + yMove);
    }
}
