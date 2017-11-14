#include"header.h"

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
 read(nsfd,s,sizeof(s));
 if(strcmp(s,"exit")==0)
  return;
 if(fork()==0)
 {
  execlp(s,s,NULL);
  return;
 }
}
}
}
return 0;
}
