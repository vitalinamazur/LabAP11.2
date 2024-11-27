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
        size_t dotPos = token.find('.'); // ��������� ������� ������

        if (dotPos != string::npos && dotPos + 1 < token.length() && isdigit(token[dotPos + 1])) { // �������� �� � ����� ���� ������
            size_t digitCount = 0;
            for (size_t i = dotPos + 1; i < token.length(); ++i) {
                if (isdigit(token[i])) {
                    digitCount++;
                    if (digitCount > 2) { // ���� ���� ����� ���� ���� ������
                        token.erase(i); // ������� ���� �����
                        break;
                    }
                }
                else {
                    break; // �������� ����, ���� ���� ������ �� �����
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

// ������� ������� ��� ������� �����
void processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw runtime_error("�� ������� ������� ���� ��� �������: " + inputFileName);
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw runtime_error("�� ������� ������� ���� ��� ������: " + outputFileName);
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
    cout << "������ ��'� �������� �����: ";
    cin >> inputFileName;
    cout << "������ ��'� ��������� �����: ";
    cin >> outputFileName;

    try {
        processFile(inputFileName, outputFileName);
        cout << "���� ������ ��������� �� �������� � " << outputFileName << endl;
    }
    catch (const exception& ex) {
        cerr << "�������: " << ex.what() << endl;
    }

    return 0;
}
