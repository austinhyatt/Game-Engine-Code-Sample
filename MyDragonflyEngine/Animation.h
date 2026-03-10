#ifndef ANIMATION_H
#define ANIMATION_H

// System includes.
#include <string>

// Engine includes.
#include "Box.h"
#include "Sprite.h"

namespace df {

	class Animation {

	private:
		Sprite* sprite;    ///< Sprite associated with Animation.
		int index;           ///< Current index frame for Sprite.
		int slowdown_count;  ///< Slowdown counter (-1 means stop).
		std::string name;    ///< Sprite name in ResourceManager.

	public:
		/// Animation constructor
		Animation();

		/// Set associated Sprite to new one.
		/// Note, Sprite is managed by ResourceManager.
		/// Set Sprite index to 0 (first frame).
		void setSprite(Sprite* new_sprite);

		/// Return pointer to associated Sprite.
		Sprite* getSprite() const;

		/// Set Sprite name (in ResourceManager).
		void setName(std::string new_name);

		/// Get Sprite name (in ResourceManager).
		std::string getName() const;

		/// Set index of current Sprite frame to be displayed.
		void setIndex(int new_index);

		/// Get index of current Sprite frame to be displayed.
		int getIndex() const;

		/// Set animation slowdown count (-1 means stop animation).
		void setSlowdownCount(int new_slowdown_count);

		/// Set animation slowdown count (-1 means stop animation).
		int getSlowdownCount() const;

		/// Get bounding box of associated Sprite.
		Box getBox() const;

		/// Draw single frame centered at position (x,y).
		/// Drawing accounts for slowdown, and advances Sprite frame.
		/// Return 0 if ok, else -1.
		int draw(Vector position);
	};

}
#endif