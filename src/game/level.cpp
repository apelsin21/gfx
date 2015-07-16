#include "game/level.hpp"

mg::Level::Level() {
}
mg::Level::~Level() {
}

bool mg::Level::load(const std::string& path) {
	mg::GLTexture texture;

	if(!texture.load(path)) {
		return false;
	}

	return true;
}

void mg::Level::render(mg::SpriteBatch& batch) {
	for(unsigned int i = 0; i < sprites.size(); i++) {
		batch.draw(sprites[i].pos, sprites[i].scale, sprites[i].uvs);	
	}
}
