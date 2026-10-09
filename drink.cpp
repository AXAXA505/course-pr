#include "drink.hpp"

#include <iostream>

namespace vending
{

Drink::Drink(std::string_view name, std::string_view recipeName)
    : m_name{ name }
    , m_recipe{ recipeName }
{
    if (m_name.empty())
    {
        std::cout << "[Drink] Ошибка: имя напитка не может быть пустым. "
                     "Установлено имя \"unknown\".\n";
        m_name = "unknown";
    }
}

Drink::~Drink()
{
    std::cout << "[Drink] Деструктор: напиток \"" << m_name
              << "\" уничтожен.\n";
}

bool Drink::AddIngredient(Ingredient* ingredient, int amount)
{
    return m_recipe.AddIngredient(ingredient, amount);
}

bool Drink::IsValid() const
{
    return m_recipe.GetCount() > 0;
}

void Drink::Print() const
{
    std::cout << "Напиток: " << m_name << "\n";
    m_recipe.Print();
    std::cout << "  Статус рецепта: "
              << (IsValid() ? "готов к использованию"
                            : "пустой, приготовление невозможно")
              << "\n";
}

} // namespace vending