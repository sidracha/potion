#ifndef TCPSERVER_UNIX_H_INCLUDED
#define TCPSERVER_UNIX_H_INCLUDED

class TCPServer {
  private:
    int portno;
    int sockfd;
    int newsockfd;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;

  public:
    TCPServer(int port);
    void acceptConnection();
    std::string receive();
    void send(const std::string& message);
    void closeConnection();
  
  private:
    void error(const char *msg);
};

#endif
