#pragma once

#include "recipe.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace vending
{

class BaseDrink
{
protected:
    std::string Header() const;

private:
    static inline int s_drinkCount{ 0 };

    int                     m_id{ 0 };
    std::string             m_name;
    std::shared_ptr<Recipe> m_recipe;

public:
    // === ctors and dtors ===
    BaseDrink(std::string_view name, std::shared_ptr<Recipe> recipe);
    BaseDrink(std::string_view name, std::string_view recipeName);

    BaseDrink(const BaseDrink& other);
    BaseDrink(BaseDrink&& other) noexcept;
    BaseDrink& operator=(const BaseDrink& other);
    BaseDrink& operator=(BaseDrink&& other) noexcept;
    virtual ~BaseDrink();

    // === virtual методы ===
    [[nodiscard]] virtual std::string_view            GetCategory() const = 0;
    [[nodiscard]] virtual std::unique_ptr<BaseDrink>  Clone()       const = 0;
    virtual void                                      Print()       const;

    // === геттеры ===
    [[nodiscard]] std::string_view GetName()   const { return m_name; }
    [[nodiscard]] const Recipe&    GetRecipe() const { return *m_recipe; }
    [[nodiscard]] int              GetId()     const { return m_id; }

    // === связь с рецептом ===
    bool AddIngredient(const std::shared_ptr<Ingredient>& ingredient, int amount);
    [[nodiscard]] bool IsValid() const;

    // === other ===
    static void PrintTo(const BaseDrink& drink, std::ostream& os);
    [[nodiscard]] static int GetDrinkCount() { return s_drinkCount; }


};

} // namespace vending