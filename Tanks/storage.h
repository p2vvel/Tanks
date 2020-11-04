#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


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

	sf::IntRect sprite_rects[187] = {
		sf::IntRect(513, 407, 20, 28), sf::IntRect(507, 515, 24, 24), sf::IntRect(513, 319, 20, 28), sf::IntRect(507, 443, 24, 24), sf::IntRect(414, 371, 20, 28), sf::IntRect(507, 491, 24, 24), sf::IntRect(512, 40, 20, 28), sf::IntRect(507, 467, 24, 24),
		sf::IntRect(479, 499, 28, 28), sf::IntRect(479, 527, 28, 28), sf::IntRect(356, 555, 4, 10), sf::IntRect(544, 26, 8, 14), sf::IntRect(532, 48, 8, 12), sf::IntRect(438, 455, 12, 16), sf::IntRect(500, 130, 4, 14), sf::IntRect(513, 202, 8, 18),
		sf::IntRect(386, 393, 4, 10), sf::IntRect(462, 455, 8, 14), sf::IntRect(470, 455, 8, 12), sf::IntRect(196, 544, 12, 16), sf::IntRect(435, 231, 4, 14), sf::IntRect(531, 517, 8, 18), sf::IntRect(435, 245, 4, 10), sf::IntRect(532, 160, 8, 14),
		sf::IntRect(521, 202, 8, 12), sf::IntRect(172, 544, 12, 16), sf::IntRect(471, 283, 4, 14), sf::IntRect(492, 130, 8, 18), sf::IntRect(382, 393, 4, 10), sf::IntRect(344, 551, 8, 14), sf::IntRect(336, 551, 8, 12), sf::IntRect(184, 544, 12, 16),
		sf::IntRect(206, 528, 4, 14), sf::IntRect(484, 130, 8, 18), sf::IntRect(352, 555, 4, 10), sf::IntRect(320, 551, 8, 14), sf::IntRect(312, 551, 8, 12), sf::IntRect(450, 455, 12, 16), sf::IntRect(471, 297, 4, 14), sf::IntRect(476, 130, 8, 18),
		sf::IntRect(479, 471, 28, 28), sf::IntRect(479, 443, 28, 28), sf::IntRect(480, 221, 28, 28), sf::IntRect(480, 249, 28, 28), sf::IntRect(320, 403, 60, 60), sf::IntRect(380, 471, 57, 56), sf::IntRect(0, 128, 64, 63), sf::IntRect(430, 104, 46, 45),
		sf::IntRect(53, 512, 53, 52), sf::IntRect(320, 463, 60, 60), sf::IntRect(382, 255, 57, 56), sf::IntRect(320, 192, 63, 63), sf::IntRect(384, 104, 46, 45), sf::IntRect(0, 512, 53, 52), sf::IntRect(158, 528, 48, 16), sf::IntRect(158, 512, 52, 16),
		sf::IntRect(262, 512, 50, 50), sf::IntRect(158, 544, 14, 14), sf::IntRect(382, 371, 32, 22), sf::IntRect(354, 527, 42, 28), sf::IntRect(439, 283, 32, 22), sf::IntRect(312, 523, 42, 28), sf::IntRect(507, 539, 20, 25), sf::IntRect(514, 289, 16, 28),
		sf::IntRect(508, 221, 21, 38), sf::IntRect(546, 160, 8, 26), sf::IntRect(530, 0, 14, 22), sf::IntRect(527, 539, 18, 26), sf::IntRect(544, 108, 12, 24), sf::IntRect(513, 174, 16, 28), sf::IntRect(544, 132, 10, 28), sf::IntRect(530, 244, 14, 32),
		sf::IntRect(544, 244, 10, 32), sf::IntRect(530, 276, 14, 36), sf::IntRect(531, 435, 12, 26), sf::IntRect(514, 98, 16, 30), sf::IntRect(544, 276, 8, 26), sf::IntRect(533, 312, 12, 30), sf::IntRect(544, 0, 8, 26), sf::IntRect(530, 68, 12, 30),
		sf::IntRect(531, 461, 12, 26), sf::IntRect(514, 259, 16, 30), sf::IntRect(545, 302, 8, 26), sf::IntRect(542, 48, 12, 30), sf::IntRect(545, 519, 8, 26), sf::IntRect(543, 459, 12, 30), sf::IntRect(384, 56, 48, 48), sf::IntRect(106, 512, 52, 52),
		sf::IntRect(396, 527, 38, 38), sf::IntRect(426, 149, 42, 42), sf::IntRect(468, 149, 38, 36), sf::IntRect(384, 0, 48, 56), sf::IntRect(382, 311, 52, 60), sf::IntRect(384, 149, 42, 40), sf::IntRect(476, 283, 38, 36), sf::IntRect(435, 191, 42, 40),
		sf::IntRect(380, 403, 58, 68), sf::IntRect(320, 331, 62, 72), sf::IntRect(479, 407, 34, 36), sf::IntRect(476, 0, 38, 40), sf::IntRect(476, 94, 38, 36), sf::IntRect(437, 517, 42, 40), sf::IntRect(543, 342, 12, 26), sf::IntRect(514, 68, 16, 30),
		sf::IntRect(545, 398, 8, 26), sf::IntRect(531, 373, 12, 30), sf::IntRect(553, 519, 8, 26), sf::IntRect(543, 429, 12, 30), sf::IntRect(533, 403, 12, 26), sf::IntRect(515, 377, 16, 30), sf::IntRect(553, 398, 8, 26), sf::IntRect(530, 98, 12, 30),
		sf::IntRect(552, 276, 8, 26), sf::IntRect(531, 487, 12, 30), sf::IntRect(531, 347, 12, 26), sf::IntRect(514, 0, 16, 30), sf::IntRect(546, 212, 8, 26), sf::IntRect(543, 368, 12, 30), sf::IntRect(553, 302, 8, 26), sf::IntRect(532, 128, 12, 30),
		sf::IntRect(532, 22, 12, 26), sf::IntRect(515, 347, 16, 30), sf::IntRect(546, 186, 8, 26), sf::IntRect(542, 78, 12, 30), sf::IntRect(552, 0, 8, 26), sf::IntRect(543, 489, 12, 30), sf::IntRect(210, 512, 52, 52), sf::IntRect(432, 48, 42, 46),
		sf::IntRect(434, 311, 42, 46), sf::IntRect(383, 192, 52, 60), sf::IntRect(434, 357, 42, 46), sf::IntRect(320, 255, 62, 76), sf::IntRect(474, 48, 38, 46), sf::IntRect(437, 471, 42, 46), sf::IntRect(192, 384, 64, 64), sf::IntRect(192, 320, 64, 64),
		sf::IntRect(64, 320, 64, 64), sf::IntRect(64, 384, 64, 64), sf::IntRect(0, 64, 64, 64), sf::IntRect(192, 256, 64, 64), sf::IntRect(0, 319, 64, 64), sf::IntRect(64, 0, 64, 64), sf::IntRect(64, 128, 64, 64), sf::IntRect(192, 192, 64, 64),
		sf::IntRect(192, 64, 64, 64), sf::IntRect(192, 128, 64, 64), sf::IntRect(64, 64, 64, 64), sf::IntRect(64, 256, 64, 64), sf::IntRect(192, 0, 64, 64), sf::IntRect(320, 64, 64, 64), sf::IntRect(320, 0, 64, 64), sf::IntRect(256, 448, 64, 64),
		sf::IntRect(256, 384, 64, 64), sf::IntRect(256, 320, 64, 64), sf::IntRect(256, 256, 64, 64), sf::IntRect(256, 192, 64, 64), sf::IntRect(256, 128, 64, 64), sf::IntRect(256, 64, 64, 64), sf::IntRect(256, 0, 64, 64), sf::IntRect(192, 448, 64, 64),
		sf::IntRect(128, 0, 64, 64), sf::IntRect(64, 448, 64, 64), sf::IntRect(0, 255, 64, 64), sf::IntRect(0, 191, 64, 64), sf::IntRect(0, 0, 64, 64), sf::IntRect(0, 383, 64, 64), sf::IntRect(320, 128, 64, 64), sf::IntRect(128, 448, 64, 64),
		sf::IntRect(128, 384, 64, 64), sf::IntRect(128, 320, 64, 64), sf::IntRect(128, 256, 64, 64), sf::IntRect(128, 192, 64, 64), sf::IntRect(128, 128, 64, 64), sf::IntRect(128, 64, 64, 64), sf::IntRect(438, 403, 41, 52), sf::IntRect(439, 231, 41, 52),
		sf::IntRect(476, 319, 37, 52), sf::IntRect(64, 192, 64, 64), sf::IntRect(312, 512, 8, 10), sf::IntRect(479, 371, 36, 36), sf::IntRect(506, 130, 26, 22), sf::IntRect(0, 447, 64, 64), sf::IntRect(328, 555, 8, 10), sf::IntRect(477, 185, 36, 36),
		sf::IntRect(506, 152, 26, 22), sf::IntRect(432, 0, 44, 48), sf::IntRect(529, 174, 17, 70) };

	sf::IntRect sprite_rects_hq[187] = {
		sf::IntRect(1016, 510, 40, 56), sf::IntRect(1014, 1032, 48, 48), sf::IntRect(1024, 0, 40, 56), sf::IntRect(1012, 809, 48, 48), sf::IntRect(828, 740, 40, 56), sf::IntRect(1014, 984, 48, 48), sf::IntRect(1016, 753, 40, 56), sf::IntRect(1014, 936, 48, 48),
		sf::IntRect(958, 936, 56, 56), sf::IntRect(958, 1048, 56, 56), sf::IntRect(1006, 1104, 8, 20), sf::IntRect(1106, 1069, 16, 28), sf::IntRect(990, 1104, 16, 24), sf::IntRect(1026, 705, 24, 32), sf::IntRect(870, 465, 8, 28), sf::IntRect(1107, 240, 16, 36),
		sf::IntRect(228, 1024, 8, 20), sf::IntRect(1106, 1097, 16, 28), sf::IntRect(974, 1104, 16, 24), sf::IntRect(1085, 654, 24, 32), sf::IntRect(1024, 158, 8, 28), sf::IntRect(1106, 492, 16, 36), sf::IntRect(308, 1104, 8, 20), sf::IntRect(1106, 412, 16, 28),
		sf::IntRect(684, 1099, 16, 24), sf::IntRect(1066, 1069, 24, 32), sf::IntRect(700, 1099, 8, 28), sf::IntRect(1105, 204, 16, 36), sf::IntRect(236, 1024, 8, 20), sf::IntRect(668, 1099, 16, 28), sf::IntRect(958, 1104, 16, 24), sf::IntRect(1061, 654, 24, 32),
		sf::IntRect(308, 1076, 8, 28), sf::IntRect(1064, 60, 16, 36), sf::IntRect(212, 1108, 8, 20), sf::IntRect(652, 1099, 16, 28), sf::IntRect(1090, 518, 16, 24), sf::IntRect(1084, 120, 24, 32), sf::IntRect(952, 753, 8, 28), sf::IntRect(930, 569, 16, 36),
		sf::IntRect(958, 992, 56, 56), sf::IntRect(960, 434, 56, 56), sf::IntRect(960, 753, 56, 56), sf::IntRect(960, 490, 56, 56), sf::IntRect(640, 804, 120, 120), sf::IntRect(764, 508, 114, 112), sf::IntRect(640, 256, 127, 126), sf::IntRect(860, 96, 92, 90),
		sf::IntRect(0, 1024, 106, 104), sf::IntRect(640, 924, 120, 120), sf::IntRect(760, 940, 114, 112), sf::IntRect(640, 382, 126, 126), sf::IntRect(768, 96, 92, 90), sf::IntRect(106, 1024, 106, 104), sf::IntRect(212, 1076, 96, 32), sf::IntRect(212, 1044, 104, 32),
		sf::IntRect(524, 1024, 100, 100), sf::IntRect(624, 1099, 28, 28), sf::IntRect(768, 186, 64, 44), sf::IntRect(624, 1044, 84, 55), sf::IntRect(764, 740, 64, 44), sf::IntRect(708, 1052, 84, 55), sf::IntRect(1024, 56, 40, 50), sf::IntRect(1033, 214, 32, 56),
		sf::IntRect(1016, 434, 42, 76), sf::IntRect(1106, 440, 16, 52), sf::IntRect(1014, 1080, 28, 44), sf::IntRect(1024, 106, 36, 52), sf::IntRect(1042, 1080, 24, 48), sf::IntRect(1033, 158, 32, 56), sf::IntRect(1088, 0, 20, 56), sf::IntRect(832, 186, 28, 64),
		sf::IntRect(1088, 746, 20, 64), sf::IntRect(1060, 765, 28, 72), sf::IntRect(1060, 106, 24, 52), sf::IntRect(1058, 362, 32, 60), sf::IntRect(1089, 152, 16, 52), sf::IntRect(1062, 897, 24, 60), sf::IntRect(1106, 360, 16, 52), sf::IntRect(1062, 1009, 24, 60),
		sf::IntRect(1086, 957, 24, 52), sf::IntRect(1058, 422, 32, 60), sf::IntRect(1090, 1069, 16, 52), sf::IntRect(1060, 837, 24, 60), sf::IntRect(1090, 466, 16, 52), sf::IntRect(1061, 542, 24, 60), sf::IntRect(768, 0, 96, 96), sf::IntRect(420, 1024, 104, 104),
		sf::IntRect(792, 1052, 76, 76), sf::IntRect(868, 620, 84, 84), sf::IntRect(876, 864, 76, 72), sf::IntRect(767, 256, 96, 112), sf::IntRect(764, 620, 104, 120), sf::IntRect(868, 704, 84, 80), sf::IntRect(947, 290, 76, 72), sf::IntRect(874, 1032, 84, 80),
		sf::IntRect(760, 804, 116, 136), sf::IntRect(640, 660, 124, 144), sf::IntRect(1023, 290, 68, 72), sf::IntRect(952, 569, 76, 80), sf::IntRect(952, 864, 76, 72), sf::IntRect(876, 784, 84, 80), sf::IntRect(1085, 602, 24, 52), sf::IntRect(1056, 705, 32, 60),
		sf::IntRect(1091, 308, 16, 52), sf::IntRect(1084, 837, 24, 60), sf::IntRect(1107, 276, 16, 52), sf::IntRect(1065, 210, 24, 60), sf::IntRect(1062, 957, 24, 52), sf::IntRect(1028, 857, 32, 60), sf::IntRect(1108, 746, 16, 52), sf::IntRect(1086, 897, 24, 60),
		sf::IntRect(1089, 204, 16, 52), sf::IntRect(1086, 1009, 24, 60), sf::IntRect(1061, 602, 24, 52), sf::IntRect(1026, 362, 32, 60), sf::IntRect(1090, 414, 16, 52), sf::IntRect(1085, 542, 24, 60), sf::IntRect(1090, 362, 16, 52), sf::IntRect(1088, 686, 24, 60),
		sf::IntRect(1065, 158, 24, 52), sf::IntRect(1058, 482, 32, 60), sf::IntRect(1105, 152, 16, 52), sf::IntRect(1064, 0, 24, 60), sf::IntRect(1091, 256, 16, 52), sf::IntRect(1084, 60, 24, 60), sf::IntRect(316, 1024, 104, 104), sf::IntRect(874, 940, 84, 92),
		sf::IntRect(870, 373, 84, 92), sf::IntRect(766, 382, 104, 120), sf::IntRect(864, 0, 84, 92), sf::IntRect(640, 508, 124, 152), sf::IntRect(948, 0, 76, 92), sf::IntRect(863, 281, 84, 92), sf::IntRect(384, 896, 128, 128), sf::IntRect(384, 256, 128, 128),
		sf::IntRect(0, 512, 128, 128), sf::IntRect(0, 640, 128, 128), sf::IntRect(128, 256, 128, 128), sf::IntRect(128, 384, 128, 128), sf::IntRect(128, 640, 128, 128), sf::IntRect(384, 512, 128, 128), sf::IntRect(0, 768, 128, 128), sf::IntRect(128, 896, 128, 128),
		sf::IntRect(128, 768, 128, 128), sf::IntRect(384, 384, 128, 128), sf::IntRect(384, 768, 128, 128), sf::IntRect(512, 512, 128, 128), sf::IntRect(512, 640, 128, 128), sf::IntRect(512, 768, 128, 128), sf::IntRect(512, 384, 128, 128), sf::IntRect(640, 0, 128, 128),
		sf::IntRect(512, 896, 128, 128), sf::IntRect(0, 0, 128, 128), sf::IntRect(0, 256, 128, 128), sf::IntRect(0, 128, 128, 128), sf::IntRect(640, 128, 128, 128), sf::IntRect(512, 256, 128, 128), sf::IntRect(512, 128, 128, 128), sf::IntRect(512, 0, 128, 128),
		sf::IntRect(256, 128, 128, 128), sf::IntRect(256, 0, 128, 128), sf::IntRect(384, 640, 128, 128), sf::IntRect(0, 896, 128, 128), sf::IntRect(128, 128, 128, 128), sf::IntRect(0, 384, 128, 128), sf::IntRect(384, 128, 128, 128), sf::IntRect(384, 0, 128, 128),
		sf::IntRect(256, 896, 128, 128), sf::IntRect(256, 768, 128, 128), sf::IntRect(256, 640, 128, 128), sf::IntRect(256, 512, 128, 128), sf::IntRect(256, 384, 128, 128), sf::IntRect(256, 256, 128, 128), sf::IntRect(951, 186, 82, 104), sf::IntRect(878, 465, 82, 104),
		sf::IntRect(952, 649, 74, 104), sf::IntRect(128, 512, 128, 128), sf::IntRect(212, 1024, 16, 20), sf::IntRect(952, 92, 72, 72), sf::IntRect(878, 569, 52, 44), sf::IntRect(128, 0, 128, 128), sf::IntRect(624, 1024, 16, 20), sf::IntRect(954, 362, 72, 72),
		sf::IntRect(960, 809, 52, 44), sf::IntRect(863, 186, 88, 95), sf::IntRect(1028, 566, 33, 139)
	};

	sf::Texture texture;
	sf::Texture texture_hq;




	Storage()
	{
		texture.loadFromFile("./images/allSprites_default.png");
		texture_hq.loadFromFile("./images/allSprites_retina.png");
	}

};