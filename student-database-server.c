#include"header.h"
typedef struct student
{
	int option,rollno;
	char name[20],status[20];
	float mark;
}st;

struct node
{
	st obj;
	struct node *next;
};

void search(struct node *,st *);
void addbegin(struct node **, st *);
void print(struct node *);
void sort(struct node *);

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		printf("Usage:./server port_number\n");
		return 0;
	}

	struct node *hptr=0;

	int sfd,nsfd,fd,len;
	struct sockaddr_in v1,v2;

	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return;
	}

	v1.sin_family=AF_INET;
	v1.sin_port=htons(atoi(argv[1]));
	v1.sin_addr.s_addr=inet_addr("0.0.0.0");

	len=sizeof(v1);

	if(bind(sfd,(struct sockaddr*)&v1,len)<0)
	{
		perror("bind");
		return;
	}

	if(listen(sfd,5)<0)
	{
		perror("listen");
		return;
	}

	st temp;
	char info[100];
	time_t t;
	fd=open("info.log",O_WRONLY|O_CREAT|O_TRUNC,0777);
	while(1)
	{

		nsfd=accept(sfd,(struct sockaddr*)&v2,&len);
		t=time(&t);
		sprintf(info,"%s\tip  :  %s\n\tport : %d\n\tconnected\n",ctime(&t),inet_ntoa(v2.sin_addr),(int)ntohs(v2.sin_port));
		write(fd,info,strlen(info));
		printf("%s\n",info);
		while(1)
		{
			if(read(nsfd,&temp,sizeof(temp))<=0)
				break;
			switch(temp.option)
			{
				case 1: addbegin(&hptr,&temp);
					break;
				case 2: search(hptr,&temp);
					//  printf("%s %d %f\n",temp.name,temp.rollno,temp.mark);     
					write(nsfd,&temp,sizeof(temp));
					break;
				case 3: printf("sorting....\n");
					sort(hptr);
					printf("Done\n");
					break;

					//default:
			}
			if(strcmp(temp.status,"exit")==0)
			{
				print(hptr);
				sprintf(info,"%s\tip  :  %s\n\tport : %d\n\tconnection closed\n",ctime(&t),inet_ntoa(v2.sin_addr),(int)ntohs(v2.sin_port));
				write(fd,info,strlen(info));
				printf("client connection closed\n");
				break;
			}
		}
	}

	return 0;

}

void addbegin(struct node **ptr, st *temp)
{
	struct node *tmp=malloc(sizeof(struct node));
	//  printf("%s %d %f\n",temp->name,temp->rollno,temp->mark);
	tmp->obj=*temp;
	tmp->next=*ptr;
	*ptr=tmp;
}

void search(struct node *ptr,st *temp)
{
	while(ptr)
	{
		if(ptr->obj.rollno==temp->rollno)
		{
			*temp=ptr->obj;
			break;
		}
		printf("%s %d \n",ptr->obj.name,ptr->obj.rollno);
		ptr=ptr->next;
	}
	temp->rollno=0;
}

void sort(struct node *ptr)
{
	struct node *temp,*swp=malloc(sizeof(struct node));

	while(ptr)
	{
		temp=ptr->next;
		while(temp)
		{
			if(ptr->obj.rollno > temp->obj.rollno)
			{
				swp->obj = ptr->obj;
				ptr->obj = temp->obj;
				temp->obj= swp->obj;

				/*			swp->next = ptr->next;
							ptr->next =temp->next;
							temp->next=swp->next;
				 */		}
				temp=temp->next;
		}
		ptr=ptr->next;
	}
}

void print(struct node *ptr)
{
	char s[30];
	int fd;
	fd=open("database",O_WRONLY|O_CREAT|O_TRUNC,0664);
	while(ptr)
	{

		sprintf(s,"%d %s %f\n",ptr->obj.rollno,ptr->obj.name,ptr->obj.mark);
		write(fd,s,strlen(s)); 
		ptr=ptr->next;
	}
}



