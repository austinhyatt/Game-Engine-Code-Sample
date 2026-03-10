#include "DisplayManager.h"
#include "LogManager.h"
#include "Vector.h"
#include "Utility.h"

float df::charHeight(void) { return DM.getVerticalPixels() / DM.getVertical(); }
float df::charWidth(void) { return DM.getHorizontalPixels() / DM.getHorizontal(); }
df::Vector df::spacesToPixels(Vector spaces) { return Vector(spaces.getX()*charWidth(), spaces.getY()*charHeight()); }
df::Vector df::pixelsToSpaces(Vector pixels) { return Vector(pixels.getX() / charWidth(), pixels.getY() / charHeight()); }

df::DisplayManager::DisplayManager() {
	setType("displaymanager");

	window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;

	startUp();
	LM.writeLog("DisplayManager constructed");
}


int df::DisplayManager::startUp() {
	if (window != NULL)
		return 0;
	//Load font
	//Check for font file
	if (font.loadFromFile(FONT_FILE_DEFAULT) == false) {
		LM.writeLog("Error! Unable to load font 'df-font.ttf'.");
		return -1;
	}
	window = new sf::RenderWindow(
		sf::VideoMode(window_horizontal_pixels, window_vertical_pixels), WINDOW_TITLE_DEFAULT);
	if (!window) {
		printf("Error! Unable to allocate RenderWindow.");
		return -1;
	}
	// Turn off mouse cursor for window.
	window->setMouseCursorVisible(false);
	// Synchronize refresh rate with monitor.
	window->setVerticalSyncEnabled(true);

	Manager::startUp();
	return 0;
}

void df::DisplayManager::shutDown() {
	window->close();
	delete window;
	LM.writeLog("DisplayManager destructed");
}

df::DisplayManager& df::DisplayManager::getInstance() {
	static df::DisplayManager displayManager;
	return displayManager;
}

// Draw a character at window location (x,y) with color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {

	// Make sure window is allocated.
	if (window == NULL)
		return -1;

	// Convert spaces (x,y) to pixels (x,y).
	Vector pixel_pos = spacesToPixels(worldToView(world_pos));

	// Draw background rectangle since text is "see through" in SFML.
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(pixel_pos.getX() - charWidth() / 10, pixel_pos.getY() + charHeight() / 5);
	window->draw(rectangle);

	// Create character text to draw.
	static sf::Text text("", font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold); // Make bold, since looks better.

	// Scale to right size.
	if (charWidth() < charHeight())
		text.setCharacterSize(charWidth() * 2);
	else
		text.setCharacterSize(charHeight() * 2);

	// Set SFML color based on Dragonfly color.
	switch (color) {
	case BLACK:
		text.setFillColor(sf::Color::Black);
		break;
	case RED:
		text.setFillColor(sf::Color::Red);
		break;
	case GREEN:
		text.setFillColor(sf::Color::Green);
		break;
	case YELLOW:
		text.setFillColor(sf::Color::Yellow);
		break;
	case BLUE:
		text.setFillColor(sf::Color::Blue);
		break;
	case MAGENTA:
		text.setFillColor(sf::Color::Magenta);
		break;
	case CYAN:
		text.setFillColor(sf::Color::Cyan);
		break;
	case WHITE:
		text.setFillColor(sf::Color::White);
		break;
	}

	// Set position in window (in pixels).
	text.setPosition(pixel_pos.getX(), pixel_pos.getY());

	// Draw character.
	window->draw(text);
}

int df::DisplayManager::drawString(df::Vector pos, std::string str, df::Justification just, df::Color color) const {
	// Get starting position.
	Vector starting_pos = pos;
	switch (just) {
	case CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size() / 2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
	default:
		break;
	}

	// Draw string character by character.
	for (int i = 0; i < str.size(); i++)
		drawCh(Vector(starting_pos.getX() + i, starting_pos.getY()), str[i], color);

	return 0;
}

int df::DisplayManager::swapBuffers()
{
	if (window == NULL)
		return -1;
	//display changes since last refresh
	window->display();
	//clear other window and get ready for next draw
	window->clear();

	return 0;
}

int df::DisplayManager::getHorizontalPixels() const { return window_horizontal_pixels; }

int df::DisplayManager::getVerticalPixels() const { return window_vertical_pixels; }

int df::DisplayManager::getHorizontal() const { return window_horizontal_chars; }

int df::DisplayManager::getVertical() const { return window_vertical_chars; }

sf::RenderWindow* df::DisplayManager::getWindow() const { return window; }
