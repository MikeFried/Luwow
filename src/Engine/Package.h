#pragma once

#include <string>
#include <vector>

namespace Luwow::Engine {

class Package {
public:
    Package();
    ~Package();

    void addFile(const std::string& filePath, const std::string& content);
    std::string getFile(const std::string& filePath);

    int indexOfFile(const std::string& filePath);
    int getFileCount();
    std::string getFileName(int index);
    std::string getFileContent(int index);

    bool load(const std::string& packagePath);
    bool save(const std::string& packagePath);

private:
    std::string packagePath;
    std::vector<std::string> fileNames;
    std::vector<std::string> fileContents;
};

} // namespace Luwow::Engine