import * as dgram from "dgram";
import { thomsonCrossSectionDependencies } from "mathjs";
import * as net from "net";

import * as Physics from "./physics_functions.js"


const screen = { width: 1280, height: 720 }



class TanksServer {
	constructor(port = 3000, address = "127.0.0.1") {
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
		this.update_Bullets = this.update_Bullets.bind(this);
		this.handle_Map_Loop = this.handle_Map_Loop.bind(this);
		this.update_Tank = this.update_Tank.bind(this);
		this.update = this.update.bind(this);
		this.handle_Bullets_Collision = this.handle_Bullets_Collision.bind(this);
		this.handle_Tanks_Collision = this.handle_Tanks_Collision.bind(this);

		this.prepareDataToSend = this.prepareDataToSend.bind(this);


		this.tcp = net.createServer();
		this.tcp.on("connection", this.handleConnectionTCP);


		//start listening od UDP and TCP ports
		this.udp.bind(this.port);
		this.tcp.listen(this.port);



		this.active_players = 0;
		this.players_counter = 0;
		this.data = {};
		this.data.players = {};	//players connection
		this.data.players_data = {};	//current player data
		this.data.bullets_data = [];


		setInterval(this.update, 16);	//updates bullets positions every frame
	}

	handleConnectionTCP(connection) {
		// this.players.push(connection);
		connection.on("data", this.handleDataTCP);
		connection.on("error", this.handleErrorTCP);
		connection.on("close", (e) => {
			this.active_players -= 1;
			console.log(`${connection.id}# player disconnected`)
			console.log(`Active players: ${this.active_players}`)
			delete this.data.players[connection.id];
			delete this.data.players_data[connection.id];
		});

		connection.id = this.players_counter;	//saves id data in connection object
		this.data.players[this.players_counter] = connection;	//saves connection object(player connection)
		connection.write(this.players_counter.toString());	//sends to player info about his ID


		console.log(`New player connected[id: ${connection.id}]: ${connection.remoteAddress}:${connection.remotePort}`)


		this.players_counter += 1;
		// this.active_players += 1;
		// console.log(`Active players: ${this.active_players}`)

	}

	handleErrorTCP(err) {
		console.log(`TCP error: ${err}`);
	}

	handleDataTCP(data) {
		let temp_data;
		try {

			temp_data = JSON.parse(data);

			if (!(temp_data.id in this.data.players_data)) {
				this.active_players += 1;	//increments active players after receiving first packet from new player
				console.log(`Active players: ${this.active_players}`)
			}

			if ('shot' in temp_data) {
				// console.log(temp_data);
				this.data.bullets_data.push(temp_data.shot);
				delete temp_data.shot;
			}

			this.data.players_data[temp_data.id] = temp_data;



			//Updates
			this.update_Tank(temp_data.id);



			let temp = this.prepareDataToSend();
			this.data.players[temp_data.id].write(temp);


		}
		catch (err) {
			console.log(err, data)
		}
		// console.log(temp_data)

	}

	handleListeningTCP() {
		console.log(`TCP started listening at: ${this.tcp.address()}:[${this.port}]`)
	}


	//##############
	//UDP functions:
	//##############
	handleErrorUDP(err) {
		console.log(`UDP error: ${err}`);
		this.udp.close();
	}

	handleReceiveUDP(msg, rinfo) {
		// this.data.push(JSON.parse(msg));
		// console.log(`New UDP message: ${this.data[this.players_counter - 1]}\nFrom: ${rinfo}`);
		console.log("New udp data");
	}

	handleListeningUDP() {
		console.log(`UDP started listening at: ${this.udp.address().address}:[${this.udp.address().port}]`);
	}




	prepareDataToSend() {
		let temp = {}
		temp.tanks = []
		temp.bullets = this.data.bullets_data;

		for (let index in this.data.players_data) {
			let temp_player = this.data.players_data[index];

			temp.tanks.push(temp_player);


		}

		temp.players = this.active_players;


		return JSON.stringify(temp);

	}

	update_Bullets() {
		let temp = this.data.bullets_data.length;
		this.data.bullets_data = this.data.bullets_data.filter((e) => ((e.pos.x >= -50 && e.pos.x <= screen.width + 50) && (e.pos.y >= -50 && e.pos.y <= screen.height + 50)));	//delete bullets that flew away from displayed area

		if (temp != this.data.bullets_data.length)
			console.log("Bullet deleted");

		for (let b of this.data.bullets_data) {
			let movement_vector = Physics.calculate_vector(b.speed, b.angle);
			b.pos.x += movement_vector.x;
			b.pos.y += movement_vector.y;
		}
	}

	update() {
		this.update_Bullets();
		// this.update_Tanks();
	}

	handle_Map_Loop(tank_id) {
		if (this.data.players_data[tank_id].pos.x < -50)
			this.data.players_data[tank_id].pos.x = screen.width + 50;
		else if (this.data.players_data[tank_id].pos.x > screen.width + 50)
			this.data.players_data[tank_id].pos.x = -50;

		if (this.data.players_data[tank_id].pos.y < -50)
			this.data.players_data[tank_id].pos.y = screen.height + 50;
		else if (this.data.players_data[tank_id].pos.y > screen.height + 50)
			this.data.players_data[tank_id].pos.y = -50;
	}

	handle_Bullets_Collision(tank_id) {
		let tank = this.data.players_data[tank_id];
		let tank_collision_area = {
			x: tank.pos.x,
			y: tank.pos.y,
			r: 30,
		};

		for (let b of this.data.bullets_data) {
			if (b.shooter === tank.id)	//kurt cobain does not approve
				continue;

			let bullet_collision_area = {
				x: b.pos.x,
				y: b.pos.y,
				r: 15,
			};

			if (Physics.check_collision(tank_collision_area, bullet_collision_area)) {
				b.shooter = -1;
				this.data.players_data[tank_id].health -= b.power;
				if (b.shooter in this.data.players_data)	//if shooter didnt rage quit
					this.data.players_data[b.shooter].score += 1;	//someones bullet killed me, his profit	:(
			}
		}

		this.data.bullets_data = this.data.bullets_data.filter(e => e.shooter != -1);	//deletes bullets that hit targets
	}

	handle_Tanks_Collision(tank_id) {
		let tank = this.data.players_data[tank_id];
		let tank_collision_area = {
			x: tank.pos.x,
			y: tank.pos.y,
			r: 30,
		};

		for (let enemy in this.data.players_data) {
			if (this.data.players_data[enemy].id === tank.id || this.data.players_data[enemy].health <= 0)
				continue;

			let enemy_collision_area = {
				x: this.data.players_data[enemy].pos.x,
				y: this.data.players_data[enemy].pos.y,
				r: 30,
			}

			if (Physics.check_collision(tank_collision_area, enemy_collision_area)) {
				tank.health = 0;
				this.data.players_data[enemy].health = 0;
			}
		}
	}

	handle_Tank_Respawn(tank_id) {
		let tank = this.data.players_data[tank_id];
		let tank_collision_area = {
			x: tank.pos.x,
			y: tank.pos.y,
			r: 30,
		};

		let collision_areas = [{
			x: 100,
			y: 100,
			r: 30,
		}, {
			x: screen.width - 100,
			y: 100,
			r: 30,
		}, {
			x: 100,
			y: screen.height - 100,
			r: 30,
		}, {
			x: screen.width - 100,
			y: screen.height - 100,
			r: 30,
		}];


		//check if any spawn area can be used
		for (let i = 0; i < collision_areas.length; i++) {

			let can_be_used = true;
			for (let enemy in this.data.players_data) {
				if (this.data.players[enemy].id === tank_id)
					continue;

				let enemy_collision_area = {
					x: this.data.players_data[enemy].pos.x,
					y: this.data.players_data[enemy].pos.y,
					r: 30,
				}

				if (Physics.check_collision(collision_areas[i], enemy_collision_area)) {
					can_be_used = false;
					break;
				}
			}

			if (can_be_used) {
				tank.pos.x = collision_areas[i].x;	//sets spawn position
				tank.pos.y = collision_areas[i].y;	//sets spawn position
				tank.health = 100;	//restores full health
				tank.cycle = 0;	//resets death animation cycles
				tank.speed = 0;	//stops dead tank
				//zapisansko
				break;
			}



		}
	}


	update_Tank(tank_id) {
		if (this.data.players_data[tank_id].health > 0) {
			this.handle_Map_Loop(tank_id);
			this.handle_Bullets_Collision(tank_id);
			this.handle_Tanks_Collision(tank_id);
		}
		else {
			if (this.data.players_data[tank_id].cycle >= 120)	//player has to wait some time for respawn
				this.handle_Tank_Respawn(tank_id);
		}
	}
}


export default TanksServer;
