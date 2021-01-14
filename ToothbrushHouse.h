#include "House.h"

#ifndef _TOOTHBRUSH_HOUSE_H
#define _TOOTHBRUSH_HOUSE_H

class ToothbrushHouse : public House
{
	public:
		ToothbrushHouse(std::string house_name, std::map<int, std::string> candy_map);
		std::string ringDoorbell(std::ostringstream &);
		~ToothbrushHouse();
};

#endif	