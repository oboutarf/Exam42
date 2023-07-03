/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:07:26 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/03 14:25:15 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* --- INCLUDES --------- */
#include <stdio.h>//	   |
#include <fcntl.h>//	   |
#include <stdlib.h>//      |
#include <unistd.h>//	   |
#include <string.h>//	   |	
#include <sys/socket.h>//  |
#include <netinet/in.h>//  |
/* --- DEFINES ---------- */
#define STDIN 0 //	       |
#define STDOUT 1 //   	   |
#define STDERR 2 //   	   |
#define MAX_CLIENTS 10//   |
#define BUFFER_SIZE 4096// |
/* ---------------------- */

typedef struct		s_client	{
		int fd;
		int id;
}					t_client;

typedef struct		s_server	{
		int 	fd;
		int 	port;
		struct 	sockaddr_in server;
}					t_server;

void	terminate(t_server s)	{ (void)s; (void)listen; }
int	main(int ac, char **av)	{
	if (ac != 2) { dprintf(STDERR, "Wrong number of arguments\n"); exit(EXIT_FAILURE); }
	/* [create SERVER and instantiate it] */
	t_server		s;
	s.port = atoi(av[1]);
	s.fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&s.server, 0, sizeof(s.server));
    s.server.sin_port = htons(s.port);
	s.server.sin_family = AF_INET;
	s.server.sin_addr.s_addr = htonl(2130706433);
	if ( bind(s.fd, (struct sockaddr *)&s.server, sizeof(s.server)) == -1 ) { dprintf(STDERR, "Fatal error\n"); terminate(s); exit(EXIT_FAILURE); }
	if ( listen(s.fd, MAX_CLIENTS) == -1 ) { dprintf(STDERR, "Fatal error\n"); terminate(s); exit(EXIT_FAILURE); }
	/* [instantiate the CLIENT pool [CLIENT fd's manager] ] */
    char 		buf_len[BUFFER_SIZE];
    t_client 	clients[MAX_CLIENTS];
	fd_set		read_fds;
    int max_fd = s.fd;
    for (int i = 0; i < MAX_CLIENTS; i++) { clients[i].id = -1; clients[i].fd = -1; }
	/* [main inifinite loop the SERVER awaits and handles the client connexions] */
	while (1)	{

		dprintf(2, "%s\n", "listening on port 127.0.0.1:9000\n");
	}

	return dprintf(STDOUT, "[mini_serve]: Ciao! Ciao!\n"), EXIT_SUCCESS;

	(void)buf_len;(void)clients;(void)read_fds;(void)max_fd;
}
