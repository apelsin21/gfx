#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include "gfx/mesh.hpp"
#include "gfx/texture.hpp"

namespace mg {
	class MeshLoader {
		protected:
			Assimp::Importer _importer;
		public:
			MeshLoader();
			~MeshLoader();

			bool load(const std::string&, mg::Mesh&, mg::Texture&);
	};
}

#endif //MESH_LOADER_HPP
