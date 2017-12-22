#ifndef FUG_CORE_JSON_UTILITY_HPP
#define FUG_CORE_JSON_UTILITY_HPP

#include <unordered_set>
#include <json/json.hpp>

namespace fug {

// Checks that given json doesn't have invalid keys and contains all required keys
// Potential errors are printed to FUG_LOG(LogLevel::Error) and result in a throw
void assertJsonValidity(const std::string& type, const nlohmann::json& json,
                        const std::unordered_set<std::string>& validKeys,
                        const std::vector<std::string>& requiredKeys);

}

#endif // FUG_CORE_JSON_UTILITY_HPP
