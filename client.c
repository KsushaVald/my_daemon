#include <stdio.h>
#include <fcntl.h>

int main(){
	int ch_w, ch_r; char request[256]; char time[256];

	ch_w=open("/tmp/kzevs/what_time",O_WRONLY|O_TRUNC);
	scanf("%s", request);
	write(ch_w,request,sizeof(char)*256);
	close(ch_w);
	ch_r=open("/tmp/kzevs/info_time",O_RDONLY);
	read(ch_r, time, sizeof(char)*256);
	printf("%s\n", time);
}
