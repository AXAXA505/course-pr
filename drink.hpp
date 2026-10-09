#pragma once

#include "recipe.hpp"

#include <string>
#include <string_view>

namespace vending
{

class Drink
{
private:
    std::string m_name;
    Recipe      m_recipe;

public:
    Drink(std::string_view name, std::string_view recipeName);
    ~Drink();
    Drink() : Drink("unknown", "unknown recipe") {};

    Drink(const Drink&)            = delete;
    Drink& operator=(const Drink&) = delete;

    [[nodiscard]] std::string_view GetName()   const { return m_name; }
    [[nodiscard]] const Recipe&    GetRecipe() const { return m_recipe; }

    bool AddIngredient(Ingredient* ingredient, int amount);

    [[nodiscard]] bool IsValid() const;

    void Print() const;
};

} // namespace vending