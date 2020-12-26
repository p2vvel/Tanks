import * as dgram from "dgram";
import * as net from "net";


class TanksServer{
	constructor(port = 3000, address = "127.0.0.1"){
		this.port = port;
		this.handleErrorUDP = this.handleErrorUDP.bind(this);
		this.handleReceiveUDP = this.handleReceiveUDP.bind(this);
		this.handleListeningUDP = this.handleListeningUDP.bind(this);



		this.udp = dgram.createSocket("udp4");
		this.udp.on("error", this.handleErrorUDP);
		this.udp.on("message", this.handleReceiveUDP);
		this.udp.on("listening", this.handleListeningUDP);



		this.handleConnectionTCP = this.handleConnectionTCP.bind(this);
		this.handleDataTCP = this.handleDataTCP.bind(this);
		this.handleErrorTCP = this.handleErrorTCP.bind(this);
		this.handleListeningTCP = this.handleListeningTCP.bind(this);
		this.handleDisconnectTCP = this.handleDisconnectTCP.bind(this);


		this.prepareDataToSend = this.prepareDataToSend.bind(this);


		this.tcp = net.createServer();
		this.tcp.on("connection", this.handleConnectionTCP);




		//start listening od UDP and TCP ports
		this.udp.bind(this.port);
		this.tcp.listen(this.port);

	

		setInterval( () => {

			let xd = this.prepareDataToSend();
			console.log(xd);
			// console.log(this.data.players)
			for(let index in this.data.players)
				this.data.players[index].write(xd);
			

		}, 1000);



		this.players_counter = 0;
		this.data = {};
		this.data.players = {};	//players connection
		this.data.players_data = {};	//current player data
	}

	handleConnectionTCP(connection) {
		console.log(`New player connected: ${connection.remoteAddress}:${connection.remotePort}`)
		// this.players.push(connection);
		connection.on("data", this.handleDataTCP);
		connection.on("error", this.handleErrorTCP);
		connection.on("close", (e) => { 
			console.log("Player disconnected: ", connection.id)
			delete this.data.players[connection.id];
		});
		
		connection.id = this.players_counter;	//saves id data in connection object
		this.data.players[this.players_counter] = connection;	//saves connection object(player connection)
		connection.write(this.players_counter.toString());	//sends to player info about his ID


		this.players_counter += 1;


	}

	handleErrorTCP(err) {
		console.log(`TCP error: ${err}`);
	}

	handleDataTCP(data) {
		let temp_data = JSON.parse(data);
		// console.log(temp_data)
		console.log(`Received data from player #${temp_data.id}`);
		this.data.players_data[temp_data.id] = temp_data;
	}

	handleListeningTCP() {
		console.log(`TCP started listening at: ${this.tcp.address()}:[${this.port}]`)
	}

	handleDisconnectTCP(e, id) {
		console.log("#", id, "disconnected");
		console.log("Client disconnected");
	}

	//##############
	//UDP functions:
	//##############
	handleErrorUDP(err){
		console.log(`UDP error: ${err}`);
		this.udp.close();
	}

	handleReceiveUDP(msg, rinfo){
		// this.data.push(JSON.parse(msg));
		// console.log(`New UDP message: ${this.data[this.players_counter - 1]}\nFrom: ${rinfo}`);
		console.log("New udp data");
	}

	handleListeningUDP() {
		console.log(`UDP started listening at: ${this.udp.address().address}:[${this.udp.address().port}]`);
	}




	prepareDataToSend(){
		let temp = {}
		temp.tanks = []
		
		for (let index in this.data.players_data){
			temp.tanks.push(this.data.players_data[index]);
		}


		return JSON.stringify(temp);

	}
}


export default TanksServer;
