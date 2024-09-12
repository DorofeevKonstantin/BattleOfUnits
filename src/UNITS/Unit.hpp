#pragma once

#include <string>
#include <memory>

namespace sw::units
{
    class Unit
    {
    protected:
        uint32_t _unitId{};
        uint32_t _x{};
        uint32_t _y{};
        uint32_t _hp{};
        bool targetLocatedInRadius(std::shared_ptr<units::Unit> target, uint32_t radius)
        {
            bool result = false;
            uint32_t distanceX = (this->getX() > target->getX()) ? this->getX() - target->getX() : target->getX() - this->getX();
            uint32_t distanceY = (this->getY() > target->getY()) ? this->getY() - target->getY() : target->getY() - this->getY();
            if ((distanceX + distanceY) <= radius)
                result = true;
            if (distanceX == distanceY == radius)
                result = true;
            return result;
        }

    public:
        uint32_t getId() const { return _unitId; }
        uint32_t getX() const { return _x; }
        uint32_t getY() const { return _y; }
        uint32_t getHp() const { return _hp; }
        std::string virtual getType() = 0;
        Unit(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp) : _unitId(unitId), _x(x), _y(y), _hp(hp) {};
        virtual bool attack(std::shared_ptr<Unit> target) = 0;
        void getDamage(uint32_t damage)
        {
            if (damage > _hp)
                _hp = 0;
            else
                _hp -= damage;
        }
        virtual ~Unit() {};
    };
}
