#include <iostream>
#include<thread>
#include<string>
#include<mutex>

class Swimmer
{
private:
	std::string name;
	double speed = 0;
public:
	void setName(std::string& inName)
	{
		name = inName;
	}
	std::string getName()
	{
		return name;
	}
	void setSpeed(double& inSpeed)
	{
		speed = inSpeed;
	}
	double getSpeed()
	{
		return speed;
	}
};

int main()
{
	return 0;
}
