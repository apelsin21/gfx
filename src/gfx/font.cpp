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

    int error = FT_New_Face(fl, path.c_str(), 0, &ff);

	if(error == FT_Err_Unknown_File_Format) {
        std::string errMsg("failed to open font ");
        errMsg += path;
        errMsg += ". Unknown format.\n";
        throw std::runtime_error(errMsg);
        return false;
    }

	//size of 6*64 at 96 dpi
    if(FT_Set_Pixel_Sizes(ff, 0, size) != 0) {
        std::string errMsg("failed to set pixel size ");
		errMsg += size;
		errMsg += " on font: ";
        errMsg += path;
        errMsg += ". Maybe it's unavailable.\n";
        throw std::runtime_error(errMsg);
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

    for(size_t i = ' '; i < '~'; i++) {
        if(FT_Load_Char(ff, i, FT_LOAD_RENDER)) {
            printf("failed to load character %c from font %s\n", (char)i, path.c_str());
            continue;
        }

		this->resolution.x += fg->bitmap.width;
		this->resolution.y = std::max((unsigned int)0, fg->bitmap.rows);
    }

	this->bindID();

	printf("font texture size: %ux%u\n", this->resolution.x, this->resolution.y);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->resolution.x, this->resolution.y, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	int x = 0;

	//cache the ascii table
	for(size_t i = ' '; i <= '~'; i++) {
		if(FT_Load_Char(ff, i, FT_LOAD_RENDER)) {
			continue;
		}

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, fg->bitmap.width, fg->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fg->bitmap.buffer);

		//gfx::Glyph character;
		//character.resolution = glm::vec2(fg->bitmap.width, fg->bitmap.rows);
		//character.advance = glm::vec2(fg->advance.x >> 6, fg->advance.y >> 6);
		//character.left = fg->bitmap_left;
		//character.top = fg->bitmap_top;
		//character.offset = (float)x / this->resolution.x;

		float blx = ((float)x / this->resolution.x);
		
		this->glyphs[i] = glm::vec4(blx,
			0.0f,
		   	blx + ((float)fg->bitmap.width / this->resolution.x),
		   	(float)fg->bitmap.rows / this->resolution.y);

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
