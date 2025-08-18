#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <external/include/stb_image.h>
#include <util/Log.hpp>

#include "AssetManager.hpp"

Texture::Texture(const std::string& filePath) : Asset(filePath)
{
    rawData = AssetManager::getInstance().loadRawDataFromDisk(filePath);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
    glDeleteVertexArrays(1, &textureVAO);
    glDeleteBuffers(1, &textureVBO);
    textureID = 0;
    textureVAO = 0;
    textureVBO = 0;
}

glm::vec4 Texture::getNormalizedCoordinates(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
{
    return glm::vec4(
        static_cast<float>(topLeftX) / textureWidth,
        static_cast<float>(topLeftY) / textureHeight,
        static_cast<float>(bottomRightX) / textureWidth,
        static_cast<float>(bottomRightY) / textureHeight
    );
}

bool Texture::loadData()
{
    int textureWidth, textureHeight, textureChannels;
    stbi_uc* data = stbi_load_from_memory(rawData.data(), rawData.size(), &textureWidth, &textureHeight, &textureChannels, 3);
    if (!data)
    {
        log_error("Failed to parse font atlas texture");
        return false;
    }

    glGenBuffers(1, &textureVBO);
    glGenVertexArrays(1, &textureVAO);
    glBindVertexArray(textureVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW); // 6 vertices for a squad
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    return true;
}

AssetType Texture::getType() const
{
    return AssetType::Texture;
}


GLuint Texture::getTextureID() const
{
    return textureID;
}

GLuint Texture::getVBO() const
{
    return textureVBO;
}

GLuint Texture::getVAO() const
{
    return textureVAO;
}
