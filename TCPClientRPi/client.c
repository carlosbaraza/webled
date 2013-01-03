#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <bcm2835.h>
// TCP BlInk on RPi pin GPIO 17
#define PIN RPI_GPIO_P1_11

#define DATA "The sea is calm tonight, the tide is full . . ."
#define SERVER_PORT 2000
#define BUFFER_SIZE 1024


/* prototypes */
void die(const char *);
void pdie(const char *);


/**********************************************************************
 * main
 **********************************************************************/

int main(int argc, char *argv[]) {

   int sock;   /* fd for socket connection */
   struct sockaddr_in server;   /* Socket info. for server */
   struct sockaddr_in client;   /* Socket info. about us */
   int clientLen;   /* Length of client socket struct. */
   struct hostent *hp;   /* Return value from gethostbyname() */
   char buf[BUFFER_SIZE];   /* Received data buffer */
   int i;   /* loop counter */
   char *hostname;

   if (argc == 1)
   {
      hostname = "37.247.55.158";
   }
   else if (argc == 2)
   {
	   hostname = argv[1];
   }
   else if (argc != 2)
   {
      die("Usage: client hostname");
   }

   while (1)
   {
      /* Open a socket --- not bound yet. */
      /* Internet TCP type. */
      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         pdie("Opening stream socket");
      
      /* Prepare to connect to server. */
      bzero((char *) &server, sizeof(server));
      server.sin_family = AF_INET;
      if ((hp = gethostbyname( hostname )) == NULL) {
         sprintf(buf, "%s: unknown host\n", argv[1]);
         die(buf);
      }
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons((u_short) SERVER_PORT);
      
      /* Try to connect */
      if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
         pdie("Connecting stream socket");
      
      /* Prepare our buffer for a read and then read. */
      bzero(buf, sizeof(buf));
      if (read(sock, buf, BUFFER_SIZE) < 0)
         pdie("Reading stream message");
      
      printf("Is led ON? %s\n", buf);

      close(sock);
      
      int on = atoi(buf);

      //    bcm2835_set_debug(1);
    
      if (!bcm2835_init())
        return 1;
    
      // Set the pin to be an output
      bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
      
      if (on == 1)
      { 
	     // Turn it on
	     bcm2835_gpio_write(PIN, HIGH);
      }
      else
      {
	     // Turn it off
	     bcm2835_gpio_write(PIN, LOW);
      }
	
      sleep(1);

   }

   exit(0);

}


/**********************************************************************
 * pdie --- Call perror() to figure out what's going on and die.
 **********************************************************************/

void pdie(const char *mesg) {

   perror(mesg);
   exit(1);
}


/**********************************************************************
 * die --- Print a message and die.
 **********************************************************************/

void die(const char *mesg) {

   fputs(mesg, stderr);
   fputc('\n', stderr);
   exit(1);
}


