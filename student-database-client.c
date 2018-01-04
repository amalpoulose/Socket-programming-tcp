#include"header.h"
typedef struct student
{
	int option,rollno;
	char name[20],status[20];
	float mark;
}st;


int main(int argc,char **argv)
{
	if(argc != 3)
	{
		printf("Usage:./client port_number ip_address\n");
		return 0;
	}
	struct node *hptr=0;

	int sfd,fd,len;
	struct sockaddr_in v1;

	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return;
	}

	v1.sin_family=AF_INET;
	v1.sin_port=htons(atoi(argv[1]));
	v1.sin_addr.s_addr=inet_addr(argv[2]);

	len=sizeof(v1);

	if(connect(sfd,(struct sockaddr*)&v1,len)<0)
	{
		perror("connect");
		return 0;
	}

	st temp;
	int c;
	char ch;
	while(1)
	{
		system("clear");

		printf("1. Data\n2.search\n3.sort\n4.exit\n\n\nenter choice: ");
		scanf(" %d",&c);
		switch(c)
		{
			case 1:do
			       {
				       printf("Name , roll , mark\n");
				       scanf("%s%d%f",temp.name,&temp.rollno,&temp.mark);
				       temp.option=1;
				       write(sfd,&temp,sizeof(temp));
				       printf("continue?(y/n)  : ");
				       scanf(" %c",&ch);
			       }     while(ch=='y' ||ch=='Y');

			       break;
			case 2: temp.option=2;
				printf("rollno\n");
				scanf("%d",&temp.rollno);
				write(sfd,&temp,sizeof(temp));
				if(read(sfd,&temp,sizeof(temp))<=0)
					break;
				if(temp.rollno != 0)
				printf("%s   %d   %f\n\n",temp.name,temp.rollno,temp.mark);
				else printf("No data found\n");
				printf("\npress any key  : ");
				scanf(" %c",&ch);
			case 3: temp.option=3;
				write(sfd,&temp,sizeof(temp));
				break;
			case 4: temp.option=0;
				strcpy(temp.status,"exit");
				write(sfd,&temp,sizeof(temp));
				break;

				//default:
		}
		if(strcmp(temp.status,"exit")==0)
			break;

	}

	return 0;

}
