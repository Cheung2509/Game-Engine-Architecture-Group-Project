#include "Levels.h"
#include <jsoncons/json.hpp>

Levels::Levels(std::string Ti, std::string MP)
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
	//Json file reader test now should be moved to an oop set up im thinking two classes one to store all the levels we will need and another to load the current level 
	using jsoncons::json;
	//std::string RoomName;

	std::ifstream LevelsFile("..\\Application\\LevelSetUp.json");

	if (LevelsFile.is_open())
	{
		json Rooms;
		LevelsFile >> Rooms;

		for (const auto& room : Rooms.members())
		{
			const auto& name = room.name();
			const auto& data = room.value();

			auto File_Title = data["RoomName"].as_cstring();
			auto File_Map = data["Map"].as_cstring();
			//RoomName = Title; //currently passes vairablew from file called room name to room name string but cud just get name of the room from the 
			/*std::ifstream model("..\\..\\Resources\\ASCII\\"
				+ ascii);
			std::string str((
				std::istreambuf_iterator<char>(model)),
				std::istreambuf_iterator<char>());*/
			LoadedLevels.push_back(Levels(File_Title,File_Map));
		}
	}
}
std::vector<Levels> Levels::LoadedLevels;