#pragma once

namespace finance::domain::value_objects {

class Money {
public:
    explicit Money(double amount);

    [[nodiscard]] double amount() const;

private:
    double amount_;
};

}  // namespace finance::domain::value_objects
