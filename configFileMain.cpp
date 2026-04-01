#include "configFile.hpp"

int main()
{
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
    fixConfigFormat(ss);
    std::cout << "->" << ss << "<-" << std::endl;
    
}