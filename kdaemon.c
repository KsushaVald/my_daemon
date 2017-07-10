#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void what_time(int fd_log)
{
	int ch_r, ch_w; char request[256];
	char str[10]="what_time\0"; char error[6]="error\0";
	long int s_time; struct tm* m_time; char *time;

	ch_r=open("/tmp/kzevs/what_time", O_RDWR);
	ch_w=open("/tmp/kzevs/info_time", O_WRONLY|O_TRUNC);
	if((read(ch_r,request,sizeof(char)*256))!=NULL){
		s_time=times(NULL);
		m_time=localtime(&s_time);
		time=asctime(m_time);
		if(strcmp(request,str)==0){
			write(ch_w,time,sizeof(char)*256);
		}
		else{
			write(ch_w,error,sizeof(error));
			write(fd_log,request,sizeof(char)*256);
			write(fd_log,time,sizeof(time));
		}
	}
	close(ch_r);
	close(ch_w);
}

void create_channel(void)
{
	mkfifo("/tmp/kzevs/info_time", 0666);
	mkfifo("/tmp/kzevs/what_time", 0666);
}

void my_daemon(void)
{
	int fd_null, fd_log;
	setsid();
	chdir("/");
	fd_null=open("/dev/null",O_RDWR);
	dup2(fd_null,0);
	dup2(fd_null,1);
	fd_log=open("tmp/kzevs/log", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	close(fd_null);
	while(1){
		what_time(fd_log);
		sleep(5);
	}
	close(fd_log);
}

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==0){
		create_channel();
		my_daemon();
	}
}
