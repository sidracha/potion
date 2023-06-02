
#include "../includes/potion.hpp"
#include "../includes/tcpserver_unix.hpp"
#include "../includes/threading.hpp"
#include "../includes/test.hpp"


void Potion::run () {
 
  int port = 8080;

  TCPServer* server;
  server = new TCPServer(port);
  ThreadPool threadPool;

  threadPool.start_threads(10, &p_app, server);

  while (1) {
    int socket = server->accept_connection();
    threadPool.add_job(socket);
  }


}
