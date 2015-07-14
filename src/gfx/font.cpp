#include "gfx/font.hpp"

mg::Font::Font() {
	this->createID();
}
mg::Font::~Font() {
	this->deleteID();
}

void mg::Font::createID() {
    if(!this->hasValidID()) {
        glGenTextures(1, &this->id);
        this->bindID(); //Texture name isn't valid until bound
    }
}
void mg::Font::deleteID() {
    if(this->hasValidID()) {
        glDeleteTextures(1, &this->id);
    }
}
void mg::Font::bindID() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
bool mg::Font::hasValidID() {
    if(glIsTexture(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}
unsigned int mg::Font::getID() {
    return this->id;
}

bool mg::Font::load(const std::string& path, unsigned int size) {
	if(!this->hasValidID()) {
        printf("Font %s tried load, but the texture is invalid.\n", path.c_str());
        return false;
	}

    this->path = path;

    FT_Library fl;
    FT_GlyphSlot fg;
    FT_Face ff;
	FT_Matrix fm; //Oh god why

    if(FT_Init_FreeType(&fl)) {
        printf("Freetype failed to initialize loading font %s.\n", path.c_str());
        return false;
    }

    int error = FT_New_Face(fl, path.c_str(), 0, &ff);

	if(error == FT_Err_Unknown_File_Format) {
        printf("Font %s failed to load, unknown font format.\n", path.c_str());
        return false;
    }

    if(FT_Set_Pixel_Sizes(ff, 0, size) != 0) {
        printf("Font failed to set pixel size %d on %s. Unavailable in font?\n", size, path.c_str());
        return false;
	}
    fg = ff->glyph;

	//pls to the halp
	double angle = 3.14f;
  	fm.xx = (FT_Fixed)(glm::cos(angle*2) * 0x10000L);
  	fm.xy = (FT_Fixed)(-glm::sin(angle) * 0x10000L);
  	fm.yx = (FT_Fixed)(glm::sin(angle*2) * 0x10000L);
  	fm.yy = (FT_Fixed)(glm::cos(angle) * 0x10000L);

    FT_Set_Transform(ff, &fm, NULL);

	//if we have no characters to cache, load some common characters
	if(this->cacheString.empty()) {
		this->cacheString = L" abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ1234567890!#¤%&/\"()=?`*^_-:.,'@£$€¥{[]};<>|";
	}
    for(size_t i = 0; i < this->cacheString.size(); i++) {
        if(FT_Load_Char(ff, this->cacheString[i], FT_LOAD_RENDER)) {
            printf("failed to load character %c from font %s\n", (wchar_t)i, path.c_str());
            continue;
        }

		this->resolution.x += fg->bitmap.width;
		this->resolution.y = std::max((unsigned int)0, fg->bitmap.rows);
    }

	this->bindID();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->resolution.x, this->resolution.y, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	float x = 0;
	for(size_t i = 0; i < this->cacheString.size(); i++) {
        if(FT_Load_Char(ff, this->cacheString[i], FT_LOAD_RENDER)) {
            continue;
        }

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, fg->bitmap.width, fg->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fg->bitmap.buffer);

		mg::Glyph character;
		character.advance = glm::vec2(fg->advance.x >> 6, fg->advance.y >> 6);
		character.resolution = glm::vec2(fg->bitmap.width, fg->bitmap.rows);
		character.left = fg->bitmap_left;
		character.top = fg->bitmap_top;

		float offset = x / this->resolution.x;
		character.uvs = glm::vec4(
			offset,
			0.0f,
			offset + (character.resolution.x / this->resolution.x),
			character.resolution.y / this->resolution.y
		);

		this->glyphs[this->cacheString[i]] = character;

		x += character.resolution.x;
	}

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    FT_Done_Face(ff);
    FT_Done_FreeType(fl);

    return true;
}
