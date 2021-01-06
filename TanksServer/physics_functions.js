import * as Math from "mathjs";
// const Math = require("mathjs"); 

export function calculate_vector(distance, angle){
    let rad_angle = (3.1415926536 / 180) * (angle); //funkcje trygonometryczne wymagaja wartosci w radianach
    let result = {}
	result.y = distance * -Math.cos(rad_angle);
	result.x = distance * Math.sin(rad_angle);

	return result;
}


export function check_collision(a, b){
	let distance = Math.sqrt(Math.pow(b.x - a.x, 2) + Math.pow(b.y - a.y, 2))
	return distance <= (a.r + b.r)
}