#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include"student.h"
#include<string.h>
#define FILENAME "D:/ʵѵ�γ�/data.txt"

//ȫ�ֱ����洢ѧ����Ϣ
//�ṹ�������� 
stu s[50];
//ѧ��������
int idx = 0;
//s[i].id���������������


//����ʵ�� 
//�˵�����
void menu()
{
	//����ϵͳ����-������
	system("cls");

	printf("============================================\n");
	printf("=================ѧ������ϵͳ===============\n");
	printf("================1��¼��ѧ����Ϣ=============\n");
	printf("================2����ʾѧ����Ϣ=============\n");
	printf("================3���޸�ѧ����Ϣ=============\n");
	printf("================4��ɾ��ѧ����Ϣ=============\n");
	printf("================5������ѧ����Ϣ=============\n");
	printf("================6����ѯѧ����Ϣ=============\n");
	printf("================7��ѧ���ܷ�����=============\n");
	printf("================8����ʾѧ������=============\n");
	printf("================0���˳�����ϵͳ=============\n");
	printf("============================================\n");
	printf("�������Ӧ��ţ�\n");
}
//¼��ѧ����Ϣ
void insert_student()
{
	/*
	1�����ļ��Դ���ѧ���ɼ�
	2�����ļ�������ѧ����Ϣ
	*/
	FILE* fp = fopen(FILENAME, "ab+");
	if (!fp)
	{
		printf("��ѧ����Ϣ����ʧ��\n");
		return;
	}

	//��¼���ļ��дӴ洢��ѧ����Ϣ�±�
	int index = 0;
	//�û������־λ
	char key;
	while (1)
	{
		fread(&s[index], sizeof(stu), 1, fp);
		if (feof(fp))
			break;
		index++;
	}
	//�ر��ļ�
	fclose(fp);
	while (1)
	{
		printf("��ǰѧ������Ϊ��%d�ˣ��Ƿ�Ҫ��������(Y|N)\n", index);
		getchar();
		key = getchar();
		if (key == 'Y')
		{
			printf("�����룺���\t����\t���޿�\tѡ�޿�\tʵ���\n");
			scanf("%d%s%d%d%d", &s[index].id, s[index].name,
				&s[index].expe, &s[index].elec, &s[index].requ);

			//�����ܷ�
			s[index].sum = s[index].expe + s[index].elec + s[index].requ;

			FILE* fp = fopen(FILENAME, "wb+");
			if (!fp)
			{
				printf("��ѧ����Ϣ����ʧ��\n");
				return;
			}
			//index+1 ��ʾԪ�ظ���
			fwrite(s, sizeof(stu), index + 1, fp);
			printf("�������ݳɹ�\n");
			fclose(fp);
			index++;
		}
		else
			return;
	}
	

}
//��ʾѧ����Ϣ
void show_student()
{
	FILE* fp = fopen(FILENAME, "rb");
	if (fp == NULL)
	{
		printf("��ȡѧ����Ϣʧ��\n");
		return;
	}
	int index = 0;
	//һֱ���ļ� ֱ���ļ���β
	while (1)
	{
		fread(&s[index], sizeof(stu), 1, fp);
		if (feof(fp))//�ļ���β�ж�
			break;
		index++;
	}

	fclose(fp);
	//printf("��ǰ����Ϊ��%d��\n", index);

	if (index == 0)
	{
		printf("δ�ҵ�ѧ����Ϣ��¼\n");
		return;
	}
	printf("���\t����\t���޿�\tѡ�޿�\tʵ���\t�ܳɼ�\n");
	//ͨ��ȫ�ֱ�����¼ѧ������
	idx = index;
	for (int i = 0; i < index; i++)
	{
		printf("%d\t%s\t%d\t%d\t%d\t%d\n",s[i].id, s[i].name,
			s[i].expe, s[i].elec, s[i].requ, s[i].sum);
	}
}
//�޸�ѧ����Ϣ
void modify_student()
{
	//��ʾѧ����Ϣ
	show_student();
	int id;
	printf("������Ҫ�޸�ѧ����Ϣ�ı�ţ�\n");
	scanf("%d", &id);
	for (int i = 0; i < idx; i++)
	{
		if (id == s[i].id)
		{
			printf("�ҵ�����ѧ����\n");
			//i��ʾ��ǰѧԱ����Ϣ
			printf("�����룺���\t����\t���޿�\tѡ�޿�\tʵ���\n");
			scanf("%d%s%d%d%d", &s[i].id, s[i].name,
				&s[i].expe, &s[i].elec, &s[i].requ);

			//���µ�ǰѧ���ܳɼ�
			s[i].sum = s[i].elec + s[i].expe + s[i].requ;

			FILE* fp = fopen(FILENAME, "wb");
			if (!fp)
			{
				printf("��ѧ����Ϣ����ʧ��\n");
				return;
			}
			fwrite(s, sizeof(stu), idx, fp);

			fclose(fp);
			printf("�޸�ѧ����Ϣ�ɹ�\n");

			//show_student();
			return;
		}
	}
	printf("δ�ҵ�����ѧ����\n");

}
//ɾ��ѧ����Ϣ
void delete_student()
{
	//1���ҵ�ѧ�����
	//2�����θ���֮ǰ���� ������һ������
	//3��������-1  д���ļ���
	show_student();
	int id;
	printf("������Ҫɾ��ѧ����Ϣ�ı�ţ�\n");
	scanf("%d", &id);

	for (int i = 0; i < idx; i++)
	{
		if (id == s[i].id)
		{
			//printf("�ҵ�Ҫɾ����ѧ����Ϣ\n");
			//�ж��Ƿ������һ��ѧ��
			if (i == idx - 1)
			{
				//����ڴ�
				memset(&s[i], 0, sizeof(stu));
			}
			while (i < idx - 1)
			{
				//����һ��ѧ����Ϣ������ǰһ��ѧ��
				s[i] = s[i + 1];
				i++;
			}
			memset(&s[i], 0, sizeof(stu));

			idx--;//������-1
			FILE* fp = fopen(FILENAME, "wb");
			if (!fp)
			{
				printf("��ѧ����Ϣʧ��\n");
				return;
			}

			fwrite(s, sizeof(stu), idx, fp);

			printf("ɾ��ѧ����Ϣ�ɹ�\n");
			fclose(fp);
			return;
		}
	}
	printf("δ�ҵ�Ҫɾ����ѧ����Ϣ\n");

}
//����ѧ����Ϣ
void insert_info()
{
	show_student();
	int id;
	printf("���������ѧ����Ϣ�ı�ţ�\n");
	scanf("%d", &id);
	for (int i = 0; i < idx; i++)
	{
		if (id == s[i].id)
		{
			int temp = idx;
			//��������ΪֵΪi  s[i]
			//i=i+1  ���ҵ���������һ��λ����Ϊ�����λ��
			i = i + 1;
			while (temp > i)
			{
				s[temp] = s[temp - 1];
				temp--;
			}

			printf("�����룺���\t����\t���޿�\tѡ�޿�\tʵ���\n");
			scanf("%d%s%d%d%d", &s[i].id, s[i].name,
				&s[i].expe, &s[i].elec, &s[i].requ);

			s[i].sum = s[i].expe + s[i].elec + s[i].requ;

			FILE* fp = fopen(FILENAME, "wb");
			if (!fp)
			{
				printf("��ѧԱ��Ϣʧ��\n");
				return;
			}
			fwrite(s, sizeof(stu), idx + 1, fp);
			fclose(fp);
			printf("����ѧԱ���ݳɹ�\n");
			return;
		}
	}
	printf("δ�ҵ�����λ�ã�����ʧ��\n");

}
//��ѯѧ����Ϣ
void search_student()
{
	printf("�������ѯѧ����Ϣ��ţ�\n");
	int id;
	scanf("%d", &id);
	FILE* fp = fopen(FILENAME, "rb");
	if (!fp)
	{
		printf("��ѧ����Ϣʧ��\n");
		return;
	}
	//�ṹ������Ԫ���±�
	int index = 0;
	while (1)
	{
		fread(&s[index], sizeof(stu), 1, fp);
		if (feof(fp))
			break;
		index++;
	}
	fclose(fp);
	//if (index == 0)
	//{
	//	printf(printf("δ�ҵ�ѧԱ��Ϣ,����ʧ��\n"));
	//	return;
	//}

	for (int i = 0; i < index; i++)
	{
		if (id == s[i].id)
		{
			printf("�ҵ�����ѧ�����ݣ�\n");
			printf("���\t����\t���޿�\tѡ�޿�\tʵ���\t�ܳɼ�\n");
				printf("%d\t%s\t%d\t%d\t%d\t%d\n", s[i].id, s[i].name,
					s[i].expe, s[i].elec, s[i].requ, s[i].sum);
				return;
		}
	}

	printf("δ�ҵ�����ѧ�����ݣ�\n");

}
//ѧ���ɼ�����
void order_student()
{
	printf("ѧ���ɼ�����\n");
}
//��ʾѧ������
void total_student()
{
	printf("��ʾѧ������");
}