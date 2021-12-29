#include <iostream>
#include "Server.h"

int main()
{

	unsigned short portNumber;

	std::cout << "Local Host: " << sf::IpAddress::LocalHost << std::endl
				<< "Local IP: " << sf::IpAddress::getLocalAddress() << std::endl;
//				<< "Public: " << sf::IpAddress::getPublicAddress() << std::endl;
	std::cout << std::endl;


	std::cout << "Enter the port Number ? ";
	std::cin >> portNumber;
	std::cout << std::endl;

	Server server(portNumber);

	// audio player thread
	sf::Thread thread(&Server::playAudio, &server);			
	thread.launch();

	// receive thread
	server.run();

}
