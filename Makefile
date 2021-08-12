BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = .
GLFW_LINKER_FLAGS = $(shell pkg-config --static --libs glfw3)
ASSIMP_LINKER_FLAGS = -Lshared -lassimp

main: main.o shader.o glad.o stb_image.o camera.o mesh.o model.o
	$(CXX) -o $(BIN_DIR)/main $(OBJ_DIR)/glad.o $(OBJ_DIR)/shader.o $(OBJ_DIR)/mesh.o $(OBJ_DIR)/model.o $(OBJ_DIR)/camera.o $(OBJ_DIR)/stb_image.o $(OBJ_DIR)/main.o $(GLFW_LINKER_FLAGS) $(ASSIMP_LINKER_FLAGS)

glad.o: glad.c includes/glad.h
	$(CXX) -o $(OBJ_DIR)/glad.o $(SRC_DIR)/glad.c -c

main.o: main.cpp
	$(CXX) -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.cpp -c

shader.o: Shader.cpp includes/Shader.h
	$(CXX) -o $(OBJ_DIR)/shader.o $(SRC_DIR)/Shader.cpp -c

stb_image.o : stb_image.cpp includes/stb_image.h
	$(CXX) -o $(OBJ_DIR)/stb_image.o $(SRC_DIR)/stb_image.cpp -c

camera.o : Camera.cpp includes/Camera.h
	$(CXX) -o $(OBJ_DIR)/camera.o $(SRC_DIR)/Camera.cpp -c

mesh.o : Mesh.cpp includes/Mesh.h
	$(CXX) -o $(OBJ_DIR)/mesh.o $(SRC_DIR)/Mesh.cpp -c

model.o : Model.cpp includes/Model.h
	$(CXX) -o $(OBJ_DIR)/model.o $(SRC_DIR)/Model.cpp -c

clean:
	rm $(BIN_DIR)/* -rf
	rm $(OBJ_DIR)/* -rf