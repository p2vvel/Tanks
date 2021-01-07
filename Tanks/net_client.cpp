#include<stdexcept>
#include "net_client.h"
#include "engine.h"


NetClient::NetClient(const unsigned short& server_port, const std::string& server_address) {
	this->server_port = server_port;
	this->server_address = server_address;

	buffer = new char[BUFFER_SIZE];
	json_buffer_old = new json;
	json_buffer = new json;
	read_data_recently = false;

	listening_mode = false;



	if (!(
#ifndef UDP_UNUSED
		initializeSocketUDP() && 
#endif // !UDP_UNUSED
		initializeSocketTCP())) {
		connected_to_server = false;
		std::cout << "\nCouldn't initialize network!";
	}
	else {
		connected_to_server = true;
		std::cout << "\nSuccesfully connected to the server";
	}
};

NetClient::~NetClient() {
	delete json_buffer_old;
	delete json_buffer;
	delete[] buffer;

	this->tcp.disconnect();
	std::cout << "\nDisconnected";
};





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
			std::cout << "My id: " << this->my_id << std::endl;
		}

		delete[] temp_buffer;
		return true;
	}
}


void NetClient::readDataTCP() {
	char* temp_buffer = new char[BUFFER_SIZE]();
	std::size_t received_data = 0;

	sf::Socket::Status status = tcp.receive(temp_buffer, BUFFER_SIZE, received_data);
	if (status == sf::Socket::Status::Done) {
		try {
			//Swaps pointers to then overwrite json_buffer with new data
			json* temp = this->json_buffer;
			this->json_buffer = this->json_buffer_old;
			this->json_buffer_old = temp;

			*(this->json_buffer) = json::parse(temp_buffer);
			read_data_recently = true;
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



bool NetClient::sendDataTCP(const char* data, const unsigned short& data_size) {
	sf::Socket::Status status = this->tcp.send(data, data_size);
	if (status != sf::Socket::Status::Done)
		return false;
	else
		return true;
}


#ifndef UDP_UNUSED

bool NetClient::initializeSocketUDP() {
	sf::Socket::Status status = udp.bind(sf::Socket::AnyPort);
	if (status != sf::Socket::Done) {
		std::cout << "\nFailed to bind UDP port";
		return false;
	}
	else
		return true;
}

void NetClient::readDataUDP() {
	char* temp_buffer = new char[BUFFER_SIZE];
	std::size_t received_data = 0;

	sf::IpAddress sender(this->server_address);
	sf::Socket::Status status = udp.receive(temp_buffer, BUFFER_SIZE, received_data, sender, this->server_port);
	if (status == sf::Socket::Status::Done) {
		try {
			//Swaps pointers to then overwrite json_buffer with new data
			json* temp = this->json_buffer;
			this->json_buffer = this->json_buffer_old;
			this->json_buffer_old = temp;

			*(this->json_buffer) = json::parse(temp_buffer);
			read_data_recently = true;
		}
		catch (std::exception& e) {
			std::cout << "Parse error, rejecting packet:\n" << temp_buffer << std::endl;
		}
	}

	delete[] temp_buffer;
}


void NetClient::listenUDP() {
	do {
		if (listening_mode)
			this->readDataUDP();
	} while (true);
}


bool NetClient::sendDataUDP(const char* data, const unsigned short& data_size) {
	sf::Socket::Status status = this->udp.send(data, data_size, this->server_address, this->server_port);
	if (status != sf::Socket::Status::Done)
		return false;
	else
		return true;
}

#endif //UDP_UNUSED
