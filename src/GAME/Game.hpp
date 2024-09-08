#pragma once

#include <list>
#include <string>
#include <memory>

#include <IO/System/EventLog.hpp>
#include <UNITS/Unit.hpp>
#include <MAP/Map.hpp>

namespace sw::game
{
    class Game
    {
    private:
        uint32_t _round = 1;
        std::unique_ptr<map::Map> _map;
        std::list<std::shared_ptr<units::Unit>> _units;
        std::unique_ptr<EventLog> _eventLog;
        bool endOfSimulation()
        {
            return true;
        };
        void round()
        {
            for (auto unit : _units)
            {
                /*
                auto enemy = findEnemy(unit);
                auto way = findWay(unit, enemy);
                if (!way)
                    unit->attack(enemy);
                */
            }
            ++_round;
            _eventLog->print();
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
            _eventLog = std::make_unique<EventLog>();
        };
        ~Game()
        {
            std::cout << "\n\nEvents:\n";
            _eventLog->print();
        };
        void start()
        {
            while (!endOfSimulation())
            {
                round();
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
            _map->placeUnit(unit->getId(), unit->getX(), unit->getY());
            _eventLog->collect(_round, io::UnitSpawned{unit->getId(), unit->getType(), 0, 0});
        };
        void marchUnit(uint32_t unitId, uint32_t width, uint32_t height)
        {
            auto unit = findUnit(unitId);
            _map->placeUnit(unitId, width, height);
            _eventLog->collect(_round, io::MarchStarted{unitId, unit->getX(), unit->getY(), width, height});
        }
    };
}
