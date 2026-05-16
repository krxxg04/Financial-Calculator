#pragma once

namespace finance::domain::value_objects {

class Period {
public:
    explicit Period(int value);

    [[nodiscard]] int value() const;

private:
    int value_;
};

}  // namespace finance::domain::value_objects
