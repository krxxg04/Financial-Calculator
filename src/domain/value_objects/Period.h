#pragma once

namespace finance {
namespace domain {
namespace value_objects {

class Period {
public:
    explicit Period(int value);

    int value() const;

private:
    int value_;
};

}  // namespace value_objects
}  // namespace domain
}  // namespace finance
