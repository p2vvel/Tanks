#include "net_client.h"





NetClient::NetClient(const unsigned short& server_port , const std::string& server_address) {
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

NetClient::~NetClient()
{
	delete[] buffer;
	delete json_buffer;


	std::cout << "Rozlonczansko xdd";
	this->tcp.disconnect();
	std::cout << "Rozlonczylem :---D";
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


		char* temp_buffer = new char[BUFFER_SIZE];
		std::size_t received_data = 0;

		sf::Socket::Status status = tcp.receive(temp_buffer, BUFFER_SIZE, received_data);
		if (status == sf::Socket::Status::Done) {
			char* temp = substring(temp_buffer, BUFFER_SIZE, received_data);
			my_id = atoi(temp);
			std::cout << "My id: " << this->my_id;
		}



		return true;
	}
}


void NetClient::readDataTCP() {
	char* temp_buffer = new char[BUFFER_SIZE];
	std::size_t received_data = 0;

	sf::Socket::Status status = tcp.receive(temp_buffer, BUFFER_SIZE, received_data);
	if (status == sf::Socket::Status::Done) {
		char* temp = substring(temp_buffer, BUFFER_SIZE, received_data);
		std::cout << "\nTCP[" << received_data << "B]: " << temp;


		delete[] temp;
	}
}

void NetClient::readDataUDP() {
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