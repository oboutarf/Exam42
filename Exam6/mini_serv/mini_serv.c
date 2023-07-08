/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:07:26 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/09 00:20:20 by oboutarf         ###   ########.fr       */
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
#define MAX_CLIENTS 10//    |
#define BUFFER_SIZE 200000 + 50//  |
/* ------------------------*/

typedef struct		s_client	{
		int fd;
		int id;
}					t_client;

typedef struct		s_server	{
		int 	port;
		int 	socket;
		struct 	sockaddr_in server;
}					t_server;


void	fatal()					{ dprintf(STDERR, "Fatal error\n"); }
void	terminate(t_server s)	{ (void)s; (void)listen; }

int	main(int ac, char **av)		{
	if (ac != 2) { dprintf(STDERR, "Wrong number of arguments\n"); exit(EXIT_FAILURE); }
	
	t_server		s;
	int next_id = 0;
	s.port = atoi(av[1]);
	s.socket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&s.server, 0, sizeof(s.server));
    s.server.sin_port = htons(s.port);
	s.server.sin_family = AF_INET;
	s.server.sin_addr.s_addr = htonl(2130706433);
	if ( bind(s.socket, (struct sockaddr *)&s.server, sizeof(s.server)) == -1 ) { terminate(s); fatal(); exit(EXIT_FAILURE); }
	dprintf(2, "--- [server] listening on port 9000 ---\n");
	if ( listen(s.socket, MAX_CLIENTS) == -1 ) { terminate(s); fatal(); exit(EXIT_FAILURE); }
    
	int 		clientSockets[MAX_CLIENTS];
	t_client 	clients[MAX_CLIENTS];
    fd_set		activeSockets, readySockets;
  	char 		buf[BUFFER_SIZE];
	int			max_fd = s.socket;
    // for (int i = 0; i < MAX_CLIENTS; i++) { clients[i].id = -1; clients[i].fd = -1; }
	while (1)	{
		FD_ZERO(&activeSockets);
		FD_SET(s.socket, &activeSockets);
		for (int i = 0; i < next_id; i++)
			FD_SET(clientSockets[i], &activeSockets);
		readySockets = activeSockets;
		int activity = select(max_fd + 1, &readySockets, NULL, NULL, NULL);
		if (activity == -1) { dprintf(2, "[mini_serv]: error with select."); terminate(s); return EXIT_FAILURE; }
    	for (int socketId = 0; socketId <= max_fd; socketId++) 
        {
            if (FD_ISSET(socketId, &readySockets)) 
            {
				if (socketId == s.socket) {
					int clientSocket = accept(s.socket, NULL, NULL);
					if (clientSocket < 0)  { perror("Error accepting client connection"); exit(1); }
					FD_SET(clientSocket, &activeSockets);
					if (clientSocket > max_fd)
						max_fd = clientSocket;
					sprintf(buf, "server: client %d just arrived\n", next_id);
					send(clientSocket, buf, strlen(buf), 0);
					dprintf(2, "[%d] client socket\n", clientSocket);
					clientSockets[next_id++] = clientSocket;
                }
                else 
                {
					int bytesRead = recv(socketId, buf, sizeof(buf) - 1, 0);
					if (bytesRead <= 0) {
                    sprintf(buf, "server: client %d just left\n", socketId);
                    for (int i = 0; i < next_id; i++)
                        if (clientSockets[i] != socketId) { send(clientSockets[i], buf, strlen(buf), 0); }
                    close(socketId);
                    FD_CLR(socketId, &activeSockets);
                    } 
					else 
					{
						buf[bytesRead] = '\0';
						char sendBuf[BUFFER_SIZE + 100];
						snprintf(sendBuf, sizeof(sendBuf), "client %d: %s\n", socketId, buf);
						for (int i = 0; i < next_id; i++) {
							if (clientSockets[i] != socketId) {
								send(clientSockets[i], sendBuf, strlen(sendBuf), 0);
							}
                    	}
					}
                }
          	}
        }
	}
	return EXIT_SUCCESS; (void)clients;
}
