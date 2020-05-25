#include "Complex.h"
#include <cmath>
#include <iostream>

Complex::Complex(double real, double image)
                : m_real(real)
                , m_image(image)
{
}

double Complex::Re() const
{
    return m_real;
}

double Complex::Im() const
{
    return m_image;
}

double Complex::GetMagnitude() const
{
    return sqrt(std::pow(m_real, 2)
    + std::pow(m_image, 2));
}

double Complex::GetArgument() const
{
    try
    {
        if (m_real > 0)
        {
            return atan(m_image / m_real);
        }
        else
        {
            if (m_image > 0)
            {
                return M_PI + atan(m_image / m_real);
            }
            else
            {
                return -M_PI + atan(m_image / m_real);
            }
        }
    }
    catch (std::overflow_error& e)
    {
        throw e;
    }
}

Complex const operator+(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.m_real + rhs.m_real, lhs.m_image + rhs.m_image);
}

Complex const operator-(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.m_real - rhs.m_real, lhs.m_image - rhs.m_image);
}

Complex const operator*(const Complex& lhs, const Complex& rhs)
{
    double image = lhs.m_image * rhs.m_real + lhs.m_real * rhs.m_image;
    double real = lhs.m_real * rhs.m_real - lhs.m_image * rhs.m_image;

    return Complex(real, image);    // z1 * z2 = (ac - bd) + (bc + ad)j
}

Complex const operator*(const Complex& lhs, const double rhs)
{
    return Complex(lhs.m_real * rhs, lhs.m_image * rhs);
}

Complex const operator*(const double lhs, const Complex& rhs)
{
    return Complex(rhs.m_real * lhs, rhs.m_image * lhs);
}

Complex const operator/(const Complex& lhs, const Complex& rhs)
{
    double denominator = pow(rhs.m_real, 2) + pow(rhs.m_image, 2);
    if (denominator == 0)
    {
        throw std::overflow_error("Divide by zero exception");
    }

    double real = (lhs.m_real*rhs.m_real + lhs.m_image*rhs.m_image) / denominator;
    double image = (lhs.m_image*rhs.m_real - lhs.m_real*rhs.m_image) / denominator;

    return Complex(real, image);
}

Complex const operator/(const Complex& lhs, const double rhs)
{
    if (rhs == 0)
    {
        throw std::overflow_error("Divide by zero exception");
    }

    return Complex(lhs.m_real/rhs, lhs.m_image/rhs);
}

Complex const operator/(const double lhs, const Complex& rhs)
{
    if (lhs == 0)
    {
        throw std::overflow_error("Divide by zero exception");
    }

    return Complex(rhs.m_real/lhs, rhs.m_image/lhs);
}

Complex Complex::operator+() const
{
    return *this;
}

Complex Complex::operator-() const
{
    return Complex(0 - m_real, 0 - m_image);
}

Complex& Complex::operator+=(const Complex& rhs)
{
    m_real += rhs.m_real;
    m_image += rhs.m_image;

    return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
    m_real -= rhs.m_real;
    m_image -= rhs.m_image;

    return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
    m_real *= rhs.m_real;
    m_image *= rhs.m_image;

    return *this;
}

Complex& Complex::operator*=(const double& rhs)
{
    m_real *= rhs;
    m_image *= rhs;

    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    try
    {
        m_real /= rhs.m_real;
        m_image /= rhs.m_image;
    }
    catch (std::overflow_error& e)
    {
        throw e;
    }

    return *this;
}

Complex& Complex::operator/=(const double& rhs)
{
    try
    {
        m_real /= rhs;
        m_image /= rhs;
    }
    catch (std::overflow_error& e)
    {
        throw e;
    }

    return *this;
}

bool Complex::operator==(const Complex& complex) const
{
    return std::fabs(m_real-complex.m_real) < ACCEPTABLE_DELTA && std::fabs(m_image-complex.m_image) < ACCEPTABLE_DELTA;
}

bool Complex::operator==(const double& number) const
{
    return std::fabs(m_real-number) < ACCEPTABLE_DELTA && m_image == 0;
}

bool Complex::operator!=(const Complex& complex) const
{
    return !(*this == complex);
}

bool Complex::operator!=(const double& number) const
{
    return !(*this == number);
}

std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    os << complex.Re() << " + " << complex.Im() << "i";

    return os;
}

std::istream& operator>>(std::istream& is, Complex& complex)
{
    double real, image;
    is >> real >> image;

    if (is)
    {
        complex.m_real = real;
        complex.m_image = image;
    }

    return is;
}
