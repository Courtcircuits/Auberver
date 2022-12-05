#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>


int main(){
    struct hostent* SERV;

    char* serv_addr = "127.0.0.1";
    int port = 12345;

    int lg = sizeof(struct sockaddr_in);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in distant;

    bzero(&distant, sizeof(distant));

    distant.sin_family = AF_INET;
    distant.sin_port = htons(port);

    SERV = gethostbyname(serv_addr);

    bcopy(SERV, &distant.sin_addr.s_addr, SERV->h_length);

    

    char* message= "Hello World!";

    socklen_t len = sizeof(distant);

    sendto(sockfd, message, lg, 0, (struct sockaddr *)&distant, len);

    char* response = malloc(sizeof(char)*1024);

    recvfrom(sockfd, response, lg,0, (struct sockaddr *)&distant, &len);
    close(sockfd);
    free(response);
}