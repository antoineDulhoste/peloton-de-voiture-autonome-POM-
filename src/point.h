#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <string>

class Point
{
public:
	Point(int x, int y, std::string img);
  std::string getImage();
  void setImage(std::string img);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	Point getDestination(int index);
	~Point();

private:
	int x;
	int y;
	std::string image;
	Point* destinations;
};
#endif
