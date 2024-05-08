#pragma once
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
/*
    This class is for loading different type of resources; texture, sound, spritesheet, tilesheet etc.
    Source: Pupius, R. (2015) SFML Game Development By Example. Birmingham: Packt Publishing Ltd.
*/
template<typename Derived, typename T>
class ResourceManager {
public:
    ResourceManager(const std::string& cfgFile) {
        LoadFilePaths(cfgFile);
    }
    virtual ~ResourceManager() { ClearAllResources(); }

    //Get resource by id.
    T* GetResource(const std::string& resId) {
        auto res = Find(resId);
        return(res ? res->first : nullptr);
    }

    //Get resource path by id.
    std::string GetPath(const std::string& resId) {
        auto path = m_paths.find(resId);
        return(path != m_paths.end() ? path->second : "");
    }

    //Load specific resource using its id.
    bool AllocateResource(const std::string& resId) {
        //Does the resouce already exist?
        auto res = Find(resId);
        if (res) {
            ++res->second; //If yes, increment usage amount
            return true;
        }

        //Resource does not exist, get the path.
        auto path = m_paths.find(resId);
        if (path == m_paths.end())
            return false; //Path does not exist, allocation failed.

        T* resource = Load(path->second); //Load file.

        if (!resource)
            return false; //File load failed, return.

        //Insert loaded resource to the map.
        m_resources.emplace(resId, std::make_pair(resource, 1));
        return true;
    }

    //Release a specific resource using id.
    bool ReleaseResource(const std::string& resId) {
        if (m_resources.empty())
            return true;
        auto res = Find(resId);
        if (!res) //There isn't any instance of this to release.
            return false;

        --res->second; //Decrement usage amount.

        if (res->second == 0) //Is it still being used?
            Unload(resId); //If not, release it.

        return true;
    }

    //Delete everything.
    void ClearAllResources() {
        while (m_resources.begin() != m_resources.end()) {
            delete m_resources.begin()->second.first;
            m_resources.erase(m_resources.begin());
        }
    }

    //Override this method for type specific loading.
    virtual T* Load(const std::string& resPath) {
        return static_cast<Derived*>(this)->Load(resPath);
    }

private:
    // resource id - type - usage count
    std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
    // reource id - resource file path
    std::unordered_map<std::string, std::string> m_paths;


    std::pair<T*, unsigned int>* Find(const std::string& resId) {
        auto itr = m_resources.find(resId);
        return (itr == m_resources.end() ? nullptr : &itr->second);
    }

    bool Unload(const std::string& resId) {
        auto itr = m_resources.find(resId);

        if (itr == m_resources.end())
            return false;

        delete itr->second.first;
        m_resources.erase(itr);
        return true;
    }

    //Load resource item's name(id) and path from file.
    void LoadFilePaths(const std::string& filePath) {
        std::ifstream pathsFile;
        pathsFile.open("Game/Data/" + filePath);
        if (pathsFile.is_open()) {
            std::string line;
            while (std::getline(pathsFile, line)) {
                std::stringstream keystream(line);
                std::string reourceName;
                std::string resourcePath;
                keystream >> reourceName;
                keystream >> resourcePath;
                m_paths.emplace(reourceName, resourcePath);
            }
            pathsFile.close();
            return;
        }
    }
};