#include "ResourceManager.h"
#include "LogManager.h"

df::ResourceManager::ResourceManager() {
	setType("resourceManager");
	sound_count = 0;
	music_count = 0;

	startUp();

	LM.writeLog("ResourceManager constructed");
}

int df::ResourceManager::startUp()
{
	return 0;
}

void df::ResourceManager::shutDown()
{
	LM.writeLog("ResourceManager destructed");
}

df::ResourceManager& df::ResourceManager::getInstance()
{
	static df::ResourceManager s_resourceManager;
	return s_resourceManager;
}

int df::ResourceManager::loadSprite(std::string filename, std::string label)
{
	return SpriteResourceManager::loadSprite(filename, label);
}

int df::ResourceManager::unloadSprite(std::string label)
{
	return SpriteResourceManager::unloadSprite(label);
}

df::Sprite* df::ResourceManager::getSprite(std::string label) const
{
	return SpriteResourceManager::getSprite(label);
}

int df::ResourceManager::loadSound(std::string filename, std::string label)
{
	if (sound_count == MAX_SOUNDS)
		return -1;
	if (sound[sound_count].loadSound(filename) == -1) {
		return -1;
	}
	sound[sound_count].setLabel(label);
	sound_count++;

	return 0;
}

int df::ResourceManager::unloadSound(std::string label)
{
	for (int i = 0; i < sound_count; i++)
	{
		if (sound[i].getLabel() == label)
		{
			for (int j = i; j < sound_count - 1; j++)
				sound[j] = sound[j + 1];
			sound_count--;
			return 0;
		}
	}
	return -1;
}

df::Sound* df::ResourceManager::getSound(std::string label)
{
	for (int i = 0; i < sound_count; i++)
		if (sound[i].getLabel() == label)
			return &(sound[i]);
	return NULL;
}

int df::ResourceManager::loadMusic(std::string filename, std::string label)
{
	if (music_count == MAX_MUSICS)
		return -1;
	if (music[music_count].loadMusic(filename) == -1)
		return -1;
	music[music_count].setLabel(label);
	music_count++;

	return 0;
}

int df::ResourceManager::unloadMusic(std::string label)
{
	for (int i = 0; i < music_count; i++)
	{
		if (music[i].getLabel() == label)
		{
			music[i].setLabel("");
			return 0;
		}
	}
	return -1;
}

df::Music* df::ResourceManager::getMusic(std::string label)
{
	for (int i = 0; i < music_count; i++)
		if (music[i].getLabel() == label)
			return &music[i];
	return NULL;
}

