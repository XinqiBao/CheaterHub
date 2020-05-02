#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "wordscapes/wordscapes.h"

#define PORT 2020

std::queue<std::pair<int, std::string>> qu;

std::mutex mtx_th;
std::mutex mtx_qu;

Wordscapes ws;

void thread_on_msg(int i)
{
    while (true)
    {
        mtx_th.lock();

        mtx_qu.lock();
        if (qu.empty())
        {
            mtx_qu.unlock();
            continue;
        }
        int client_fd   = qu.front().first;
        std::string msg = qu.front().second;
        qu.pop();
        mtx_qu.unlock();

        // do msg
        std::cout << "Thread " << i << " receive: " << msg << std::endl;

        std::vector<std::string> msg_vt;
        boost::split(msg_vt, msg, boost::is_any_of(";"));

        auto result = ws.solve(msg_vt[0], msg_vt[1]);

        std::string ret = "";
        for (auto& res : result) ret += res + ';';

        send(client_fd, ret.c_str(), ret.size(), 0);
        std::cout << "Thread " << i << " send: " << ret << std::endl;

        close(client_fd);

        mtx_qu.lock();
        if (!qu.empty()) mtx_th.unlock();
        mtx_qu.unlock();
    }
}

int main()
{
    struct sockaddr_in server_addr;
    struct sockaddr_storage client_addr;
    int addrlen                 = sizeof(server_addr);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) <
        0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::thread threads[5];
    for (int i = 0; i < 5; i++) threads[i] = std::thread(thread_on_msg, i);

    while (true)
    {
        socklen_t clientAddr_len = sizeof(client_addr);
        int new_socket =
            accept(server_fd, (struct sockaddr*)&client_addr, &clientAddr_len);
        char buffer[1024] = {0};
        recv(new_socket, buffer, 1024, 0);

        mtx_qu.lock();
        qu.push({new_socket, std::string(buffer)});
        mtx_qu.unlock();
        mtx_th.unlock();
    }
    for (int i = 0; i < 5; i++) threads[i].join();

    return 0;
}
