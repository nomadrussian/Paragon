#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

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

#endif // MESHRESOURCE_H
