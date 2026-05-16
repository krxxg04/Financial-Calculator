#pragma once

namespace finance {
namespace domain {
namespace value_objects {

class InterestRate {
public:
    explicit InterestRate(double rate);

    static InterestRate fromPercentage(double percent);

    double rate() const;
    double asPercentage() const;

private:
    double rate_;
};

}  // namespace value_objects
}  // namespace domain
}  // namespace finance
