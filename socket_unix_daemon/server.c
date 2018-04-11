#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "mylog.h"

#define MAX_READ 256

int server_socket ()
{
  struct sockaddr_un name;
  int sock;
  size_t size;
  const char *filename= MYLOG_PATH;

  /* Remove any preexisting socket (or other file) */
  unlink(filename);


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

  if (bind (sock, (struct sockaddr *) &name, size) < 0)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }

  return sock;
}

int main(void) {
    struct sockaddr_un address;
    int sock, conn;
    char recvbuf[1024] = {0};
    size_t sz;


    sock = server_socket();

    while(1)
    {

read_again:
        sz = read(sock, recvbuf, MAX_READ - 1);
        if (sz < 0) {
            break;
        }

        /* Drop trailing '\n' and NULs (typically there is one NUL) */
        while (1) {
            if (sz == 0)
                goto read_again;

            /* man 3 syslog says: "A trailing newline is added when needed".
             * However, neither glibc nor uclibc do this:
             * syslog(prio, "test")   sends "test\0" to /dev/log,
             * syslog(prio, "test\n") sends "test\n\0".
             * IOW: newline is passed verbatim!
             * I take it to mean that it's syslogd's job
             * to make those look identical in the log files. */
            if (recvbuf[sz-1] != '\0' && recvbuf[sz-1] != '\n')
                break;
            sz--;
        }
        recvbuf[sz] = '\0';
        printf("-->[Yolin:%s:%d:%s]%s\n", __FILE__, __LINE__, __FUNCTION__, recvbuf);

    }
    close(sock);
    return 0;
}
