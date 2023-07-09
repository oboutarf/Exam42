/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:07:26 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/09 21:14:03 by oboutarf         ###   ########.fr       */
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

void	fatal()
	{ dprintf(STDERR, "Fatal error\n"); exit(EXIT_FAILURE); }

int	main(int ac, char **av)		{

	if (ac != 2) { dprintf(STDERR, "Wrong number of arguments\n"); exit(EXIT_FAILURE); }
	char		str[42*4096];

	t_server	server;
	t_client	client[MAX_CLIENTS];
	fd_set		reads;
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
	
	FD_ZERO(&reads);
	FD_SET(server.socket_fd, &reads);
	server.activity = -1;
	server.new_client = 0;
	server.max_socket_fd = server.socket_fd;
	while (1)	{
		if ((server.activity = select(server.max_socket_fd + 1, &reads, NULL, NULL, NULL)) < 0)
			fatal();
		dprintf(2, "LOOP");
		for (int fd = 0; fd <= server.max_socket_fd; fd++)
		{
			if (FD_ISSET(fd, &reads))	{
				if (fd == server.socket_fd)	{
					struct sockaddr_in client_connexion;
					socklen_t len = sizeof(client_connexion);
					if ((client[server.new_client].socket_fd = accept(server.socket_fd, (struct sockaddr *)&client_connexion, &len)) < 0)
						fatal();
					client[server.new_client].id = server.new_client;
					if (client[server.new_client].socket_fd > server.max_socket_fd)
						server.max_socket_fd = client[server.new_client].socket_fd;
					dprintf(2, "[mini serve]: accept [client %d] on socket_fd: %d\n", client[server.new_client].id, client[server.new_client].socket_fd);
					FD_SET(client[server.new_client].socket_fd, &reads);
					FD_CLR(server.socket_fd, &reads);
				}
				else	{
					
				}
			}
		}
		// for (int fd = 0; fd < server.max_socket_fd; fd++)	{
		// 	if (FD_ISSET(fd, &reads))	{
		// 		dprintf(2, "%s\n", "catched");
		// 		if (fd == server.socket_fd)	{
		// 			struct sockaddr_in client_addr;
		// 			socklen_t client_addr_len = sizeof(client_addr);
		// 			int new_socket = accept(server.socket_fd, (struct sockaddr *)&client_addr, &client_addr_len);
		// 			if (new_socket < 0)
		// 				fatal();
		// 			FD_SET(new_socket, &reads);
		// 			if (new_socket > server.max_socket_fd)
		// 				server.max_socket_fd = new_socket;
		// 			int client_id = server.new_client;
		// 			client[server.new_client].id = client_id;
		// 			client[server.new_client].socket_fd = new_socket;
		// 			server.new_client++;
		// 		}
		// 		else {
		// 			int ret_recv = 1000;
		// 			while (ret_recv == 1000 || str[strlen(str) - 1] != '\n')
		// 			{
		// 				ret_recv = recv(fd, str + strlen(str), 1000, 0);
		// 				if (ret_recv <= 0)
		// 					break ;
		// 			}
		// 			dprintf(2, "%s", str);
		// 		}
		// 	}
		// }
	}
	(void)str;
	(void)client;
	return EXIT_SUCCESS;
}













		// for (int fd = 0; fd <= get_max_fd(); fd++)
		// 		{
        //     if (FD_ISSET(fd, &cpy_read))
        //     {
        //         if (fd == sock_fd)
        //         {
        //             bzero(&msg, sizeof(msg));
        //             add_client();
        //             break;
        //         }
        //         else
        //         {
		// 	int ret_recv = 1000;
		// 	while (ret_recv == 1000 || str[strlen(str) - 1] != '\n')
		// 	{
		// 		ret_recv = recv(fd, str + strlen(str), 1000, 0);
		// 		if (ret_recv <= 0)
		// 			break ;
		// 	}
        //             if (ret_recv <= 0)
        //             {
        //                 bzero(&msg, sizeof(msg));
        //                 sprintf(msg, "server: client %d just left\n", rm_client(fd));
        //                 send_all(fd, msg);
        //                 FD_CLR(fd, &curr_sock);
        //                 close(fd);
        //                 break;
        //             }
        //             else
        //             {
        //                 ex_msg(fd);
        //             }
        //         }
        //     }