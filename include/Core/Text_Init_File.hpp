#ifndef TEXT_INIT_FILE_HPP
#define TEXT_INIT_FILE_HPP

#include <cstdio>
#include <string>

#include "Core/JsonUtility.hpp"
#include "Core/ResourceInitInfoMap.hpp"

namespace fug {
    struct TextInitInfo_File  {
        std::string fileName;
    };

    FUG_RESOURCE_INITINFO_INIT(Text, TextInitInfo_File)
    {
        // Check that keys are valid
        assertJsonValidity("TextInitInfo_File", json, {"type", "fileName"}, {"fileName"});

        // Parse fields
        std::string fileName = json["fileName"];
        initInfo.fileName = std::string(FUG_RES_DIRECTORY) + fileName;
    }

    FUG_RESOURCE_INIT(Text, TextInitInfo_File) {
        // Open file
        FILE *fp = fopen(initInfo.fileName.c_str(), "rb");
        if (!fp) {
            FUG_LOG(LogLevel::Error)("TextInitInfo_File: fopen failed\n");
            FUG_LOG(LogLevel::Error)("File: %s\n", initInfo.fileName.c_str());
            FUG_LOG(LogLevel::Error)("Error: %s\n", strerror(errno));
            throw;
        }
        // Get size of file
        int err = 0;
        if ((err = fseek(fp, 0, SEEK_END)) < 0) {
            fclose(fp);
            FUG_LOG(LogLevel::Error)("TextInitInfo_File: fseek SEEK_END failed\n");
            FUG_LOG(LogLevel::Error)("File: %s\n", initInfo.fileName.c_str());
            FUG_LOG(LogLevel::Error)("Error: %s\n", strerror(errno));
            throw;
        }
        size_ = ftell(fp);
        // Reset file pointer to start of file
        if ((err = fseek(fp, 0, SEEK_SET)) < 0) {
            fclose(fp);
            FUG_LOG(LogLevel::Error)("TextInitInfo_File: fseek SEEK_SET failed\n");
            FUG_LOG(LogLevel::Error)("File: %s\n", initInfo.fileName.c_str());
            FUG_LOG(LogLevel::Error)("Error: %s\n", strerror(errno));
            throw;
        }
        // Read file
        buffer_ = new char[size_ + 1];
        size_t ret;
        if ((ret = fread(buffer_, 1, size_, fp)) < size_) {
            fclose(fp);
            FUG_LOG(LogLevel::Error)("TextInitInfo_File: fread failed\n");
            FUG_LOG(LogLevel::Error)("File: %s\n", initInfo.fileName.c_str());
            FUG_LOG(LogLevel::Error)("Read: %i of %i bytes\n", ret, size_);
            throw;
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
