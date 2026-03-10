#include "InputManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "DisplayManager.h"
#include "LogManager.h"


df::InputManager::InputManager() {
	setType("InputManager");
}

int df::InputManager::startUp() {
	if (!DM.isStarted()) {
		LM.writeLog("df::InputManager::startUp(): Display Manager not started!");
		return -1;
	}

	sf::RenderWindow* window = DM.getWindow();
	window->setKeyRepeatEnabled(false);

	Manager::startUp();
	LM.writeLog("Input Manager started!");
	return 0;
}

df::InputManager& df::InputManager::getInstance() {
	static InputManager input_manager = InputManager();
	return input_manager;
}

void df::InputManager::shutDown() {
	sf::RenderWindow* window = DM.getWindow();
	window->setKeyRepeatEnabled(true);
	LM.writeLog("Input Manager Shutting Down");
	Manager::shutDown();
}

void df::InputManager::getInput() {

	EventKeyboard ek = EventKeyboard();
	EventMouse em = EventMouse();

	// Check past window events.
	sf::Event event;
	while (DM.getWindow()->pollEvent(event)) {
		Vector mouse_pos;
		switch (event.type) {
		case sf::Event::Closed:
			GM.setGameOver();
			return;
		case sf::Event::KeyPressed:
			ek.setKeyboardAction(df::EventKeyboardAction::KEY_PRESSED);
			switch (event.key.code) {
			case sf::Keyboard::Space:
				ek.setKey(df::Keyboard::SPACE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Return:
				ek.setKey(df::Keyboard::RETURN);
				onEvent(&ek);
				break;
			case sf::Keyboard::Escape:
				ek.setKey(df::Keyboard::ESCAPE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Tab:
				ek.setKey(df::Keyboard::TAB);
				onEvent(&ek);
				break;
			case sf::Keyboard::Left:
				ek.setKey(df::Keyboard::LEFTARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Right:
				ek.setKey(df::Keyboard::RIGHTARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Up:
				ek.setKey(df::Keyboard::UPARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Down:
				ek.setKey(df::Keyboard::DOWNARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Pause:
				ek.setKey(df::Keyboard::PAUSE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Subtract:
				ek.setKey(df::Keyboard::MINUS);
				onEvent(&ek);
				break;
			case sf::Keyboard::Add:
				ek.setKey(df::Keyboard::PLUS);
				onEvent(&ek);
				break;
			case sf::Keyboard::Tilde:
				ek.setKey(df::Keyboard::TILDE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Period:
				ek.setKey(df::Keyboard::PERIOD);
				onEvent(&ek);
				break;
			case sf::Keyboard::Comma:
				ek.setKey(df::Keyboard::COMMA);
				onEvent(&ek);
				break;
			case sf::Keyboard::Slash:
				ek.setKey(df::Keyboard::SLASH);
				onEvent(&ek);
				break;
			case sf::Keyboard::LControl:
				ek.setKey(df::Keyboard::LEFTCONTROL);
				onEvent(&ek);
				break;
			case sf::Keyboard::RControl:
				ek.setKey(df::Keyboard::RIGHTCONTROL);
				onEvent(&ek);
				break;
			case sf::Keyboard::LShift:
				ek.setKey(df::Keyboard::LEFTSHIFT);
				onEvent(&ek);
				break;
			case sf::Keyboard::RShift:
				ek.setKey(df::Keyboard::RIGHTSHIFT);
				onEvent(&ek);
				break;
			case sf::Keyboard::F1:
				ek.setKey(df::Keyboard::F1);
				onEvent(&ek);
				break;
			case sf::Keyboard::F2:
				ek.setKey(df::Keyboard::F2);
				onEvent(&ek);
				break;
			case sf::Keyboard::F3:
				ek.setKey(df::Keyboard::F3);
				onEvent(&ek);
				break;
			case sf::Keyboard::F4:
				ek.setKey(df::Keyboard::F4);
				onEvent(&ek);
				break;
			case sf::Keyboard::F5:
				ek.setKey(df::Keyboard::F5);
				onEvent(&ek);
				break;
			case sf::Keyboard::F6:
				ek.setKey(df::Keyboard::F6);
				onEvent(&ek);
				break;
			case sf::Keyboard::F7:
				ek.setKey(df::Keyboard::F7);
				onEvent(&ek);
				break;
			case sf::Keyboard::F8:
				ek.setKey(df::Keyboard::F8);
				onEvent(&ek);
				break;
			case sf::Keyboard::F9:
				ek.setKey(df::Keyboard::F9);
				onEvent(&ek);
				break;
			case sf::Keyboard::F10:
				ek.setKey(df::Keyboard::F10);
				onEvent(&ek);
				break;
			case sf::Keyboard::F11:
				ek.setKey(df::Keyboard::F11);
				onEvent(&ek);
				break;
			case sf::Keyboard::F12:
				ek.setKey(df::Keyboard::F12);
				onEvent(&ek);
				break;
			case sf::Keyboard::A:
				ek.setKey(df::Keyboard::A);
				onEvent(&ek);
				break;
			case sf::Keyboard::B:
				ek.setKey(df::Keyboard::B);
				onEvent(&ek);
				break;
			case sf::Keyboard::C:
				ek.setKey(df::Keyboard::C);
				onEvent(&ek);
				break;
			case sf::Keyboard::D:
				ek.setKey(df::Keyboard::D);
				onEvent(&ek);
				break;
			case sf::Keyboard::E:
				ek.setKey(df::Keyboard::E);
				onEvent(&ek);
				break;
			case sf::Keyboard::F:
				ek.setKey(df::Keyboard::F);
				onEvent(&ek);
				break;
			case sf::Keyboard::G:
				ek.setKey(df::Keyboard::G);
				onEvent(&ek);
				break;
			case sf::Keyboard::H:
				ek.setKey(df::Keyboard::H);
				onEvent(&ek);
				break;
			case sf::Keyboard::I:
				ek.setKey(df::Keyboard::I);
				onEvent(&ek);
				break;
			case sf::Keyboard::J:
				ek.setKey(df::Keyboard::J);
				onEvent(&ek);
				break;
			case sf::Keyboard::K:
				ek.setKey(df::Keyboard::K);
				onEvent(&ek);
				break;
			case sf::Keyboard::L:
				ek.setKey(df::Keyboard::L);
				onEvent(&ek);
				break;
			case sf::Keyboard::M:
				ek.setKey(df::Keyboard::M);
				onEvent(&ek);
				break;
			case sf::Keyboard::N:
				ek.setKey(df::Keyboard::N);
				onEvent(&ek);
				break;
			case sf::Keyboard::O:
				ek.setKey(df::Keyboard::O);
				onEvent(&ek);
				break;
			case sf::Keyboard::P:
				ek.setKey(df::Keyboard::P);
				onEvent(&ek);
				break;
			case sf::Keyboard::Q:
				ek.setKey(df::Keyboard::Q);
				onEvent(&ek);
				break;
			case sf::Keyboard::R:
				ek.setKey(df::Keyboard::R);
				onEvent(&ek);
				break;
			case sf::Keyboard::S:
				ek.setKey(df::Keyboard::S);
				onEvent(&ek);
				break;
			case sf::Keyboard::T:
				ek.setKey(df::Keyboard::T);
				onEvent(&ek);
				break;
			case sf::Keyboard::U:
				ek.setKey(df::Keyboard::U);
				onEvent(&ek);
				break;
			case sf::Keyboard::V:
				ek.setKey(df::Keyboard::V);
				onEvent(&ek);
				break;
			case sf::Keyboard::W:
				ek.setKey(df::Keyboard::W);
				onEvent(&ek);
				break;
			case sf::Keyboard::X:
				ek.setKey(df::Keyboard::X);
				onEvent(&ek);
				break;
			case sf::Keyboard::Y:
				ek.setKey(df::Keyboard::Y);
				onEvent(&ek);
				break;
			case sf::Keyboard::Z:
				ek.setKey(df::Keyboard::Z);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num1:
				ek.setKey(df::Keyboard::NUM1);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num2:
				ek.setKey(df::Keyboard::NUM2);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num3:
				ek.setKey(df::Keyboard::NUM3);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num4:
				ek.setKey(df::Keyboard::NUM4);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num5:
				ek.setKey(df::Keyboard::NUM5);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num6:
				ek.setKey(df::Keyboard::NUM6);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num7:
				ek.setKey(df::Keyboard::NUM7);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num8:
				ek.setKey(df::Keyboard::NUM8);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num9:
				ek.setKey(df::Keyboard::NUM9);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num0:
				ek.setKey(df::Keyboard::NUM0);
				onEvent(&ek);
				break;
			}
			break;
		case sf::Event::KeyReleased:
			ek.setKeyboardAction(df::EventKeyboardAction::KEY_RELEASED);
			switch (event.key.code) {
			case sf::Keyboard::Space:
				ek.setKey(df::Keyboard::SPACE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Return:
				ek.setKey(df::Keyboard::RETURN);
				onEvent(&ek);
				break;
			case sf::Keyboard::Escape:
				ek.setKey(df::Keyboard::ESCAPE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Tab:
				ek.setKey(df::Keyboard::TAB);
				onEvent(&ek);
				break;
			case sf::Keyboard::Left:
				ek.setKey(df::Keyboard::LEFTARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Right:
				ek.setKey(df::Keyboard::RIGHTARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Up:
				ek.setKey(df::Keyboard::UPARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Down:
				ek.setKey(df::Keyboard::DOWNARROW);
				onEvent(&ek);
				break;
			case sf::Keyboard::Pause:
				ek.setKey(df::Keyboard::PAUSE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Subtract:
				ek.setKey(df::Keyboard::MINUS);
				onEvent(&ek);
				break;
			case sf::Keyboard::Add:
				ek.setKey(df::Keyboard::PLUS);
				onEvent(&ek);
				break;
			case sf::Keyboard::Tilde:
				ek.setKey(df::Keyboard::TILDE);
				onEvent(&ek);
				break;
			case sf::Keyboard::Period:
				ek.setKey(df::Keyboard::PERIOD);
				onEvent(&ek);
				break;
			case sf::Keyboard::Comma:
				ek.setKey(df::Keyboard::COMMA);
				onEvent(&ek);
				break;
			case sf::Keyboard::Slash:
				ek.setKey(df::Keyboard::SLASH);
				onEvent(&ek);
				break;
			case sf::Keyboard::LControl:
				ek.setKey(df::Keyboard::LEFTCONTROL);
				onEvent(&ek);
				break;
			case sf::Keyboard::RControl:
				ek.setKey(df::Keyboard::RIGHTCONTROL);
				onEvent(&ek);
				break;
			case sf::Keyboard::LShift:
				ek.setKey(df::Keyboard::LEFTSHIFT);
				onEvent(&ek);
				break;
			case sf::Keyboard::RShift:
				ek.setKey(df::Keyboard::RIGHTSHIFT);
				onEvent(&ek);
				break;
			case sf::Keyboard::F1:
				ek.setKey(df::Keyboard::F1);
				onEvent(&ek);
				break;
			case sf::Keyboard::F2:
				ek.setKey(df::Keyboard::F2);
				onEvent(&ek);
				break;
			case sf::Keyboard::F3:
				ek.setKey(df::Keyboard::F3);
				onEvent(&ek);
				break;
			case sf::Keyboard::F4:
				ek.setKey(df::Keyboard::F4);
				onEvent(&ek);
				break;
			case sf::Keyboard::F5:
				ek.setKey(df::Keyboard::F5);
				onEvent(&ek);
				break;
			case sf::Keyboard::F6:
				ek.setKey(df::Keyboard::F6);
				onEvent(&ek);
				break;
			case sf::Keyboard::F7:
				ek.setKey(df::Keyboard::F7);
				onEvent(&ek);
				break;
			case sf::Keyboard::F8:
				ek.setKey(df::Keyboard::F8);
				onEvent(&ek);
				break;
			case sf::Keyboard::F9:
				ek.setKey(df::Keyboard::F9);
				onEvent(&ek);
				break;
			case sf::Keyboard::F10:
				ek.setKey(df::Keyboard::F10);
				onEvent(&ek);
				break;
			case sf::Keyboard::F11:
				ek.setKey(df::Keyboard::F11);
				onEvent(&ek);
				break;
			case sf::Keyboard::F12:
				ek.setKey(df::Keyboard::F12);
				onEvent(&ek);
				break;
			case sf::Keyboard::A:
				ek.setKey(df::Keyboard::A);
				onEvent(&ek);
				break;
			case sf::Keyboard::B:
				ek.setKey(df::Keyboard::B);
				onEvent(&ek);
				break;
			case sf::Keyboard::C:
				ek.setKey(df::Keyboard::C);
				onEvent(&ek);
				break;
			case sf::Keyboard::D:
				ek.setKey(df::Keyboard::D);
				onEvent(&ek);
				break;
			case sf::Keyboard::E:
				ek.setKey(df::Keyboard::E);
				onEvent(&ek);
				break;
			case sf::Keyboard::F:
				ek.setKey(df::Keyboard::F);
				onEvent(&ek);
				break;
			case sf::Keyboard::G:
				ek.setKey(df::Keyboard::G);
				onEvent(&ek);
				break;
			case sf::Keyboard::H:
				ek.setKey(df::Keyboard::H);
				onEvent(&ek);
				break;
			case sf::Keyboard::I:
				ek.setKey(df::Keyboard::I);
				onEvent(&ek);
				break;
			case sf::Keyboard::J:
				ek.setKey(df::Keyboard::J);
				onEvent(&ek);
				break;
			case sf::Keyboard::K:
				ek.setKey(df::Keyboard::K);
				onEvent(&ek);
				break;
			case sf::Keyboard::L:
				ek.setKey(df::Keyboard::L);
				onEvent(&ek);
				break;
			case sf::Keyboard::M:
				ek.setKey(df::Keyboard::M);
				onEvent(&ek);
				break;
			case sf::Keyboard::N:
				ek.setKey(df::Keyboard::N);
				onEvent(&ek);
				break;
			case sf::Keyboard::O:
				ek.setKey(df::Keyboard::O);
				onEvent(&ek);
				break;
			case sf::Keyboard::P:
				ek.setKey(df::Keyboard::P);
				onEvent(&ek);
				break;
			case sf::Keyboard::Q:
				ek.setKey(df::Keyboard::Q);
				onEvent(&ek);
				break;
			case sf::Keyboard::R:
				ek.setKey(df::Keyboard::R);
				onEvent(&ek);
				break;
			case sf::Keyboard::S:
				ek.setKey(df::Keyboard::S);
				onEvent(&ek);
				break;
			case sf::Keyboard::T:
				ek.setKey(df::Keyboard::T);
				onEvent(&ek);
				break;
			case sf::Keyboard::U:
				ek.setKey(df::Keyboard::U);
				onEvent(&ek);
				break;
			case sf::Keyboard::V:
				ek.setKey(df::Keyboard::V);
				onEvent(&ek);
				break;
			case sf::Keyboard::W:
				ek.setKey(df::Keyboard::W);
				onEvent(&ek);
				break;
			case sf::Keyboard::X:
				ek.setKey(df::Keyboard::X);
				onEvent(&ek);
				break;
			case sf::Keyboard::Y:
				ek.setKey(df::Keyboard::Y);
				onEvent(&ek);
				break;
			case sf::Keyboard::Z:
				ek.setKey(df::Keyboard::Z);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num1:
				ek.setKey(df::Keyboard::NUM1);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num2:
				ek.setKey(df::Keyboard::NUM2);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num3:
				ek.setKey(df::Keyboard::NUM3);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num4:
				ek.setKey(df::Keyboard::NUM4);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num5:
				ek.setKey(df::Keyboard::NUM5);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num6:
				ek.setKey(df::Keyboard::NUM6);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num7:
				ek.setKey(df::Keyboard::NUM7);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num8:
				ek.setKey(df::Keyboard::NUM8);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num9:
				ek.setKey(df::Keyboard::NUM9);
				onEvent(&ek);
				break;
			case sf::Keyboard::Num0:
				ek.setKey(df::Keyboard::NUM0);
				onEvent(&ek);
				break;
			}
			break;
		case sf::Event::MouseMoved:
			em.setMouseAction(df::EventMouseAction::MOVED);
			mouse_pos.setXY(event.mouseMove.x, event.mouseMove.y);
			em.setMousePosition(mouse_pos);
			onEvent(&em);
			break;
		case sf::Event::MouseButtonPressed:
			em.setMouseAction(df::EventMouseAction::PRESSED);
			switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				em.setMouseButton(df::Mouse::Button::LEFT);
				onEvent(&em);
				break;
			case sf::Mouse::Right:
				em.setMouseButton(df::Mouse::Button::RIGHT);
				onEvent(&em);
				break;
			case sf::Mouse::Middle:
				em.setMouseButton(df::Mouse::Button::MIDDLE);
				onEvent(&em);
				break;
			}
			break;
		}
	}
}