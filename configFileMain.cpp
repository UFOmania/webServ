#include "configFile.hpp"

void tokenizeConfig(std::string & conf, std::vector<std::string> &tokens)
{
    std::stringstream ss(conf);
    std::string str;

    while (ss >> str)
    {
        tokens.push_back(str);
    }
}

#define tokens std::vector<std::string>


void parser(tokens &t)
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

bool validateSyntax(tokens &t);
bool validateShape(tokens &t);

int main()
{
    /*
	std::string ss("servers {\
    server {\
        listen 80;\
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
        locations {\
            location / {\
                root ./www;\
                index index.html;\
                allow_methods GET;\
                auto_index off;\
            }\
\
            location /images {\
                root ./assets/images;\
                allow_methods GET;\
                auto_index on;\
            }\
            location /upload {\
                root ./uploads;\
                upload_path ./uploads;\
                allow_methods POST;\
                client_body_size 500000;\
            }\
            location /delete {\
                root ./data;\
                allow_methods DELETE;\
            }\
            location /old {\
                return 301 ./new;\
            }\
            location /cgi {\
                root ./cgi-bin;\
                allow_methods GET POST;\
                cgi_pass {\
                    .php /usr/bin/php;\
                    .py /usr/bin/phython3;\
                }\
            }\
            location /files {\
                root ./files;\
                auto_index on;\
            }\
            location /alias-test {\
                root ./some/other/path;\
                allow_methods GET;\
            }\
        }\
    }\
}");
*/

	std::string s("server { k v  ;} server { mad max ; kk { hh hh ; }  file ss ; sucks f { gg r ; } }  ff { ff g ;} ");
    normalizeConfigFormat(s);
    // configSyntaxValidator(ss);

	std::vector<std::string> tokenss;
    tokenizeConfig(s, tokenss);

    // std::cout << "->" << s << "<-" << std::endl;

	// parser(tokenss);
	// std::cout << validateSyntax(tokenss) << std::endl;

	bool status = validateShape(tokenss);

    std::cout << "main ends here : " << status <<std::endl;
}



#ifndef syntax
#define syntax

bool validateBlocks( std::string & conf)
{
    int p = 0;
    for(size_t i = 0; i < conf.length() ; ++i)
    {
        switch (conf[i])
        {
            case ('{'): p++; break;
            case ('}'): p--; break;
        }
        if (p < 0) return false;
    }
    return (p == 0);
}

void pr(const char *str)
{
	std::cout << str << std::endl;
}

bool validateSyntax(tokens &t)
{
	bool s = false;
	bool specialK;
	int p = 0;
	for(int i=0; i < t.size(); i++)
	{
		std::cout << "---" << t[i] << " " << s << "----\n";
		if (!s && t[i] == "server")
		{
			s = true;
			pr("server detected");
			continue;
		}
		if (t[i] == "{")
		{
			pr("start block");
			p++; continue;
		}
		else if (t[i] == "}")
		{
			p--;
			// pr("end block");
			std::cout << "end block | p:" << p<< "\n"; 
			if (p == 0)
				s = false;
			continue;
		}
		if (t[i] != "}" && t[i] != "{" && t[i] != ";")
		{
			std::cout <<"key: " << t[i] ;
			i++;
			if (t[i] != "}" && t[i] != "{" && t[i] != ";")
			{
				std::cout <<" | value: " << t[i] << std::endl;
				i++;
				if (t[i] != ";")
					return false;
			}
			
			else
			{
				std::cout << std::endl;
				return false;
			}
			
		
		}
		else
			return false; //bad
		
	}
	return true;
}

bool isWord(std::string & s)
{
	return s != "{" && s != "}" && s != ";"; 
}

void putErr(std::string msg)
{
	std::cerr << "Error:" << msg << std::endl;
}

int detectType(tokens & t, size_t &idx)
{
	/*ex:
	server {  } 		-- group
	location /img {  }	-- special group
	*/

	if (!isWord(t[idx])) //first its always word
	{
		putErr("Invalid '{', '}', ';' position");
		return 0;
	}

	// ---- WORD ----

	idx++;
	if (t[idx] == "{") // ---- WORD { ----
	{
		return 1;
	}
	else if (isWord(t[idx])) // ---- WORD WORD ----
	{
		idx++;
		if (t[idx] == "{") // ---- WORD WORD { ----
			return 2;
		else
		{
			for(; idx < t.size() && isWord(t[idx]); idx++)
				;
			if (t[idx] != ";")
			{
				putErr("Key Value/s is not closed ';'");
				return 0;
			}
			return 3;
		}
	}
	else
	{
		putErr("Invalid sybmol after a WORD");
		return 0; // ---- WORD ; ---- | ---- WORD } ----
	}
}


bool validateShape(tokens &t)
{
	int s = t.size();
	int blockDepth = 0;
	bool freshGroup = false;


	for(size_t i = 0; i < s; i++)
	{
		if(t[i] == "}")
		{
			// std::cout << "End Block detected } --\n";
			if (freshGroup)
			{
				putErr("Empty block is not allowed");
				return false; 
			}
			blockDepth--;
			continue;
		}

		switch (detectType(t, i))
		{
			case (1):
				blockDepth++;
				// std::cout << "group detected \n";
				freshGroup = true;
				break;
			case (2):
				//validate special group
				blockDepth++;
				freshGroup = true;
				// std::cout << "special group detected\n";
				break;
			case (3):
				if (blockDepth == 0)
				{
					putErr("Value outside of a block is not allowed");
					return false;
				}
				freshGroup = false;
				//validate key
				// std::cout << "keyValue detected\n";
				break;
			default://the probleam was here
				//error
				// std::cout << "error detected\n";
				return false;
		}
		
	}
	return true;
}



#endif