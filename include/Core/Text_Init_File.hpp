#ifndef TEXT_INIT_FILE_HPP
#define TEXT_INIT_FILE_HPP

#include <cstdio>
#include <string>

namespace fug {
    struct TextInitInfo_File  {
        std::string fileName;
    };

    FUG_RESOURCE_INITINFO_INIT(Text, TextInitInfo_File)
    {
        std::string fileName = json["fileName"];
        initInfo.fileName = std::string(FUG_RES_DIRECTORY) + fileName;
    }

    FUG_RESOURCE_INIT(Text, TextInitInfo_File) {
        FILE *fp = fopen(initInfo.fileName.c_str(), "rb");
        if (!fp) {
            throw "Text: open failed";
        }
        if (fseek(fp, 0, SEEK_END) < 0) {
            fclose(fp);
            throw "Text: fseek failed";
        }
        size_ = ftell(fp);
        if (fseek(fp, 0, SEEK_SET) < 0) {
            fclose(fp);
            throw "Text: fseek failed";
        }
        buffer_ = new char[size_ + 1];
        if (fread(buffer_, 1, size_, fp) < size_) {
            fclose(fp);
            throw "Text: read failed";
        }
        buffer_[size_] = '\0';
    }

    FUG_RESOURCE_DESTROY(Text, TextInitInfo_File) {
        if (buffer_) {
            delete[] buffer_;
            buffer_ = nullptr;
            size_ = 0;
        }
    }
}

#endif // TEXT_INIT_FILE_HPP
