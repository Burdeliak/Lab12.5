#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.5/lab12.5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test125
{
	TEST_CLASS(test125)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Arrange: створюємо тестові дані
			string testFilename = "test_file.bin";

			vector<Faculty> testFaculties = {
				{"Computer Science", {
					{"CS-101", "Smith", 1, 4.0},
					{"CS-102", "Johnson", 2, 3.5}
				}},
				{"Mathematics", {
					{"MATH-201", "Brown", 3, 4.2}
				}}
			};

			// Act: записуємо дані у файл і зчитуємо їх назад
			WriteToFile(testFilename, testFaculties);
			vector<Faculty> resultFaculties = ReadFromFile(testFilename);

			// Assert: перевіряємо, чи записані та зчитані дані співпадають
			Assert::AreEqual(testFaculties.size(), resultFaculties.size(), L"Faculty count mismatch");

			for (size_t i = 0; i < testFaculties.size(); ++i) {
				Assert::AreEqual(testFaculties[i].name, resultFaculties[i].name, L"Faculty name mismatch");

				Assert::AreEqual(testFaculties[i].students.size(), resultFaculties[i].students.size(), L"Student count mismatch");

				for (size_t j = 0; j < testFaculties[i].students.size(); ++j) {
					Assert::AreEqual(testFaculties[i].students[j].group, resultFaculties[i].students[j].group, L"Group mismatch");
					Assert::AreEqual(testFaculties[i].students[j].surname, resultFaculties[i].students[j].surname, L"Surname mismatch");
					Assert::AreEqual(testFaculties[i].students[j].course, resultFaculties[i].students[j].course, L"Course mismatch");
					Assert::AreEqual(testFaculties[i].students[j].averageMark, resultFaculties[i].students[j].averageMark, L"Average mark mismatch");
				}
			}

			// Cleanup: видаляємо тестовий файл
			remove(testFilename.c_str());
		}
	};
}
