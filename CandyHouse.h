#include "House.h"

#ifndef _CANDY_HOUSE_H
#define _CANDY_HOUSE_H

class CandyHouse : public House
{
	public:
		CandyHouse(std::string house_name, std::map<int, std::string> candy_map);
		std::string ringDoorbell(std::ostringstream &);
		~CandyHouse();
};

#endif	