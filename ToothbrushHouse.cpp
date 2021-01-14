#include "ToothbrushHouse.h"

ToothbrushHouse::ToothbrushHouse(std::string house_name, std::map<int, std::string> candy_map)
: House{house_name, candy_map}
{
}

std::string ToothbrushHouse::ringDoorbell(std::ostringstream& doorbell_wrung)
{
	this->door.lock();
	doorbell_wrung << "-";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	int random_number = rand() % this->CandyRankingMap.size() + 1;
	this->door.unlock();
	std::string toothbrush = "TOOTHBRUSH";
	//return this->CandyRankingMap[random_number];
	return toothbrush;
}

ToothbrushHouse::~ToothbrushHouse()
{
	std::cout << "TOOTHBRUSHHOUSE" << std::endl;
}