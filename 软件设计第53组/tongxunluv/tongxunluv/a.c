#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define NAME_MAX 15
#define TEL_MAX 12
#define MAIL_MAX 9 //��������
#define ADDR_MAX 20
#define SIZE 100
typedef struct contact//����һ���ṹ�������ͨѶ¼�е���Ա��Ϣ
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
	printf("-----------------------ͨѶ¼����---------------------\n");
	printf("-----------------0.�˳�-------------------------------\n");
	printf("-----------------1.�����ϵ����Ϣ---------------------\n");
	printf("-----------------2.��ʾ��ϵ����Ϣ---------------------\n");
	printf("-----------------3.��ѯ��ϵ����Ϣ---------------------\n");
	printf("-----------------4.�޸���ϵ����Ϣ---------------------\n");
	printf("-----------------5.ɾ����ϵ����Ϣ---------------------\n");
	printf("-----------------6.������ϵ����Ϣ---------------------\n\n\n");
	printf("��ѡ��\n");
}
void init(pcon p)//��ʼ��ͨѶ¼
{
	memset(p->student, 0, SIZE*sizeof(contact));//�� 0 ���ṹ���г�Ա��Ϣ���г�ʼ��
	p->count = 0;
}
//��Ϊ��߼��������ж�����������һ����ϵ�ˣ����Ե���дһ�����Һ�������ʹ��
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
void add_people(pcon p)//¼����ϵ����Ϣ
{
	if ((p->count) >= SIZE)
	{
		printf("ͨѶ¼������\n");
		return;
	}
	printf("������������\n");
	scanf("%s", p->student[p->count].name);
	printf("�������ַ��\n");
	scanf("%s", p->student[p->count].address);
	printf("������绰���룺\n");
	scanf("%s", p->student[p->count].tel);
	printf("�������������룺\n");
	scanf("%s", p->student[p->count].mail);
	printf("�����ϵ�˳ɹ�\n");
	p->count++;
}
void find_people(pcon p)//����һ����ϵ�ˣ����������������Ϣ
{
	printf("������Ҫ���ҵ��˵�������\n");
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
		printf("��ϵ�˲�����!\n ");
}

void delete_people(pcon p)//ɾ��ĳ��ϵ����Ϣ
{
	int i = 0;
	printf("������Ҫɾ�����˵�������\n");
	int ret = search(p);
	if (ret != -1)
	{
		for (i = ret; i < p->count; i++)
		{
			p->student[i] = p->student[i + 1];
		}
		printf("ɾ���ɹ���\n");
	}
	else
		printf("��ϵ�˲����ڣ�\n");
}
void change_people(pcon p)//�޸���ϵ����Ϣ
{
	printf("������Ҫ�޸ĵ��˵�������\n");
	int ret = search(p);
	if (ret != -1)
	{
		printf("��ѵ�ַ�޸�Ϊ��\n");
		scanf("%s", &(p->student[ret].address));
		printf("��ѵ绰�޸�Ϊ��\n");
		scanf("%s", &(p->student[ret].tel));
		printf("������������޸�Ϊ��\n");
		scanf("%s", &(p->student[ret].mail));
	}
	else
	{
		printf("��ϵ�˲����ڣ�\n");
	}
}
void show_people(pcon p)//��ʾ������ϵ����Ϣ
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

void filesave(pcon p)//����ӵ���ϵ�˱������ļ���
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

void read_from_file(pcon p)   //���ļ��ж�ȡ��ϵ����Ϣ  
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
		default: printf("�������");
			break;
		}
	}
	system("pause");
	return 0;
}
