/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:19:20 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/13 01:24:10 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct  s_client    {
    int                     id;
    int                     socket;
    char                    msg[4096];
}                           t_client;

typedef struct  s_serv  {
    int                     port;
    int                     socket;
    int                     pool;
    int                     next_id;
    int                     socket_max;
    char                    buf[42*4096];
    char                    send_buf[42*4096];
	struct sockaddr_in      addr;
    t_client                clients[1024];
}                           t_serv;

void    fatal() {
    dprintf(2, "Fatal error\n");
    exit(1);
}

void    transmit_message_to_pool(int sender, t_serv serv)  {
    for (int id = serv.socket; id < 1024; id++)    {
        if (serv.clients[id].socket != sender && serv.clients[id].id != -1) {
            if (send(serv.clients[id].socket, serv.buf, sizeof(serv.buf), 0) < 0)
                fatal();
        }
    }
}

int main(int ac, char **av)  {
    if (ac != 2)    {
        dprintf(2, "Wrong number of arguments\n");
        exit(1);
    }
    t_serv      serv;
    fd_set      reads;
    fd_set      socket_pool;

	if ((serv.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        fatal();
	bzero(&serv.addr, sizeof(serv.addr)); 
	serv.addr.sin_family = AF_INET; 
	serv.addr.sin_addr.s_addr = htonl(2130706433);
	serv.addr.sin_port = htons(atoi(av[1])); 
	if ((bind(serv.socket, (const struct sockaddr *)&serv.addr, sizeof(serv.addr))) < 0)
		fatal();
	if (listen(serv.socket, 0) < 0)
        fatal();

    for (int i = 0; i < 1024; i++)  {
        serv.clients[i].id = -1;
        serv.clients[i].socket = -1;
        bzero(serv.clients[i].msg, sizeof(serv.clients[i].msg));
    }
    serv.pool = 0;
    serv.next_id = 0;
    serv.socket_max = serv.socket;

    FD_ZERO(&socket_pool);
    FD_SET(serv.socket, &socket_pool);

    while (1)   {
        reads = socket_pool;
        bzero(serv.buf, sizeof(serv.buf));
        bzero(serv.send_buf, sizeof(serv.send_buf));
        if ((serv.pool = select(serv.socket_max, &reads, NULL, NULL, NULL)) < 0)
            continue;
        for (int fd = serv.socket; fd <= serv.socket_max; fd++) {
            if (FD_ISSET(fd, &reads))   {
                if (fd == serv.socket)  {
                    struct sockaddr     new_client;
                    int                 new_socket;
                    socklen_t           addr_len = sizeof(new_client);
                    if ((new_socket = accept(serv.socket, (struct sockaddr *)&new_client, &addr_len)) < 0)
                        fatal();
                    if (serv.socket_max < new_socket)
                        serv.socket_max = new_socket;
                    serv.clients[new_socket].id = serv.next_id;
                    serv.clients[new_socket].socket = new_socket;
                    sprintf(serv.buf, "server: client %d just arrived\n", serv.clients[new_socket].id);
                    serv.next_id++;
                    transmit_message_to_pool(new_socket, serv);
                    FD_SET(new_socket, &socket_pool);

                    break ;
                }
                else    {
                    int ret = recv(fd, serv.buf, sizeof(serv.buf), 0);
                    if (ret <= 0)   {
                        sprintf(serv.send_buf, "server: client %d just left\n", serv.clients[fd].id);
                        transmit_message_to_pool(fd, serv);
                        serv.clients[fd].id = -1;
                        serv.clients[fd].socket = -1;
                        bzero(serv.clients[fd].msg, sizeof(serv.clients[fd].msg));
                        FD_CLR(fd, &socket_pool);
                        close(fd);

                        break ;
                    }
                    else    {
                        for (int i = 0, j = strlen(serv.clients[fd].msg); i < ret; i++, j++)    {
                            serv.clients[fd].msg[j] = serv.send_buf[i];
                            if (serv.clients[fd].msg[j] == '\n')    {
                                serv.clients[fd].msg[j] = 0;
                                sprintf(serv.buf, "client %d: %s", serv.clients[fd].id, serv.clients[fd].msg);
                                transmit_message_to_pool(fd, serv);
                                bzero(serv.buf, sizeof(serv.buf));
                                bzero(serv.clients[fd].msg, sizeof(serv.clients[fd].msg));
                            }
                        }
                    }
                }
            }
        }
    }
}