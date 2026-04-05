flags = #-Wall -Wextra -Werror -fsanitize=address -g3 

src = normalizeConfigFormat.cpp configFileMain.cpp
OBJ			= $(src:.cpp=.o)

NAME = parser

all: $(NAME)

debug:
	valgrind --track-origins=yes ./$(NAME)  
	
#--leak-check=full --show-leak-kinds=all 

$(NAME): $(OBJ)
	c++ $(flags) $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ $(flags) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)


re: fclean all

.PHONY: all fclean re clean
