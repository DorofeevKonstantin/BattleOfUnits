#include "Game.hpp"

namespace sw::game
{
    void Game::checkDeads()
    {
        for (auto unit : _units)
        {
            if (unit->getHp() == 0)
            {
                _map->clearCell(unit->getX(), unit->getY());
                _eventLog->collect(_round, io::UnitDied{unit->getId()});
            }
        }
        _units.remove_if([](std::shared_ptr<units::Unit> unit)
                         { return unit->getHp() == 0; });
    }
    bool Game::endOfSimulation()
    {
        bool result = false;
        if (_units.empty() || _units.size() == 1)
            result = true;
        return result;
    };
    void Game::round()
    {
        ++_round;
        for (auto unit : _units)
        {
            auto enemy = _logic->findEnemy(_units, unit);
            if (enemy)
            {
                uint32_t damagedone = unit->attack(*enemy);
                if (damagedone == 0)
                {
                    uint32_t currentX = unit->getX();
                    uint32_t currentY = unit->getY();
                    auto [x, y] = _map->findWay(unit, *enemy);
                    if (_map->placeUnit(unit, x, y))
                        _eventLog->collect(_round, io::UnitMoved{unit->getId(), x, y});
                }
                else
                    _eventLog->collect(_round, io::UnitAttacked{unit->getId(), (*enemy)->getId(), damagedone, (*enemy)->getHp()});
            }
        }
    }
    Game::Game()
    {
        _logic = std::make_unique<logic::WeakestEnemyLogic>();
        _eventLog = std::make_shared<EventLog>();
    };
    Game::~Game()
    {
        _eventLog->print();
    };
    void Game::start()
    {
        std::cout << "\n\nEvents:\n";
        while (!endOfSimulation())
        {
            round();
            _eventLog->print();
            checkDeads();
        }
    };
    void Game::createMap(uint32_t width, uint32_t height)
    {
        _map = std::make_unique<map::MapWithoutBarriers>(width, height);
        _eventLog->collect(_round, io::MapCreated{width, height});
    };
    void Game::spawnUnit(std::shared_ptr<units::Unit> unit)
    {
        _units.push_back(unit);
        _map->placeUnit(unit, unit->getX(), unit->getY());
        _eventLog->collect(_round, io::UnitSpawned{unit->getId(), unit->getType(), unit->getX(), unit->getY()});
    };
    void Game::marchUnit(uint32_t unitId, uint32_t targetX, uint32_t targetY)
    {
        std::shared_ptr<units::Unit> unit = nullptr;
        for (auto u : _units)
        {
            if (u->getId() == unitId)
                unit = u;
        }
        if (unit)
        {
            uint32_t currentX = unit->getX();
            uint32_t currentY = unit->getY();
            _map->placeUnit(unit, targetX, targetY);
            _eventLog->collect(_round, io::MarchStarted{unitId, currentX, currentY, targetX, targetY});
        }
    }
}
