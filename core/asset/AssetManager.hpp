#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <common/Singleton.hpp>
#include <util/Log.hpp>

class AssetManager : public Singleton<AssetManager>
{

public:

protected:
    AssetManager();
    ~AssetManager();

private:
    const Asset* findByID(AssetID ID) const;
    const Asset* findByPath(const std::string& filePath) const;
};

#endif // ASSETMANAGER_HPP
