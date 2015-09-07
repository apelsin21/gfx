#include "gfx/mesh_loader.hpp"

mg::MeshLoader::MeshLoader() {
}
mg::MeshLoader::~MeshLoader() {
}

bool mg::MeshLoader::load(const std::string& path, mg::Mesh& out_mesh, mg::Texture& out_texture) {
	if(path.empty()) {
		printf("tried to load mesh from empty path.\n");
		return false;
	}

	const aiScene* scene = _importer.ReadFile(
		path.c_str(),
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
	);

	if(!scene) {
		printf("error loading mesh %s: %s\n", path.c_str(), _importer.GetErrorString());
		return false;
	}

	return true;
}
