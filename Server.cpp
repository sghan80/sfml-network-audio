#include <iostream>
#include <SFML/Audio.hpp>
#include "Server.h"


Server::Server(unsigned short port)
{
	listner.listen(port);
	listner.setBlocking(false);
}

Server::~Server()
{
}

void Server::handlePackets()
{
	//handle incoming packet
	for(Clients::iterator it=clients.begin(); it!=clients.end();)
	{
		sf::Packet packet;
		sf::Socket::Status status=it->first->receive(packet);
		
		switch (status)
		{
		case sf::Socket::Done:
			PacketType type;
			packet >> type;
			
			if(type == MSG_GENERAL)		// store client name
			{
				packet >> it->second;
				std::cout << it->second << " has joined\n";
				broadCast(MSG_GENERAL, it->second + " has joined broadcast\n");
			}
			else if(type == MSG_PLAY)	// handling player
			{
				std::string msg;
				packet >> msg;
				std::cout << "Received from " + it->second + " : " + msg[0] + "\n";
				broadCast(MSG_PLAY, it->second + ": " + msg[0] + " broadcast");

				if ('p' == msg[0])
					setAudio(true);
				else if ('s' == msg[0] || 'q' == msg[0])
					setAudio(false);
			}
			++it;
			break;

		case sf::Socket::Disconnected:
			std::cout << it->second << " has been disconnected\n";
			broadCast(MSG_PLAY, it->second + " has been disconnected broadcast \n");
			it=clients.erase(it);
			break;

		default:
			++it;
		}
	//	std::cout<<"wtf\n";
	}
}

void Server::broadCast(PacketType type, const std::string & msg)
{
	for(Clients::iterator it=clients.begin(); it!=clients.end(); ++it)
	{
		sf::Packet pack;
		pack << type << msg;
		it->first->send(pack);
	}
}

void Server::run()
{
	sf::Thread thread([&]()
	{
		while(1)
		{
			std::string s;
			std::getline(std::cin, s);
			broadCast(MSG_FROM_SERVER, "SERVER: " + s);
		}
	});
	thread.launch();

	sf::TcpSocket * nextClient = nullptr;

	while(1)
	{
		if(nextClient==nullptr)
		{
			nextClient=new sf::TcpSocket;
			nextClient->setBlocking(false);
		}
		
		if(listner.accept(*nextClient) == sf::Socket::Done)
		{
			clients.insert(std::make_pair(nextClient, ""));
			nextClient=nullptr;
		}
		handlePackets();
	}
}

void Server::setAudio(bool b)
{
	isPlaying = b;
}

void Server::playAudio()
{
    sf::Music mp;
    
    if (!mp.openFromFile("next_level_aespa.ogg")) 
    	exit(0);

	while (1)
	{
		if (!isPlaying)
		{
			if (mp.getStatus() != sf::Music::Paused)
				mp.pause();
		}
		else
		{
			if (mp.getStatus() != sf::Music::Playing)
				mp.play();
		}
	}
}


