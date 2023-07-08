/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:06:47 by oboutarf          #+#    #+#             */
/*   Updated: 2023/07/09 00:11:59 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 3) { printf("Usage: %s <server IP> <server port>\n", argv[0]); exit(EXIT_FAILURE); }

    const char *serverIP = argv[1];
    int serverPort = atoi(argv[2]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) { perror("socket"); exit(EXIT_FAILURE); }
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP, &(serverAddr.sin_addr)) <= 0) { perror("inet_pton"); exit(EXIT_FAILURE); }
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) { perror("connect"); exit(EXIT_FAILURE); }
    
    while (1)   {
        char message[BUFFER_SIZE];
        printf("Enter your message (or 'exit' to quit): ");
        fgets(message, BUFFER_SIZE, stdin);
        size_t len = strlen(message);
        if (len > 0 && message[len - 1] == '\n') { message[len - 1] = '\0'; }
        if (strcmp(message, "exit") == 0) { break;  }
        if (send(sockfd, message, strlen(message), 0) == -1) {
            perror("send");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }
    close(sockfd);
    return EXIT_SUCCESS;
}
