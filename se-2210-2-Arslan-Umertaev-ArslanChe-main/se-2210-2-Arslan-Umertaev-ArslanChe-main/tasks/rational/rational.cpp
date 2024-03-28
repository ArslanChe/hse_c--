#include <rational.h>

Rational::Rational(int numer, int denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    Set(numer, denom);
};

Rational::Rational(int value) : numer_(value), denom_(1) {
}
Rational::Rational() : numer_(0), denom_(1) {
}
int Rational::GetNumerator() const {
    return numer_;
}
int Rational::GetDenominator() const {
    return denom_;
}

[[maybe_unused]] void Rational::SetNumerator(int value) {
    numer_ = value;
    auto gcd = std::gcd(numer_, denom_);

    numer_ = static_cast<int>(numer_ / gcd);
    denom_ = static_cast<int>(denom_ / gcd);
    if (denom_ < 0) {
        denom_ *= -1;
        numer_ *= -1;
    }
}
[[maybe_unused]] void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero();
    }
    denom_ = value;
    auto gcd = std::gcd(numer_, denom_);

    numer_ = static_cast<int>(numer_ / gcd);
    denom_ = static_cast<int>(denom_ / gcd);
    if (denom_ < 0) {
        denom_ *= -1;
        numer_ *= -1;
    }
}
void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero();
    }
    auto gcd = std::gcd(numer, denom);

    numer_ = static_cast<int>(numer / gcd);
    denom_ = static_cast<int>(denom / gcd);
    if (denom_ < 0) {
        denom_ *= -1;
        numer_ *= -1;
    }
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t lcm = std::lcm(lhs.denom_, rhs.denom_);
    int64_t numerator = (lhs.numer_ * (lcm / lhs.denom_)) + (rhs.numer_ * (lcm / rhs.denom_));
    lhs.Set(numerator, lcm);
    return lhs;
}
Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += (-rhs);
}

Rational& operator++(Rational& ratio) {
    ratio += Rational(1);
    return ratio;
}
Rational& operator--(Rational& ratio) {
    ratio -= Rational(1);
    return ratio;
}

Rational operator++(Rational& ratio, int) {
    Rational ans = ratio;
    ++ratio;
    return ans;
}
Rational operator--(Rational& ratio, int) {
    Rational ans = ratio;
    --ratio;
    return ans;
}

Rational operator+(const Rational& ratio) {
    return ratio;
}
Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational ans = lhs;
    ans += rhs;
    return ans;
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational ans = lhs;
    ans -= rhs;
    return ans;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational ans = lhs;
    ans *= rhs;
    return ans;
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational ans = lhs;
    ans /= rhs;
    return ans;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.numer_, lhs.denom_ * rhs.denom_);
    return lhs;
}
Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero();
    }
    lhs = Rational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
    return lhs;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    int64_t lcm = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    return lhs.GetNumerator() * (lcm / lhs.GetDenominator()) < rhs.GetNumerator() * (lcm / rhs.GetDenominator());
}
bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
        return os;
    } else {
        os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
        return os;
    }
}
std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string input;
    is >> input;
    int numer = 0;
    int denom = 0;
    auto index = input.find('/');
    if (index < input.size()) {
        numer = std::stoi(input.substr(0, index));
        denom = std::stoi(input.substr(index + 1, input.size() - index - 1));
    } else {
        numer = std::stoi(input);
        denom = 1;
    }
    ratio.Set(numer, denom);
    return is;
}
