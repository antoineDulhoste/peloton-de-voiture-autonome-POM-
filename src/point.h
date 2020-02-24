#ifndef MY_HEADER_H
#define MY_HEADER_H
class Point
{
public:
	Point(bool drive,char* img);
  char* getImage();
  void setImage(char* img);
  bool getDrivable();
  void setDrivable(bool drive);
	~Point();

private:
	char* image;
	bool drivable;
};
#endif
