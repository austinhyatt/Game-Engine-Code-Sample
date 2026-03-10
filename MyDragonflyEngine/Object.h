#ifndef OBJECT_H
#define OBJECT_H

// System includes.
#include <string>

// Engine includes.
#include "Vector.h"
#include "Event.h"
#include "DisplayManager.h"
#include "Animation.h"
#include "Box.h"

namespace df {

	// Types of solidness of Object.
	enum Solidness {
		HARD,       // Object causes collisions and impedes.
		SOFT,       // Object causes collision, but doesn't impede.
		SPECTRAL,   // Object doesn't cause collisions.
	};

	class Object {

	private:
		int id;		        // Unique game engine defined identifier.
		std::string type;	        // Game-programmer defined identification.
		Vector position;            // Position in game world.
		Vector direction;	        // Direction vector.
		float speed;                // Object speed in direction.
		int altitude;               // 0 to MAX_ALTITUDE (higher drawn on top).
		Solidness solidness;        // Solidness state of Object.
		Animation animation;        // Animation associated with Object.
		Box box;                    // Box for sprite boundary & collisions.

	public:
		// Construct Object. 
		// Set default parameters and add to game world (WorldManager).
		Object();

		// Destroy object, removing itself from game world (WorldManager).
		virtual ~Object();

		// Set Object id.
		void setId(int new_id);

		// Get Object id.
		int getId() const;

		// Set type identifier of Object.
		void setType(std::string new_type);

		// Get type identifier of Object.
		std::string getType() const;

		// Set position of Object.
		virtual void setPosition(Vector new_position);

		// Get position of Object.
		Vector getPosition() const;

		// Handle event.
		// Base class ignores everything.
		// Return 0 if ignored, else 1.
		virtual int eventHandler(const Event* p_event);

		// Set speed of Object.
		void setSpeed(float new_speed);

		// Get speed of Object.
		float getSpeed() const;

		// Set direction of Object.
		void setDirection(Vector new_direction);

		// Get direction of Object.
		Vector getDirection() const;

		// Set direction and speed of Object.
		void setVelocity(Vector new_velocity);

		// Get velocity of Object based on direction and speed.
		Vector getVelocity() const;

		// Predict Object position based on speed and direction.
		// Return predicted position.
		Vector predictPosition();
		
		// Return altitude of Object.
		int getAltitude() const;

		// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
		// Return 0 if ok, else -1.
		int setAltitude(int new_altitude);

		// Return True if Object is HARD or SOFT, else false.
		bool isSolid() const;

		// Set solidness of Object, with checks for consistency.  
		// Return 0 if ok, else -1.
		void setSolidness(Solidness new_solid);

		// Return solidness of Object.
		Solidness getSolidness() const;

		// Set Sprite for this Object to animate.
		// Return 0 if ok, else -1.
		int setSprite(std::string sprite_label);

		// Set Animation for this Object to new one.
		// Set bounding box to size of associated Sprite.
		void setAnimation(Animation new_animation);

		// Get Animation for this Object.
		Animation getAnimation() const;

		// Draw Object Animation.
		virtual int draw();

		// Set bounding box of Object.
		void setBox(Box new_box);

		// Get bounding box of Object.
		Box getBox() const;
	};

}
#endif
