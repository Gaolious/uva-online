CC = g++
#CFLAGS = -g -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
CFLAGS = -g -lm -lcrypt -O0 -pipe 
LDFLAGS =
LIBS = 
TARGET = UVA
.SUFFIXES : .cpp .c .o 

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJ) -o $(TARGET)
	echo "Complete"

obj/%.o: src/%.cpp
	[ -d obj ] || mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(TARGET) core
