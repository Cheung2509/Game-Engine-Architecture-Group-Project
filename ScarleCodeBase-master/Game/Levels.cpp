#include "Levels.h"
#include "Room.h"
#include <jsoncons/json.hpp>

Levels::Levels(std::string Ti, std::vector<string> MP)
{
	Title = Ti;
	Map = MP;
}

Room * Levels::createRoom()
{
	return new Room(*this);
}

void Levels::load()
{
	//FileSelecte();
	//Json file reader test now should be moved to an oop set up im thinking two classes one to store all the levels we will need and another to load the current level 
	using jsoncons::json;
	//std::string RoomName;

	std::ifstream LevelsFile("..\\Application\\Level1.json");

	if (LevelsFile.is_open())
	{
		json Rooms;
		LevelsFile >> Rooms;

		for (const auto& room : Rooms.members())
		{
			const auto& name = room.name();
			const auto& data = room.value();

			auto File_Title = data["RoomName"].as_cstring();
			auto File_Map = data["Map"].as<std::vector<string>>();
	
			LoadedLevels.push_back(Levels(File_Title,File_Map));
		}
	}
}

std::vector<Levels> Levels::LoadedLevels;