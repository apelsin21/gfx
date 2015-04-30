#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace gfx {
	class Vertex {
		protected:
		public:
			float x, y, u, v, r, g, b, a;

			Vertex();
			Vertex(int, int, int, int, int, int, int, int);
			~Vertex();
	};
}

#endif //VERTEX_HPP
