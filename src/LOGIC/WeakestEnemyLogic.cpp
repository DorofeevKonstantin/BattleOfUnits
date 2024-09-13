#include "WeakestEnemyLogic.hpp"

namespace sw::logic
{
    std::optional<std::shared_ptr<units::Unit>> WeakestEnemyLogic::findEnemy(const std::list<std::shared_ptr<units::Unit>> &units, std::shared_ptr<units::Unit> attacker)
    {
        std::shared_ptr<units::Unit> result = nullptr;
        uint32_t minHp = std::numeric_limits<uint32_t>::max();
        for (std::shared_ptr<units::Unit> unit : units)
        {
            if (unit->getId() != attacker->getId())
            {
                if (unit->getHp() < minHp)
                {
                    minHp = unit->getHp();
                    result = unit;
                }
            }
        }
        if (result == nullptr)
        {
            uint32_t minId = std::numeric_limits<uint32_t>::max();
            for (std::shared_ptr<units::Unit> unit : units)
            {
                if (unit->getId() != attacker->getId())
                {
                    if (unit->getId() < minId)
                    {
                        minId = unit->getId();
                        result = unit;
                    }
                }
            }
        }
        return result;
    }
}
