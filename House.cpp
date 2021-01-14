/* Name: Sarker Nadir Afridi Azmi, ID: 1001644326 */
#include "House.h"

House::House(std::string house_name, std::map<int, std::string> candy_map)
: houseName{house_name}, CandyRankingMap{candy_map}
{
}

House::~House()
{
	std::cout << "HOUSE" << std::endl;
}