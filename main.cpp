#include <iostream>
#include <string>
#include <fstream>

struct Expense {
    std::string category;
    double amount;
    std::string comment;
};

// Створюємо ФУНКЦІЮ для збереження. 
// Тепер нам не треба писати код відкриття файлу щоразу.
void saveToFile(Expense e) {
    std::ofstream outFile("expenses.txt", std::ios::app);
    if (outFile.is_open()) {
        // Використовуємо розділювач '|', щоб потім було легше читати рядки з пробілами
        outFile << e.category << "|" << e.amount << "|" << e.comment << "\n";
        outFile.close();
    }
}

int main() {
    int userChoice;

    while (true) {
        std::cout << "\n=== PRO FINANCE TRACKER ===\n1. Add\n2. View\n3. Exit\nChoice: ";
        std::cin >> userChoice;
        std::cin.ignore(); // ВАЖЛИВО: очищуємо буфер після введення числа

        if (userChoice == 3) break;

        switch (userChoice) {
            case 1: {
                Expense e;
                std::cout << "Category: ";
                std::getline(std::cin, e.category); // Читає весь рядок з пробілами
                
                std::cout << "Amount: ";
                std::cin >> e.amount;
                std::cin.ignore(); // Знову очищуємо після числа
                
                std::cout << "Comment: ";
                std::getline(std::cin, e.comment);

                saveToFile(e); // Просто викликаємо нашу функцію
                std::cout << "Done!\n";
                break;
            }
            case 2: {
                std::ifstream inFile("expenses.txt");
                std::string line;
                std::cout << "\n--- History ---\n";
                while (std::getline(inFile, line)) { // Читаємо файл по рядках
                    std::cout << line << std::endl;
                }
                inFile.close();
                break;
            }
        }
    }
    return 0;
}
