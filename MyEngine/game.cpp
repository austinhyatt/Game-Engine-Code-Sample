#include <iostream>
#include <cstdio>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>

#include "GameManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "TestObject.h"
#include "EventStep.h"
#include "Vector.h"
#include "ResourceManager.h"
#include "Rail.h";
#include "Hero.h"
#include "GameStart.h"
#include "HighScore.h"

int main(int argc, char* argv[]) {
	GM;

	RM.loadSprite("sprites/rail_sprite.txt", "railsprite");
	RM.loadSprite("sprites/wall_sprite.txt", "wallsprite");
	RM.loadSprite("sprites/star_sprite.txt", "starsprite");
	RM.loadSprite("sprites/hero-right-spr.txt", "heror");
	RM.loadSprite("sprites/hero-left-spr.txt", "herol");
	RM.loadSprite("sprites/hero-explode.txt", "heroexplode");
	RM.loadSprite("sprites/main-menu-spr.txt", "gamestart");
	RM.loadSprite("sprites/game-over-spr.txt", "gameover");
	RM.loadSprite("sprites/border-spr.txt", "border");
	RM.loadMusic("sounds/game-music.wav", "gamemusic");
	RM.loadSound("sounds/damage.wav", "damage");
	RM.loadSound("sounds/explosion.wav", "explosion");

	//HS.writeScore(0);

	GameStart* menu = new GameStart();

	GM.run();

	GM.shutDown();

	return 0;
}