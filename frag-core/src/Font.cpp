#include"Font.h"
using namespace fragview;

Font::Font(void) {
	this->texture = NULL;
}

Font::~Font(void) {
	//TODO reduce references.
}

unsigned int Font::getNumberCharacter(void) const {
	return this->characters.size();
}

Font::Character Font::getCharacter(unsigned int index) {
	return this->characters[index];
}

const Font::Character &Font::getCharacter(unsigned int index) const {
	return this->characters[index];
}

Texture *Font::getTexture(void) const {
	return this->texture;
}
