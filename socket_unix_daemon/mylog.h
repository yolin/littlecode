#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MYLOG_PATH "./log-socket-test"

static int LogFile = -1; 

static int client_socket ()
{
  struct sockaddr_un name;
  int sock;
  size_t size;
  const char *filename= MYLOG_PATH;

  /* Create the socket. */
  sock = socket (PF_LOCAL, SOCK_DGRAM, 0);
  if (sock < 0)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  /* Bind a name to the socket. */
  name.sun_family = AF_LOCAL;
  strncpy (name.sun_path, filename, sizeof (name.sun_path));
  name.sun_path[sizeof (name.sun_path) - 1] = '\0';

  /* The size of the address is
     the offset of the start of the filename,
     plus its length (not including the terminating null byte).
     Alternatively you can just do:
     size = SUN_LEN (&name);
 */
  size = (offsetof (struct sockaddr_un, sun_path)
          + strlen (name.sun_path));

  if( connect(sock, (struct sockaddr *) &name, size) == -1 )
  {
       perror ("connect");
  }

  return sock;
}

void openlog()
{
    LogFile = client_socket();
}
void closelog()
{
    close(LogFile);
}
void mylog(char *logstring)
{
    write(LogFile, logstring, strlen(logstring));
}