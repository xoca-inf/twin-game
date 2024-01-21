#pragma once
#include "W4Framework.h"
#include "SettingsContainer.h"

W4_USE_UNSTRICT_INTERFACE

class ResourceLibary {
public:
    static ResourceLibary& instance() {
        static ResourceLibary instance;
        return instance;
    }

    ResourceLibary();
    virtual ~ResourceLibary();

    sptr<Asset>        getModel(const std::string& key)        { return m_modelsData[key];}
    sptr<Material>     getMaterial(const std::string& key)     { return m_materialsData[key];}
    sptr<Texture>      getTexture(const std::string& key)      { return m_texturesData[key];}

    std::string       getModelPath(const std::string& key)     { return m_modelsDataPath[key];}
    std::string       getMaterialPath(const std::string& key)  { return m_materialsDataPath[key];}
    std::string       getTexturePath(const std::string& key)   { return m_texturesDataPath[key];}

private:
    std::unordered_map<std::string, std::string>  m_modelsDataPath;
    std::unordered_map<std::string, std::string>  m_materialsDataPath;
    std::unordered_map<std::string, std::string>  m_texturesDataPath;

    std::unordered_map<std::string, sptr<Asset>>  m_modelsData;
    std::unordered_map<std::string, sptr<Material>>  m_materialsData;
    std::unordered_map<std::string, sptr<Texture>>  m_texturesData;

    SettingsContainer<std::string>huy;
};