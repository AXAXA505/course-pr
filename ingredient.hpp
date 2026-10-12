#pragma once

#include <string>
#include <string_view>

namespace vending
{

class Ingredient
{
public:
    enum class Type
    {
        eBase,
        eTopping,
        eIce
    };

private:
    std::string m_name;
    Type m_type{ Type::eBase }; 
    Ingredient() : Ingredient("unknown", Type::eBase) {};

public:
    Ingredient(std::string_view name, Type type);
    ~Ingredient();

    Ingredient(const Ingredient&)            = delete;
    Ingredient& operator=(const Ingredient&) = delete;

    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] Type             GetType() const { return m_type; }
    [[nodiscard]] bool IsTopping() const { return m_type == Type::eTopping; }
    [[nodiscard]] bool IsIce()     const { return m_type == Type::eIce; }

    void Print() const;
};

} // namespace vending