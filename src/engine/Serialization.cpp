//
// Project: fug
// File: Serialization.cpp
//
// Copyright (c) 2020 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include "Serialization.hpp"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


fug::Serialization::Serialization()
{
    _document.SetObject();
}

rapidjson::Document& fug::Serialization::getDocument()
{
    return _document;
}

void fug::Serialization::saveToFile(const std::string& filename) const
{
    rapidjson::StringBuffer stringBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
    _document.Accept(writer);

    FILE* f = fopen(filename.c_str(), "w");
    fprintf(f, "%s", stringBuffer.GetString());
    fclose(f);
}

FUG_SERIALIZATION_IMPLEMENTATION(std::string)
{
    jsonHandle.AddMember(
        rapidjson::Value().SetString(objName, _jsonAlloc),
        rapidjson::Value().SetString(obj.c_str(), _jsonAlloc),
        _jsonAlloc);
}
