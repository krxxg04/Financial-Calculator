#pragma once

namespace finance {
namespace domain {
namespace value_objects {

class Money {
public:
    explicit Money(double amount);

    double amount() const;

private:
    double amount_;
};

}  // namespace value_objects
}  // namespace domain
}  // namespace finance
