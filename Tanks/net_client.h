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
	friend class Engine;
	sf::TcpSocket tcp;
	sf::UdpSocket udp;

	unsigned short server_port;
	std::string server_address;

	char* buffer;
	json *json_buffer_old;
	json* json_buffer;
	bool read_data_recently;

	bool listening_mode;	//indicates if sockets should try to read incoming data
	unsigned short my_id;

	bool connected_to_server;

public:

	NetClient(const unsigned short& server_port = 3000, const std::string& server_address = "127.0.0.1");
	~NetClient();

	const bool& succesfullConnection() const { return this->connected_to_server;  }

	void setListeningMode(const bool& listen = false) { 
		if (listen == true) {
			read_data_recently = false;
		}
		else {
			if (read_data_recently) {
				json* temp = this->json_buffer_old;
				this->json_buffer_old = this->json_buffer;
				this->json_buffer = temp;
			}
		}
		
		this->listening_mode = listen; 
	}

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