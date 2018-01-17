#include"header.h"

void space_bgn(char *);
void seperator(char **,char *,char);
void my_isr(int n)
{
	wait(0);
}


int main(int argc ,char **argv)
{

	if(argc !=2)
	{
		printf("Usage:./server port_number\n");
		return;
	}
	int sfd,nsfd,r,len;
	struct sockaddr_in v,v1;
        char s[100];
        bzero(s,sizeof(s));
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("socket");
		return;
	}

	v.sin_family=AF_INET;
	v.sin_port=htons(atoi(argv[1]));
	v.sin_addr.s_addr=inet_addr("0.0.0.0");
	len=sizeof(v);
	if(bind(sfd,(struct sockaddr*)&v,len)==-1)
	{
		perror("bind");
		return ;
	}
        while(1)
       {
        recvfrom(sfd,s,sizeof(s),0,(struct sockaddr*)&v1,&len);
        perror("recvfrom");
        printf("Data recieved from %s : %d > %s\n",inet_ntoa(v1.sin_addr),(int)ntohs(v1.sin_port),s);
        if(strcmp(s,"exit")==0)
         break;
       }
       return 0;
}
