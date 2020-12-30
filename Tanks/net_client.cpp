#include "net_client.h"

#include<stdexcept>

#include "engine.h"


NetClient::NetClient(const unsigned short& server_port, const std::string& server_address) {
	this->server_port = server_port;
	this->server_address = server_address;

	buffer = new char[BUFFER_SIZE];

	listening_mode = false;


	if (!(initializeSocketUDP() && initializeSocketTCP())) {
		connected_to_server = false;
		std::cout << "\nCouldn't initialize network!";
	}
	else {
		connected_to_server = true;
		std::cout << "\nSuccesfully connected to the server";
	}
};

NetClient::~NetClient()
{
	delete[] buffer;


	std::cout << "\nRozlonczansko xdd";
	this->tcp.disconnect();
	std::cout << "\nRozlonczylem :---D";
};



bool NetClient::initializeSocketUDP()
{
	sf::Socket::Status status = udp.bind(sf::Socket::AnyPort);
	if (status != sf::Socket::Done) {
		std::cout << "\nFailed to bind UDP port";
		return false;
	}
	else {
		return true;
	}
}

bool NetClient::initializeSocketTCP() {
	sf::Socket::Status status = tcp.connect(server_address, server_port);
	if (status != sf::Socket::Done) {
		std::cout << "\nFailed to establish TCP connection";
		return false;
	}
	else {


		char* temp_buffer = new char[BUFFER_SIZE]();
		std::size_t received_data = 0;

		sf::Socket::Status status = tcp.receive(temp_buffer, BUFFER_SIZE, received_data);
		if (status == sf::Socket::Status::Done) {
			my_id = atoi(temp_buffer);
			std::cout << "My id: " << this->my_id;
		}



		return true;
	}
}


void NetClient::readDataTCP() {
	char* temp_buffer = new char[BUFFER_SIZE]();
	std::size_t received_data = 0;

	sf::Socket::Status status = tcp.receive(temp_buffer, BUFFER_SIZE, received_data);
	if (status == sf::Socket::Status::Done) {

		try {

			json temp_json = json::parse(temp_buffer);

			
			this->json_buffer = temp_json;
			if (this->json_buffer["players"].is_null())
				std::cout << "\n\n##" << temp_buffer << "\n\n##";


			//std::cout << "\nTCP[" << received_data << "B]: " << temp_json.dump();
		}
		catch (std::exception &e) {
			std::cout << "Parse error, rejecting packet:\n" << temp_buffer<<std::endl;
		}


	}

	delete[] temp_buffer;
}

void NetClient::readDataUDP() {
	char* temp_buffer = new char[BUFFER_SIZE];
	std::size_t received_data = 0;
	sf::IpAddress sender(this->server_address);

	sf::Socket::Status status = udp.receive(temp_buffer, BUFFER_SIZE, received_data, sender, this->server_port);
	if (status == sf::Socket::Status::Done) {
		try {
			json temp_json = json::parse(temp_buffer);
			this->json_buffer = temp_json;

			//std::cout << "\nUDP[" << received_data << "B]: " << temp_json.dump();
		}
		catch (std::exception& e) {
			std::cout << "Parse error, rejecting packet:\n" << temp_buffer << std::endl;
		}


	}
	delete[] temp_buffer;
}

void NetClient::listenTCP() {
	do {
		if (listening_mode)
			this->readDataTCP();
	} while (true);
}

void NetClient::listenUDP() {
	do {
		if (listening_mode)
			this->readDataUDP();
	} while (true);
}

bool NetClient::sendDataTCP(const char* data, const unsigned short& data_size) {
	sf::Socket::Status status = this->tcp.send(data, data_size);
	if (status != sf::Socket::Status::Done)
		return false;
	else
		return true;
}

bool NetClient::sendDataUDP(const char* data, const unsigned short& data_size) {
	sf::Socket::Status status = this->udp.send(data, data_size, this->server_address, this->server_port);
	if (status != sf::Socket::Status::Done)
		return false;
	else
		return true;
}