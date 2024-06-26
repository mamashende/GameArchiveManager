#include <string>
#include <windows.h>
#include <ShlObj.h>
#include <iostream>

#include "comReader.h"
#include "fileUtils.h"
#include "MyExpection.h"

st_time::st_time()
{
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto lt = std::localtime(&time);

        year = lt->tm_year + 1900;
        month = lt->tm_mon + 1; // 月份从0开始计算，所以需要加上1
        day = lt->tm_mday;
        hour = lt->tm_hour;
        minute = lt->tm_min;
        second = lt->tm_sec;
}
////////////////////////////////////////

void fileUtils::saveLog()
{
    infofile.open(infopath,std::ios::out|std::ios::binary);
    infofile.write(reinterpret_cast<char*>(infos.data()),sizeof(inform)*infos.size());
    infofile.close();
}

void fileUtils::save(inform info)
{
    fs::path newArchpath = crrpath;
    newArchpath.append("Archive"+std::to_string(infos.size()));
    fs::create_directories(newArchpath);
    fs::copy(datapath,newArchpath,fs::copy_options::recursive);
    infos.push_back(info);
    saveLog();
}

void fileUtils::delArchive(int index)
{
    fs::path p=crrpath;
    p.append("Archive"+std::to_string(index));
    try {
        fs::remove_all(p);
        fs::path old;
        while(index<(int)(infos.size()-1))
        {
            old=crrpath;
            old.append("Archive"+std::to_string(index+1));
            fs::rename(old,p);
            p=old;
            index++;
        }
        infos.erase(infos.begin()+index);
        saveLog();
    } catch (const std::filesystem::filesystem_error& e) {
        std::cout<<e.what()<<std::endl;
        throw MyExpection("未能删除存档");
    }
}

void fileUtils::loadArchive(int index)
{
    try
    {
        fs::remove_all(datapath);
        fs::create_directories(datapath);
        fs::path p=crrpath;
        p.append("Archive"+std::to_string(index));
        fs::copy(p,datapath,fs::copy_options::recursive);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        throw MyExpection("读档失败");
    }
}

double fileUtils::getUsageSpace()
{
    std::uintmax_t size = 0;

    for (const auto& entry : fs::recursive_directory_iterator(crrpath))
        if (fs::is_regular_file(entry))
            size += fs::file_size(entry);

    return static_cast<double>(size) / (1024 * 1024);
}

///////////////////////////////////////
fileUtils::fileUtils()
{
    char path[MAX_PATH];
    std::string line;
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
        throw MyExpection("无法找到文件夹");
    datapath.assign(path);
    if (!fs::exists(datapath))
        throw MyExpection("无法找到文件夹");
    std::fstream file("path.txt",std::fstream::in);
    if (file.is_open()) {
    // 文件已成功打开，可以进行读取操作
    
    // 读取文件内容的代码
    std::getline(file, line);
    // 关闭文件
    file.close();
}
    datapath=datapath.parent_path().append(line);
    //datapath=datapath.parent_path().append("D:\\GAME\\The.Binding.of.Isaac.Afterbirth.Plus.With.Update.6.CHS.3.0-ALI213-22099\\The Binding of Isaac Rebirth\\Profile\\ALI213\\Saves");
    if (!fs::exists(datapath))
        throw MyExpection("无法找到存档文件夹  请检查是否安装");
    crrpath=fs::current_path();
    crrpath.append("Archive");
    fs::create_directory(crrpath);

    infopath=crrpath;
    infopath.append("information.log");
    if (!fs::exists(infopath))
    {
        std::fstream f(infopath,std::ios::out);
        if (!f.is_open())
            throw MyExpection("创建日志文件失败");
        f.close();
    }
    else{
        infofile.open(infopath,std::ios::in|std::ios::binary);
        if (!infofile.is_open())
            throw MyExpection("打开日志文件失败");

        infofile.seekg(0, std::ios::end);
        size_t file_size = infofile.tellg();
        if (file_size)
        {
            infofile.seekg(0,std::ios::beg);
            infos=std::vector <inform> (file_size/sizeof(inform));
            try
            {
                infofile.read(reinterpret_cast<char*>(infos.data()),file_size);
            }
            catch(const std::exception& e)
            {
                throw MyExpection("读取日志文件失败(Archive文件夹下的information.log损坏)");
            }
        }
        infofile.close();
    }
}

fileUtils::~fileUtils()
{
}
