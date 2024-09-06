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
        std::unique_ptr<map::Map> _map;
        std::list<std::shared_ptr<units::Unit>> _units;
        std::unique_ptr<EventLog> _eventLog;
        bool endOfSimulation()
        {
            return true;
        };

    public:
        Game() {

        };
        ~Game() {

        };
        void start() {};
        void createMap(uint32_t width, uint32_t height)
        {
            // _eventLog.log(1, io::MapCreated{ 10, 10 });
            // parse command
        };
        void spawnUnit(std::shared_ptr<units::Unit> unit)
        {
            // _eventLog.log(1, io::UnitSpawned{ 1, "Warrior", 0, 0 });
            // parse command
            _units.push_back(unit);
        };
        void marchUnit(uint32_t unitId, uint32_t width, uint32_t height)
        {
            // _eventLog.log(1, io::MarchStarted{ 1, 0, 0, 9, 0 });
            // parse command
        }
    };
}