#include "gfx/context_settings.hpp"

gfx::ContextSettings::ContextSettings(int ma, int mi, bool core) {
    this->major = ma;
    this->minor = mi;
    this->coreProfile = core;
    this->doubleBuffered = true;
	this->vsync = true;
    this->depthBits = 24;
}
gfx::ContextSettings::ContextSettings(int ma, int mi, int db, bool core, bool buffers, bool vsync_) {
    this->major = ma;
    this->minor = mi;
    this->depthBits = db;
    this->coreProfile = core;
    this->doubleBuffered = buffers;
	this->vsync = vsync_;
}
gfx::ContextSettings::ContextSettings() {
    this->major = 3;
    this->minor = 0;
    this->coreProfile = false;
    this->doubleBuffered = true;
    this->vsync = true;
    this->depthBits = 24;
}
gfx::ContextSettings::~ContextSettings() {
}

bool gfx::ContextSettings::operator<(const ContextSettings& other) {
    if(this->major < other.major || (this->major == other.major && this->minor < other.minor)) {
        return true;
    } else {
        return false;
    }
}
bool gfx::ContextSettings::operator>(const ContextSettings& other) {
    if(this->major < other.major || (this->major == other.major && this->minor < other.minor)) {
        return false;
    } else {
        return true;
    }
}
