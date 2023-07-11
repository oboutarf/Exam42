/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.v.1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:07:26 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/11 00:40:14 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* --- INCLUDES -----------*/
# include <stdio.h>//	    |
# include <fcntl.h>//	    |
# include <stdlib.h>//      |
# include <unistd.h>//	    |
# include <string.h>//	    |	
# include <sys/socket.h>//  |
# include <netinet/in.h>//  |
# include <sys/select.h>//  |
/* --- DEFINES ------------*/
#define STDIN 0 //	        |
#define STDOUT 1 //   	    |
#define STDERR 2 //   	    |
#define MAX_CLIENTS 20//    |
#define BUFFER_SIZE 200000 + 50//  |
/* ------------------------*/

typedef struct			s_client	{
	int 				id;
	int 				socket_fd;
}						t_client;

typedef struct			s_server	{
	int 				port;
	int					activity;
	int 				socket_fd;
	int 				new_client;
	int					max_socket_fd;
	struct 	sockaddr_in server_addr;
}						t_server;

void	fatal() { dprintf(STDERR, "Fatal error\n"); exit(EXIT_FAILURE); }
int		get_socket_id(int fd, t_client *client)	{ for (int i = 0; i < MAX_CLIENTS; i++)	{ if (client[i].socket_fd == fd) {return client[i].id;} } return -1; }


void	transmit_client_message(t_client *client, char *buffer, int sender_id)	{
	for (int i = 0; i < MAX_CLIENTS; i++)	{
		if (client[i].id != -1 && client[i].id != sender_id)	{
			int byte_send = send(client[i].socket_fd, buffer, strlen(buffer), 0);
			if (byte_send < 0)
				fatal();
		}
	}
}

void	destroy_client(int fd, t_client *client)	{
	char 	buffer[4096];
	int	client_id = get_socket_id(fd, client);
	if (client_id == -1)
		return ;
	client[client_id].id = -1;
	client[client_id].socket_fd = -1;
	sprintf(buffer, "server: client %d just left\n", client_id);
	dprintf(2, "server: client %d just left\n", client_id);
	transmit_client_message(client, buffer, client_id);
}

int	main(int ac, char **av)		{

	if (ac != 2) { dprintf(STDERR, "Wrong number of arguments\n"); exit(EXIT_FAILURE); }
	char		str[4096 * 42];

	t_server	server;
	t_client	client[MAX_CLIENTS];
	fd_set		sockets, reads;
	server.port = atoi(av[1]);
	bzero(&server.server_addr, sizeof(server.server_addr));
	server.server_addr.sin_family = AF_INET;
	server.server_addr.sin_port = htons(server.port);
	server.server_addr.sin_addr.s_addr = htonl(2130706433);
	if ((server.socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		fatal();
	if (bind(server.socket_fd, (const struct sockaddr *)&server.server_addr, sizeof(server.server_addr)) < 0)
		fatal();
	 if (listen(server.socket_fd, 0) < 0)
        fatal();
	for (int i = 0; i < MAX_CLIENTS; i++)	{ client[i].id = -1; client[i].socket_fd = -1; }
	server.activity = -1;
	server.new_client = 0;
	server.max_socket_fd = server.socket_fd;


	FD_ZERO(&sockets);
	FD_SET(server.socket_fd, &sockets);
	while (1)	{
		reads = sockets;
		if ((server.activity = select(server.max_socket_fd + 1, &reads, NULL, NULL, NULL)) < 0)
			fatal();
		for (int fd = server.socket_fd; fd <= server.max_socket_fd; fd++)
		{
			char buffer[1024];
			if (FD_ISSET(fd, &reads))	{
				if (fd == server.socket_fd)	{
					struct sockaddr_in client_connexion;
					socklen_t len = sizeof(client_connexion);
					if ((client[server.new_client].socket_fd = accept(server.socket_fd, (struct sockaddr *)&client_connexion, &len)) < 0)
						fatal();
					client[server.new_client].id = server.new_client;
					if (client[server.new_client].socket_fd > server.max_socket_fd)
						server.max_socket_fd = client[server.new_client].socket_fd;
					sprintf(buffer, "server: client %d just arrived\n", client[server.new_client].id);
					int	new_client_id = get_socket_id(fd, client);
					transmit_client_message(client, buffer, new_client_id);
					FD_SET(client[server.new_client].socket_fd, &sockets);
					server.new_client++;
					break ;
				}
				else	{
					int num_bytes = recv(fd, buffer, sizeof(buffer), 0);
					if (num_bytes <= 0)	{
						destroy_client(fd, client);
						FD_CLR(fd, &sockets);
						close(fd);
						server.new_client--;
						break ;
					}
					else	{
						int sender_id = get_socket_id(fd, client);
						char new_buffer[2048];
						bzero(new_buffer, sizeof(new_buffer));
						sprintf(new_buffer, "client %d: %s", sender_id, buffer);
						transmit_client_message(client, new_buffer, sender_id);
					}
				}
			}
			bzero(buffer, sizeof(buffer));
		}
	}
	(void)str;(void)client;
	return EXIT_SUCCESS;
}
