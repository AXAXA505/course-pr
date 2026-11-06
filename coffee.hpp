#pragma once

#include "base_drink.hpp"

namespace vending
{

class Coffee : public BaseDrink
{
public:
    // === ctors and dtors ===
    Coffee();
    Coffee(std::string_view name, std::string_view      recipeName);
    Coffee(std::string_view name, std::shared_ptr<Recipe> recipe);

    Coffee(const Coffee& other);
    Coffee(Coffee&& other) noexcept;
    Coffee& operator=(const Coffee& other)            = default;
    Coffee& operator=(Coffee&& other) noexcept        = default;
    ~Coffee() override;

    // === virtual методы ===
    [[nodiscard]] std::string_view            GetCategory() const override;
    [[nodiscard]] std::unique_ptr<BaseDrink>  Clone()       const override;
    void                                      Print()       const override;
};

} // namespace vending