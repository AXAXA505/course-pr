#include "drink.hpp"
#include "ingredient.hpp"
#include "recipe.hpp"

#include <windows.h>
#include <iostream>
#include <memory>
#include <utility>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== Старт программы. Создаем ингредиенты через make_shared ===\n";
    auto coffee  = std::make_shared<vending::Ingredient>("Кофе",     vending::Ingredient::Type::eBase);
    auto milk    = std::make_shared<vending::Ingredient>("Молоко",   vending::Ingredient::Type::eBase);
    auto caramel = std::make_shared<vending::Ingredient>("Карамель", vending::Ingredient::Type::eTopping);
    auto ice     = std::make_shared<vending::Ingredient>("Лёд",      vending::Ingredient::Type::eIce);

    // демонстрация времени жизни shared_ptr
    std::cout << "\n--- shared_ptr: уничтожение с последним владельцем ---\n";
    {
        auto demo = std::make_shared<vending::Ingredient>("Демо", vending::Ingredient::Type::eIce);
        std::cout << "demo.use_count() = " << demo.use_count() << "\n";          // 1
        {
            auto demoCopy = demo;
            std::cout << "после копии: use_count = " << demo.use_count() << "\n"; // 2
        }
        std::cout << "после выхода из блока: use_count = " << demo.use_count() << "\n";   // 1
    }

    // время жизни напитка через unique_ptr
    {
        std::cout << "\n--- Вход в локальный блок (unique_ptr) ---\n";
        auto latte = std::make_unique<vending::Drink>("Латте", "Рецепт Латте");

        latte->AddIngredient(coffee, 20);
        latte->AddIngredient(milk, 150);
        latte->AddIngredient(caramel, 22);

        std::cout << "\ncoffee.use_count() после добавления в рецепт: " << coffee.use_count() << "\n";

        // Проверки
        latte->AddIngredient(ice, 0);        // Некорректное количество
        latte->AddIngredient(coffee, 5);     // Дубликат
        latte->AddIngredient(nullptr, 10);   // Пустой указатель

        std::cout << "\nТекущее состояние напитка:\n";
        latte->Print();

        std::cout << "\n--- Выход из локального блока (уничтожение latte) ---\n";
    }

    std::cout << "\nПроверка сохранности ингредиентов после уничтожения напитка:\n";
    coffee->Print();


    std::cout << "\n=== unique_ptr: передача владения ===\n";
    auto americano = std::make_unique<vending::Drink>("Американо", "Рецепт Американо");
    americano->AddIngredient(coffee, 15);
    americano->Print();

    std::unique_ptr<vending::Drink> owner = std::move(americano);   // владение перешло
    std::cout << "americano пуст после std::move: " << (americano == nullptr ? "да" : "нет") << "\n";
    std::cout << "у owner лежит: " << owner->GetName() << "\n";


    std::cout << "\n=== Массив умных указателей ===\n";
    std::unique_ptr<vending::Drink> many[2];
    many[0] = std::make_unique<vending::Drink>("Эспрессо", "Рецепт Эспрессо");
    many[1] = std::make_unique<vending::Drink>("Капучино", "Рецепт Капучино");

    many[0]->AddIngredient(coffee, 7);
    many[1]->AddIngredient(milk, 100);

    for (const auto& drink : many)
    {
        drink->Print();
    }

    // 5. weak_ptr
    std::cout << "\n=== weak_ptr ===\n";
    vending::Drink raf("Раф", "Рецепт Раф кофе");
    raf.AddIngredient(coffee, 7);

    {
        auto syrup = std::make_shared<vending::Ingredient>("Сироп", vending::Ingredient::Type::eTopping);
        raf.AddIngredient(syrup, 10);
        raf.Print();
    } 

    raf.Print();

    std::cout << "\n=== Завершение main ===\n";
    return 0;
}