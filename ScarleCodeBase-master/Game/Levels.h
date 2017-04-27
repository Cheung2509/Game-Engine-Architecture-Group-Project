#pragma once
#include<vector>
#include<string>

class Room;

class Levels
{
public:
	Levels(std::string Ti, std::vector<std::string>MP);
	~Levels()=default;

	Room* createRoom();
	static void load();

	std::string getTitle() { return Title; }
	std::vector<std::string> getMap() { return Map; }

private:
	std::string Title="Name of Room";
	//std::string Map="ASKI picture of level";
	std::vector<std::string> Map;
public:
	static std::vector<Levels> LoadedLevels;

};

