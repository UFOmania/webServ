flags = -Wall -Wextra -Werror -fsanitize=address -g3

src = normalizeConfigFormat.cpp

all:
	c++ normalizeConfigFormat.cpp configFileMain.cpp  configSyntaxValidator.cpp && ./a.out
