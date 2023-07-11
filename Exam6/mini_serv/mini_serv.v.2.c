/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.v.2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:59:07 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/11 13:28:45 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>

typedef struct s_client   {
    int                 id;
    int                 socket;
    char                msg[1024];
}                       t_client;

typedef struct s_serv   {
    int                 port;
    int                 socket;
    int                 pool_fd;
    int                 id_dispatch;
    int                 socket_max;
    char                read_buf[120000];
    fd_set              reads;
    fd_set              sockets;
    t_client            clients[1024];
    struct sockaddr_in  addr;
}                       t_serv;



void    check_argument(int ac)    {
    if (ac != 2)    {
        dprintf(2, "Wrong number of arguments\n");
        exit(1);
    }
}

void    fatal() {
    dprintf(2, "Fatal error\n");
    exit(1);
}

void    initialise_clients(t_serv serv)    {
    for (int i = 0; i < 1024; i++)   {
        serv.clients[i].id = -1;
        serv.clients[i].socket = -1;
        bzero(serv.clients[i].msg, sizeof(serv.clients[i].msg));
    }
}

void    disconnect_user(t_serv serv)   {
    (void)serv;
    dprintf(2, "server: big need to disconnect user.");
}

void    add_new_client(t_serv serv)    {
    (void)serv;
    dprintf(2, "Client added.");
}

void    transmit_message_to_pool(t_serv serv, int fd)  {
    for (int i = serv.socket; i <= serv.socket_max; i++)   {
        if (serv.clients[i].socket > serv.socket && serv.clients[i].socket != fd)   {
            dprintf(2, "client: [id %d] [socket %d]\n", serv.clients[i].id, serv.clients[i].socket);
            if (send(serv.clients[i].socket, serv.read_buf, strlen(serv.read_buf), 0) < 0)
                fatal();
        }
    }
    bzero(serv.read_buf, sizeof(serv.read_buf));
}

int main(int ac, char **av)  {
    check_argument(ac);
    t_serv      serv;

    serv.addr.sin_port = htons(atoi(av[1]));
    serv.addr.sin_family = AF_INET;
    serv.addr.sin_addr.s_addr = htonl(2130706433);
    if ((serv.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        fatal();
    if ((bind(serv.socket, (const struct sockaddr *)&serv.addr, sizeof(serv.addr))) < 0)
        fatal();
    if (listen(serv.socket, 0) < 0)
        fatal();
    serv.id_dispatch = 0;
    serv.socket_max = serv.socket;
    initialise_clients(serv);
    FD_ZERO(&serv.sockets);
    FD_SET(serv.socket, &serv.sockets);
    while (1)   {
        serv.reads = serv.sockets;
        if ((serv.pool_fd = select(serv.socket_max + 1, &serv.reads, NULL, NULL, NULL)) < 0)
            continue ;
        for (int fd = serv.socket; fd <= serv.socket_max; fd++) {
            if (FD_ISSET(fd, &serv.reads))   {
                if (fd == serv.socket)  {
                    struct sockaddr_in  new_client;
                    int                 new_socket;
                    socklen_t           new_addr_len = sizeof(new_client);
                    if ((new_socket = accept(fd, (struct sockaddr *)&new_client, &new_addr_len)) < 0)
                        fatal();
                    dprintf(2, "%d\n", new_socket);
                    if (new_socket > serv.socket_max)
                        serv.socket_max = new_socket;
                    serv.clients[new_socket].id = serv.id_dispatch++;
                    serv.clients[new_socket].socket = new_socket;
                    bzero(serv.clients[new_socket].msg, sizeof(serv.clients[new_socket].msg));
                    sprintf(serv.read_buf, "server: client %d just arrived\n", serv.clients[new_socket].id);
                    transmit_message_to_pool(serv, new_socket);
                    FD_SET(new_socket, &serv.sockets);
                    break ;
                }
                else
                {
                    int read_bytes = recv(fd, serv.read_buf, sizeof(serv.read_buf), 0);
                    if (read_bytes <= 0)    {
                        sprintf(serv.read_buf, "server: client %d just left\n", serv.clients[fd].id);
                        transmit_message_to_pool(serv, fd);
                        serv.clients[fd].id = -1;
                        serv.clients[fd].socket = -1;
                        bzero(serv.clients[fd].msg, sizeof(serv.clients[fd].msg));
                        FD_CLR(fd, &serv.sockets);
                        close(fd);
                        break ;
                    }
                    else    {
                        for (int i = 0, j = strlen(serv.clients[fd].msg); i < read_bytes; i++, j++)    {
                            serv.clients[fd].msg[j] = serv.read_buf[i];
                            if (serv.clients[fd].msg[j] == '\n')   {
                                serv.clients[fd].msg[j] = 0;
                                bzero(serv.read_buf, sizeof(serv.read_buf));
                                sprintf(serv.read_buf, "client %d: %s\n", serv.clients[fd].id, serv.clients[fd].msg);
                                bzero(serv.clients[fd].msg, sizeof(serv.clients[fd].msg));
                                transmit_message_to_pool(serv, fd);
                            }
                        }
                    }
                }
            }
        }
    }
}
