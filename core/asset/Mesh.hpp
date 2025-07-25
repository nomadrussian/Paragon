#ifndef MESH_HPP
#define MESH_HPP

#include "Asset.hpp"

class Mesh : public Asset
{
    friend class AssetManager;
public:
    Mesh();
    ~Mesh();
private:
    bool loadFromData(const std::vector<uint8_t>& rawData) override;
    void unload() override;
    AssetType getType() const override;
};

#endif // MESH_HPP
