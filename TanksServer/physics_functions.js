import * as Math from "mathjs";
// const Math = require("mathjs"); 

export function calculate_vector(distance, angle){
    let rad_angle = (3.1415926536 / 180) * (angle); //funkcje trygonometryczne wymagaja wartosci w radianach
    let result = {}
	result.y = distance * -Math.cos(rad_angle);
	result.x = distance * Math.sin(rad_angle);

	return result;
}