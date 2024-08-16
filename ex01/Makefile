NAME= RPN

SRC= main.o RPN.o
SRC+= 

HEADERS= 
CC= c++

val = -ggdb3
CPPFLAGS +=	-Wall -Werror -Wextra
# CPPFLAGS += -g $(val)
# CPPFLAGS +=	-std=c++98

all:$(NAME)

$(NAME): $(SRC)
	$(CC) $(CPPFLAGS) -o $@ $^
%.o:%.cpp $(HEADERS)
	$(CC) -c $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(SRC)
fclean:
	rm -rf $(SRC) $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

vgrind: all
	valgrind --leak-check=full ./$(NAME)

r: all
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	# ./$(NAME) "8 (1 + 1)"

.PHONY: all clean fclean re r vgrind