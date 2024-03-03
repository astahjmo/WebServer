#include "webserver.h"
#include <stdio.h>
#include <string.h>

static int	setup_server()
{
	int							socket_fd;
	int							bind_status;
	const struct sockaddr_in6 	addr = {
		AF_INET6,
		htons(PORT),
		OPT_IGR,
		IN6ADDR_LOOPBACK_INIT,
		OPT_IGR
	};

	socket_fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (socket_fd == -1)
		return (-1);
	bind_status = bind(socket_fd, (const struct sockaddr *)&addr, sizeof(addr));
	if (bind_status < 0)
		return(-1);
	listen(socket_fd, 10);
	printf("SERVER RUNNING IN ::1 or localhost in port %d\n", PORT);
	return (socket_fd);
}


void	handle_conn(int conn)
{
	size_t 						valread;
	char 						buffer[1024];

	memset((void *)buffer, 0, 1024);
	valread = read(conn, buffer, 1024);
	printf("%s", buffer);
}


int	start_server(int socket_fd)
{
	const struct sockaddr_in6 	client;
	unsigned int 				len;
	int							conn;

	len = sizeof(client);
	while(1)
	{
		conn = accept(socket_fd,(struct sockaddr *)&client,&len);
		if (conn <= 0)
		{
			perror("ERROR: ");
			return (-1);
		}
		handle_conn(conn);
		close(conn);
	}
	return (0);
}

int	main()
{
	int							socket_fd;

	socket_fd = setup_server();
	start_server(socket_fd);
	close(socket_fd);
}
