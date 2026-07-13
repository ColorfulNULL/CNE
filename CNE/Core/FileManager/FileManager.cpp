#include "FileManager.hpp"

cne::FileManager* cne::FileManager::instance_ = nullptr;

void cne::FileManager::WriteJson(std::string path, const Json& data, std::string name, int indent)
{
    std::ofstream ofs(path);
    Json root;
    root[name] = data;
    ofs << root.dump(indent);
}

void cne::FileManager::WriteJson(std::string path, const Json& data, int indent)
{
    std::ofstream ofs(path);
    ofs << data.dump(indent);
}

void cne::FileManager::ReadJson(std::string path, Json& outData, std::string name)
{
    std::ifstream ifs(path);
    Json root;
    ifs >> root;
    outData = root[name];
}

void cne::FileManager::ReadJson(std::string path, Json& outData)
{
    std::ifstream ifs(path);
    ifs >> outData;
}