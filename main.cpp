#include "coffee.hpp"
#include "tea.hpp"

#include <iostream>
#include <memory>
#include <windows.h>
#include <vector>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    auto coffee  = std::make_shared<vending::Ingredient>("Кофе",     vending::Ingredient::Type::eBase);
    auto milk    = std::make_shared<vending::Ingredient>("Молоко",   vending::Ingredient::Type::eBase);
    auto caramel = std::make_shared<vending::Ingredient>("Карамель", vending::Ingredient::Type::eTopping);

    // === Четыре вида конструкторов ===
    std::cout << "\n=== Конструкторы ===\n";
    {
        vending::Coffee latte("Латте", "Рецепт Латте");      // параметризованный
        vending::Coffee defaultCoffee;                       // по умолчанию
        vending::Coffee latteCopy = latte;                   // копирования
        vending::Coffee latteMoved = std::move(latteCopy);   // перемещения
    }

    // === Поверхностная копия ===
    std::cout << "\n=== Поверхностная копия ===\n";
    {
        auto sharedRecipe = std::make_shared<vending::Recipe>("Общий рецепт");
        vending::Coffee a("Кофе A", sharedRecipe);
        vending::Coffee b("Кофе B", sharedRecipe);

        a.AddIngredient(coffee, 10);
        std::cout << "Ингредиентов у B после изменения A: "
                  << b.GetRecipe().GetLiveCount() << " (B видит изменения A)\n";
    }

    // === Глубокая копия ===
    std::cout << "\n=== Глубокая копия ===\n";
    {
        vending::Coffee original("Американо", "Рецепт Американо");
        original.AddIngredient(coffee, 15);

        vending::Coffee copy = original; // copy ctor глубокая копия
        copy.AddIngredient(milk, 50);  

        vending::BaseDrink& asBase = original;
        auto clone = asBase.Clone();
        clone->AddIngredient(milk, 50);
        clone->AddIngredient(caramel, 5);

        std::cout << "Ингредиентов — оригинал: " << original.GetRecipe().GetLiveCount()
                << ", копия: " << copy.GetRecipe().GetLiveCount()
                << ", клон:  " << clone->GetRecipe().GetLiveCount() << "\n";
    }

    // === this ===
    std::cout << "\n=== This ===\n";
    {
        vending::Coffee x("X", "Рецепт X");
        vending::Coffee y("Y", "Рецепт Y");
        x.AddIngredient(coffee, 5);
        x = y;   // глубокое присваивание
        x = x;   // сработает `if (this == &other) return *this;`
    }

    // === Виртуальный деструктор через указатель на базу ===
    std::cout << "\n=== Виртуальный деструктор ===\n";
    {
        std::unique_ptr<vending::BaseDrink> ptr = std::make_unique<vending::Coffee>("Удаляемый", "Рецепт");
        std::cout << "reset() -> сначала ~Coffee, затем ~BaseDrink:\n";
        ptr.reset();
    }

    // === Строки concat / find / substr  ===
    std::cout << "\n=== Строки ===\n";
    {
        vending::Coffee searchable("Латте", "Рецепт Латте");

        const std::string full = std::string(searchable.GetCategory()) + " " + std::string(searchable.GetName());
        std::cout << "Конкатенация: \"" << full << "\"\n";

        const std::size_t pos = full.find("Лат");
        std::cout << "find(\"Лат\") = " << pos << "\n";

        const std::string part = full.substr(pos, 6); // в ру языке один символ = 2 байт
        std::cout << "substr = \"" << part << "\", == \"Лат\": " << (part == "Лат") << "\n";
    }

    std::cout << "\n=== Массив unique_ptr<BaseDrink> ===\n";
    {
        std::vector<std::unique_ptr<vending::BaseDrink>> drinks;
        drinks.push_back(std::make_unique<vending::Coffee>("Американо",    "Р A"));
        drinks.push_back(std::make_unique<vending::Tea>   ("Зелёный чай", "Р Ч"));
        drinks.push_back(std::make_unique<vending::Coffee>("Латте",       "Р Л"));
        drinks.push_back(std::make_unique<vending::Tea>   ("Чёрный чай",  "Р ЧЧ"));

        // Coffee::Print зовёт базу, Tea::Print - нет
        for (const std::unique_ptr<vending::BaseDrink>& d : drinks)
        {
            std::cout << "--- id = " << d->GetId()
                    << ", категория = " << d->GetCategory() << " ---\n";
            d->Print();
        }
        std::cout << "\nДеструкторы:\n";
        drinks.clear();
    }
    std::cout << "Всего создано напитков: " << vending::BaseDrink::GetDrinkCount() << "\n";

    std::cout << "\n=== Конец main ===\n";
    return 0;
}