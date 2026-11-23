#pragma once

#include "ingredient.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace vending
{

class Recipe
{
public:
    struct Requirement
    {
        std::weak_ptr<Ingredient> ingredient;
        int                       amount{ 0 };
    };
private:
    std::string              m_name;
    std::vector<Requirement> m_requirements;

public:

    // === ctors and dtors ===
    Recipe();
    explicit Recipe(std::string_view name);
    ~Recipe();

    
    Recipe(const Recipe&)                = default;
    Recipe& operator=(const Recipe&)     = default;
    Recipe(Recipe&&) noexcept            = default;
    Recipe& operator=(Recipe&&) noexcept = default;

    // === операции с рецептом ===
    bool AddIngredient(const std::shared_ptr<Ingredient>& ingredient, int amount);

    // === геттеры ===
    [[nodiscard]] bool             HasIngredient(const Ingredient* ingredient) const;
    [[nodiscard]] std::string_view GetName()      const { return m_name; }
    [[nodiscard]] std::size_t      GetLiveCount() const;

    // === вывод ===
    void Print() const;

};

} // namespace vending