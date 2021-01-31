#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
struct student
{
	int id;
	char name[100];
	float score;
	struct student *next;
};
struct student head,*p,*q;
struct student stu[100],t;
void idsort();
void menu()
{
	printf("-----------------------------\n");
	printf("|                           |\n");
	printf("| 欢迎进入学生成绩管理系统！|\n");
	printf("|                           |\n");
	printf("| 请输入序号执行对应功能    |\n");
	printf("| 1.显示所有学生成绩        |\n");
	printf("| 2.根据学号有序添加学生成绩|\n");
	printf("| 3.根据学号查找学生成绩    |\n");
	printf("| 4.根据学号删除学生成绩    |\n");
	printf("| 5.按总分高低排序          |\n");
	printf("| 6.单科成绩排名            |\n");
	printf("| 7.将学生成绩保存至文件    |\n");
	printf("| 8.按姓名查找学生成绩      |\n");
	printf("| 9.按姓名删除学生成绩      |\n");
	printf("| a.按学号进行排序          |\n");
	printf("| b.按姓名排序              |\n");
	printf("| 0.退出                    |\n");
	printf("-----------------------------\n");
}
void read()
{
	int i;
	FILE *fp;
	head.next=NULL;
	fp=fopen("student.txt","r");
	for(i=0;;i++)
	{
		p=(struct student*)malloc(sizeof(struct student));
		fscanf(fp,"%d%s%f",&p->id,p->name,&p->score);
		if(feof(fp)) break;
		p->next=NULL;
		if(head.next==NULL) head.next=p;
		else q->next=p;
		q=p;
	}
	fclose(fp);
}
void show()
{
	q=head.next;
	while(q!=NULL)
	{
		printf("%d\t%s\t%.1f\n",q->id,q->name,q->score);
		q=q->next;
	}
}
void insertstu()
{
	int flag=1;
	idsort();
	p=(struct student*)malloc(sizeof(struct student));
	scanf("%d%s%f",&p->id,p->name,&p->score);
	q=head.next;
	while(q!=NULL)
	{
		if(q->next==NULL) break;
		if(q->next->id>p->id) {p->next=q->next;q->next=p;flag=0;break;}
		q=q->next;
	}
	if(flag==1) {q->next=p;p->next=NULL;}
	printf("添加后的结果为：\n");
	show();
}
void find()
{
	int n,flag=1;
	scanf("%d",&n);
	q=head.next;
	while(q!=NULL)
	{
		if(q->id==n) 
		{
			printf("查询学生的成绩为：");
			printf("%d\t%s\t%.1f\n",q->id,q->name,q->score);
			flag=0;
		}
		q=q->next;
	}
	if(flag) printf("查询不到该学生！");
}
void removestu()
{
	int flag=1,n;
	scanf("%d",&n);
	q=head.next;
	while(q!=NULL)
	{
		if(q->next==NULL) break;
		if(q->next->id==n) {q->next=q->next->next;flag=0;break;}
		q=q->next;
	}
	if(flag==1) 
	{
		if(head.next->id==n) head.next=head.next->next;
		else printf("没有该学生的信息！");
	}
	printf("删除后的结果为：\n");
	show();
}
void exchange(int a,int b)
{
	struct student t;
	t.id=stu[a].id;stu[a].id=stu[b].id;stu[b].id=t.id;
	strcpy(t.name,stu[a].name);strcpy(stu[a].name,stu[b].name);strcpy(stu[b].name,t.name);
	t.score=stu[a].score;stu[a].score=stu[b].score;stu[b].score=t.score;
}
void scoresort()
{
	int i=0,j,k;
	q=head.next;
	while(q!=NULL)
	{
		stu[i++]=*q;
		q=q->next;
	}
	for(j=0;j<i;j++)
	{
		for(k=j+1;k<i;k++)
		{
			if(stu[k].score>=stu[j].score)
			{
				exchange(j,k);
			}
		}
	}
	*head.next=stu[0];
	q=head.next;
	for(j=1;j<i;j++) {*q->next=stu[j];q=q->next;}
	q->next=NULL;

}
void idsort()
{
	int i=0,j,k;
	q=head.next;
	while(q!=NULL)
	{
		stu[i++]=*q;
		q=q->next;
	}
	for(j=0;j<i;j++)
	{
		for(k=j+1;k<i;k++)
		{
			if(stu[k].id<=stu[j].id)
			{
				exchange(j,k);
			}
		}
	}
	*head.next=stu[0];
	q=head.next;
	for(j=1;j<i;j++) {*q->next=stu[j];q=q->next;}
	q->next=NULL;
}
void rank()
{
	int i=1;
	scoresort();
	q=head.next;
	while(q!=NULL)
	{
		printf("第%d名 ",i);
		i++;
		printf("%d\t%s\t%.1f\n",q->id,q->name,q->score);
		q=q->next;
	}
}
void namefind()
{
	int flag=1;
	char n[100];
	scanf("%s",n);
	q=head.next;
	while(q!=NULL)
	{
		if(strcmp(q->name,n)==0) 
		{
			printf("查询学生的成绩为：");
			printf("%d\t%s\t%.1f\n",q->id,q->name,q->score);
			flag=0;
		}
		q=q->next;
	}
	if(flag) printf("查询不到该学生！");
}
void removename()
{
	int flag=1;
	char n[100];
	scanf("%s",n);
	q=head.next;
	while(q!=NULL)
	{
		if(q->next==NULL) break;
		if(strcmp(q->next->name,n)==0) {q->next=q->next->next;flag=0;break;}
		q=q->next;
	}
	if(flag==1) 
	{
		if(strcmp(head.next->name,n)==0) head.next=head.next->next;
		else printf("没有该学生的信息！");
	}
	printf("删除后的结果为：\n");
	show();
}
void namesort()
{
	int i=0,j,k;
	q=head.next;
	while(q!=NULL)
	{
		stu[i++]=*q;
		q=q->next;
	}
	for(j=0;j<i;j++)
	{
		for(k=j+1;k<i;k++)
		{
			if(strcmp(stu[k].name,stu[j].name)==-1)
			{
				exchange(j,k);
			}
		}
	}
	*head.next=stu[0];
	q=head.next;
	for(j=1;j<i;j++) {*q->next=stu[j];q=q->next;}
	q->next=NULL;
}
void savefile()
{
	FILE *fp;
	fp=fopen("student.txt","w");
	q=head.next;
	while(q!=NULL)
	{
		fprintf(fp,"%d\t%s\t%.1f\n",q->id,q->name,q->score);
		q=q->next;
	}
	fclose(fp);
}
int main()
{
	char c;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("Tip!  该学生成绩管理系统有bug，请不要额外输入任何内容，否则将会瘫痪！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	read();
	menu();
	while(1)
	{
		c=getchar();
		if(c=='0') break;
		getchar();
		switch (c)
		{
			case '1':
				system("cls");
				show();
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
			case '2':
				system("cls");
				insertstu();
				printf("\n按回车键继续\n");
				getchar();
				getchar();
				system("cls");
				break;
			case '3':
				system("cls");
				find();
				printf("\n按回车键继续\n");
				getchar();
				getchar();
				system("cls");
				break;
			case '4':
				system("cls");
				removestu();
				printf("\n按回车键继续\n");
				getchar();
				getchar();
				system("cls");
				break;
			case '5':
				system("cls");
				scoresort();
				printf("排序后的结果为：\n");
				show();
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
			case '6':
				system("cls");
				rank();
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
			case '7':
				system("cls");
				savefile();
				printf("已保存！");
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
			case '8':
				system("cls");
				namefind();
				printf("\n按回车键继续\n");
				getchar();
				getchar();
				system("cls");
				break;
			case '9':
				system("cls");
				removename();
				printf("\n按回车键继续\n");
				getchar();
				getchar();
				system("cls");
				break;
			case 'a':
				system("cls");
				idsort();
				printf("排序后的结果为：\n");
				show();
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
			case 'b':
				system("cls");
				namesort();
				printf("排序后的结果为：\n");
				show();
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
			default:
				printf("输入错误！");
				printf("\n按回车键继续\n");
				getchar();
				system("cls");
				break;
		}
		menu();
	}
}