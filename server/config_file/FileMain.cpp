#include "configFile.hpp"


void parser(Configtokens &t)
{
	int servers = 0;
	std::string v1, v2;

	for (size_t i = 0; i < t.size(); i++)
	{
		std::cout << "1\n";
		if (t[i] == "server")
		{
			i++;
			servers++;
			// std::cout << i << "<\n";
			if (t[i] == "{")
			{
				i++;
			}

			int p = 1;
			
			while (1)
			{
				if (t[i] == "{") {
					p++;
					i++;
					continue;
				}
				else if (t[i] == "}") {
					p--;
					if (p == 0)
						break;
					i++;
					continue;
				}

				if (t[i] == "k")
					v1 = t[++i];
				else if(t[i] == "k1")
					v2 = t[++i];
				i++;
			}
		}
		std::cout << "v1:" << v1 << "| v2:"<< v2 << std::endl;
	}
}



int main()
{
    
	std::string ss("server {\
    listen 127.0.0.1:805;\
    server_name google;\
    root ./www;\
    index index.html;\
    client_body_size 10000;\
\
    error_page {\
        404 page_not_found.html;\
        501 server_error.html;\
    }\
\
    location /files {\
        root ./files jj;\
        auto_index on;\
    }\
    location /alias-test {\
        root ./some/other/path;\
        allow_methods GET;\
    }\
    \
}\
\
\
server {\
    listen 80;\
    client_body_size 10000;\
\
    location /images {\
        root ./assets/img;\
        allow_methods GET;\
        auto_index on;\
    }\
}");


	std::string s("server { k v  ;} server { mad max ; kk { hh hh ; }  file ss ; sucks f { gg r ; } }  ff { ff g ;} ");
    normalizeConfigFormat(ss);
    // configSyntaxValidator(ss);
    validateBlocks(ss);


	Configtokens tokens;
    tokenizeConfig(ss, tokens);
	bool status = validateShape(tokens);
    parse(tokens);

    int *a;
    int64_t b = (int64_t)a;


    std::cout << "main ends here : " << status <<std::endl;
}









