//
// Project: fug
// File: Serialization.hpp
//
// Copyright (c) 2020 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ENGINE_SERIALIZATION_HPP
#define FUG_ENGINE_SERIALIZATION_HPP


#include <stdexcept>
#include <rapidjson/document.h>


#define FUG_SERIALIZE(SERIALIZATION, OBJECT) \
    (SERIALIZATION).serialize(OBJECT, #OBJECT)

#define FUG_SERIALIZE_RECURSIVE(OBJECT) \
    this->serialize(value, obj.OBJECT, #OBJECT)

#define FUG_SERIALIZE_CREATE_OBJECT \
    rapidjson::Value value; \
    value.SetObject()

#define FUG_SERIALIZE_WRITE_OBJECT \
    jsonHandle.AddMember(rapidjson::Value().SetString(objName, _jsonAlloc), value, _jsonAlloc)

#define FUG_SERIALIZATION_IMPLEMENTATION(TYPE) \
    template<> \
    void fug::Serialization::serialize<TYPE>( \
        rapidjson::Value& jsonHandle, const TYPE& obj, const char* objName)


namespace fug {

    class Serialization {
    public:
        Serialization();

        rapidjson::Document& getDocument();

        void saveToFile(const std::string& filename) const;

        template<typename T_Object>
        void serialize(rapidjson::Value& jsonHandle, const T_Object& obj, const char* objName)
        {
            jsonHandle.AddMember(rapidjson::Value().SetString(objName, _jsonAlloc), obj, _jsonAlloc);
        }

        template<typename T_Object>
        void serialize(const T_Object& obj, const char* objName)
        {
            serialize(_document, obj, objName);
        }

    private:
        rapidjson::Document                 _document;
        rapidjson::MemoryPoolAllocator<>    _jsonAlloc;
    };

    FUG_SERIALIZATION_IMPLEMENTATION(std::string);

} // namespace fug


#endif //FUG_ENGINE_SERIALIZATION_HPP
