#include <iostream>
#include <string>
#include <fstream>

struct Expense {
    std::string category;
    double amount;
    std::string comment;
};

void saveToFile(Expense e) {
    std::ofstream outFile("expenses.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << e.category << " | " << e.amount << " UAH | " << e.comment << "\n";
        outFile.close();
    }
}

int main() {
    int userChoice;

    while (true) {
        std::cout << "\n=== LVIV IT FINANCE TRACKER ===\n"; // Трохи локального контексту ;)
        std::cout << "1. Add Expense\n2. View History\n3. Clear All Data\n4. Exit\n";
        std::cout << "Choice: ";
        if (!(std::cin >> userChoice)) break; // Захист від введення букв
        std::cin.ignore();

        if (userChoice == 4) break;

        switch (userChoice) {
            case 1: {
                Expense e;
                std::cout << "Category (e.g. Gym, Food): ";
                std::getline(std::cin, e.category);
                std::cout << "Amount: ";
                std::cin >> e.amount;
                std::cin.ignore();
                std::cout << "Comment: ";
                std::getline(std::cin, e.comment);
                saveToFile(e);
                std::cout << "Successfully saved!\n";
                break;
            }
            case 2: {
                std::ifstream inFile("expenses.txt");
                std::string line;
                std::cout << "\n--- Full History ---\n";
                if (!inFile) std::cout << "History is empty.\n";
                while (std::getline(inFile, line)) {
                    std::cout << line << std::endl;
                }
                inFile.close();
                break;
            }
            case 3: {
                // Маленький трюк: якщо відкрити файл без ios::app, 
                // він автоматично очищається (переписується порожнечею).
                std::ofstream outFile("expenses.txt"); 
                outFile.close();
                std::cout << "All data cleared!\n";
                break;
            }
            default:
                std::cout << "Invalid option!\n";
        }
    }
    return 0;
}
