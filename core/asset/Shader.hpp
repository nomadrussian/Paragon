#ifndef SHADER_HPP
#define SHADER_HPP

#include "Asset.hpp"
#include "AssetManager.hpp"

class Shader : public Asset
{
    friend class AssetManager;
public:
    Shader();
    ~Shader();
private:
    bool loadFromData(const std::vector<uint8_t>& data) override;
    void unload();
    AssetType getType();
};

#endif // SHADER_HPP
