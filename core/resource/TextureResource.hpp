#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Asset.hpp"

class Texture : public Asset
{
    friend class AssetManager;
private:
    std::vector<uint8_t> rawData;
    GLuint textureID = 0;
    GLuint textureVBO = 0;
    GLuint textureVAO = 0;
    GLuint textureWidth = 1;
    GLuint textureHeight = 1;

public:
    Texture(const std::string& filePath);
    ~Texture();

    GLuint getTextureID() const;
    GLuint getVBO() const;
    GLuint getVAO() const;

    // returns normilized OpenGL coordinates: { topLeftUVX, topLeftUVY, bottomRightUVX, bottomRightUVY } in range [ 0.0f; 1.0f ]
    glm::vec4 getNormalizedCoordinates(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);

private:
    bool loadData() override;
    AssetType getType() const override;
};

#endif // TEXTURERESOURCE_H
