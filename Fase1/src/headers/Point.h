#ifndef POINT_H__
#define POINT_H__

#include <string>

using namespace std;

class Point {
	float x;
	float y;
	float z;

	public:
		Point();
		Point(float, float, float);
		float getX();
		float getY();
		float getZ();
		void setX(float);
		void setY(float);
		void setZ(float);
		string to_String();
};

#endif