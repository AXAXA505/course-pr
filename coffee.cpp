#include "coffee.hpp"

#include <iostream>

namespace vending
{

// === ctors and dtors ===

Coffee::Coffee()
    : BaseDrink("кофе по умолчанию", "рецепт по умолчанию")
{
    std::cout << "[Coffee] default ctor\n";
}

Coffee::Coffee(std::string_view name, std::string_view recipeName)
    : BaseDrink(name, recipeName)
{
    std::cout << "[Coffee] ctor: \"" << GetName() << "\"\n";
}

Coffee::Coffee(std::string_view name, std::shared_ptr<Recipe> recipe)
    : BaseDrink(name, std::move(recipe))
{
    std::cout << "[Coffee] ctor (shared recipe): \"" << GetName() << "\"\n";
}

Coffee::Coffee(const Coffee& other)
    : BaseDrink(other)
{
    std::cout << "[Coffee] copy ctor\n";
}

Coffee::Coffee(Coffee&& other) noexcept
    : BaseDrink(std::move(other))
{
    std::cout << "[Coffee] move ctor\n";
}

Coffee::~Coffee()
{
    std::cout << "[Coffee] dtor\n";
}

// === виртуальные методы ===

std::string_view Coffee::GetCategory() const
{
    return "Кофе";
}

std::unique_ptr<BaseDrink> Coffee::Clone() const
{
    return std::make_unique<Coffee>(*this);
}

void Coffee::Print() const
{
    BaseDrink::Print();
    std::cout << "  [Coffee] содержит кофеин, употреблять в умеренном количестве.\n";
}

} // namespace vending