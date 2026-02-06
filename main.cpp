#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip> // Бібліотека для красивого вирівнювання тексту

struct Expense {
    std::string category;
    double amount;
    std::string comment;
};

// Функція збереження (Додали розділювач '|' для легкого читання пізніше)
void saveToFile(Expense e) {
    std::ofstream outFile("expenses.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << e.category << "|" << e.amount << "|" << e.comment << "\n";
        outFile.close();
    }
}

// Нова функція: перегляд історії + ПІДРАХУНОК СУМИ
void viewHistory() {
    std::ifstream inFile("expenses.txt");
    std::string cat, comm, line;
    double price;
    double total = 0; // Змінна для накопичення суми

    std::cout << "\n--- Full History ---\n";
    std::cout << std::left << std::setw(15) << "Category" 
              << std::setw(10) << "Amount" 
              << "Comment" << std::endl;
    std::cout << "-------------------------------------------\n";

    // Читаємо файл. Формат: Category|Amount|Comment
    while (std::getline(inFile, cat, '|') && (inFile >> price) && (inFile.ignore(1, '|') && std::getline(inFile, comm))) {
        std::cout << std::left << std::setw(15) << cat 
                  << std::setw(10) << price 
                  << comm << std::endl;
        total += price; // Додаємо кожну ціну до загальної суми
    }

    if (total == 0 && !inFile.eof()) {
        std::cout << "History is empty or file error.\n";
    } else {
        std::cout << "-------------------------------------------\n";
        std::cout << "💰 TOTAL SPENT: " << total << " UAH\n";
    }
    inFile.close();
}

int main() {
    int userChoice;

    while (true) {
        std::cout << "\n=== LVIV IT FINANCE TRACKER ===\n";
        std::cout << "1. Add Expense\n2. View History & Total\n3. Clear All Data\n4. Exit\n";
        std::cout << "Choice: ";

        // Захист від введення літер
        if (!(std::cin >> userChoice)) {
            std::cout << "Please enter a number (1-4)!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        std::cin.ignore();

        if (userChoice == 4) break;

        switch (userChoice) {
            case 1: {
                Expense e;
                std::cout << "Category: ";
                std::getline(std::cin, e.category);
                
                std::cout << "Amount: ";
                // Валідація суми
                while (!(std::cin >> e.amount) || e.amount < 0) {
                    std::cout << "Invalid input! Enter positive number: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                std::cin.ignore();

                std::cout << "Comment: ";
                std::getline(std::cin, e.comment);

                saveToFile(e);
                std::cout << "✅ Successfully saved!\n";
                break;
            }
            case 2: {
                viewHistory(); // Викликаємо нову функцію
                break;
            }
            case 3: {
                std::ofstream outFile("expenses.txt"); 
                outFile.close();
                std::cout << "🗑️ All data cleared!\n";
                break;
            }
            default:
                std::cout << "Invalid option!\n";
        }
    }
    return 0;
}
