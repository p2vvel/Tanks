#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "names.h"

//Klasa pojemnika na przechowywanie zasobow (np. spritey)
class Storage
{
public:

	enum sprite_index {
		barrelBlack_side, barrelBlack_top, barrelGreen_side, barrelGreen_top, barrelRed_side, barrelRed_top, barrelRust_side, barrelRust_top,
		barricadeMetal, barricadeWood, bulletBlue1, bulletBlue1_outline, bulletBlue2, bulletBlue2_outline, bulletBlue3, bulletBlue3_outline,
		bulletDark1, bulletDark1_outline, bulletDark2, bulletDark2_outline, bulletDark3, bulletDark3_outline, bulletGreen1, bulletGreen1_outline,
		bulletGreen2, bulletGreen2_outline, bulletGreen3, bulletGreen3_outline, bulletRed1, bulletRed1_outline, bulletRed2, bulletRed2_outline,
		bulletRed3, bulletRed3_outline, bulletSand1, bulletSand1_outline, bulletSand2, bulletSand2_outline, bulletSand3, bulletSand3_outline,
		crateMetal, crateMetal_side, crateWood, crateWood_side, explosion1, explosion2, explosion3, explosion4,
		explosion5, explosionSmoke1, explosionSmoke2, explosionSmoke3, explosionSmoke4, explosionSmoke5, fenceRed, fenceYellow,
		oilSpill_large, oilSpill_small, sandbagBeige, sandbagBeige_open, sandbagBrown, sandbagBrown_open, shotLarge, shotOrange,
		shotRed, shotThin, specialBarrel1, specialBarrel1_outline, specialBarrel2, specialBarrel2_outline, specialBarrel3, specialBarrel3_outline,
		specialBarrel4, specialBarrel4_outline, specialBarrel5, specialBarrel5_outline, specialBarrel6, specialBarrel6_outline, specialBarrel7, specialBarrel7_outline,
		tankBlue_barrel1, tankBlue_barrel1_outline, tankBlue_barrel2, tankBlue_barrel2_outline, tankBlue_barrel3, tankBlue_barrel3_outline, tankBody_bigRed, tankBody_bigRed_outline,
		tankBody_blue, tankBody_blue_outline, tankBody_dark, tankBody_darkLarge, tankBody_darkLarge_outline, tankBody_dark_outline, tankBody_green, tankBody_green_outline,
		tankBody_huge, tankBody_huge_outline, tankBody_red, tankBody_red_outline, tankBody_sand, tankBody_sand_outline, tankDark_barrel1, tankDark_barrel1_outline,
		tankDark_barrel2, tankDark_barrel2_outline, tankDark_barrel3, tankDark_barrel3_outline, tankGreen_barrel1, tankGreen_barrel1_outline, tankGreen_barrel2, tankGreen_barrel2_outline,
		tankGreen_barrel3, tankGreen_barrel3_outline, tankRed_barrel1, tankRed_barrel1_outline, tankRed_barrel2, tankRed_barrel2_outline, tankRed_barrel3, tankRed_barrel3_outline,
		tankSand_barrel1, tankSand_barrel1_outline, tankSand_barrel2, tankSand_barrel2_outline, tankSand_barrel3, tankSand_barrel3_outline, tank_bigRed, tank_blue,
		tank_dark, tank_darkLarge, tank_green, tank_huge, tank_red, tank_sand, tileGrass1, tileGrass2,
		tileGrass_roadCornerLL, tileGrass_roadCornerLR, tileGrass_roadCornerUL, tileGrass_roadCornerUR, tileGrass_roadCrossing, tileGrass_roadCrossingRound, tileGrass_roadEast, tileGrass_roadNorth,
		tileGrass_roadSplitE, tileGrass_roadSplitN, tileGrass_roadSplitS, tileGrass_roadSplitW, tileGrass_roadTransitionE, tileGrass_roadTransitionE_dirt, tileGrass_roadTransitionN, tileGrass_roadTransitionN_dirt,
		tileGrass_roadTransitionS, tileGrass_roadTransitionS_dirt, tileGrass_roadTransitionW, tileGrass_roadTransitionW_dirt, tileGrass_transitionE, tileGrass_transitionN, tileGrass_transitionS, tileGrass_transitionW,
		tileSand1, tileSand2, tileSand_roadCornerLL, tileSand_roadCornerLR, tileSand_roadCornerUL, tileSand_roadCornerUR, tileSand_roadCrossing, tileSand_roadCrossingRound,
		tileSand_roadEast, tileSand_roadNorth, tileSand_roadSplitE, tileSand_roadSplitN, tileSand_roadSplitS, tileSand_roadSplitW, tracksDouble, tracksLarge,
		tracksSmall, treeBrown_large, treeBrown_leaf, treeBrown_small, treeBrown_twigs, treeGreen_large, treeGreen_leaf, treeGreen_small,
		treeGreen_twigs, wireCrooked, wireStraight
	};

	const static sf::IntRect sprite_rects[]; 

	const static sf::IntRect sprite_rects_hq[]; 

	sf::Texture texture;
	sf::Texture texture_hq;

	sf::Font font;


#define GET_SPRITE_HQ(NAME) (storage.sprite_rects_hq[Storage::sprite_index::NAME])


	Storage()
	{
		texture.loadFromFile("./images/allSprites_default.png");
		texture_hq.loadFromFile("./images/allSprites_retina.png");
		font.loadFromFile("./fonts/PixelSplitter-Bold.ttf");
	}

	static sf::Color get_tank_color(const Names::tank_color& color) {
		if (color == Names::tank_color::blue)
			return sf::Color(65, 159, 221);
		else if (color == Names::tank_color::green)
			return sf::Color(46, 204, 113);
		else if (color == Names::tank_color::red)
			return sf::Color(231, 76, 60);
		else if (color == Names::tank_color::sand)
			return sf::Color(245, 225, 180);
		else	//color == dark
			return sf::Color(95, 93, 85);
	}

	static sf::IntRect get_TankRect(const Names::tank_color& color) {
		if (color == Names::tank_color::blue)
			return sprite_rects_hq[Storage::sprite_index::tankBody_blue_outline];
		else if (color == Names::tank_color::green)
			return sprite_rects_hq[Storage::sprite_index::tankBody_green_outline];
		else if (color == Names::tank_color::red)
			return sprite_rects_hq[Storage::sprite_index::tankBody_red_outline];
		else if (color == Names::tank_color::sand)
			return sprite_rects_hq[Storage::sprite_index::tankBody_sand_outline];
		else	//color == dark
			return sprite_rects_hq[Storage::sprite_index::tankBody_dark_outline];
	}


	static sf::IntRect get_BarrelRect(const Names::tank_color& color, const Names::barrel_size& size) {
		if (color == Names::tank_color::blue)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::tankBlue_barrel2_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::tankBlue_barrel3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::tankBlue_barrel1_outline];
			}
		}
		else if (color == Names::tank_color::green)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::tankGreen_barrel2_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::tankGreen_barrel3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::tankGreen_barrel1_outline];
			}
		}
		else if (color == Names::tank_color::red)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::tankRed_barrel2_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::tankRed_barrel3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::tankRed_barrel1_outline];
			}
		}
		else if (color == Names::tank_color::sand)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::tankSand_barrel2_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::tankSand_barrel3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::tankSand_barrel1_outline];
			}
		}
		else	//color == dark
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::tankDark_barrel2_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::tankDark_barrel3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::tankDark_barrel1_outline];
			}
		}
	}


	static sf::IntRect get_BulletRect(const Names::tank_color& color, const Names::barrel_size& size)  {
		if (color == Names::tank_color::blue)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::bulletBlue1_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::bulletBlue3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::bulletBlue2_outline];
			}
		}
		else if (color == Names::tank_color::green)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::bulletGreen1_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::bulletGreen3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::bulletGreen2_outline];
			}
		}
		else if (color == Names::tank_color::red)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::bulletRed1_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::bulletRed3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::bulletRed2_outline];
			}
		}
		else if (color == Names::tank_color::sand)
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::bulletSand1_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::bulletSand3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::bulletSand2_outline];
			}
		}
		else	//color == dark
		{
			switch (size) {
			case Names::barrel_size::small:
				return sprite_rects_hq[Storage::sprite_index::bulletDark1_outline];
			case Names::barrel_size::medium:
				return sprite_rects_hq[Storage::sprite_index::bulletDark3_outline];
			default:	//case big
				return sprite_rects_hq[Storage::sprite_index::bulletDark2_outline];
			}
		}
	}

};