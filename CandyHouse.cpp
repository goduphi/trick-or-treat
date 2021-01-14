#include "CandyHouse.h"

CandyHouse::CandyHouse(std::string house_name, std::map<int, std::string> candy_map)
: House{house_name, candy_map}
{
}

std::string CandyHouse::ringDoorbell(std::ostringstream& doorbell_wrung)
{
	this->door.lock();
	doorbell_wrung << "+";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	int random_number = rand() % this->CandyRankingMap.size() + 1;
	this->door.unlock();
	return this->CandyRankingMap[random_number];
}

CandyHouse::~CandyHouse()
{
	std::cout << "CANDYHOUSE" << std::endl;
}