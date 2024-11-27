#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.2/Lab11.2.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestMethod_ProcessFile)
        {

            string inputFile = "test_input.txt";
            string outputFile = "test_output.txt";


            ofstream inFile(inputFile);
            inFile << "ab+0.1973–1.1\n";
            inFile << "example.456another.12345\n";
            inFile << "test.99999done\n";
            inFile.close();


            processFile(inputFile, outputFile);


            ifstream outFile(outputFile);
            Assert::IsTrue(outFile.is_open(), L"Не вдалося відкрити вихідний файл!");

            stringstream buffer;
            buffer << outFile.rdbuf();
            outFile.close();


            string expectedOutput =
                "ab+0.19\n"
                "example.45\n"
                "test.99\n";

            Assert::AreEqual(expectedOutput, buffer.str());
        }
    };
}
