#include <iostream>
#include "Client.h"

int main()
{
	unsigned short portNumber;

	std::string name;
	std::cout << "Enter the client's name: ";
	std::getline(std::cin, name);
	std::cout << std::endl;

	Client client(name);

	std::cout << "Enter the port Number? ";
	std::cin >> portNumber;
	std::cin.get();

	std::cout << "Do you want to connect to [local host], [IP]? ";	
	std::string IP;
	std::getline(std::cin, IP);
	
	sf::Socket::Status status;

	if(IP == "local")
		status = client.connect(sf::IpAddress::LocalHost, portNumber);
	else
		status = client.connect(IP, portNumber);

	if(status != sf::Socket::Done)
	{
		std::cout << "Sorry we couldn't connect\n";
		return -1;
	}

	client.send(MSG_GENERAL, name);

	do
	{
		std::cout << "Enter Play/Resume(p), Stop(s) or Quit(q) : ";

		std::getline(std::cin, name);
		
		client.send(MSG_PLAY, name);

	} while (name[0] != 'q');

	exit(0);

}
