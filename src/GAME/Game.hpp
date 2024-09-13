#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>

#include <IO/System/CommandParser.hpp>
#include <IO/System/PrintDebug.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/SpawnWarrior.hpp>
#include <IO/Commands/SpawnArcher.hpp>
#include <IO/Commands/March.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitAttacked.hpp>

#include <UNITS/Unit.hpp>
#include <MAP/Map.hpp>
#include <MAP/MapWithoutBarriers.hpp>
#include <LOGIC/Logic.hpp>
#include <LOGIC/WeakestEnemyLogic.hpp>

namespace sw::game
{
    class Game
    {
    private:
        uint32_t _round = 1;
        std::unique_ptr<map::Map> _map;
        std::unique_ptr<logic::Logic> _logic;
        std::list<std::shared_ptr<units::Unit>> _units;
        std::shared_ptr<EventLog> _eventLog;

        void checkDeads();
        bool endOfSimulation();
        void round();

    public:
        Game();
        ~Game();
        void start();
        void createMap(uint32_t width, uint32_t height);
        void spawnUnit(std::shared_ptr<units::Unit> unit);
        void marchUnit(uint32_t unitId, uint32_t targetX, uint32_t targetY);
    };
}
