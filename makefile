# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
LDFLAGS = 

# Имя исполняемого файла
TARGET = fibonacci

# Исходные файлы
SRCS = fibonacci.cpp
OBJS = $(SRCS:.cpp=.o)

# Цветной вывод (для красоты)
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Цель по умолчанию
all: $(TARGET)
	@echo "${GREEN}✓ Сборка завершена. Исполняемый файл: $(TARGET)${NC}"

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "  Компиляция $<"

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Отладка (сборка с отладочной информацией)
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean $(TARGET)

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "${GREEN}✓ Очистка завершена${NC}"

# Установка в систему
install: $(TARGET)
	@echo "Установка $(TARGET) в /usr/local/bin/"
	sudo install -d /usr/local/bin
	sudo install -m 755 $(TARGET) /usr/local/bin/$(TARGET)
	@echo "${GREEN}✓ Установка завершена${NC}"

# Удаление из системы
uninstall:
	@echo "Удаление $(TARGET) из /usr/local/bin/"
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "${GREEN}✓ Удаление завершено${NC}"

# Проверка зависимостей
check:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "${RED}✗ Ошибка: $(CXX) не установлен.${NC}\n  Установите: sudo apt install build-essential"; exit 1; }
	@echo "${GREEN}✓ Все зависимости установлены${NC}"

# Помощь
help:
	@echo "Доступные команды:"
	@echo "  make          - Собрать программу"
	@echo "  make run      - Собрать и запустить программу"
	@echo "  make debug    - Собрать с отладочной информацией"
	@echo "  make clean    - Очистить собранные файлы"
	@echo "  make install  - Установить программу в систему"
	@echo "  make uninstall- Удалить программу из системы"
	@echo "  make check    - Проверить наличие компилятора"

.PHONY: all run debug clean install uninstall check help
