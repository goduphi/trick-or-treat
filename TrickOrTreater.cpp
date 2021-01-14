/* Name: Sarker Nadir Afridi Azmi, ID: 1001644326 */
#include "TrickOrTreater.h"

int TrickOrTreater::ImDone = 0;

TrickOrTreater::TrickOrTreater(std::string tot_name, std::vector<House*> list_of_houses_to_visit)
: name{tot_name}, ListOfHouses{list_of_houses_to_visit}
{
}

std::string TrickOrTreater::getName()
{
	return this->name;
}

void TrickOrTreater::startThread()
{
	/* pass in the pointer to the GoTrickOrTreating and the associated pointer to the object (this) */
	TOTThreadPtr = new std::thread(&TrickOrTreater::GoTrickOrTreating, this);
}

void TrickOrTreater::joinThread()
{
	/* The current running thread for the current object, let's say the first trick or treater is joined */
	this->TOTThreadPtr->join();
	delete this->TOTThreadPtr;
}

void TrickOrTreater::Walk(int speed)
{
	this->path << ".";
	std::this_thread::sleep_for(std::chrono::milliseconds(speed));
}

/*
This function moves the trick or treater between houses, rings
the doorbell at each house and increments the chosen candy
in the trick or treater’s candy bucket. It also tracks which
house the trick or treater is heading towards.
*/

//this function is called when a thread has been instantiated
void TrickOrTreater::GoTrickOrTreating()
{
	//each trick or treater gets a list of all the houses to visit
	for(House * house : this->ListOfHouses)
	{
		int speed = rand() % 500 + 1; //pick a random number between 1 and 500
		for(int i = 0; i < 10; i++)
		{
			this->Walk(speed); //to be modifed later
		}
		//we would want to select the current TrickOrTreater object, so this is used
		/*
			What I have to make sure is that ListOfHouses is vector of pointers to House. 
			After picking which house I want, I need to dereference it with '->' in order to access its members
		*/
		std::string candy_name_returned = house->ringDoorbell(this->path);
		this->Bucket[candy_name_returned]++;
	}
	TrickOrTreater::ImDone++;
}

std::string TrickOrTreater::getPath()
{
	return this->path.str();
}

std::ostream& operator<<(std::ostream& output, TrickOrTreater& list_of_candies)
{
	output << list_of_candies.getName() << "'s - ";
	
	for(auto it : list_of_candies.Bucket)
		output << it.second << " " << it.first << ",";
	
	return output;
}