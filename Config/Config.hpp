#include "../utils/Features.hpp"
#include <fstream>
#include <string>
#include <filesystem>

inline std::string filepath[3] = { "Legit", "Rage", "Custom" };
inline void AddItem(bool value, std::string name, std::ofstream file)
{
    file << name << " : " << (value ? "on" : "off") << "\n";
}
inline void LoadItem(bool& value, std::string name, std::ifstream file) {
    std::string data;
    while (std::getline(file, data))
    {
        if (data.find(name.c_str()) != std::string::npos)
        {
            if (data.find("1"))
                value = true;
        }
    }
}
inline bool CreateConfig()
{
    return true;
}

inline bool SaveConfig()
{
    return true;

}


inline bool LoadConfig()
{
    return true;

}
