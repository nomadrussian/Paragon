#ifndef SHADER_HPP
#define SHADER_HPP

#include "Asset.hpp"

class Shader : public Asset
{
    friend class AssetManager;
public:
    Shader();
    ~Shader();
private:
    bool loadFromData(const std::vector<uint8_t>& rawData) override;
    AssetType getType() const override;
};

#endif // SHADER_HPP
