#include "gfx/font.hpp"

gfx::Font::Font() {
}
gfx::Font::~Font() {
}

void gfx::Font::createID() {
    if(!this->hasValidID()) {
        glGenTextures(1, &this->id);
        this->bindID(); //Texture name isn't valid until bound
    }
}
void gfx::Font::deleteID() {
    if(this->hasValidID()) {
        glDeleteTextures(1, &this->id);
    }
}
void gfx::Font::bindID() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
bool gfx::Font::hasValidID() {
    if(glIsTexture(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}

bool gfx::Font::loadFromFile(const std::string& path, unsigned int size) {
	if(!this->hasValidID()) {
        std::string errMsg("tried to load font ");
        errMsg += path;
        errMsg += ", but the font texture id is invalid.\n";
        throw std::runtime_error(errMsg);
        return false;
	}

    this->path = path;

    FT_Library fl;
    FT_GlyphSlot fg;
    FT_Face ff;
	FT_Matrix fm; //Oh god why

    if(FT_Init_FreeType(&fl)) {
        std::string errMsg("failed to initialize freetype when loading font ");
        errMsg += path;
        errMsg += "\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    int error  = FT_New_Face(fl, path.c_str(), 0, &ff);

	if(error == FT_Err_Unknown_File_Format) {
        std::string errMsg("failed to open font ");
        errMsg += path;
        errMsg += ". Unknown format.\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    FT_Set_Pixel_Sizes(ff, 0, 128);

    fg = ff->glyph;

    glm::vec2 glyph_res;
	unsigned int numLoaded = 0;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int atlas_width = 0;

	//pls to the halp
	double angle = 3.14f;
  	fm.xx = (FT_Fixed)(glm::cos(angle*2) * 0x10000L);
  	fm.xy = (FT_Fixed)(-glm::sin(angle) * 0x10000L);
  	fm.yx = (FT_Fixed)(glm::sin(angle*2) * 0x10000L);
  	fm.yy = (FT_Fixed)(glm::cos(angle) * 0x10000L);

    FT_Set_Transform(ff, &fm, NULL);

    for(int i = 32; i < 128; i++) {
        if(FT_Load_Char(ff, i, FT_LOAD_RENDER)) {
            printf("failed to load character %c from font %s\n", (char)i, path.c_str());
            continue;
        } else {
			numLoaded++;
		}

		w += fg->bitmap.width;
		h = std::max(h, fg->bitmap.rows);
		atlas_width = w;
    }

	this->bindID();

	printf("font %s, res:%ux%u\n", this->path.c_str(), fg->bitmap.width, fg->bitmap.rows);
	printf("loaded %u characters, out of %u possible characters\n", numLoaded, ff->num_glyphs);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	int x = 0;

	for(int i = 32; i < 128; i++) {
		if(FT_Load_Char(ff, i, FT_LOAD_RENDER)) {
			continue;
		}

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, fg->bitmap.width, fg->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fg->bitmap.buffer);

		gfx::Glyph character;
		character.resolution = glm::vec2(fg->bitmap.width, fg->bitmap.rows);
		character.advance = glm::vec2(fg->advance.x >> 6, fg->advance.y >> 6);
		character.left = fg->bitmap_left;
		character.top = fg->bitmap_top;
		character.offset = (float)x / w;

		this->glyphs.emplace_back(character);

		x += fg->bitmap.width;
	}

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    FT_Done_Face(ff);
    FT_Done_FreeType(fl);

    return true;
}
