/**
 * \brief	Contains functions for the host server.
 *
 */
#define NUM_CONN 5
#define PORT 5000

#include "server.h"

/*
 * A player's address is the address of his listening socket
 */

struct player player_tab[MAXPLAYER];//!< Array of connected players

void error(const char *msg) {
    perror(msg);
    pthread_exit(NULL);
}

/**
 * \brief	Server main thread
 * \returns	0 if success, 1 if error.
 */
int main(int argc, char *argv[]) {
    // Variable declaration
    int serv_sock;
    struct sockaddr_in serv_addr;
    int i = 0;
    int port = 5000;
    pthread_t thread;

    // Construction of the Adress
    // TCP Protocol
    CHECK(serv_sock = socket(AF_INET, SOCK_STREAM, 0), "Error : socket"); /* if = -1 , perror msg*/
    // inet_aton("127.0.0.1", &(serv_addr.sin_addr));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memset(&serv_addr.sin_zero, 0, 8);

    // Bind listening socket with this address
    CHECK((bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))), "Error : bind");

    // Listening
    CHECK(listen(serv_sock, NUM_CONN), "Error : listen");

    while (1) {
        // Waiting for receiving
        player_tab[i].addr_len = sizeof(player_tab[i].addr_d); //!\\ Initialization of each player
        CHECK(player_tab[i].sfd = accept(serv_sock, (struct sockaddr *) &(player_tab[i].addr_d),
                                         &(player_tab[i].addr_len)), "Error : accept");
        // Thread creation
        pthread_create(&thread, NULL, routine_thread, (void *) &(player_tab[i]));
        i++;
    }
}

void disconnectPlayer(struct player *player) {
    for (int i = 0; i < MAXPLAYER; i++) {
        if (strlen(player_tab[i].name) != 0) {
            if (strcmp(player_tab[i].name, player->name) == 0) {
                player->status = OFFLINE;
                break;
            }
        }
    }
};

struct player *searchPlayer(char *name) {
    for (int i = 0; i < MAXPLAYER; ++i) {
        if (strcmp(name, player_tab[i].name) == 0)
            return &player_tab[i];
    }

    return NULL;
}

void *routine_thread(void *arg) {
    // Variable declaration
    struct player *arg_pl = (struct player *) arg;
    char buff[MAXBUFF];
    ssize_t sts;
    char cmd[50];
    char addr[50];
    int port;
    int mode; // 0. Host 1. Join
    char name[50];
    int i = 0;
    arg_pl->status = AVAILABLE;
    while (1) {
        // Receiving a request
        CHECK(sts = recv(arg_pl->sfd, buff, MAXBUFF, 0), "Error : read");
        sscanf(buff, "%s", cmd);
        printf("%s\n", cmd);
        printf("Received : %s \n", buff);
        if (sts == 0) {
            printf("Player %s are exiting.\n", arg_pl->name);
            disconnectPlayer(arg_pl);
            pthread_exit(NULL);
        }
        // Compare the request and execute it
        if (!strcmp("LOGIN", cmd)) {
            // Informations about the player
            sscanf(buff, "LOGIN %s %d %d", arg_pl->name, &port, &mode);

            struct player *temp = searchPlayer(arg_pl->name);
            if (temp != NULL) {
                if (temp->status != OFFLINE &&
                    ((temp->addr_d.sin_addr.s_addr != arg_pl->addr_d.sin_addr.s_addr) ||
                     (temp->addr_d.sin_port != arg_pl->addr_d.sin_port))) {
                    // error same name online
                    printf("Login failed: same name online");

                    sprintf(buff, "LOGIN %s %s", "FAILED", "Login failed: same name online");
                    CHECK(send(arg_pl->sfd, buff, strlen(buff) + 1, 0), "Error : write");

                    arg_pl->status = OFFLINE;
                    pthread_exit(NULL);
                } else {
                    temp->sfd = arg_pl->sfd;
                    temp->addr_d = arg_pl->addr_d;
                    temp->addr_len = arg_pl->addr_len;
                    temp->status = arg_pl->status;
                    arg_pl = temp;
                }
            }
            arg_pl->addr_l = arg_pl->addr_d;
            arg_pl->addr_l.sin_port = htons(port);
            arg_pl->mode = mode;
            // return to client
            sprintf(buff, "LOGIN %s %s", "OK", "Login success");
            CHECK(send(arg_pl->sfd, buff, strlen(buff) + 1, 0), "Error : write");
            //** TEST **//
            printf("Name : %s \t Address : %s \t Port : %d \t Host/Player : %d \n", arg_pl->name,
                   inet_ntoa(arg_pl->addr_l.sin_addr), ntohs(arg_pl->addr_l.sin_port), arg_pl->mode);
            //** FIN TEST **//
        } else if (!strcmp("GAMES", cmd)) // Scan for games
        {
            // Informations about the other players
            for (i = 0; i < MAXPLAYER; i++) {
                if (strlen(player_tab[i].name) != 0 && player_tab[i].status == AVAILABLE &&
                    strcmp(player_tab[i].name, arg_pl->name) != 0) {
                    strcpy(addr, inet_ntoa(player_tab[i].addr_l.sin_addr));
                    sprintf(buff, "GAME %s %s %d %d", player_tab[i].name, addr, ntohs(player_tab[i].addr_l.sin_port),
                            player_tab[i].status);
                    CHECK(send(arg_pl->sfd, buff, strlen(buff) + 1, 0), "Error : write");
                    CHECK(sts = recv(arg_pl->sfd, buff, MAXBUFF, 0), "Error : read"); //!\\ Synchronize

                }
            }
            CHECK(send(arg_pl->sfd, "STOP", strlen("STOP") + 1, 0), "Error : write");


        } else if (!strcmp("JOIN", cmd)) {
            sscanf(buff, "%s %s %s %d", cmd, name, addr, &port);
            for (i = 0; i < MAXPLAYER; i++) {
                if (strlen(player_tab[i].name) != 0 && player_tab[i].status != INGAME) {
                    player_tab[i].status = READY;
                    player_tab[i].opponent = arg_pl;
                    arg_pl->opponent = &player_tab[i];
                }
            }
            arg_pl->status = READY;
            //** TEST **//
            printf("%s Status : %d \t %s Status : %d \n", arg_pl->name, arg_pl->status, arg_pl->opponent->name,
                   arg_pl->opponent->status);
            //** FIN TEST **//
            // Switch the player to "Ready" status
        } else if (!strcmp("START", cmd)) {
            // Switch the player to "IG" status
            arg_pl->status = INGAME;
            arg_pl->opponent->status = INGAME;
            //** TEST **//
            printf("%s Status : %d \t %s Status : %d \n", arg_pl->name, arg_pl->status, arg_pl->opponent->name,
                   arg_pl->opponent->status);
            //** FIN TEST **//
        }
    }
    pthread_exit(NULL);
}
