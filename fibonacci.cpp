#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>
#include <stdexcept>

/**
 * Класс для вычисления чисел Фибоначчи
 */
class FibonacciCalculator {
public:
    /**
     * Вычисляет n-е число Фибоначчи (итеративный метод)
     * @param n порядковый номер числа Фибоначчи (0-50)
     * @return n-е число Фибоначчи
     * @throws std::invalid_argument при некорректном входе
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
        
        for (int i = 2; i <= n; ++i) {
            long long next = prev + curr;
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
        
        for (char c : str) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        
        try {
            result = std::stoi(str);
            return result >= 0 && result <= 50;
        } catch (const std::exception&) {
            return false;
        }
    }
};

/**
 * Основная функция программы
 */
int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "  Fibonacci Number Calculator v1.0" << std::endl;
    std::cout << "  Вариант 1: Последовательность Фибоначчи" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    std::string input;
    int n;
    
    // Если аргумент передан через командную строку
    if (argc == 2) {
        input = argv[1];
        if (FibonacciCalculator::isValidNumber(input, n)) {
            try {
                auto start = std::chrono::high_resolution_clock::now();
                long long result = FibonacciCalculator::calculate(n);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                
                std::cout << "F(" << n << ") = " << result << std::endl;
                std::cout << "Время вычисления: " << duration.count() << " мкс" << std::endl;
                return 0;
            } catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Ошибка: некорректный аргумент. Используйте число от 0 до 50." << std::endl;
            return 1;
        }
    }
    
    // Интерактивный режим
    while (true) {
        std::cout << "Введите целое число n (0-50) или 'q' для выхода: ";
        std::getline(std::cin, input);
        
        if (input == "q" || input == "Q" || input == "quit") {
            std::cout << "До свидания!" << std::endl;
            break;
        }
        
        if (FibonacciCalculator::isValidNumber(input, n)) {
            try {
                auto start = std::chrono::high_resolution_clock::now();
                long long result = FibonacciCalculator::calculate(n);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                
                std::cout << "Результат: F(" << n << ") = " << result << std::endl;
                std::cout << "Время вычисления: " << duration.count() << " мкс" << std::endl;
                std::cout << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Ошибка: введите целое число от 0 до 50!" << std::endl;
            std::cout << std::endl;
        }
    }
    
    return 0;
}