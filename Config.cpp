#include "configFile.hpp"

#define tokens std::vector<std::string>

void parser(tokens &t)
{
	int servers = 0;
	int keyValue = 0;
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i] == "server")
		{
			servers++;
			if (t[i] == "(")
				i++;
			int p = 1;
			while (1)
			{
				if (t[i] == "{") {p++; i++; continue;}
				else if (t[i] == "}") {p--; i++; continue;}

				if (p == 0) { i++; break; }
			}
		}
	}

	std::cout << servers << "|\n";

}