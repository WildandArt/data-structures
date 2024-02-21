
C = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

TARGET = output
NAME = queue
OBJ = $(NAME)_test.o $(NAME).o

$(TARGET): $(OBJ)
	$(C) $(CFLAGS) -o $(TARGET) $(OBJ)

$(CLASSNAME)_test.o: $(NAME)_test.cpp $(NAME).hpp
	$(C) $(CFLAGS) -c $(NAME)_test.cpp

CLASSNAME.o: $(NAME).cpp $(NAME).hpp
		$(C) $(CFLAGS) -c $(NAME).cpp

cl:
	rm -f $(OBJ) $(TARGET)
	clear
run:
	./$(TARGET)
vlg:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)
dump:
	objdump -d $(TARGET) > dump.txt
sym:
	nm $(TARGET)
# strings outDebug #useful to see all
# readelf --symbols a.out
# readelf -s a.out
#objdump -t a.out

#alias gd='gcc -ansi -pedantic-errors -Wall -Wextra -g'
#alias gc='gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3'
#alias gd9='gcc -std=c99 -pedantic-errors -Wall -Wextra -g'
#alias gc9='gcc -std=c99 -pedantic-errors -Wall -Wextra -DNDEBUG -O3'

#alias vlg='valgrind --leak-check=yes --track-origins=yes'
#alias vlgh='valgrind --tool=helgrind'

