CC = g++
SRC_DIR = ./src
OBJ_DIR = ./obj
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
CFLAGS = -I ./lib/glew-2.1.0/include/ -I ./lib/glfw-3.2.1/include/ -I ./lib/glm/glm/
LDFLAGS = -L ./lib/glfw-3.2.1/lib-mingw-w64/ -lglfw3 -lgdi32 -L ./lib/glew-2.1.0/bin/Release/x64/ -lglew32 -lopengl32 -static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -mwindows

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -std=c++17 -c -o $@ $<

main: $(OBJ)
	mkdir -p build
	cp ./lib/glew-2.1.0/bin/Release/x64/glew32.dll ./build/glew32.dll
	cp -r ./shaders/ ./build/
	cp ./todo.txt ./build/todo.txt
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o ./build/$@
	./build/$@