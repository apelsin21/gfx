#include "gfx/framebuffer.hpp"

mg::FrameBuffer::FrameBuffer() {
	_fbo = 0;
	_rboDepth = 0;
	_rboColor = 0;
}
mg::FrameBuffer::~FrameBuffer() {
	if(glIsRenderbuffer(_rboDepth) == GL_TRUE) {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glDeleteRenderbuffers(1, &_rboDepth);
	}
	if(glIsFramebuffer(_fbo) == GL_TRUE) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &_fbo);
	}
}

bool mg::FrameBuffer::isComplete() const {
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		return true;
	}

	return false;
}

bool mg::FrameBuffer::createColorTexture(const glm::vec2& resolution) {
	if(glIsFramebuffer(_fbo) == GL_FALSE) {
		glGenFramebuffers(1, &_fbo);
	}
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);

	_colorTexture = std::make_shared<mg::Texture>();
	_colorTexture->setResolution(resolution);
	_colorTexture->setBPP(32);
	_colorTexture->setSize((resolution.x * resolution.y) * (_colorTexture->getBPP() / 8));
	_colorTexture->setFormat(mg::TextureFormat::RGB);
	_colorTexture->setInternalFormat(mg::TextureFormat::RGB);
	_colorTexture->setFilter(mg::TextureFilter::Nearest);
	_colorTexture->setWrap(mg::TextureWrap::Repeat);
	_colorTexture->upload(nullptr);

	glGenRenderbuffers(1, &_rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, _rboDepth);
	glRenderbufferStorage(
		GL_RENDERBUFFER,
		GL_DEPTH_COMPONENT,
		resolution.x,
		resolution.y
	);
	glFramebufferRenderbuffer(
		GL_DRAW_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER,
		_rboDepth
	);

	glFramebufferTexture2D(
		GL_DRAW_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		_colorTexture->getGLHandle(),
		0
	);

	GLint result;

	glGetFramebufferAttachmentParameteriv(
		GL_DRAW_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
		&result
	);

	switch(result) {
		case GL_NONE:
			printf("framebuffer color attachment is GL_NONE.\n");
			return false;
			break;
		case GL_FRAMEBUFFER_DEFAULT:
			printf("framebuffer color attachment is GL_FRAMEBUFFER_DEFAULT.\n");
			break;
		case GL_TEXTURE:
			glGetFramebufferAttachmentParameteriv(
				GL_DRAW_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
				&result
			);

			if(result != _colorTexture->getGLHandle()) {
				printf("but it doesn't match the texture name!\n");
				return false;
			}

			break;
		case GL_RENDERBUFFER:
			printf("framebuffer color attachment is GL_RENDERBUFFER.\n");
			break;
		default:
			printf("framebuffer has unhandled color attachment type.\n");
			return false;
			break;
	}

	const GLenum drawBuffers[] = {
		GL_COLOR_ATTACHMENT0
	};

	glDrawBuffers(1, drawBuffers);

	if(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("framebuffer is incomplete.\n");
		return false;
	}

	return true;
}
std::shared_ptr<mg::Texture> mg::FrameBuffer::getColorTexture() const {
	return _colorTexture;
}

GLuint mg::FrameBuffer::getGLHandle() const {
	return _fbo;
}
