#include "ViewObject.h"
#include "WorldManager.h"
#include "Utility.h"
#include "EventView.h"

df::ViewObject::ViewObject()
{
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("viewobject");

	value = 0;
	draw_value = true;
	border = true;
	setLocation(TOP_CENTER);
	color = COLOR_DEFAULT;
	just = CENTER_JUSTIFIED;
}

int df::ViewObject::draw()
{
	std::string temp_value;
	if (draw_value)
		temp_value = std::to_string(value);
	else
		temp_value = "";
	std::string temp_str;
	if (border) 
		temp_str = " " + getViewString() + " " + temp_value + " ";
	else
		temp_str = getViewString() + " " + temp_value;
	
	DM.drawString(viewToWorld(getPosition()), temp_str, just, getColor());
	return 0;
}

int df::ViewObject::eventHandler(const Event* e)
{
	if (e->getType() == VIEW_EVENT) {
		const df::EventView* ve = static_cast <const df::EventView*> (e);
		if (ve->getTag() == getType()) {
			if (ve->getDelta())
				setValue(getValue() + ve->getValue());
			else
				setValue(ve->getValue());
			return 0;
		}
	}
	return -1;
}

void df::ViewObject::setLocation(ViewObjectLocation new_location)
{
	Vector p = Vector();
	int y_delta = 0;
	switch (new_location)
	{
	case df::TOP_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
		just = LEFT_JUSTIFIED;
		if (!getBorder())
			y_delta = -1;
		break;
	case df::TOP_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
		just = CENTER_JUSTIFIED;
		if (!getBorder())
			y_delta = -1;
		break;
	case df::TOP_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
		just = RIGHT_JUSTIFIED;
		if (!getBorder())
			y_delta = -1;
		break;
	case df::CENTER_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical()/2);
		break;
	case df::CENTER_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() / 2);
		break;
	case df::CENTER_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() / 2);
		break;
	case df::BOTTOM_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 1);
		if (!getBorder())
			y_delta = 1;
		break;
	case df::BOTTOM_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 1);
		if (!getBorder())
			y_delta = 1;
		break;
	case df::BOTTOM_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 1);
		if (!getBorder())
			y_delta = 1;
		break;
	}
	p.setY(p.getY() + y_delta);
	setPosition(p);
	location = new_location;
}

df::ViewObjectLocation df::ViewObject::getLocation() const { return location; }

void df::ViewObject::setDrawValue(bool new_draw_value) { draw_value = new_draw_value; }

bool df::ViewObject::getDrawValue() const { return draw_value; }

void df::ViewObject::setValue(int new_value) { value = new_value; }

int df::ViewObject::getValue() const { 
	if(draw_value == true)
		return value;
	return NULL;
}

void df::ViewObject::setBorder(bool new_border) {
	if (border == new_border)
		return;
	border = new_border; 
	setLocation(getLocation());
}

bool df::ViewObject::getBorder() const { return border; }

void df::ViewObject::setColor(Color new_color) { color = new_color; }

df::Color df::ViewObject::getColor() const { return color; }

void df::ViewObject::setViewString(std::string new_view_string) { view_string = new_view_string; }

std::string df::ViewObject::getViewString() const { return view_string; }

void df::ViewObject::setPosition(Vector new_pos)
{
}
