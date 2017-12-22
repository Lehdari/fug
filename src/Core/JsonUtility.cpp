#include "Core/JsonUtility.hpp"

#include "Core/Log.hpp"

void fug::assertJsonValidity(const std::string& type, const nlohmann::json& json,
                             const std::unordered_set<std::string>& validKeys,
                             const std::vector<std::string>& requiredKeys)
{
    // Check that all keys are valid
    for (auto it = json.begin(); it != json.end(); it++) {
        if (validKeys.find(it.key()) == validKeys.end()) {
            FUG_LOG(LogLevel::Error)("%s: invalid key '%s'\n", type.c_str(), it.key().c_str());
            throw;
        }
    }

    // Check that all required keys are present
    for (auto& key : requiredKeys) {
        if (json.find(key) == json.end()) {
            FUG_LOG(LogLevel::Error)("%s: required key '%s' not found\n", type.c_str(), key.c_str());
            FUG_LOG(LogLevel::Error)("%s\n", json.dump(2).c_str());
            throw;
        }
    }
}
