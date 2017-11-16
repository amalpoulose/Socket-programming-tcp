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

	sfd=socket(AF_INET,SOCK_STREAM,0);
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
	if(listen(sfd,5)==-1)
	{
		perror("listen");
		return ;
	}
	signal(SIGCHLD,my_isr);
	char s[50];
	while(1)
	{

		nsfd=accept(sfd,(struct sockaddr*)&v1,&len);
		if(fork()==0)
		{

			printf("host ip  : %s\n",inet_ntoa((struct in_addr)v1.sin_addr));
			printf("host port: %d\n",(int)ntohs(v1.sin_port));
			close(1);
			dup(nsfd);
			while(1)
			{ 
				if(read(nsfd,s,sizeof(s))<=0)
                                       return 0;
				if(strcmp(s,"exit")==0)
					return;
				if(strcmp(s,"poweroff")==0||strcmp(s,"reboot")==0 || strcmp(s,"passwd")==0)
				{
					printf("unauthorized access\n");
					continue;
				}
				char *p[60];
				space_bgn(s);
				seperator(p,s,' ');
				if(fork()==0)
				{
					if(execvp(*p,p)==-1)
						printf("%s:No such file/directory\n",*p);
					return 0;
				}
			}
		}
	}
	return 0;
}


void space_bgn(char *cmd)
{
	int i;
	//remove spaces in begining 
	for(i=0;cmd[i];i++)
	{
		if(cmd[i]==' ')
			continue;
		strcpy(cmd,cmd+i);
		break; 
	}
	//remove spaces at end
	for(i=strlen(cmd)-1;i;i--)
	{
		if(cmd[i]==' ')
		{
			cmd[i]='\0';
			continue;
		}
		break;
	}
}

void seperator(char **s,char *p,char ch)
{
	while(*p!='\0')
	{
		while(*p==ch || *p=='\0')
			*p++='\0';
		*s++=p;
		while(*p!=ch && *p!='\0')
			p++;	

	}
	*s='\0';
}
