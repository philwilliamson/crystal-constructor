#include <crystal_constructor/utils/gen_sphere_mesh_data.h>

namespace crystal_constructor{ namespace utils {

crystal_constructor::opengl_graphics::MeshData gen_sphere_mesh_data(float radius, int heightSegments, int widthSegments)
{
    crystal_constructor::opengl_graphics::MeshData sphereMeshData{};

    float thetaDiff{glm::radians(180.0f / (float)heightSegments)};
    float phiDiff{glm::radians(360.0f / (float)widthSegments)};
    int vertexCount = 0;

    // top cap
    for (int widthIdx = 0; widthIdx < widthSegments; widthIdx++)
    {
        crystal_constructor::opengl_graphics::Vertex vert0{glm::vec3{0.0f, radius, 0.0f}};
        crystal_constructor::opengl_graphics::Vertex vert1{glm::vec3{
            radius * glm::sin(thetaDiff) * glm::sin(phiDiff * widthIdx),
            radius * glm::cos(thetaDiff),
            radius * glm::sin(thetaDiff) * glm::cos(phiDiff * widthIdx)
        }};
        crystal_constructor::opengl_graphics::Vertex vert2{glm::vec3{
            radius * glm::sin(thetaDiff) * glm::sin(phiDiff * (widthIdx + 1)),
            radius * glm::cos(thetaDiff),
            radius * glm::sin(thetaDiff) * glm::cos(phiDiff * (widthIdx + 1))
        }};

        vert0.normal = glm::normalize(vert0.position);
        vert1.normal = glm::normalize(vert1.position);
        vert2.normal = glm::normalize(vert2.position);

        sphereMeshData.vertices.push_back(vert0);
        sphereMeshData.vertices.push_back(vert1);
        sphereMeshData.vertices.push_back(vert2);

        sphereMeshData.indices.push_back(vertexCount);
        sphereMeshData.indices.push_back(vertexCount + 1);
        sphereMeshData.indices.push_back(vertexCount + 2);
        
        vertexCount += 3;
    }
    
    
    // in between layers
    for (int heightIdx = 1; heightIdx < (heightSegments - 1); heightIdx++)
    {
        for (int widthIdx = 0; widthIdx < widthSegments; widthIdx++)
        {
            crystal_constructor::opengl_graphics::Vertex vert0{glm::vec3{
                radius * glm::sin(thetaDiff * (heightIdx)) * glm::sin(phiDiff * (widthIdx)),
                radius * glm::cos(thetaDiff * (heightIdx)),
                radius * glm::sin(thetaDiff * (heightIdx)) * glm::cos(phiDiff * (widthIdx))
            }};
            crystal_constructor::opengl_graphics::Vertex vert1{glm::vec3{
                radius * glm::sin(thetaDiff * (heightIdx + 1)) * glm::sin(phiDiff * (widthIdx)),
                radius * glm::cos(thetaDiff * (heightIdx + 1)),
                radius * glm::sin(thetaDiff * (heightIdx + 1)) * glm::cos(phiDiff * (widthIdx))
            }};
            crystal_constructor::opengl_graphics::Vertex vert2{glm::vec3{
                radius * glm::sin(thetaDiff * (heightIdx + 1)) * glm::sin(phiDiff * (widthIdx + 1)),
                radius * glm::cos(thetaDiff * (heightIdx + 1)),
                radius * glm::sin(thetaDiff * (heightIdx + 1)) * glm::cos(phiDiff * (widthIdx + 1))
            }};
            crystal_constructor::opengl_graphics::Vertex vert3{glm::vec3{
                radius * glm::sin(thetaDiff * (heightIdx)) * glm::sin(phiDiff * (widthIdx + 1)),
                radius * glm::cos(thetaDiff * (heightIdx)),
                radius * glm::sin(thetaDiff * (heightIdx)) * glm::cos(phiDiff * (widthIdx + 1))
            }};

            // glm::vec3 normal{glm::cross(glm::vec3(vert1.position - vert0.position), glm::vec3(vert3.position - vert0.position))};
            vert0.normal = glm::normalize(vert0.position);
            vert1.normal = glm::normalize(vert1.position);
            vert2.normal = glm::normalize(vert2.position);
            vert3.normal = glm::normalize(vert3.position);

            sphereMeshData.vertices.push_back(vert0);
            sphereMeshData.vertices.push_back(vert1);
            sphereMeshData.vertices.push_back(vert2);
            sphereMeshData.vertices.push_back(vert3);

            sphereMeshData.indices.push_back(vertexCount);
            sphereMeshData.indices.push_back(vertexCount + 1);
            sphereMeshData.indices.push_back(vertexCount + 2);
            sphereMeshData.indices.push_back(vertexCount + 2);
            sphereMeshData.indices.push_back(vertexCount + 3);
            sphereMeshData.indices.push_back(vertexCount);
            
            vertexCount += 4;
        }
        
    }

    // bottom cap
    for (int widthIdx = 0; widthIdx < widthSegments; widthIdx++)
    {
        crystal_constructor::opengl_graphics::Vertex vert0{glm::vec3{0.0f, -1.0f * radius, 0.0f}};
        crystal_constructor::opengl_graphics::Vertex vert1{glm::vec3{
            radius * glm::sin(thetaDiff * (heightSegments - 1)) * glm::sin(phiDiff * (widthIdx + 1)),
            radius * glm::cos(thetaDiff * (heightSegments - 1)),
            radius * glm::sin(thetaDiff * (heightSegments - 1)) * glm::cos(phiDiff * (widthIdx + 1))
        }};
        crystal_constructor::opengl_graphics::Vertex vert2{glm::vec3{
            radius * glm::sin(thetaDiff * (heightSegments - 1)) * glm::sin(phiDiff * widthIdx),
            radius * glm::cos(thetaDiff * (heightSegments - 1)),
            radius * glm::sin(thetaDiff * (heightSegments - 1)) * glm::cos(phiDiff * widthIdx)
        }};

        glm::vec3 normal{glm::cross(glm::vec3(vert1.position - vert0.position), glm::vec3(vert2.position - vert0.position))};
        vert0.normal = glm::normalize(vert0.position);
        vert1.normal = glm::normalize(vert1.position);
        vert2.normal = glm::normalize(vert2.position);

        sphereMeshData.vertices.push_back(vert0);
        sphereMeshData.vertices.push_back(vert1);
        sphereMeshData.vertices.push_back(vert2);

        sphereMeshData.indices.push_back(vertexCount);
        sphereMeshData.indices.push_back(vertexCount + 1);
        sphereMeshData.indices.push_back(vertexCount + 2);
        
        vertexCount += 3;
    }

    return sphereMeshData;
}

}} // generates params to create sphere mesh