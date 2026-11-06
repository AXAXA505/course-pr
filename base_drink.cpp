#include "base_drink.hpp"

#include <iostream>

namespace vending
{

// === ctors and dtors ===

BaseDrink::BaseDrink(std::string_view name, std::shared_ptr<Recipe> recipe)
    : m_id{ ++s_drinkCount }
    , m_name{ name }
    , m_recipe{ recipe }
{
    if (m_name.empty())
    {
        std::cout << "[BaseDrink] Ошибка: имя напитка не может быть пустым. "
                     "Установлено имя \"unknown\".\n";
        m_name = "unknown";
    }

    std::cout << "[BaseDrink] ctor: \"" << m_name << "\"\n";
}

BaseDrink::BaseDrink(std::string_view name, std::string_view recipeName)
    : BaseDrink(name, std::make_shared<Recipe>(recipeName))
{
}

BaseDrink::BaseDrink(const BaseDrink& other)
    : m_id{ ++s_drinkCount }
    , m_name{ other.m_name }
    , m_recipe{ std::make_shared<Recipe>(*other.m_recipe) }   // глубокая копия
{
    std::cout << "[BaseDrink] copy ctor: \"" << m_name << "\"\n";
}

BaseDrink::BaseDrink(BaseDrink&& other) noexcept
    : m_id{ other.m_id }
    , m_name{ std::move(other.m_name) }
    , m_recipe{ std::move(other.m_recipe) }
{
    ++s_drinkCount;
    std::cout << "[BaseDrink] move ctor: \"" << m_name << "\"\n";
}

BaseDrink::~BaseDrink()
{
    std::cout << "[BaseDrink] Деструктор: напиток \"" << m_name
              << "\" уничтожен.\n";
}

/// === операторы ===

BaseDrink& BaseDrink::operator=(const BaseDrink& other)
{
    if (this == &other)   // защита от самоприсваивания
    {
        return *this;
    }

    m_name   = other.m_name;
    m_recipe = std::make_shared<Recipe>(*other.m_recipe);

    std::cout << "[BaseDrink] copy (DEEP): \"" << m_name << "\"\n";
    return *this;
}

BaseDrink& BaseDrink::operator=(BaseDrink&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    m_name   = std::move(other.m_name);
    m_recipe = std::move(other.m_recipe);

    std::cout << "[BaseDrink] move: \"" << m_name << "\"\n";
    return *this;
}

// === связь с рецептом ===

bool BaseDrink::AddIngredient(const std::shared_ptr<Ingredient>& ingredient, int amount)
{
    return m_recipe->AddIngredient(ingredient, amount);
}

bool BaseDrink::IsValid() const
{
    return m_recipe->GetLiveCount() > 0;
}

// === вывод ===

std::string BaseDrink::Header() const
{
    return std::string(GetCategory()) + " \"" + m_name + "\"";
}

void BaseDrink::Print() const
{
    PrintTo(*this, std::cout);
    m_recipe->Print();

    std::cout << "  Статус рецепта: "
              << (IsValid() ? "готов к использованию"
                            : "пустой, приготовление невозможно")
              << "\n";
}

void BaseDrink::PrintTo(const BaseDrink& drink, std::ostream& os)
{
    os << "Напиток: " << drink.Header() << "\n";
}

} // namespace vending