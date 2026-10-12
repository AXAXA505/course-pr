#include "recipe.hpp"

#include <iostream>

namespace vending
{

Recipe::Recipe(std::string_view name)
    : m_name{ name }
{
    if (m_name.empty())
    {
        std::cout << "[Recipe] Ошибка: имя рецепта не может быть пустым. "
                     "Установлено имя \"unknown\".\n";
        m_name = "unknown";
    }
}

Recipe::~Recipe()
{
    std::cout << "[Recipe] Деструктор: рецепт \"" << m_name
              << "\" уничтожен.\n";
}

bool Recipe::AddIngredient(Ingredient* ingredient, int amount)
{
    if (ingredient == nullptr)
    {
        std::cout << "[Recipe] Отказ: ингредиент не задан (nullptr).\n";
        return false;
    }

    if (amount <= 0)
    {
        std::cout << "[Recipe] Отказ: количество ингредиента \""
                  << ingredient->GetName()
                  << "\" должно быть больше нуля (получено "
                  << amount << ").\n";
        return false;
    }

    if (HasIngredient(ingredient))
    {
        std::cout << "[Recipe] Отказ: ингредиент \""
                  << ingredient->GetName()
                  << "\" уже присутствует в рецепте.\n";
        return false;
    }

    m_requirements.push_back({ ingredient, amount });
    return true;
}

bool Recipe::HasIngredient(const Ingredient* ingredient) const
{
    for (const auto& req : m_requirements)
    {
        if (req.ingredient == ingredient)
        {
            return true;
        }
    }
    return false;
}

void Recipe::Print() const
{
    std::cout << "Рецепт \"" << m_name << "\": "
              << m_requirements.size() << " ингредиент(ов)\n";
    for (const auto& req : m_requirements)
    {
        std::cout << "  - " << req.ingredient->GetName()
                  << " x " << req.amount << "\n";
    }
}

} // namespace vending