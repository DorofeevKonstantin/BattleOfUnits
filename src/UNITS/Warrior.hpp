#pragma once

#include <UNITS/Unit.hpp>

namespace sw::units
{
    class Warrior : public Unit
    {
    private:
        uint32_t _strength{};
    protected:
        bool meleeAttack(std::shared_ptr<Unit> target)
        {
            return true;
        }

    public:
        Warrior(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) : Unit(unitId, x, y, hp), _strength(strength) {};
        std::string getType() override
        {
            return "Warrior";
        }
        bool attack(std::shared_ptr<Unit> target) override
        {
            return true;
        }
    };
}
