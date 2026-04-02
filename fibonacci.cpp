#include <iostream>
#include <string>
#include <cctype>
#include <chrono>

/**
 * Класс для вычисления чисел Фибоначчи
 */
class FibonacciCalculator {
public:
    /**
     * Вычисляет n-е число Фибоначчи (итеративный метод)
     * @param n порядковый номер числа Фибоначчи (0-50)
     * @return n-е число Фибоначчи
     * @throws std::invalid_argument если n < 0 или n > 50
     */
    static long long calculate(int n) {
        // Проверка корректности входных данных
        if (n < 0) {
            throw std::invalid_argument("Число не может быть отрицательным");
        }
        if (n > 50) {
            throw std::invalid_argument("Число слишком велико (максимум 50)");
        }
        
        // Итеративное вычисление
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        long long prev = 0;
        long long curr = 1;
        long long next;
        
        for (int i = 2; i <= n; ++i) {
            next = prev + curr;
            prev = curr;
            curr = next;
        }
        
        return curr;
    }
    
    /**
     * Проверяет, является ли строка корректным целым неотрицательным числом
     */
    static bool isValidNumber(const std::string& str, int& result) {
        if (str.empty()) return false;
        
        // Проверяем, что все символы - цифры
        for (char c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        
        try {
            result = std::stoi(str);
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
};

/**
 * Основная функция программы
 */
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Программа вычисления чисел Фибоначчи" << std::endl;
    std::cout << "  Вариант 1: Последовательность Фибоначчи" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    std::string input;
    int n;
    
    // Цикл для корректного ввода
    while (true) {
        std::cout << "Введите целое неотрицательное число n (0-50): ";
        std::getline(std::cin, input);
        
        // Проверка на пустой ввод
        if (input.empty()) {
            std::cout << "Ошибка: Ввод не может быть пустым!" << std::endl;
            continue;
        }
        
        // Проверка на корректность числа
        if (FibonacciCalculator::isValidNumber(input, n)) {
            // Проверка диапазона
            if (n >= 0 && n <= 50) {
                break;
            } else {
                std::cout << "Ошибка: Число должно быть в диапазоне от 0 до 50!" << std::endl;
            }
        } else {
            std::cout << "Ошибка: Введите целое неотрицательное число!" << std::endl;
        }
    }
    
    // Вычисление и вывод результата
    try {
        auto start = std::chrono::high_resolution_clock::now();
        long long result = FibonacciCalculator::calculate(n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << std::endl;
        std::cout << "Результат вычислений:" << std::endl;
        std::cout << "  Fibonacci(" << n << ") = " << result << std::endl;
        std::cout << "  Время вычисления: " << duration.count() << " микросекунд" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << std::endl;
    std::cout << "Программа завершена. Нажмите Enter для выхода...";
    std::cin.get();
    
    return 0;
}
