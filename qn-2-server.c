#include"header.h"

float my_atof(char *s);

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
	float result,result1;
	char s[50];
	nsfd=accept(sfd,(struct sockaddr*)&v1,&len);
	read(nsfd,s,sizeof(s));
	result=my_atof(s);
	result1=atof(s);
	write(nsfd,&result,sizeof(float));

	return 0;
}


float my_atof(char *s)
{

	int i,j,count=0,div;
	float result;
	char s1[20];
	for(i=0;(s1[i]=s[i])!='.';i++);
        s1[i]='\0';
        result=my_atoi(s+i+1);
	for(i=i+1;(s[i]>='0' && s[i]<='9');count++,i++);
	for(i=div=1;i<=count;div*=10,i++);
        result=result/div;
        result+=my_atoi(s1);
	return result;
}

int my_atoi(char *s)
{
	int sig=0,num=0,i=0;
	if(s[0]=='-')
	{
		sig=1;
		i++;
	}
	while(s[i]>='0' && s[i]<='9')
	{
		num=num*10+(s[i]-48);
                i++;
	}
	if(sig==1)
		num=-num;
	return num;
}
