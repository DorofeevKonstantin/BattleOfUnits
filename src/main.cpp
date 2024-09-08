#include <iostream>
#include <fstream>
#include <typeinfo>
#include <memory>

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
#include <UNITS/Warrior.hpp>
#include <UNITS/Archer.hpp>
#include <GAME/Game.hpp>

int main(int argc, char **argv)
{
	using namespace sw;
	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}
	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	try
	{
		std::unique_ptr<game::Game> game = std::make_unique<game::Game>();
		std::cout << "Commands:\n";
		io::CommandParser parser;
		parser.add<io::CreateMap>(
				  [&game](auto command)
				  {
					  printDebug(std::cout, command);
					  game->createMap(command.width, command.height);
				  })
			.add<io::SpawnWarrior>(
				[&game](auto command)
				{
					printDebug(std::cout, command);
					game->spawnUnit(std::make_shared<units::Warrior>(command.unitId, command.x, command.y, command.hp, command.strength));
				})
			.add<io::SpawnArcher>(
				[&game](auto command)
				{
					printDebug(std::cout, command);
					game->spawnUnit(std::make_shared<units::Archer>(command.unitId, command.x, command.y, command.hp, command.agility, command.strength, command.range));
				})
			.add<io::March>(
				[&game](auto command)
				{
					printDebug(std::cout, command);
					game->marchUnit(command.unitId, command.targetX, command.targetY);
				});
		parser.parse(file);
		game->start();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
