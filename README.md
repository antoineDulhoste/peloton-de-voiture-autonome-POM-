This program show a simulation of cars packing up to move together in parts of their route
They are randomly placed on points and move from a point to another by using roads that links them.
We used a simple A* algorithm to identify the route that is resumed in a array of identifiers.
Each time a car reach a point of its route, it try to match with other car by testing multiple parameters, then it determine the best car to follow as a leader.
Car will group on it a the next reached point.
When a car reach its final destination, a new one appear with randomized start and final destination point

Tested parameters are (in this order) :
    Precondition :
        Both group have the same next and second next point in common
        If a group have to speed up or down, he is still in the speed limit of the road
    
    The group with highest value of members take the lead
    The group that have less distance to get to the meeting point take the lead
    The group that is first is the group list take the lead

**KNOWN BUGS:**
Due to rounded values of double (up to 15 decimals) we had to use a error margin to avoid error. We set this at e-10.
When a new car spawn in the map, it may looks like the car superposed with an already present one without matching together in a group,
Cars can't match on their first part of route and so they will on the second part if they can.

Requirements to compile:

    For linux compilation :
        `sudo apt-get install libsdl2-dev`
        `sudo apt-get install libsdl2-image-dev`
        `sudo apt-get install libsdl2-ttf-dev`

    For windows compilation :
        `sudo apt-get install mingw-w64`

Use to compile :

  - make
  - make win (for Windows compilation)

In main.cpp:

	To change the values in the program :
		NB_VOITURE      -> number of cars
		TICK_PER_FRAME  -> speed, less is faster
		RANDOM_SEED     -> seed for car generation

	To add a point in the map:
		`points.push_back(Point(id,x,y));`

	To add a road in the map:
		`m.setRoute(point1, point2, vitesse_min, vitesse_max);`