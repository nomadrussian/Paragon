#ifndef MESH_HPP
#define MESH_HPP

#include "Asset.hpp"
#include "AssetManager.hpp"

class Mesh : public Asset
{
    friend class AssetManager;
public:
    Mesh();
    ~Mesh();
private:
    bool loadFromData(const std::vector<uint8_t>& data) override;
    void unload();
    AssetType getType();
};

#endif // MESH_HPP
