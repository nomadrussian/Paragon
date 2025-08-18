#ifndef MESH_HPP
#define MESH_HPP

#include "Asset.hpp"

class Mesh : public Asset
{
    friend class AssetManager;
public:
    Mesh(const std::string& filePath);
    ~Mesh();

private:
    bool loadData() override;
    AssetType getType() const override;
};

#endif // MESH_HPP
