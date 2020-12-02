#pragma once
#include<SFML\Network.hpp>
#include<string>
#include<thread>
#include<iostream>
#include<limits>
#include<nlohmann/json.hpp>

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


	//returns slice of char array
	static char* substring(const char* str, const unsigned short& length, const unsigned char& end, const unsigned char& start = 0) {
		if (end > length || end <= start) {
			char* temp = new char[1];
			temp[0] = '\0';;
			return temp;
		};

		//+1 in size to store terminating NULL character at the end
		char* temp = new char[end - start + 1]();	//with () at the end all elements will be initialized with 0 ('\0')
		//temp[end - start] = '\0';

		for (int i = 0; i < (end - start); i++)
			temp[i] = str[start + i];


		return temp;
	}


public:
	NetClient(const unsigned short& server_port = 3000, const std::string& server_address = "127.0.0.1") {
		this->server_port = server_port;
		this->server_address = server_address;

		buffer = new char[BUFFER_SIZE];
		json_buffer = new json;

		listening_mode = false;


		if (!(initializeSocketUDP() && initializeSocketTCP()))
			std::cout << "\nCouldn't initialize network!";
		else
			std::cout << "\nSuccesfully connected to the server";
	};

	~NetClient()
	{
		delete[] buffer;
		delete json_buffer;
	};

	void setListeningMode(const bool& listen = false) {
		this->listening_mode = listen;
	}


	bool initializeSocketUDP()
	{
		sf::Socket::Status status = udp.bind(sf::Socket::AnyPort);
		if (status != sf::Socket::Done) {
			std::cout << "\nFailed to bind UDP port";
			return false;
		}
		else
			return true;
	}

	bool initializeSocketTCP() {
		sf::Socket::Status status = tcp.connect(server_address, server_port);
		if (status != sf::Socket::Done) {
			std::cout << "\nFailed to establish TCP connection";
			return false;
		}
		else
			return true;
	}


	void readDataTCP() {
		char* temp_buffer = new char[BUFFER_SIZE];
		std::size_t received_data = 0;

		sf::Socket::Status status = tcp.receive(temp_buffer, BUFFER_SIZE, received_data);
		if (status == sf::Socket::Status::Done) {
			char* temp = substring(temp_buffer, BUFFER_SIZE, received_data);
			std::cout << "\nTCP["<<received_data<<"B]: " << temp;
			

			delete[] temp;
		}
	}

	void readDataUDP() {
		char* temp_buffer = new char[BUFFER_SIZE];
		std::size_t received_data = 0;
		sf::IpAddress sender(this->server_address);

		sf::Socket::Status status = udp.receive(temp_buffer, BUFFER_SIZE, received_data, sender, this->server_port);
		if (status == sf::Socket::Status::Done) {
			char* temp = substring(temp_buffer, BUFFER_SIZE, received_data);
			std::cout << "\nUDP[" << received_data << "B]: " << temp;


			delete[] temp;
		}
	}

	void listenTCP() {
		do {
			if (listening_mode)
				this->readDataTCP();
		} while (true);
	}

	void listenUDP() {
		do {
			if (listening_mode)
				this->readDataUDP();
		} while (true);
	}
};