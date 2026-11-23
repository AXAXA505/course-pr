#include "tea.hpp"

#include <iostream>

namespace vending
{

// === ctors and dtors ===

Tea::Tea()
    : BaseDrink("чай по умолчанию", "рецепт по умолчанию")
{
    std::cout << "[Tea] default ctor\n";
}

Tea::Tea(std::string_view name, std::string_view recipeName)
    : BaseDrink(name, recipeName)
{
    std::cout << "[Tea] ctor\n";
}

Tea::Tea(std::string_view name, std::shared_ptr<Recipe> recipe)
    : BaseDrink(name, std::move(recipe))
{
    std::cout << "[Tea] ctor (shared recipe): \"" << GetName() << "\"\n";
}

Tea::Tea(const Tea& other)
    : BaseDrink(other)
{
    std::cout << "[Tea] copy ctor\n";
}

Tea::Tea(Tea&& other) noexcept
    : BaseDrink(std::move(other))
{
    std::cout << "[Tea] move ctor\n";
}

Tea::~Tea()
{
    std::cout << "[Tea] dtor\n";
}

// === виртуальные методы ===

std::string_view Tea::GetCategory() const
{
    return "Чай";
}

std::unique_ptr<BaseDrink> Tea::Clone() const
{
    return std::make_unique<Tea>(*this);
}

void Tea::Print() const
{
    // Полностью своя реализация, поэтому без вызова бащы
    std::cout << "ЧАЙ: \"" << GetName()
              << "\" (категория: " << GetCategory() << ")\n";
    std::cout << "  Ингредиентов: " << GetRecipe().GetLiveCount() << "\n";
}

} // namespace vending