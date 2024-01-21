#include "ResourceLibary.h"

ResourceLibary::ResourceLibary()
{
    auto file = w4::filesystem::open("resources.json");
    auto json = nlohmann::json::parse(file->data(), file->data() + file->size());

    m_modelsDataPath = json.at("models").get<std::unordered_map<std::string, std::string>>();
    m_materialsDataPath = json.at("materials").get<std::unordered_map<std::string, std::string>>();
    m_texturesDataPath = json.at("textures").get<std::unordered_map<std::string, std::string>>();

    for (auto &[key, value] : m_modelsDataPath) {
        m_modelsData[key] = Asset::get(value);
    }
    for (auto &[key, value] : m_materialsDataPath) {
        m_materialsData[key] = Material::get(value);
    }
    for (auto &[key, value] : m_texturesDataPath) {
        if (value.substr(0, 2) != "Ui")
            m_texturesData[key] = Texture::get(value);
    }

    W4_LOG_DEBUG("[RESOURCE LIBARY] Loaded");
}

ResourceLibary::~ResourceLibary() {}