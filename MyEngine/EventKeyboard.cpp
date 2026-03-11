#include "EventKeyboard.h"

df::EventKeyboard::EventKeyboard() {
	setType(KBD_EVENT);
	key_val = Keyboard::UNDEFINED_KEY;
	keyboard_action = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
}

void df::EventKeyboard::setKey(Keyboard::Key new_key) { key_val = new_key; }

df::Keyboard::Key df::EventKeyboard::getKey() const {return key_val;}

void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) { keyboard_action = new_action; }

df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const { return keyboard_action; }

df::Keyboard::Key df::EventKeyboard::convertFromSfKey(sf::Keyboard::Key k)
{
	switch (k)
	{
	case sf::Keyboard::Unknown:
		return Keyboard::UNDEFINED_KEY;
	case sf::Keyboard::A:
		return Keyboard::A;
	case sf::Keyboard::B:
		return Keyboard::B;
	case sf::Keyboard::C:
		return Keyboard::C;
	case sf::Keyboard::D:
		return Keyboard::D;
	case sf::Keyboard::E:
		return Keyboard::E;
	case sf::Keyboard::F:
		return Keyboard::F;
	case sf::Keyboard::G:
		return Keyboard::G;
	case sf::Keyboard::H:
		return Keyboard::H;
	case sf::Keyboard::I:
		return Keyboard::I;
	case sf::Keyboard::J:
		return Keyboard::J;
	case sf::Keyboard::K:
		return Keyboard::K;
	case sf::Keyboard::L:
		return Keyboard::L;
	case sf::Keyboard::M:
		return Keyboard::M;
	case sf::Keyboard::N:
		return Keyboard::N;
	case sf::Keyboard::O:
		return Keyboard::O;
	case sf::Keyboard::P:
		return Keyboard::P;
	case sf::Keyboard::Q:
		return Keyboard::Q;
	case sf::Keyboard::R:
		return Keyboard::R;
	case sf::Keyboard::S:
		return Keyboard::S;
	case sf::Keyboard::T:
		return Keyboard::T;
	case sf::Keyboard::U:
		return Keyboard::U;
	case sf::Keyboard::V:
		return Keyboard::V;
	case sf::Keyboard::W:
		return Keyboard::W;
	case sf::Keyboard::X:
		return Keyboard::X;
	case sf::Keyboard::Y:
		return Keyboard::Y;
	case sf::Keyboard::Z:
		return Keyboard::Z;
	case sf::Keyboard::Num0:
		return Keyboard::NUM0;
	case sf::Keyboard::Num1:
		return Keyboard::NUM1;
	case sf::Keyboard::Num2:
		return Keyboard::NUM2;
	case sf::Keyboard::Num3:
		return Keyboard::NUM3;
	case sf::Keyboard::Num4:
		return Keyboard::NUM4;
	case sf::Keyboard::Num5:
		return Keyboard::NUM5;
	case sf::Keyboard::Num6:
		return Keyboard::NUM6;
	case sf::Keyboard::Num7:
		return Keyboard::NUM7;
	case sf::Keyboard::Num8:
		return Keyboard::NUM8;
	case sf::Keyboard::Num9:
		return Keyboard::NUM9;
	case sf::Keyboard::Escape:
		return Keyboard::ESCAPE;
	case sf::Keyboard::LControl:
		return Keyboard::LEFTCONTROL;
	case sf::Keyboard::LShift:
		return Keyboard::LEFTSHIFT;
	case sf::Keyboard::RControl:
		return Keyboard::RIGHTCONTROL;
	case sf::Keyboard::RShift:
		return Keyboard::RIGHTSHIFT;
	case sf::Keyboard::Semicolon:
		return Keyboard::SEMICOLON;
	case sf::Keyboard::Comma:
		return Keyboard::COMMA;
	case sf::Keyboard::Period:
		return Keyboard::PERIOD;
	case sf::Keyboard::Quote:
		return Keyboard::QUOTE;
	case sf::Keyboard::Slash:
		return Keyboard::SLASH;
	case sf::Keyboard::Backslash:
		return Keyboard::BACKSLASH;
	case sf::Keyboard::Tilde:
		return Keyboard::TILDE;
	case sf::Keyboard::Equal:
		return Keyboard::EQUAL;
	case sf::Keyboard::Space:
		return Keyboard::SPACE;
	case sf::Keyboard::Enter:
		return Keyboard::RETURN;
	case sf::Keyboard::Backspace:
		return Keyboard::BACKSPACE;
	case sf::Keyboard::Tab:
		return Keyboard::TAB;
	case sf::Keyboard::Add:
		return Keyboard::PLUS;
	case sf::Keyboard::Subtract:
		return Keyboard::MINUS;
	case sf::Keyboard::Multiply:
		return Keyboard::MULTIPLY;
	case sf::Keyboard::Left:
		return Keyboard::LEFTARROW;
	case sf::Keyboard::Right:
		return Keyboard::RIGHTARROW;
	case sf::Keyboard::Up:
		return Keyboard::UPARROW;
	case sf::Keyboard::Down:
		return Keyboard::DOWNARROW;
	case sf::Keyboard::F1:
		return Keyboard::F1;
	case sf::Keyboard::F2:
		return Keyboard::F2;
	case sf::Keyboard::F3:
		return Keyboard::F3;
	case sf::Keyboard::F4:
		return Keyboard::F4;
	case sf::Keyboard::F5:
		return Keyboard::F5;
	case sf::Keyboard::F6:
		return Keyboard::F6;
	case sf::Keyboard::F7:
		return Keyboard::F7;
	case sf::Keyboard::F8:
		return Keyboard::F8;
	case sf::Keyboard::F9:
		return Keyboard::F9;
	case sf::Keyboard::F10:
		return Keyboard::F10;
	case sf::Keyboard::F11:
		return Keyboard::F11;
	case sf::Keyboard::F12:
		return Keyboard::F12;
	default:
		return Keyboard::UNDEFINED_KEY;
	}
}

