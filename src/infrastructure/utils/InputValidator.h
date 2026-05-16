#pragma once

#include <string>

namespace finance {
namespace infrastructure {
namespace utils {

class InputValidator {
public:
    static double readDouble(const std::string& prompt);
    static double readPositiveDouble(const std::string& prompt, bool allowZero = false);
    static int readPositiveInt(const std::string& prompt);
    static int readIntInRange(const std::string& prompt, int min, int max);

private:
    static bool tryParseDouble(const std::string& text, double& value);
    static bool tryParseInt(const std::string& text, int& value);
};

}  // namespace utils
}  // namespace infrastructure
}  // namespace finance
