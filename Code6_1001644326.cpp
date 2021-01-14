/* Name: Sarker Nadir Afridi Azmi, ID: 1001644326 */
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <map>
#include <fstream>
#include "TrickOrTreater.h"
#include "House.h"
#include "ToothbrushHouse.h"
#include "CandyHouse.h"
using namespace std;

void get_command_line_params(int argc, char *argv[], vector<string>& input_file_names)
{
	if(argc < 4)
	{
		throw invalid_argument("Missing command line parameters - - Usage : TrickOrTreater.txt House.txt CandyRankings.txt");
	}
	
	input_file_names.push_back(argv[1]);
	input_file_names.push_back(argv[2]);
	input_file_names.push_back(argv[3]);
}

void convert_CPP_C_input_filetype(char *candy_placeholder_converted, string candy_placeholder)
{
	for(int i = 0; i < candy_placeholder.size(); i++)
		candy_placeholder_converted[i] = candy_placeholder.at(i);
	
	candy_placeholder_converted[candy_placeholder.size()] = '\0';
}

void parse_candy_file(map<int, string, less<int>>& candy_map, string& candy_file_name)
{
	ifstream candy_input_file{candy_file_name};
	if(!candy_input_file.is_open())
		exit(0);
	string candy_placeholder{};
	char candy_placeholder_converted[100];
	int int_candy_ranking;
	while(getline(candy_input_file, candy_placeholder))
	{
		convert_CPP_C_input_filetype(candy_placeholder_converted, candy_placeholder);
		char *candy_name = strtok(candy_placeholder_converted, "|");
		char *candy_ranking = strtok(NULL, "\n");
		int_candy_ranking = stoi(candy_ranking);
		
		candy_map.insert(make_pair(int_candy_ranking, candy_name));
	}
	candy_input_file.close();
}

int main(int argc, char *argv[])
{
	vector<string> input_file_names;
	try
	{
		get_command_line_params(argc, argv, input_file_names);
	}
	catch(invalid_argument& say)
	{
		cout << "Exception encountered: " << say.what() << endl;
		exit(0);
	}
	
	srand(time(NULL));
	
	map<int, string, less<int>> candy_map;
	
	parse_candy_file(candy_map, input_file_names[2]);
	
	vector<House *> MyHouseVector;
	
	ifstream house_input_file{input_file_names[1]};
	
	if(!house_input_file.is_open())
		exit(0);
	
	string house_name{};
	
	stringstream house_name_header;
	
	house_name_header << setw(10) << " "; //set 10 spaces aside
	string prevHouseLength{"abcdefghij"};
	
	while(getline(house_input_file, house_name))
	{
		house_name_header << house_name << setw(11- house_name.length()) << " ";
		int picker = rand() % 2;
		if(picker == 1)
		{
			ToothbrushHouse *new_house{new ToothbrushHouse(house_name, candy_map)};
			MyHouseVector.push_back(new_house);
		}
		else
		{
			CandyHouse *new_house{new CandyHouse(house_name, candy_map)};
			MyHouseVector.push_back(new_house);
		}
		prevHouseLength = house_name;
	}
	
	house_input_file.close();
	
	vector<TrickOrTreater> TOTs;
	
	ifstream TrickOrTreater_input_file{input_file_names[0]};
	
	if(!TrickOrTreater_input_file.is_open())
	{
		cout << "TrickOrTreater_input_file failed to open! Exiting ..." << endl;
		exit(0);
	}
	
	string TrickOrTreater_input_file_line{};
	
	while(getline(TrickOrTreater_input_file, TrickOrTreater_input_file_line))
	{
		TOTs.push_back(TrickOrTreater{TrickOrTreater_input_file_line, MyHouseVector});
	}
	
	TrickOrTreater_input_file.close();
	
	for(TrickOrTreater& it : TOTs)
	{
		it.startThread();
	}
	
	while(TrickOrTreater::ImDone != TOTs.size())
	{
		for(int i = 0; i < 34; i++)
			cout << endl;
		cout << house_name_header.str() << endl;
		for(TrickOrTreater& it : TOTs)
		{
			cout << it.getPath() << it.getName() << endl;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	
	for(TrickOrTreater& it : TOTs)
	{
		it.joinThread();
	}
	
	for(TrickOrTreater& it : TOTs)
	{
		cout << it << endl;
	}
	
	for(House * it : MyHouseVector)
	{
		delete it;
		it = nullptr;
	}
	
	return 0;
}