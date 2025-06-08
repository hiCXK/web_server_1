#include <proxy_parse.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10

typedef struct cache_element cache_element;

struct cache_element
{
    char* data;
    char* url;
    int len;
    time_t lru_time_track;
    cache_element* next;
};

// returns element from linked list of cached urls
cache_element* find(char* url);

int add_cache_element(char* data, int size,char* url);
void remove_cache_element();

int port_number = 8080; //a port number identifies a specific application on a computer
int proxy_socket_id;

pthread_t tid[MAX_CLIENTS];
sem_t semaphore;
pthread_mutex_t lock;

cache_element* head;
int cache_size;

int main(int argc, char* argv[]){
    int client_socket_id, client_len;
    struct sockaddr_in server_addr, client_addr;
    sem_init(&semaphore, 0, MAX_CLIENTS);
    pthread_mutex_init(&lock, NULL);

    if(argv == 2){
        port_number = atoi(argv[1]);
    }else{
        printf("Too few arguments\n");
        exit(1);
    }
    
    printf("Starting proxy server at port: %d\n", port_number);

    proxy_socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(proxy_socket_id < 0){
        perror("Failed to create a socket");
        exit(1);
    }

    int reuse = 1;
    if(setsockopt(proxy_socket_id, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0){
        perror("setsockopt failed");
    }

    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;


}