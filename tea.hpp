#pragma once

#include "base_drink.hpp"

namespace vending
{

class Tea final : public BaseDrink
{
public:
    // === ctors and dtors ===
    Tea();
    Tea(std::string_view name, std::string_view        recipeName);
    Tea(std::string_view name, std::shared_ptr<Recipe> recipe);

    Tea(const Tea& other);
    Tea(Tea&& other) noexcept;
    Tea& operator=(const Tea& other)           = default;
    Tea& operator=(Tea&& other) noexcept       = default;
    ~Tea() override;

    // === virtual методы ===
    [[nodiscard]] std::string_view            GetCategory() const override;
    [[nodiscard]] std::unique_ptr<BaseDrink>  Clone()       const override;
    void                                      Print()       const override;
};

} // namespace vending