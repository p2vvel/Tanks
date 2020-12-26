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



		this.tcp = net.createServer();
		this.tcp.on("connection", this.handleConnectionTCP);




		//start listening od UDP and TCP ports
		this.udp.bind(this.port);
		this.tcp.listen(this.port);

	

		setInterval( () => {


			// console.log(this.data.players)
			for(let index in this.data.players)
			{
				this.data.players[index].write(`\nGraczor #${index}`);
				console.log(index)
			}
			

			// for (let i = 0; i < this.players_counter; i++)
			// 	this.players[i].write(`\nGraczor #${i}`);
		}, 1000);



		this.players_counter = 0;
		this.data = {};
		this.data.players = {};
	}

	handleConnectionTCP(connection) {
		console.log(`New player connected: ${connection.remoteAddress}:${connection.remotePort}`)
		// this.players.push(connection);
		connection.on("data", this.handleDataTCP);
		connection.on("error", this.handleErrorTCP);
		connection.on("close", this.handleDisconnectTCP.apply(this, [this.players_counter]));
		
		connection.id = this.players_counter;	//saves id data in connection object
		this.data.players[this.players_counter] = connection;	//saves connection object(player connection)
		connection.write(this.players_counter.toString());	//sends to player info about his ID


		this.players_counter += 1;


		// connection.write(JSON.stringify({t: 0, id: this.players.length}));
	}

	handleErrorTCP(err) {
		console.log(`TCP error: ${err}`);
	}
	

	handleDataTCP(data) {
		// console.log(`Received new data: ${data}`);
	}

	handleListeningTCP() {
		console.log(`TCP started listening at: ${this.tcp.address()}:[${this.port}]`)
	}

	handleDisconnectTCP(e, id) {
		console.log("#", id, "disconnected", this);
		console.log("Client disconnected");
	}

	//##############
	//UDP functions:
	//##############
	handleErrorUDP(err){
		console.log(`UDP error: ${err}`)
		this.udp.close();
	}

	handleReceiveUDP(msg, rinfo){
		this.data.push(JSON.parse(msg))
		console.log(`New UDP message: ${this.data[this.players_counter - 1]}\nFrom: ${rinfo}`);
	}

	handleListeningUDP() {
		console.log(`UDP started listening at: ${this.udp.address().address}:[${this.udp.address().port}]`)
	}
}


export default TanksServer;
