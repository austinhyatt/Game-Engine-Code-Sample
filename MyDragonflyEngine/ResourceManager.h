#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

// System includes.
#include <string>

// Engine includes.
#include "Manager.h"
#include "Sprite.h"
#include "SpriteResourceManager.h"
#include "Music.h"
#include "Sound.h"

// Two-letter acronym for easier access to manager.
#define RM df::ResourceManager::getInstance()

namespace df {
	// Delimiters used to parse Sprite files -
	// the ResourceManager "knows" file format.
	#define HEADER_TOKEN "HEADER"
	#define BODY_TOKEN "BODY"
	#define FOOTER_TOKEN "FOOTER"
	#define FRAMES_TOKEN "frames"
	#define HEIGHT_TOKEN "height"
	#define WIDTH_TOKEN "width"
	#define COLOR_TOKEN "color"
	#define SLOWDOWN_TOKEN "slowdown"
	#define END_FRAME_TOKEN "end"
	#define VERSION_TOKEN "version"

	// Maximum number of unique assets in game.
	const int MAX_SOUNDS = 64;
	const int MAX_MUSICS = 64;

	class ResourceManager : public SpriteResourceManager {

	private:
		ResourceManager();		           // Private (a singleton).
		ResourceManager(ResourceManager const&); // Don't allow copy.
		void operator=(ResourceManager const&);  // Don't allow assignment.
		Sound sound[MAX_SOUNDS];	 // Array of sound buffers.
		int sound_count;	         // Count of number of loaded sounds.
		Music music[MAX_MUSICS];	 // Array of music buffers.
		int music_count;	         // Count of number of loaded musics.

	public:
		// Get the one and only instance of the ResourceManager.
		static ResourceManager& getInstance();

		// Get ResourceManager ready to manager for resources.
		int startUp();

		// Shut down ResourceManager, freeing up any allocated Sprites.
		void shutDown();

		// Load Sprite from file.
		// Assign indicated label to sprite.
		// Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		// Unload Sprite with indicated label.
		// Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		// Find Sprite with indicated label.
		// Return pointer to it if found, else NULL.
		Sprite* getSprite(std::string label) const;

		// Load sound from file.
        // Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		// Remove Sound with indicated label.
		// Return 0 if ok, else -1.
		int unloadSound(std::string label);

		// Find Sound with indicated label.
		// Return pointer to it if found, else NULL.
		Sound* getSound(std::string label);

		// Associate file with Music.
		// Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		// Remove label for Music with indicated label.
		// Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		// Find Music with indicated label.
		// Return pointer to it if found, else NULL.
		Music* getMusic(std::string label);
	};
}
#endif //__RESOURCE_MANAGER_H__