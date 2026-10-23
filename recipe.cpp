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

bool Recipe::AddIngredient(const std::shared_ptr<Ingredient>& ingredient, int amount)
{
    if (!ingredient)
    {
        std::cout << "[Recipe] Отказ: ингредиент не задан (nullptr).\n";
        return false;
    }
    if (amount <= 0)
    {
        std::cout << "[Recipe] Отказ: количество ингредиента \"" << ingredient->GetName()
                  << "\" должно быть больше нуля (получено "<< amount << ").\n";
        return false;
    }
    if (HasIngredient(ingredient.get()))
    {
        std::cout << "[Recipe] Отказ: ингредиент \"" << ingredient->GetName()
                  << "\" уже присутствует в рецепте.\n";
        return false;
    }
    m_requirements.push_back({ ingredient, amount });
    return true;
}

bool Recipe::HasIngredient(const Ingredient* ingredient) const
{
    if (ingredient == nullptr)
    {
        return false;
    }
    for (const auto& req : m_requirements)
    {
        if (req.ingredient.lock().get() == ingredient)
        {
            return true;
        }
    }
    return false;
}

void Recipe::Print() const
{
    std::cout << "Рецепт \"" << m_name << "\": "<< GetLiveCount() << " ингредиент(ов)\n";
    for (const auto& req : m_requirements)
    {
        if (auto ing = req.ingredient.lock())
        {
            std::cout << "  - " << ing->GetName() << " x " << req.amount << "\n";
        }
        else
        {
            std::cout << "  - [ингредиент уничтожен] x " << req.amount << "\n";
        }
    }
}


std::size_t Recipe::GetLiveCount() const
{
    std::size_t count = 0;
    for (const auto& req : m_requirements)
    {
        if (!req.ingredient.expired())
        {
            ++count;
        }
    }
    return count;
}

} // namespace vending