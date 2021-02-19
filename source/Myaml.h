#ifndef __YAML__
#define __YAML__

#include <iostream>
#include <string>
#include"yaml-cpp/yaml.h" //https://github.com/jbeder/yaml-cpp/wiki/Tutorial

using namespace std;

class M_Yaml
{
public:
    M_Yaml()
    {
        /*
        YAML::Node config = YAML::LoadFile("config/config.yaml");
        cout << "name:" << config["name"].as<string>() << endl;
        cout << "sex:" << config["sex"].as<string>() << endl;
        cout << "age:" << config["age"].as<int>() << endl;
        */
    }
    inline void show_all_files();

private:
    string config_path {"config/"};
};

inline void M_Yaml::show_all_files()
{

}


#endif
