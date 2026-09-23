CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -Iinclude
export PYTHONDONTWRITEBYTECODE := 1
.PHONY: build run test
build:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp -o build/demonstracao
run: build
	@./build/demonstracao
	@python3 src/main.py
test:
	@python3 tools/testar.py "$(ETAPA)"
