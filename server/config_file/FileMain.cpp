#include "configFile.hpp"


#include <fstream>

int main(int ac, char **av)
{

	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <config_file_path>" << std::endl;
		return 1;
	}
	std::ifstream file(av[1]);

	std::string ss;
	std::string s;
	while (std::getline(file, s))
		ss +=  s + "\n";


	try
	{
		Configtokens tokens;
		std::vector < Server > servers;


		normalizeConfigFormat(ss);
		validateBlocks(ss);
		tokenizeConfig(ss, tokens);
		validateShape(tokens);
		
		// for(int i = 0; i < tokens.size(); i++)
		// 	std::cout << "[" << i << "] -> [" << tokens[i] << "]" << std::endl;


		parseConfig(tokens, servers);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}









