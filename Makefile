flags =  -fsanitize=address -g3 

src			= 	server/config_file/FileMain.cpp \
				server/config_file/FormatValidator.cpp \
				server/config_file/ShapeValidator.cpp \
				server/config_file/parseConfig.cpp \
				server/config_file/Tokenizer.cpp \
				server/config_file/Utils.cpp \
				server/config_file/validateBlocks.cpp \
				server/config_file/validateServerValues.cpp \
				server/config_file/classes/ConfigException.cpp \
				server/config_file/classes/Location.cpp \
				server/config_file/classes/Server.cpp
				
				
				
				
				
				


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
