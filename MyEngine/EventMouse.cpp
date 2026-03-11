#include "EventMouse.h"

df::EventMouse::EventMouse()
{
	setType(MSE_EVENT);
	mouse_action = EventMouseAction::UNDEFINED_MOUSE_ACTION;
	mouse_button = Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	mouse_xy = Vector();
}

void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action) { mouse_action = new_mouse_action; }

df::EventMouseAction df::EventMouse::getMouseAction() const { return mouse_action; }

void df::EventMouse::setMouseButton(Mouse::Button new_mouse_button) { mouse_button = new_mouse_button; }

df::Mouse::Button df::EventMouse::getMouseButton() const {return mouse_button;}

void df::EventMouse::setMousePosition(Vector new_mouse_xy) { mouse_xy = new_mouse_xy; }

df::Vector df::EventMouse::getMousePosition() const { return mouse_xy; }

df::Mouse::Button df::EventMouse::convertFromSfMouse(sf::Mouse::Button mb)
{
	switch (mb) {
	case sf::Mouse::Button::Left:
		return Mouse::Button::LEFT;
	case sf::Mouse::Button::Right:
		return Mouse::Button::RIGHT;
	case sf::Mouse::Button::Middle:
		return Mouse::Button::MIDDLE;
	default:
		return Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	}
}
