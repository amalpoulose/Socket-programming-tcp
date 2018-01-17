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
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("socket");
		return;
	}

	v.sin_family=AF_INET;
	v.sin_port=htons(atoi(argv[1]));
	v.sin_addr.s_addr=inet_addr(argv[2]);
	len=sizeof(v);

	char s[5000];
	while(1)
	{
		printf("String : ");
		scanf(" %[^\n]",s);
		sendto(sfd,s,strlen(s)+1,0,(struct sockaddr*)&v,len);
                perror("sendto");
                if(strcmp(s,"exit")==0)
			break;
	}

	return 0;
}
