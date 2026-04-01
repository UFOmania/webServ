flags = -Wall -Wextra -Werror -fsanitize=address -g3

src = normalizeConfigFormat.cpp

all:
	c++ fixFormat.cpp configFileMain.cpp 
