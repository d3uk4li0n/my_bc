CC=gcc
CFLAGS+=-Wall -Werror -Wextra -g3 -fsanitize=address
DEPS+=./include/my_bc.h 
OBJ+=src/my_bc.o src/string_utils.o src/utility.o src/main.o 
TARGET=my_bc

all: $(TARGET)

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

.PHONY: all clean fclean re
clean:
	rm -f src/*.o 

fclean: clean
	rm -f $(TARGET)

re: fclean all