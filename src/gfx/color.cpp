#include "gfx/color.hpp"

mg::Color::Color() {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
}
mg::Color::Color(float val_r, float val_g, float val_b, float val_a) {
	float r = val_r;
	float g = val_g;
	float b = val_b;
	float a = val_a;
}
mg::Color::~Color() {
}

void mg::Color::setRed(float val) {
	r = val;
}
float mg::Color::getRed() const {
	return r;
}

void mg::Color::setGreen(float val) {
	g = val;
}
float mg::Color::getGreen() const {
	return g;
}

void mg::Color::setBlue(float val) {
	b = val;
}
float mg::Color::getBlue() const {
	return b;
}

void mg::Color::setAlpha(float val) {
	a = val;
}
float mg::Color::getAlpha() const {
	return a;
}
