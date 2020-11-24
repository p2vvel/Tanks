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
			for (let i = 0; i < this.players.length; i++)
				this.players[i].write(`\nGraczor #${i}`);
		}, 1000);

		this.players = [];
	}

	handleConnectionTCP(connection) {
		console.log(`New player connected: ${connection.remoteAddress}:${connection.remotePort}`)
		this.players.push(connection);
		connection.on("data", this.handleDataTCP);
		connection.on("error", this.handleErrorTCP);
		connection.on("end", this.handleDisconnectTCP);

		// connection.write(JSON.stringify({t: 0, id: this.players.length}));
	}

	handleErrorTCP(err) {
		console.log(`TCP error: ${err}`);
	}
	

	handleDataTCP(data) {
		console.log(`Received new data: ${data}`);
	}

	handleListeningTCP() {
		console.log(`TCP started listening at: ${this.tcp.address()}:[${this.port}]`)
	}

	handleDisconnectTCP(e) {
		console.log("Client disconnected");
		// this.players.pop();
	}

	//##############
	//UDP functions:
	//##############
	handleErrorUDP(err){
		console.log(`UDP error: ${err}`)
		this.udp.close();
	}

	handleReceiveUDP(msg, rinfo){
		console.log(`New UDP message: ${msg}\nFrom: ${rinfo}`);
	}

	handleListeningUDP() {
		console.log(`UDP started listening at: ${this.udp.address().address}:[${this.udp.address().port}]`)
	}
}


export default TanksServer;
