#pragma once

#include <Interfaces/IShape.h>
#include <Point/Point.h>
#include <string>
#include <cstdint>

class ISolidShape: public IShape
{
public:
    [[nodiscard]] virtual std::uint32_t GetFillColor() const = 0;

    ~ISolidShape() override= default;;
};
