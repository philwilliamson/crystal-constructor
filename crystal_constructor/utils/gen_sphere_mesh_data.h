#ifndef GEN_SPHERE_MESH_DATA_H
#define GEN_SPHERE_MESH_DATA_H

#include <crystal_constructor/opengl_graphics/mesh_data.h>

namespace crystal_constructor{ namespace utils {

crystal_constructor::opengl_graphics::MeshData gen_sphere_mesh_data(float radius, int heightSegments, int widthSegments);

}} // generates params to create sphere mesh

#endif