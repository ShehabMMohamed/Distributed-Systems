#ifndef DISTRIBUTED_SYSTEMS_REGISTRY_H
#define DISTRIBUTED_SYSTEMS_REGISTRY_H

#include <map>
#include <sqlite3.h>
#include "../common/CM/CM.h"

class Registry {
private:
    CM serverConnector;

    // const char * to be of the same type as columns
    //structs create vectors from database
    struct user {
        int token;
        const char * username;
        const char  *password;

    };

    struct image {
        const char  * img_name;
        const char  * owner_addr;
        int owner_port;

    };

    struct viewable_by {
        const char  * img_name;
        int token;

    };

    // vectors contain the tables of the database
    std::vector<user> usr_DB;
    std::vector<image> img_DB;
    std::vector<viewable_by> viewable_by_DB;


    void load_DBs();
    void update_users();
    void update_imageList();
    void update_viewable_by();

public:
    Registry (char *_listen_hostname, uint16_t _listen_port, int num_of_workers);
    ~Registry();

    void runRegistry();
    void handleRequest(Message request, sockaddr_in);

    // Registry RPC implementations

    int view_imagelist_svc(std::vector<std::string> &image_container, long int token);
    int add_entry_svc(std::string image_name, long int token, char *owner_addr, int owner_port);
    int remove_entry_svc(std::string image_name, long int token);
    int get_client_addr_svc(std::string image_name, std::string &owner_addr, uint16_t &owner_port, long int token);
    int retrieve_token_svc(  char *username,  char * password, long int &token);
    int check_viewImage_svc(std::string image_id, bool &can_view, long int token);
    int check_token(long int token);
};


#endif //DISTRIBUTED_SYSTEMS_REGISTRY_H
