#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define NAME_MAX 15
#define TEL_MAX 12
#define MAIL_MAX 9 //邮政编码
#define ADDR_MAX 20
#define SIZE 100
typedef struct contact//定义一个结构体来存放通讯录中的人员信息
{
	char name[NAME_MAX];
	char address[ADDR_MAX];
	char tel[TEL_MAX];
	char mail[MAIL_MAX];

}contact;
typedef struct people
{
	contact student[SIZE];
	int count;
}people, *pcon;

void menu()
{
	printf("-----------------------通讯录管理---------------------\n");
	printf("-----------------0.退出-------------------------------\n");
	printf("-----------------1.添加联系人信息---------------------\n");
	printf("-----------------2.显示联系人信息---------------------\n");
	printf("-----------------3.查询联系人信息---------------------\n");
	printf("-----------------4.修改联系人信息---------------------\n");
	printf("-----------------5.删除联系人信息---------------------\n");
	printf("-----------------6.储存联系人信息---------------------\n\n\n");
	printf("请选择：\n");
}
void init(pcon p)//初始化通讯录
{
	memset(p->student, 0, SIZE*sizeof(contact));//用 0 将结构体中成员信息进行初始化
	p->count = 0;
}
//因为后边几个函数中都用姓名查找一个联系人，所以单独写一个查找函数方便使用
int search(pcon p)
{
	int i = 0;
	char name[15];
	scanf("%s", name);
	for (i = 0; i < p->count; i++)
	{
		if (strcmp(p->student[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void add_people(pcon p)//录入联系人信息
{
	if ((p->count) >= SIZE)
	{
		printf("通讯录已满！\n");
		return;
	}
	printf("请输入姓名：\n");
	scanf("%s", p->student[p->count].name);
	printf("请输入地址：\n");
	scanf("%s", p->student[p->count].address);
	printf("请输入电话号码：\n");
	scanf("%s", p->student[p->count].tel);
	printf("请输入邮政编码：\n");
	scanf("%s", p->student[p->count].mail);
	printf("添加联系人成功\n");
	p->count++;
}
void find_people(pcon p)//查找一个联系人，并输出他的所有信息
{
	printf("请输入要查找的人的姓名：\n");
	int ret = search(p);
	if (ret != -1)
	{
		printf("    name       address        tel         mail      \n");
		printf("%10s   %8s    %13s   %8s \n",
			p->student[ret].name,
			p->student[ret].address,
			p->student[ret].tel,
			p->student[ret].mail);
	}
	else
		printf("联系人不存在!\n ");
}

void delete_people(pcon p)//删除某联系人信息
{
	int i = 0;
	printf("请输入要删除的人的姓名：\n");
	int ret = search(p);
	if (ret != -1)
	{
		for (i = ret; i < p->count; i++)
		{
			p->student[i] = p->student[i + 1];
		}
		printf("删除成功！\n");
	}
	else
		printf("联系人不存在！\n");
}
void change_people(pcon p)//修改联系人信息
{
	printf("请输入要修改的人的姓名：\n");
	int ret = search(p);
	if (ret != -1)
	{
		printf("请把地址修改为：\n");
		scanf("%s", &(p->student[ret].address));
		printf("请把电话修改为：\n");
		scanf("%s", &(p->student[ret].tel));
		printf("请把邮政编码修改为：\n");
		scanf("%s", &(p->student[ret].mail));
	}
	else
	{
		printf("联系人不存在！\n");
	}
}
void show_people(pcon p)//显示所有联系人信息
{
	int i = 0;
	printf("    name       address        tel         mail      \n");
	for (i = 0; i < p->count; i++)
	{
		printf("%10s   %8s    %13s   %8s \n",
			p->student[i].name,
			p->student[i].address,
			p->student[i].tel,
			p->student[i].mail);
	}
}

void filesave(pcon p)//将添加的联系人保存至文件里
{
	int i = 0;
	FILE *pf = fopen("E:/tongxunlu/main.txt", "w");
	if (pf == NULL)
	{
		perror("error");
		exit(EXIT_SUCCESS);
	}
	for (i = 0; i < p->count; i++)
	{
		fwrite(&p->student[i], sizeof(contact), 1, pf);
	}
	fclose(pf);
}

void read_from_file(pcon p)   //从文件中读取联系人信息  
{
	int i = 0;
	contact tmp = { 0 };
	FILE *pfread = fopen("E:/tongxunlu/main.txt", "r");
	if (pfread == NULL)
	{
		perror("open file for read");
		exit(EXIT_FAILURE);
	}
	while (fread(&tmp, sizeof(contact), 1, pfread))
	{

		p->student[i] = tmp;
		i++;
		p->count++;
	}
	fclose(pfread);
}

int main()
{
	int input = 1;
	people  count;
	init(&count);
	read_from_file(&count);
	while (input)
	{
		menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1: add_people(&count);
			break;
		case 5:delete_people(&count);
			break;
		case 3: find_people(&count);
			break;
		case 4: change_people(&count);
			break;
		case 2: show_people(&count);
			break;
		case 6: filesave(&count);
			break;

		case 0: exit(0);
			break;
		default: printf("输入错误！");
			break;
		}
	}
	system("pause");
	return 0;
}
