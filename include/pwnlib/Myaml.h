#ifndef __YAML__
#define __YAML__

#include <iostream>
#include <string>
#include <vector>
#include <utility>          //std:move

#include <dirent.h>
#include <unistd.h>

#include "yaml-cpp/yaml.h"  //https://github.com/jbeder/yaml-cpp/wiki/Tutorial
#include "print.h"

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
    M_Yaml(string path):config_path(path){}
    vector<string>& get_config_file() { return this->config_file;}
    inline bool load_all_files();               //load file in config_path
    inline bool load_all_files(string& path);   //load file    
    inline void set_path(string&& path);        // set the config path (std::move(path))
    inline void set_path(string& path);         // set the config path
    inline string get_owner_path();             //get the bin's path
    inline string get_execu_path();             //get the execute path
    inline string get_config_file_path(int index);           //get config file path
    inline string get_config_file_path(string file_name);    //get config file path
    inline void load_file_();

private:
    string config_path {"config/"};
    string config_file_path;
    vector<string> config_file;
};

 inline void M_Yaml::load_file_()
 {
    YAML::Node config = YAML::LoadFile(config_file_path);
    cout << "import:" << config["import"].as<string>() << endl;
    cout << "context:" << config["context"].as<string>() << endl;
    cout << "lambda:" << config["lambda"].as<int>() << endl;
 }

inline string M_Yaml::get_config_file_path(int index)
{
    int i{1};
    for(auto iter : config_file)
    {
        if(i < index)
            i++;
        else if(i == index)
        {
            config_file_path = this->config_path+iter; 
            return (config_file_path );
        }

    }
    Print out;
    out.color_(B_RED);
    out.out_("Load config Error! using Default.conf now...");
    config_file_path = this->config_path+string("Default.yaml");
    return (config_file_path);
}

inline string M_Yaml::get_config_file_path(string file_name)
{
    for(auto iter : config_file)
    {
        if(iter == file_name)
        {
            config_file_path = this->config_path+iter; 
            return (config_file_path );
        }
    }
    Print out;
    out.color_(B_RED);
    out.out_(file_name+" not found! using Default.conf now...");
    config_file_path = this->config_path+string("Default.yaml");
    return (this->config_path+string("Default.yaml"));
}

inline bool M_Yaml::load_all_files(string& path)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if((dir = opendir(path.c_str())) == NULL)
    {
        Print out;
        out.color_(B_RED);
        out.out_("[*] Config dir not found ...");
        return false;
    }

    while((ptr = readdir(dir)) != NULL)
    {
        if(string(ptr->d_name) == string(".") || string(ptr->d_name) == string(".."))
            continue;
        else if(ptr->d_type == 8)
            config_file.push_back(string(ptr->d_name));
    }
    return true;
}

inline bool M_Yaml::load_all_files()
{
    return load_all_files(config_path);
}

inline void M_Yaml::set_path(string&& path)
{
    this->config_path = path;
}


inline void M_Yaml::set_path(string& path)
{
    this->config_path = path;
}

inline string M_Yaml::get_owner_path()
{
    char path[1024];
    int cnt = readlink("/proc/self/exe", path ,1024);
    if (cnt < 0 || cnt >=1024 )
    {
        return NULL;
    }
    for(int i =cnt ; i >= 0 ;--i)
    {
        if(path[i] == '/')
        {
            path[i + 1] ='\0';
            break; 
        }
    }
    string s_path(path+string("config/"));
    set_path( std::move(s_path) ) ;
    return s_path;
} 
inline string M_Yaml::get_execu_path()
{
    char path[1024];
    getcwd (path ,sizeof(path));
    string s_path(path);
    s_path += string("/config/");
    set_path( std::move(s_path) ) ;    
    return s_path;
} 

#endif
