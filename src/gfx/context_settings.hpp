#ifndef CONTEXT_SETTINGS_HPP
#define CONTEXT_SETTINGS_HPP

namespace mg {
    class ContextSettings {
        protected:
        public:
            int major, minor, depthBits;
            bool doubleBuffered, coreProfile, vsync;

            ContextSettings(int, int, bool);
            ContextSettings(int, int, int, bool, bool, bool);
            ContextSettings();
            ~ContextSettings();

            bool operator<(const ContextSettings&);
            bool operator>(const ContextSettings&);
    };
}

#endif //CONTEXT_SETTINGS_HPP
