#pragma once

#include <list>
#include <memory>
#include <optional>
#include <limits>

#include <UNITS/Unit.hpp>

namespace sw::logic
{
    class Logic
    {
    public:
        Logic() {};
        virtual std::optional<std::shared_ptr<units::Unit>> findEnemy(const std::list<std::shared_ptr<units::Unit>> &units, std::shared_ptr<units::Unit> attacker) = 0;
        virtual ~Logic() {};
    };
}
