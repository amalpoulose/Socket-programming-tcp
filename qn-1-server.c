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

	if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
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
	if(listen(sfd,5)==-1)
	{
		perror("listen");
		return ;
	}
	char s[50];
	nsfd=accept(sfd,(struct sockaddr*)&v1,&len);
	read(nsfd,s,sizeof(s));
	int start,end,i,j;
	for(start=end=0;end<=strlen(s);end++)
	{
		if(s[end]!=' ' && s[end]!='\0')
			continue;
		i=start;
		j=end-1;
		for(;i<j;i++,j--)
			s[i]=s[i]+s[j]-(s[j]=s[i]);
		start=end+1;
	}

	write(nsfd,s,strlen(s)+1);

	return 0;
}
