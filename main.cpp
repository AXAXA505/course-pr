#include "drink.hpp"
#include "ingredient.hpp"
#include "recipe.hpp"

#include <windows.h>
#include <iostream>


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== Старт программы. Создаем базовые ингредиенты ===\n";
    vending::Ingredient coffee("Кофе",      vending::Ingredient::Type::eBase);
    vending::Ingredient milk("Молоко",      vending::Ingredient::Type::eBase);
    vending::Ingredient caramel("Карамель", vending::Ingredient::Type::eTopping);
    vending::Ingredient ice("Лёд",          vending::Ingredient::Type::eIce);

    // 1. Демонстрация времени жизни объектов
    {
        std::cout << "\n--- Вход в локальный блок ---\n";
        vending::Drink latte("Латте", "Рецепт Латте");

        latte.AddIngredient(&coffee, 20);
        latte.AddIngredient(&milk, 150);
        latte.AddIngredient(&caramel, 22);

        // Проверки
        latte.AddIngredient(&ice, 0);   // Некорректное количество
        latte.AddIngredient(&coffee, 5); // Дубликат
        latte.AddIngredient(nullptr, 10);

        std::cout << "\nТекущее состояние напитка:\n";
        latte.Print();

        std::cout << "\n--- Выход из локального блока (уничтожение latte) ---\n";
    }

    std::cout << "\nПроверка сохранности ингредиентов после уничтожения напитка:\n";
    coffee.Print();

    // 2. Работа с динамической памятью
    std::cout << "\n=== Динамическое выделение памяти ===\n";
    
    std::cout << "1) Одиночный объект:\n";
    vending::Drink* solo = new vending::Drink("Американо", "Рецепт Американо");
    solo->AddIngredient(&coffee, 15);
    solo->Print();
    delete solo;

    std::cout << "\n2) Статический массив объектов (вызываются конструкторы по умолчанию):\n";
    {
        vending::Drink drinks[2];
        drinks[0].AddIngredient(&coffee, 7);
        drinks[0].Print();
    }

    std::cout << "\n3) Динамический массив указателей:\n";
    vending::Drink** many = new vending::Drink*[2];
    many[0] = new vending::Drink("Эспрессо", "Рецепт Эспрессо");
    many[1] = new vending::Drink("Капучино", "Рецепт Капучино");

    many[0]->AddIngredient(&coffee, 7);
    many[1]->AddIngredient(&milk, 100);

    for (int i = 0; i < 2; ++i) 
    {
        many[i]->Print();
    }

    std::cout << "\nОсвобождение памяти динамического массива:\n";
    for (int i = 0; i < 2; ++i) 
    {
        delete many[i];
    }
    delete[] many;

    std::cout << "\n=== Завершение main (уничтожение оставшихся объектов) ===\n";
    return 0;
}
