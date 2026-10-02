#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "File8.h"
#include "WorkWithFiles.h"
void File8() {
	std::cout << "Задание File8" << std::endl;
	std::string file_name_one = PromptForFileName();
	std::string file_name_two = PromptForFileName();;
	std::ifstream file_one;
	std::fstream file_two;
	file_one.open(file_name_one, std::ios::in | std::ios::binary);
	file_two.open(file_name_two, std::ios::out | std::ios::binary);
	double first_num, last_num, current_num;
	file_one.read((char*)&first_num, sizeof(double));// читаем первую цифру
	while (file_one.read((char*)&current_num, sizeof(double))) {//проходим до конца и читаем последнюю цифрй
		last_num = current_num;
	}
	file_two.write((char*)&first_num, sizeof(double));
	file_two.write((char*)&last_num, sizeof(double));// записываем данные в новый файл
	file_one.close();
	file_two.close();
	std::cout << "Программа выполнена, можете проверить содержимое файла через пункт 6 в меню" << std::endl;
}




