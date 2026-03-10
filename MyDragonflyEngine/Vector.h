#ifndef DF_VECTOR_H
#define DF_VECTOR_H

namespace df {

	class Vector {

	private:
		float x; 			//< Horizontal component.
		float y; 			//< Vertical component.

	public:
		// Default is (0,0).
		Vector();

		// Create Vector with (x,y).  
		Vector(float init_x, float init_y);

		void setX(float new_x);	        // Set horizontal component.
		float getX() const;		        // Get horizontal component.
		void setY(float new_y);	        // Set vertical component.
		float getY() const;		        // Get vertical component.
		void setXY(float new_x, float new_y); // Set horizizontal & vertical.
		void normalize();			// Normalize vector.
		void scale(float s);			// Scale vector.
		float getMagnitude() const;		// Return magnitude.
		Vector operator+(const Vector& other) const; // Add Vector.
		Vector operator-(const Vector& other) const; // Subtract Vector.
		bool operator==(const Vector& other) const; // Equals Vector.
	};

} // end of namespace df
#endif