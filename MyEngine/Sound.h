#ifndef SOUND_H
#define SOUND_H

// System includes.
#include <string>
#include <SFML/Audio.hpp>

namespace df {

	class Sound {

	private:
		sf::Sound sound;	          // SFML sound.
		sf::SoundBuffer sound_buffer; // SFML sound buffer associated with sound.
		std::string label;	          // Text label to identify sound.

	public:

		// Constructor.
		Sound();

		// Destructor.
		~Sound();

		// Load sound buffer from file.
		// Return 0 if ok, else -1.
		int loadSound(std::string filename);

		// Set label associated with sound.
		void setLabel(std::string new_label);

		// Get label associated with sound.
		std::string getLabel() const;

		// Play sound.
		// If loop is true, repeat play when done.
		void play(bool loop = false);

		// Stop sound.
		void stop();

		// Pause sound.
		void pause();

		// Return SFML sound.
		sf::Sound getSound() const;
	};

}
#endif