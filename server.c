#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>


char* process(char* msg){
    return "";
}

int main(){
    int PORT = 12345;

    int socklocal = socket(AF_INET, SOCK_DGRAM, 0);

    int lg = sizeof(struct sockaddr_in);
    
    struct sockaddr_in local;
    struct sockaddr_in distant;

    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);

    //reset champ addresse
    local.sin_addr.s_addr = INADDR_ANY;
    bzero(&(local.sin_zero),8);

    
    bind(socklocal,(struct sockaddr*)&local, sizeof(struct sockaddr)); //nommage

    char* message_received = malloc(sizeof("char")*1024);

    socklen_t len = sizeof(distant);
    
    recvfrom(socklocal, message_received,lg,0,(struct sockaddr*) &distant, &len);//reçoit la requête et écrit dans l'entête

    char* response = process(message_received);

    int read = sendto(socklocal, response, lg,0,(struct sockaddr*) &distant, sizeof(distant));

    free(message_received);
    
}