#include <unordered_map>
#include <SFML/Network.hpp>
//#include <vector>
#include "PacketType.h"


class Server
{

private:
	typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
	Clients clients;
	sf::TcpListener listner;
	bool isPlaying = false;

	void handlePackets();
	void broadCast(PacketType type, const std::string & msg);

public:
	Server(unsigned short port);
	~Server();

	void run();

	void setAudio(bool);
	void playAudio();

};

