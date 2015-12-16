#include "gfx/font.hpp"

mg::Font::Font() {
	this->createID();
}
mg::Font::~Font() {
	this->deleteID();
}

void mg::Font::createID() {
    if(!this->hasValidID()) {
        glGenTextures(1, &m_id);
        this->bindID(); //Texture name isn't valid until bound
    }
}
void mg::Font::deleteID() {
    if(this->hasValidID()) {
        glDeleteTextures(1, &m_id);
    }
}
void mg::Font::bindID() {
    glBindTexture(GL_TEXTURE_2D, m_id);
}
bool mg::Font::hasValidID() {
    if(glIsTexture(m_id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}
unsigned int mg::Font::getID() {
    return m_id;
}

bool mg::Font::load(std::string path, unsigned int size) {
    m_path = std::move(path);

	if(!this->hasValidID()) {
        printf("Font %s tried load, but the texture is invalid.\n", m_path.c_str());
        return false;
	}

    FT_Library fl;
    FT_GlyphSlot fg;
    FT_Face ff;
	FT_Matrix fm;

    if(FT_Init_FreeType(&fl)) {
        printf("Freetype failed to initialize loading font %s.\n", m_path.c_str());
        return false;
    }

    int error = FT_New_Face(fl, m_path.c_str(), 0, &ff);

	if(error == FT_Err_Unknown_File_Format) {
        printf("Font %s failed to load, unknown font format.\n", m_path.c_str());
        return false;
    }

    if(FT_Set_Pixel_Sizes(ff, 0, size) != 0) {
        printf("Font failed to set pixel size %d on %s. Unavailable in font?\n", size, m_path.c_str());
        return false;
	}
    fg = ff->glyph;

	double angle = 3.14f;
  	fm.xx = (FT_Fixed)(glm::cos(angle*2) * 0x10000L);
  	fm.xy = (FT_Fixed)(-glm::sin(angle) * 0x10000L);
  	fm.yx = (FT_Fixed)(glm::sin(angle*2) * 0x10000L);
  	fm.yy = (FT_Fixed)(glm::cos(angle) * 0x10000L);

    FT_Set_Transform(ff, &fm, NULL);

	//if we have no characters to cache, load some common characters
	if(m_cacheString.empty()) {
		m_cacheString = L" abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ1234567890!#¤%&/\"()=?`*^_-:.,'@£$€¥{[]};<>|";
	}
    for(size_t i = 0; i < m_cacheString.size(); i++) {
        if(FT_Load_Char(ff, m_cacheString[i], FT_LOAD_RENDER)) {
            printf("failed to load character %c from font %s\n", (wchar_t)i, m_path.c_str());
            continue;
        }

		m_resolution.x += fg->bitmap.width;
		m_resolution.y = std::max((unsigned int)0, fg->bitmap.rows);
    }

	this->bindID();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_resolution.x, m_resolution.y, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	float x = 0;
	for(size_t i = 0; i < m_cacheString.size(); i++) {
        if(FT_Load_Char(ff, m_cacheString[i], FT_LOAD_RENDER)) {
            continue;
        }

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, fg->bitmap.width, fg->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fg->bitmap.buffer);

		mg::Glyph character;
		character.advance = glm::vec2(fg->advance.x >> 6, fg->advance.y >> 6);
		character.resolution = glm::vec2(fg->bitmap.width, fg->bitmap.rows);
		character.left = fg->bitmap_left;
		character.top = fg->bitmap_top;

		float offset = x / m_resolution.x;
		character.uvs = glm::vec4(
			offset,
			0.0f,
			offset + (character.resolution.x / m_resolution.x),
			character.resolution.y / m_resolution.y
		);

		m_glyphs[m_cacheString[i]] = character;

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

/*std::shared_ptr<mg::Mesh> mg::Font::getMeshFromString(const std::wstring& text) {
	glm::vec2 pen;
	std::shared_ptr<mg::Mesh> mesh = std::make_shared<mg::Mesh>();
	std::vector<float> vertexData;

	for(unsigned int i = 0; i < text.size(); i++) {
		mg::Glyph glyph = m_glyphs[text[i]];

		vertexData.reserve(vertexData.size() + 6*4);
    	float newQuad[] = {
			-1.0f  1.0f  0.0f 1.0f //Top left
    		 1.0f  1.0f  1.0f 1.0f //Top right
    		 1.0f -1.0f  1.0f 0.0f //Bottom right
    		 1.0f -1.0f  1.0f 0.0f //Bottom right
    		-1.0f -1.0f  0.0f 0.0f //Bottom left
    		-1.0f  1.0f  0.0f 1.0f //Top left
		}

		//add(
		//	glm::vec2(pen.x + glyph.left + glyph.resolution.x, pen.y - (glyph.top + glyph.advance.y - glyph.resolution.y)),
		//	glm::vec2(glyph.resolution.x, glyph.resolution.y),
		//	glyph.uvs
		//);

		if(text[i] == '\n') { //newline
			pen = glm::vec2(pen.x, pen.y - (m_resolution.y*2.0f));
		} else if(text[i] == '\t') { //tab
			pen.x += (glyph.advance.x*2.0f) + (m_glyphs[' '].advance.x * 8.0f);
		} else { //a normal character
			pen.x += glyph.advance.x*2.0f;
		}
	}

	if(!mesh.uploadVertexData(vertexData)) {
		return nullptr;
	}

	return mesh;
}
*/
