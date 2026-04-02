# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -DNDEBUG
DEBUG_FLAGS = -g -O0 -DDEBUG
LDFLAGS = 

# Директории
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# Исходные файлы
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Исполняемые файлы
TARGET = $(BIN_DIR)/fibonacci
TEST_TARGET = $(BIN_DIR)/test_fibonacci

# Цель по умолчанию
all: directories $(TARGET)

# Создание директорий
directories:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Сборка основной программы
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "✓ Сборка завершена: $(TARGET)"
	@echo "  Запустите программу: ./$(TARGET)"

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка тестов
$(TEST_TARGET): $(TEST_DIR)/test_fibonacci.cpp | directories
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_fibonacci.cpp -o $(TEST_TARGET)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Отладочная сборка
debug: CXXFLAGS = $(DEBUG_FLAGS)
debug: clean all
	@echo "✓ Отладочная сборка завершена"

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✓ Очистка завершена"

# Установка (для deb-пакета)
install: all
	install -d $(DESTDIR)/usr/local/bin
	install -m 755 $(TARGET) $(DESTDIR)/usr/local/bin/fibonacci

# Проверка наличия компилятора
check-deps:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "✗ Ошибка: $(CXX) не установлен"; exit 1; }
	@echo "✓ Все зависимости установлены"

.PHONY: all directories run test debug clean install check-deps