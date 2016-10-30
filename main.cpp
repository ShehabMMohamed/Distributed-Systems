#include <iostream>
#include <netdb.h>
#include <thread>
#include "UDP/UDPSocket.h"
#include "UDP/UDPClientSocket.h"
#include "UDP/UDPServerSocket.h"

using namespace std;

char message_received[50];
auto server = UDPServerSocket();
auto client = UDPClientSocket();
bool flag;

void server_test() {
    server.readFromSocketWithBlock(message_received, 50, 8);
}

void client_test() {
    client.writeToSocket((char *) "Hey shady ya wes5", 8);
}

int main() {
    flag = server.initializeServer((char *) "localhost", 1234);
    //flag = client.initializeClient((char *) "10.40.34.69", 1234);
    flag = client.initializeClient((char *) "localhost", 1234);

    std::thread t1(server_test);
    std::thread t2(client_test);
    t2.join();
    t1.join();
    cout << message_received << endl;
}