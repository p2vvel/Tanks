#pragma once
#include<SFML\Network.hpp>
#include<string>
#include<thread>
#include<iostream>
#include<limits>
#include<nlohmann/json.hpp>

#include<cstdlib>

#define BUFFER_SIZE USHRT_MAX

using nlohmann::json;


class NetClient
{
	sf::TcpSocket tcp;
	sf::UdpSocket udp;

	unsigned short server_port;
	std::string server_address;

	char* buffer;
	json* json_buffer;

	bool listening_mode;	//indicates if sockets should try to read incoming data
	unsigned short my_id;

public:

	NetClient(const unsigned short& server_port = 3000, const std::string& server_address = "127.0.0.1");
	~NetClient();

	void setListeningMode(const bool& listen = false) { this->listening_mode = listen; }
	const char& getID() const { return this->my_id; }
	bool initializeSocketUDP();
	bool initializeSocketTCP();
	void readDataTCP();
	void readDataUDP();
	void listenTCP();
	void listenUDP();
	bool sendDataTCP(const char* data, const unsigned short& data_size);
	bool sendDataUDP(const char* data, const unsigned short& data_size);
};