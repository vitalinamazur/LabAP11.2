#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <windows.h>
using namespace std;


string processLine(const string& line) {
    stringstream ss(line);
    string token, result;

    while (ss >> token) {
        size_t dotPos = token.find('.'); // Знаходить позицію крапки

        if (dotPos != string::npos && dotPos + 1 < token.length() && isdigit(token[dotPos + 1])) { // Перевіряє чи є цифри після крапки
            size_t digitCount = 0;
            for (size_t i = dotPos + 1; i < token.length(); ++i) {
                if (isdigit(token[i])) {
                    digitCount++;
                    if (digitCount > 2) { // Якщо цифр більше двох після крапки
                        token.erase(i); // Видаляє зайві цифри
                        break;
                    }
                }
                else {
                    break; // Перериває цикл, якщо після крапки не цифра
                }
            }
        }

        result += token + " ";
    }

    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}

// Основна функція для обробки файлу
void processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw runtime_error("Не вдалося відкрити файл для читання: " + inputFileName);
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw runtime_error("Не вдалося відкрити файл для запису: " + outputFileName);
    }

    string line;
    while (getline(inputFile, line)) {
        string processedLine = processLine(line);
        outputFile << processedLine << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string inputFileName, outputFileName;
    cout << "Введіть ім'я вхідного файлу: ";
    cin >> inputFileName;
    cout << "Введіть ім'я вихідного файлу: ";
    cin >> outputFileName;

    try {
        processFile(inputFileName, outputFileName);
        cout << "Файл успішно оброблено та записано у " << outputFileName << endl;
    }
    catch (const exception& ex) {
        cerr << "Помилка: " << ex.what() << endl;
    }

    return 0;
}
