import * as net from "net";

import * as Physics from "./physics_functions.js"


const screen = { width: 1280, height: 720 }



class TanksServer {
	constructor(port = 3000, address = "127.0.0.1") {
		this.port = port;

		this.handleConnectionTCP = this.handleConnectionTCP.bind(this);
		this.handleDataTCP = this.handleDataTCP.bind(this);
		this.handleListeningTCP = this.handleListeningTCP.bind(this);
		this.update_Bullets = this.update_Bullets.bind(this);
		this.handle_Map_Loop = this.handle_Map_Loop.bind(this);
		this.update_Tank = this.update_Tank.bind(this);
		this.handle_Bullets_Collision = this.handle_Bullets_Collision.bind(this);
		this.handle_Tanks_Collision = this.handle_Tanks_Collision.bind(this);

		this.prepareDataToSend = this.prepareDataToSend.bind(this);

		this.tcp = net.createServer();
		this.tcp.on("connection", this.handleConnectionTCP);
		this.tcp.listen(this.port);		//start listening at TCP port


		this.active_players = 0;
		this.players_counter = 0;
		this.data = {};
		this.data.players = {};	//players connection
		this.data.players_data = {};	//current player data
		this.data.bullets_data = [];
		this.data.score_data = {};

		setInterval(this.update_Bullets, 16);	//updates bullets positions every frame
	}

	handleConnectionTCP(connection) {
		connection.on("data", this.handleDataTCP);
		connection.on("error", () => console.log(`TCP error: ${err}`));
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

		this.players_counter += 1;	//used to count total amount of players to increment their IDs
	}

	handleDataTCP(data) {
		try {
			let temp_data = JSON.parse(data);
			let new_player = !(temp_data.id in this.data.players_data);

			if ('shot' in temp_data) {
				this.data.bullets_data.push(temp_data.shot);
				temp_data.shot = true;	//indicates that client should draw enemies muzzle flash
			}

			if (!new_player && 'has_to_be_killed' in this.data.players_data[temp_data.id] && this.data.players_data[temp_data.id].has_to_be_killed === true) {
				this.data.players_data[temp_data.id] = temp_data;
				this.data.players_data[temp_data.id].health = 0;
			}
			else {
				this.data.players_data[temp_data.id] = temp_data;
			}

			if (new_player) {
				this.data.score_data[temp_data.id] = 0;
				this.active_players += 1;	//increments active players after receiving first packet from new player
				console.log(`Active players: ${this.active_players}`)
				this.handle_Tank_Respawn(temp_data.id);	//uses respawn function to set new player position so it doesnt collide with any player
			}

			this.data.players_data[temp_data.id].score = this.data.score_data[temp_data.id];
			this.update_Tank(temp_data.id);

			let temp = this.prepareDataToSend();
			this.data.players[temp_data.id].write(temp);
		}
		catch (err) {
			console.log(err, data)
		}
	}


	handleListeningTCP() {
		console.log(`TCP started listening at: ${this.tcp.address()}:[${this.port}]`)
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
		this.data.bullets_data = this.data.bullets_data.filter((e) => ((e.pos.x >= -50 && e.pos.x <= screen.width + 50) && (e.pos.y >= -50 && e.pos.y <= screen.height + 50)));	//delete bullets that flew away from displayed area

		//updates bullets positions
		for (let b of this.data.bullets_data) {
			let movement_vector = Physics.calculate_vector(b.speed, b.angle);
			b.pos.x += movement_vector.x;
			b.pos.y += movement_vector.y;
		}
	}

	//if player crosses any map border, he is teleported on the opposite side
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
				this.data.players_data[tank_id].health -= b.power;
				if (this.data.players_data[tank_id].health < 0)
					this.data.players_data[tank_id].health = 0;
				if (b.shooter in this.data.players_data)	//if shooter didnt rage quit
					this.data.score_data[b.shooter] += b.power;	//someones bullet killed me, no profit(for me)	:(
				b.shooter = -1;	//indicates that bullet should be deleted later
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
				this.data.players_data[enemy].has_to_be_killed = true;
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
