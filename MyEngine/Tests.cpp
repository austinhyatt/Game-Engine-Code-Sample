#include <iostream>
#include <cstdio>
#include <Windows.h>

#include "GameManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "TestObject.h"
#include "EventStep.h"

int EggTest() {
	//testing manager construction and run method
	GM;

	//testing LM
	LM.writeLog("testing %s! %i, %e, %c+, ect.", "flexibility", 42, 'f', 3.9265e+2);

	//testing vectors
	df::Vector v = df::Vector(2, 6);
	printf("\nvector %.f, %.f\n", v.getX(), v.getY());
	printf("vector getMagnitude:\t%.f\n", v.getMagnitude());
	v.scale(-2);
	printf("vector scale by -2:\t%.f, %.f\n", v.getX(), v.getY());
	v.normalize();
	printf("vector normalize:\t%.f, %.f\n\n", v.getX(), v.getY());

	//testing objects, objectList, and objectListIterator
	df::Object* obj1 = new df::Object();
	obj1->setPosition(df::Vector(1, 1));
	df::Object* obj2 = new df::Object();
	obj2->setPosition(df::Vector(2, 2));
	df::Object* obj3 = new df::Object();
	obj3->setPosition(df::Vector(3, 3));

	df::ObjectList objList = df::ObjectList();
	df::ObjectListIterator objItr = df::ObjectListIterator(&objList);
	objList.insert(obj1);
	objList.insert(obj2);
	objList.insert(obj3);

	for (objItr.first(); !objItr.hasNext(); objItr.next())
		printf("List object Vector:\t%.f, %.f\n",
			objItr.currentObject()->getPosition().getX(),
			objItr.currentObject()->getPosition().getY());

	printf("list removing obj2...\n");
	objList.remove(obj2);
	for (objItr.first(); !objItr.hasNext(); objItr.next())
		printf("List object Vector:\t%.f, %.f\n",
			objItr.currentObject()->getPosition().getX(),
			objItr.currentObject()->getPosition().getY());

	//testing WorldManager object list functions
	printf("\nGetting all objects from WorldManager...\n");
	df::ObjectList worldList = WM.getAllObjects();
	df::ObjectListIterator worldItr = df::ObjectListIterator(&worldList);
	printf("current world objects:\n");
	for (worldItr.first(); !worldItr.hasNext(); worldItr.next())
		printf("object with id: %i\n", worldItr.currentObject()->getId());

	printf("\nMarking first and third object for delete...\n");
	WM.markForDelete(obj1);
	WM.markForDelete(obj3);
	GM.run();
	worldList = WM.getAllObjects();
	printf("current world objects:\n");
	for (worldItr.first(); !worldItr.hasNext(); worldItr.next())
		printf("object with id: %i\n", worldItr.currentObject()->getId());

	//Testing events
	WM.shutDown();
	WM.startUp();
	df::Object* obj4 = new df::TestObject();
	df::Object* obj5 = new df::TestObject();
	worldList = WM.getAllObjects();

	printf("\nCreating StepEvent and sending to world objects...\n");
	df::Event* e = new df::EventStep(6 * 30);
	printf("EventStep value: %i\n", 6 * 30);

	for (worldItr.first(); !worldItr.hasNext(); worldItr.next())
		worldItr.currentObject()->eventHandler(e);

	//testing manager destruction
	GM.shutDown();

	return 0;
}

//gamemanager test
void df::GameManager::test(int& testCount) {
	//prints to console every second. stops after 3 seconds.
	testCount++;
	if (testCount % 30 == 0)
		printf("%d...\n", testCount / 30);

	if (testCount / 30 >= 3) {
		setGameOver();
	}
}

int helloWorld() {
	// Load font.
	sf::Font font;
	if (font.loadFromFile("df-font.ttf") == false) {
		std::cout << "Error! Unable to load font 'df-font.ttf'." << std::endl;
		return -1;
	}

	// Setup text to display.
	sf::Text text;
	text.setFont(font); // Select font.
	text.setString("Hello, world!"); // Set string to display.
	text.setCharacterSize(32); // Set character size (in pixels).
	text.setFillColor(sf::Color::Green); // Set text color.
	text.setStyle(sf::Text::Bold); // Set text style.
	text.setPosition(96, 134); // Set text position (in pixels).

	// Create window to draw on.
	sf::RenderWindow* p_window =
		new sf::RenderWindow(sf::VideoMode(400, 300), "SFML - Hello, world!");
	if (!p_window) {
		std::cout << "Error! Unable to allocate RenderWindow." << std::endl;
		return -1;
	}

	// Turn off mouse cursor for window.
	p_window->setMouseCursorVisible(false);

	// Synchronize refresh rate with monitor.
	p_window->setVerticalSyncEnabled(true);

	// Repeat forever (as long as window is open).
	while (1) {

		// Clear window and draw text.
		p_window->clear();
		p_window->draw(text);
		p_window->display();

		// See if window has been closed.
		sf::Event event;
		while (p_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				p_window->close();
				delete p_window;
				return 0;
			}
		} // End of while (event).

	} // End of while (1).
}

void TestLabels() {
	DM.drawString(df::Vector(1, 0), "Hard Body X Hard body collision:", df::Justification::LEFT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(1, 3), "Hard Body X Soft body collision:", df::Justification::LEFT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(1, 6), "Soft Body X Soft body collision (BLUE is higher altitude):", df::Justification::LEFT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(1, 9), "Hard Body X Spectral body collision:", df::Justification::LEFT_JUSTIFIED, df::Color::WHITE);

	DM.drawString(df::Vector(1, 12), "Hard Body X Hard body angled collision:", df::Justification::LEFT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(80, 15), "'W' to move up", df::Justification::RIGHT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(80, 16), "'RMB' to move right", df::Justification::RIGHT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(80, 17), "'SPACE' to increase speed right", df::Justification::RIGHT_JUSTIFIED, df::Color::WHITE);
	DM.drawString(df::Vector(80, 18), "'MMB' to add -y velocity", df::Justification::RIGHT_JUSTIFIED, df::Color::WHITE);


}

void MakeTestObjs() {
	//hard x hard
	df::Object* obj4 = new df::TestObject();
	obj4->setPosition(df::Vector(1, 1.25));
	obj4->setVelocity(df::Vector(.75, 0));
	df::Object* obj5 = new df::TestObject();
	obj5->setPosition(df::Vector(30, 1.25));
	obj5->setVelocity(df::Vector(-1, 0));
	//hard x soft
	df::Object* obj6 = new df::TestObject();
	obj6->setPosition(df::Vector(.75, 4.5));
	obj6->setVelocity(df::Vector(.3, 0));
	df::Object* obj7 = new df::TestObject();
	obj7->setSolidness(df::Solidness::SOFT);
	obj7->setPosition(df::Vector(30, 4.5));
	obj7->setVelocity(df::Vector(-.3, 0));
	//soft x soft
	df::Object* obj8 = new df::TestObject();
	obj8->setSolidness(df::Solidness::SOFT);
	obj8->setPosition(df::Vector(1, 7));
	obj8->setVelocity(df::Vector(.2, 0));
	obj8->setAltitude(df::MAX_ALTITUDE);
	df::Object* obj9 = new df::TestObject();
	obj9->setSolidness(df::Solidness::SOFT);
	obj9->setPosition(df::Vector(30, 7));
	obj9->setVelocity(df::Vector(-.2, 0));
	//soft x soft
	df::Object* obj10 = new df::TestObject();
	obj10->setSolidness(df::Solidness::SPECTRAL);
	obj10->setPosition(df::Vector(1, 10));
	obj10->setVelocity(df::Vector(.15, 0));
	df::Object* obj11 = new df::TestObject();
	obj11->setSolidness(df::Solidness::SPECTRAL);
	obj11->setPosition(df::Vector(30, 10));
	obj11->setVelocity(df::Vector(-.15, 0));
	//hard x hard angled
	//hard x hard
	df::Object* obj12 = new df::TestObject();
	obj12->setPosition(df::Vector(1, 13));
	obj12->setVelocity(df::Vector(.1, .05));
	df::Object* obj13 = new df::TestObject();
	obj13->setPosition(df::Vector(30, 13));
	obj13->setVelocity(df::Vector(-.1, .05));
}
