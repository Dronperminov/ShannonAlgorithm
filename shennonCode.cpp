#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>

struct ShennonT {
	char character; // символ
	double p; // вероятность третить этот символ (частота встречаемости
	double b; // коээфициент для алгоритма
	int L; // длинак двоичного кода
};

// перевод вещественного числа в двоичное представление с заданным числом разрядов (symbol.L)
/*
Пример: b = 0.45, L = 4

 0.45
*   2
-----
 0.90 (старшая цифра - 0, result = "0", v = 0.9)
*   2
-----
 1.80 (старшая цифра - 1, result = "01", v = 0.8)
*   2
-----
 1.60 (старшая цифра - 1, result = "011", v = 0.6)
*   2
-----
 1.20 (старшая цифра - 1, result = "0111", v = 0.2)

Итог: 0111
*/

std::string convert(ShennonT elem) {
	std::string result = "";

	for (int i = 0; i < elem.L; i++) {
		elem.b *= 2;  // умножаем на 2 для получения нового старшего разряда

		result += elem.b >= 1 ? "1" : "0"; // если после умножения вышла единица в значащий разряд, то прибавляем строку с 1 к результату и вычитаем единицу из числа, чтобы не портить данные

		if (elem.b >= 1)
			elem.b -= 1; // зануляем старший разряд, если он стал равен 1
	}

	return result;
}

int main() {
	std::string s; // строка для ввода данных
	std::cout << "Enter string: "; // выводим сообщение - приглашение ко вводу
	getline(std::cin, s); // считыфваем строку

	ShennonT* symbols = new ShennonT[s.length()]; // создаём массив структур типа ShennonT для вычисления кодов

	int size = 0; // число уникальных символов для кодирования
	for (int i = 0; i < s.length(); i++) { // проходимся по всем символам строки
		int j = 0; // начинаем искать в созданном массиве символов с нулевого элемента

		// идём до тех пор, пока не кончится массив или пока не встретим такой символ в массиве
		while (j < size && symbols[j].character != s[i])
			j++;

		// если индекс стал равен размеру массива, то символа в массиве нет и нужно его туда добавить
		if (j == size) {
			symbols[size].character = s[i];
			symbols[j].p = 1.0 / s.length(); // вычисляем вероятность
			size++;
		}
		else
			symbols[j].p += 1.0 / s.length(); // увеличиваем значение вкероятности

		symbols[j].L = -log2(symbols[j].p) + 1; // считаем число бит для кода
	}

	// сортируем по частоте встречания символов
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++)
			if (symbols[j].p < symbols[j + 1].p) {
				ShennonT tmp = symbols[j];
				symbols[j] = symbols[j + 1];
				symbols[j + 1] = tmp;
			}
	}

	// считаем числа bx
	symbols[0].b = 0;
	for (int i = 1; i < size; i++)
		symbols[i].b = symbols[i - 1].b + symbols[i - 1].p;

	// выводим полученные значения
	std::cout << "+-----+------+------+-----+------+" << std::endl;
	std::cout << "|  A  |  Px  |  Bx  |  L  | Code |" << std::endl;
	std::cout << "+-----+------+------+-----+------+" << std::endl;

	for (int i = 0; i < size; i++) {
		std::string code = convert(symbols[i]);
		printf("|  %c  | %4.2lf | %4.2lf | %3d | %4s |\n", symbols[i].character, symbols[i].p, symbols[i].b, symbols[i].L, code.c_str()); // выводим полученные данные в табличку
	}

	std::cout << "+-----+------+------+-----+------+" << std::endl;
	system("pause"); // задерживаем экран для того, чтобы окно сразу не закрылось
}
