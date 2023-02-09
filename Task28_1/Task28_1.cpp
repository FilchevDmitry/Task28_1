#include <iostream>
#include<thread>
#include<string>
#include<mutex>
#include<chrono>
#include<vector>


std::mutex r,p;
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
	void printDistance(double inDistanse, std::vector <std::string> &tab )
	{
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		double distanse = 0;
		int temp = 0;
		while (distanse < inDistanse)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			temp++;
			distanse = speed * temp;
			if (distanse > inDistanse)distanse = inDistanse;
			r.lock();
			std::cout << "A swimmer " << name << " sailed : " << distanse << std::endl;
			r.unlock();
		}
		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::duration<double> sec = end - start;
		p.lock();
		tab.push_back(std::to_string(sec.count()) + "   " + name);
		p.unlock();

	}
};

int main()
{	double dist = 100;
	const int numberSwimmers = 6;
	std::vector<Swimmer> swimmer;
	std::vector<std::string> finalTable;
	
	for (int i = 0; i < numberSwimmers; i++)
	{
		swimmer.push_back(Swimmer());
		swimmer[i].setName();
		swimmer[i].setSpeed();
	}
	std::vector<std::thread> temp;
	for (int i = 0; i < numberSwimmers; i++)
	{	
		temp.emplace_back(&Swimmer::printDistance,swimmer[i],dist,std::ref(finalTable));
	}
	for (auto& i : temp)
	{
		i.join();
	}
	for (auto& p : finalTable)
	{
		std::cout << p << std::endl;
	}
	return 0;
}
