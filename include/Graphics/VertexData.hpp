#ifndef FUG_GRAPHICS_VERTEXDATA_HPP
#define FUG_GRAPHICS_VERTEXDATA_HPP

#include <GL/glew.h>
#include <Core/Resource.hpp>

#include <vector>
#include <array>


namespace fug {

    //  Resource
    class FUG_RESOURCE(VertexData) {
    public:
        //  Resource init and destroy template member function declarations
        FUG_RESOURCE_INIT_DESTROY_DECL
        VertexData(void);

        bool usesTextureCoordinates(void) const;
        bool usesNormals(void) const;
        bool usesIndexing(void) const;

        const std::vector<std::array<float, 4>>& getPositions(void) const;
        const std::vector<std::array<float, 3>>& getTextureCoordinates(void) const;
        const std::vector<std::array<float, 3>>& getNormals(void) const;
        const std::vector<unsigned>& getIndices(void) const;

    private:
        bool usingTexCoords_;
        bool usingNormals_;
        bool usingIndexing_;

        std::vector<std::array<float, 4>> positions_;
        std::vector<std::array<float, 3>> texCoords_;
        std::vector<std::array<float, 3>> normals_;
        std::vector<unsigned> indices_;
    };

} // namespace fug 


#endif // FUG_GRAPHICS_VERTEXDATA_HPP
