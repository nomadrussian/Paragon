#ifndef SHADER_HPP
#define SHADER_HPP

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

#endif // SHADER_HPP
