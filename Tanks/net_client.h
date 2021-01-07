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


#define UDP_UNUSED



class NetClient
{
	friend class Engine;

	unsigned short server_port;
	std::string server_address;
	
	sf::TcpSocket tcp;
#ifndef UDP_UNUSED
	sf::UdpSocket udp;
#endif
	json *json_buffer_old;
	json* json_buffer;
	char* buffer;

	bool connected_to_server;
	bool listening_mode;	//indicates if sockets should try to read incoming data
	bool read_data_recently;
	unsigned short my_id;

public:

	NetClient(const unsigned short& server_port, const std::string& server_address);
	~NetClient();

	const bool& succesfullConnection() const { return this->connected_to_server;  }

	const char& getID() const { return this->my_id; }
	
	bool sendDataTCP(const char* data, const unsigned short& data_size);
	bool initializeSocketTCP();
	void readDataTCP();
	void listenTCP();
	
#ifndef UDP_UNUSED 
	bool sendDataUDP(const char* data, const unsigned short& data_size);
	bool initializeSocketUDP();
	void readDataUDP();
	void listenUDP();
#endif
};