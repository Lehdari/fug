#ifndef BINARY_INIT_FILE_HPP
#define BINARY_INIT_FILE_HPP

#include <cstdio>
#include <string>

#include "Core/ResourceInitInfoMap.hpp"
#include "Core/ResourceManager.hpp"

namespace fug {
    struct BinaryInitInfo_File  {
        std::string fileName;
    };

    FUG_RESOURCE_INITINFO_INIT(Binary, BinaryInitInfo_File)
    {
        std::string fileName = json["fileName"];
        initInfo.fileName = std::string(FUG_RES_DIRECTORY) + fileName;
    }

    FUG_RESOURCE_INIT(Binary, BinaryInitInfo_File) {
        FILE *fp = fopen(initInfo.fileName.c_str(), "rb");
        if (!fp) {
            throw "Binary: open failed";
        }
        if (fseek(fp, 0, SEEK_END) < 0) {
            fclose(fp);
            throw "Binary: fseek failed";
        }
        size_ = ftell(fp);
        if (fseek(fp, 0, SEEK_SET) < 0) {
            fclose(fp);
            throw "Binary: fseek failed";
        }
        buffer_ = new unsigned char[size_ + 1];
        if (fread(buffer_, 1, size_, fp) < size_) {
            fclose(fp);
            throw "Binary: read failed";
        }
        buffer_[size_] = '\0';
    }

    FUG_RESOURCE_DESTROY(Binary, BinaryInitInfo_File) {
        if (buffer_) {
            delete[] buffer_;
            buffer_ = nullptr;
            size_ = 0;
        }
    }
}

#endif // BINARY_INIT_FILE_HPP
