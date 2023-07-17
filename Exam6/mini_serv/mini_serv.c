/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:05:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/18 00:11:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <netdb.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>

typedef struct  s_client {
    int     id;
    char    msg[1024];
}               t_client;

char        read_buf[120000], write_buf[120000];
fd_set      sockets, reads, writes;
t_client    clients[1024];
int         fd_max, id_client = 0;

void    ft_error(const char *msg, int len)  {
    write(2, msg, len);
    exit(1);
}

void    send_all(int sender)    {
    for (int i = 0; i <= fd_max; i++) {
        if (FD_ISSET(i, &writes) && i != sender) {
            send(i, write_buf, strlen(write_buf), 0);
        }
    }
}

int main(int ac, char **av) {
    if (ac != 2)
        ft_error("Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
    struct  sockaddr_in servaddr;
    socklen_t           len;
    bzero(&servaddr, sizeof(servaddr));
    bzero(&clients, sizeof(clients));
    servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(atoi(av[1]));
	servaddr.sin_addr.s_addr = htonl(2130706433);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        ft_error("Fatal error\n", strlen("Fatal error\n"));
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        ft_error("Fatal error\n", strlen("Fatal error\n"));
    if (listen(sockfd, 10) < 0)
        ft_error("Fatal error\n", strlen("Fatal error\n"));

    FD_ZERO(&sockets);
    FD_SET(sockfd, &sockets);
    fd_max = sockfd;

    while (1) {
        reads = writes = sockets;
        if (select(fd_max + 1, &reads, &writes, NULL, NULL) < 0)
            continue ;
        for (int fd = 0; fd <= fd_max; fd++) {
            if (FD_ISSET(fd, &reads) && fd == sockfd) {
                int new_connexion = accept(sockfd, (struct sockaddr *)&servaddr, &len);
                if (new_connexion < 0)
                    continue ;
                if (new_connexion > fd_max)
                    fd_max = new_connexion;
                clients[new_connexion].id = id_client++;
                FD_SET(new_connexion, &sockets);
                sprintf(write_buf, "server: client %d just arrived\n", clients[new_connexion].id);
                send_all(new_connexion);
                break ;
            }
            if (FD_ISSET(fd, &reads) && fd != sockfd) {
                int received = recv(fd, read_buf, 65336, 0);
                if (received <= 0) {
                    sprintf(write_buf, "server: client %d just left\n", clients[fd].id);
                    send_all(clients[fd].id);
                    FD_CLR(fd, &sockets);
                    close(fd);
                    break ;
                }
                else {
                    for (int i = 0, j = strlen(clients[fd].msg); i < received; i++, j++) {
                        clients[fd].msg[j] = read_buf[i];
                        if (clients[fd].msg[j] == '\n') {
                            clients[fd].msg[j] = '\0';
                            sprintf(write_buf, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                            send_all(fd);
                            bzero(clients[fd].msg, sizeof(clients[fd].msg));
                        }
                    }
                    break ;
                }
            }
        }
    }
    return 0;
}
