#include <iostream>
#include<thread>
#include<string>
#include<mutex>
#include<chrono>
#include<vector>
#include<map>

std::mutex r;
class Swimmer
{
private:
	std::string name;
	double speed = 0;
public:	void setName()
	{
		std::cout<<"Imput name - ";
		std::cin >> name;
	}
	std::string getName()
	{
		return name;
	}
	void setSpeed()
	{
		std::cout << "Imput speed (m/s) - ";
		std::cin >> speed;
	}
	double getSpeed()
	{
		return speed;
	}
	void printDistance(double inDistanse)
	{
		double distanse = 0;
		int temp = 0;
		while (distanse < inDistanse)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			temp++;
			distanse = speed * temp;
			if (distanse > inDistanse) distanse = inDistanse;
			r.lock();
			std::cout << "A swimmer " << name << " sailed : " << distanse << std::endl;
			r.unlock();
		}
	}
	double getTimeDistance(double &inDistance)
	{
		return inDistance / speed;
	}
};

int main()
{	double dist = 100;
	const int numberSwimmers = 6;
	std::vector<Swimmer> swimmer;
	std::map<double, std::string> table;
	
	for (int i = 0; i < numberSwimmers; i++)
	{
		swimmer.push_back(Swimmer());
		swimmer[i].setName();
		swimmer[i].setSpeed();
	}
	std::vector<std::thread> temp;
	for (int i = 0; i < numberSwimmers; i++)
	{	
		temp.emplace_back(&Swimmer::printDistance,swimmer[i],dist);
	}
	for (auto& i : temp)
	{
		i.join();
	}
	for (int i = 0; i < numberSwimmers; i++)
	{
		table[swimmer[i].getTimeDistance(dist)] = swimmer[i].getName();
	}
	std::map<double, std::string>::iterator tab = table.begin();
	std::cout << "Final table" << std::endl;
	for (int i = 0; tab != table.end(); tab++, i++)
	{
		std::cout << tab->first << "  " << tab->second << std::endl;
	}
	return 0;
}
