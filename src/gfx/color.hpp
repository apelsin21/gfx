#ifndef COLOR_HPP
#define COLOR_HPP

namespace mg {
	class Color {
		protected:
		public:
			float r, g, b, a;

			Color();
			Color(float, float, float, float);
			~Color();

			void setRed(float);
			float getRed() const;

			void setGreen(float);
			float getGreen() const;

			void setBlue(float);
			float getBlue() const;

			void setAlpha(float);
			float getAlpha() const;
	};
}
#endif //COLOR_HPP
