#pragma once

namespace finance::domain::value_objects {

class InterestRate {
public:
    explicit InterestRate(double rate);

    static InterestRate fromPercentage(double percent);

    [[nodiscard]] double rate() const;
    [[nodiscard]] double asPercentage() const;

private:
    double rate_;
};

}  // namespace finance::domain::value_objects
