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


	//returns slice of char array 4
	//static char* substring(const char* str, const unsigned short& length, const unsigned char& end, const unsigned char& start = 0) {
	//	if (end > length || end <= start) {
	//		char* temp = new char[1];
	//		temp[0] = '\0';
	//		return temp;
	//	};

	//	//+1 in size to store terminating NULL character at the end
	//	char* temp = new char[end - start + 1]();	//with () at the end all elements will be initialized with 0 ('\0')
	//	//temp[end - start] = '\0';

	//	for (int i = 0; i < (end - start); i++)
	//		temp[i] = str[start + i];


	//	return temp;
	//}

	static char* substring(const char* str, const unsigned short& length, const unsigned char& end, const unsigned char& start = 0) {
		if (end > length || end <= start) {
			char* temp = new char[1];
			temp[0] = '\0';
			return temp;
		};

		//+1 in size to store terminating NULL character at the end
		char* temp = new char[end - start + 1]();	//with () at the end all elements will be initialized with 0 ('\0')
		//temp[end - start] = '\0';

		std::cout << "\nData: ";
		for (int i = 0; i < (end - start); i++)
		{
			temp[i] = str[start + i];
			std::cout << temp[i];
		}
		std::cout << "\n\n";


		return temp;
	}


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