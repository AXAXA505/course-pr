#include "ingredient.hpp"

#include <iostream>

namespace vending
{

Ingredient::Ingredient(std::string_view name, Type type)
    : m_name{ name }
    , m_type{ type }
{
    if (m_name.empty())
    {
        std::cout << "[Ingredient] Ошибка: имя ингредиента не может быть пустым. "
                     "Установлено имя \"unknown\".\n";
        m_name = "unknown";
    }
}

Ingredient::~Ingredient()
{
    std::cout << "[Ingredient] Деструктор: ингредиент \"" << m_name
              << "\" уничтожен.\n";
}

void Ingredient::Print() const
{
    std::cout << "Ингредиент: " << m_name << " (";
    switch (m_type)
    {
    case Type::eBase:    std::cout << "основа";  break;
    case Type::eTopping: std::cout << "топпинг"; break;
    case Type::eIce:     std::cout << "лёд";     break;
    }
    std::cout << ")\n";
}

} // namespace vending