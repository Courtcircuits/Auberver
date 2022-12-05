#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>


int main(){

    char* serv_addr = "127.0.0.1";
    int port = 12345;

    int lg = sizeof(struct sockaddr_in);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in distant;
    distant.sin_family = AF_INET;
    distant.sin_port = htons(port);

    distant.sin_addr.s_addr = (in_addr_t *)gethostbyname(serv_addr);

    char* message= "Hello World!";

    sendto(sockfd, message, lg, 0, &distant, sizeof(distant));

    char* response = malloc(sizeof(char)*1024);

    recvfrom(sockfd, response, lg,0, &distant, sizeof(distant));
    close(sockfd);
    free(response);
}