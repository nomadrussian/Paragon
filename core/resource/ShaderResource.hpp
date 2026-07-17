#ifndef SHADERRESOURCE_H
#define SHADERRESOURCE_H

#include "Asset.hpp"

class Shader : public Asset
{
    friend class AssetManager;
public:
    Shader(const std::string& filePath);
    ~Shader();

private:
    bool loadData() override;
    AssetType getType() const override;
};

#endif // SHADERRESOURCE_H
