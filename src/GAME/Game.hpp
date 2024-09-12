#pragma once

#include <list>
#include <string>
#include <memory>
#include <utility>
#include <optional>
#include <algorithm>
#include <limits>

#include <IO/System/EventLog.hpp>
#include <UNITS/Unit.hpp>
#include <MAP/Map.hpp>
#include <LOGIC/Logic.hpp>

namespace sw::game
{
    class Game
    {
    private:
        uint32_t _round = 1;
        std::unique_ptr<map::Map> _map;
        std::list<std::shared_ptr<units::Unit>> _units;
        std::shared_ptr<EventLog> _eventLog;

        void checkDeads()
        {
            for (auto unit : _units)
            {
                if (unit->getHp() == 0)
                    _eventLog->collect(_round, io::UnitDied{unit->getId()});
            }
            _units.remove_if([](std::shared_ptr<units::Unit> unit)
                             { return unit->getHp() == 0; });
        }
        bool endOfSimulation()
        {
            bool result = false;
            if (_units.empty() || _units.size() == 1)
                result = true;
            if (_round > 10)
                result = true;
            return result;
        };
        std::pair<uint32_t, uint32_t> findWay(std::shared_ptr<units::Unit> attacker, std::shared_ptr<units::Unit> target)
        {
            uint32_t xMove = 0, yMove = 0;
            if (attacker->getY() < target->getY())
                yMove = 1;
            else if (attacker->getX() < target->getX())
                xMove = 1;
            else if (attacker->getY() > target->getY())
                yMove = -1;
            else if (attacker->getX() > target->getX())
                xMove = -1;

            return std::make_pair<uint32_t, uint32_t>(attacker->getX() + xMove, attacker->getY() + yMove);
        }
        std::optional<std::shared_ptr<units::Unit>> findEnemy(std::shared_ptr<units::Unit> attacker)
        {
            std::shared_ptr<units::Unit> result = nullptr;
            uint32_t minHp = std::numeric_limits<uint32_t>::max();
            for (std::shared_ptr<units::Unit> unit : _units)
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
                for (std::shared_ptr<units::Unit> unit : _units)
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
        void round()
        {
            ++_round;
            for (auto unit : _units)
            {
                auto enemy = findEnemy(unit);
                if (enemy)
                {
                    uint32_t damagedone = unit->attack(*enemy);
                    if (damagedone == 0)
                    {
                        uint32_t currentX = unit->getX();
                        uint32_t currentY = unit->getY();
                        auto [x, y] = findWay(unit, *enemy);
                        if (_map->placeUnit(unit, x, y))
                            _eventLog->collect(_round, io::UnitMoved{unit->getId(), x, y});
                    }
                    else
                        _eventLog->collect(_round, io::UnitAttacked{unit->getId(), (*enemy)->getId(), damagedone, (*enemy)->getHp()});
                }
            }
            //_map->printMap();
        }
        std::shared_ptr<units::Unit> findUnit(uint32_t unitId)
        {
            std::shared_ptr<units::Unit> unit = nullptr;
            for (auto u : _units)
            {
                if (u->getId() == unitId)
                    unit = u;
            }
            return unit;
        }

    public:
        Game()
        {
            _eventLog = std::make_shared<EventLog>();
        };
        ~Game()
        {
            _eventLog->print();
        };
        void start()
        {
            std::cout << "\n\nEvents:\n";
            while (!endOfSimulation())
            {
                round();
                _eventLog->print();
                checkDeads();
            }
        };
        void createMap(uint32_t width, uint32_t height)
        {
            _map = std::make_unique<map::Map>(width, height);
            _eventLog->collect(_round, io::MapCreated{width, height});
        };
        void spawnUnit(std::shared_ptr<units::Unit> unit)
        {
            _units.push_back(unit);
            _map->placeUnit(unit, unit->getX(), unit->getY());
            _eventLog->collect(_round, io::UnitSpawned{unit->getId(), unit->getType(), unit->getX(), unit->getY()});
        };
        void marchUnit(uint32_t unitId, uint32_t targetX, uint32_t targetY)
        {
            auto unit = findUnit(unitId);
            uint32_t currentX = unit->getX();
            uint32_t currentY = unit->getY();
            _map->placeUnit(unit, targetX, targetY);
            _eventLog->collect(_round, io::MarchStarted{unitId, currentX, currentY, targetX, targetY});
        }
    };
}
