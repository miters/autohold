#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
 
int main(int argc,char** argv)
{
        struct termios tio;
        struct termios stdio;
        int tty_fd,test_fd;
 
        unsigned char c[16],d;
        int n;
 
        printf("Please start with %s /dev/ttyUSB0 (for example)\n",argv[0]);
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
 
 
		memset(&tio,0,sizeof(tio));
		tio.c_iflag=0;
		tio.c_oflag=0;
		tio.c_cflag=CS8|CREAD|CLOCAL;          
		tio.c_lflag=0;
		tio.c_cc[VMIN]=1;
		tio.c_cc[VTIME]=5;
 
        test_fd=open("serial-test", O_RDWR | O_NONBLOCK | O_TRUNC);
        tty_fd=open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B9600);            // 9600 baud
        cfsetispeed(&tio,B9600);            // 9600 baud
 
        tcsetattr(tty_fd,TCSANOW,&tio);
        while (d!='q')
        {
                //write(tty_fd,c,1);
                usleep(500000);
				if ((n=read(tty_fd,c,1))==1)
				{
					write(test_fd,c,1);
					printf("got one\n");
				}
                if (read(STDIN_FILENO,&d,1)>0){}  //if new data is available on the console, send it to the serial port
        }
        close(tty_fd);
        close(test_fd);
        return(0);
}
