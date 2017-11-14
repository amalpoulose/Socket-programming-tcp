#include"header.h"

int main(int argc ,char **argv)
{

	if(argc !=3)
	{
		printf("Usage:./client port_number ip_address\n");
		return;
	}
	int sfd,r,len;
	struct sockaddr_in v;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return;
	}

	v.sin_family=AF_INET;
	v.sin_port=htons(atoi(argv[1]));
	v.sin_addr.s_addr=inet_addr(argv[2]);
	len=sizeof(v);
	if(connect(sfd,(struct sockaddr*)&v,len)==-1)
	{
		perror("connect");
		return ;
	}

	char s[5000];
	while(1)
	{
		printf("String : ");
		scanf(" %s",s);
		write(sfd,s,strlen(s)+1);
		if(strcmp(s,"exit")==0)
			return;
	        bzero(s,sizeof(s));
		read(sfd,s,sizeof(s));
		printf("%s\n",s);
	}

	return 0;
}
