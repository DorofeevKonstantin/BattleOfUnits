#pragma once

#include <LOGIC/Logic.hpp>

namespace sw::logic
{
    class WeakestEnemyLogic : public Logic
    {
    public:
        WeakestEnemyLogic() = default;
        ~WeakestEnemyLogic() = default;
        std::optional<std::shared_ptr<units::Unit>> findEnemy(const std::list<std::shared_ptr<units::Unit>> &units, std::shared_ptr<units::Unit> attacker) override;
    };
}
