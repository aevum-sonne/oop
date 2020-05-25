#pragma once

#include <fstream>

class Complex
{
public:
    Complex(double real = 0, double image = 0);

    // Get real from complex
    [[nodiscard]] double Re() const;

    // Get image from complex
    [[nodiscard]] double Im() const;

    [[nodiscard]] double GetMagnitude() const;

    [[nodiscard]] double GetArgument() const;

    const double ACCEPTABLE_DELTA = 0.01;

    Complex const friend operator+(const Complex& lhs, const Complex& rhs);
    Complex const friend operator-(const Complex& lhs, const Complex& rhs);

    Complex const friend operator*(const Complex& lhs, const Complex& rhs);
    Complex const friend operator*(const Complex& lhs, const double rhs);
    Complex const friend operator*(const double lhs, const Complex& rhs);

    Complex const friend operator/(const Complex& lhs, const Complex& rhs);
    Complex const friend operator/(const Complex& lhs, const double rhs);
    Complex const friend operator/(const double lhs, const Complex& rhs);

    Complex operator+() const;
    Complex operator-() const;

    Complex& operator+=(const Complex& rhs);

    Complex& operator-=(const Complex& rhs);

    Complex& operator*=(const Complex& rhs);
    Complex& operator*=(const double& rhs);

    Complex& operator/=(const Complex& rhs);
    Complex& operator/=(const double& rhs);

    bool operator==(const Complex& complex) const;
    bool operator==(const double& number) const;

    bool operator!=(const Complex& complex) const;
    bool operator!=(const double& number) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);

    friend std::istream& operator>>(std::istream& is, Complex& complex);

private:
    double m_real;
    double m_image;
};