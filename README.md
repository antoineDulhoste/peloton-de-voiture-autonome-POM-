Requirements to compile:

    For linux compilation :
        sudo apt-get install libsdl2-dev
        sudo apt-get install libsdl2-image-dev
        sudo apt-get install libsdl2-ttf-dev

    For windows compilation :
        sudo apt-get install mingw-w64

Use to compile :

  - make
  - make win (for Windows compilation)

In main.cpp:

	To change the number of car :
		NB_VOITURE

	To add a point in the map:
			points.push_back(Point(id,x,y));

	To add a road in the map:
			m.setRoute(point1, point2, vitesse_min, vitesse_max);