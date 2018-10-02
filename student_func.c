#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include"student.h"
#include<string.h>
#define FILENAME "D:/实训课程/data.txt"

//全局变量存储学生信息
//结构体数组名 
stu s[50];
//学生总人数
int idx = 0;
//s[i].id是整个程序的索引


//函数实现 
//菜单函数
void menu()
{
	//调用系统功能-》清屏
	system("cls");

	printf("============================================\n");
	printf("=================学生管理系统===============\n");
	printf("================1、录入学生信息=============\n");
	printf("================2、显示学生信息=============\n");
	printf("================3、修改学生信息=============\n");
	printf("================4、删除学生信息=============\n");
	printf("================5、插入学生信息=============\n");
	printf("================6、查询学生信息=============\n");
	printf("================7、学生总分排序=============\n");
	printf("================8、显示学生人数=============\n");
	printf("================0、退出管理系统=============\n");
	printf("============================================\n");
	printf("请输入对应编号：\n");
}
//录入学生信息
void insert_student()
{
	/*
	1、该文件以存在学生成绩
	2、该文件不存在学生信息
	*/
	FILE* fp = fopen(FILENAME, "ab+");
	if (!fp)
	{
		printf("打开学生信息数据失败\n");
		return;
	}

	//记录在文件中从存储的学生信息下标
	int index = 0;
	//用户输入标志位
	char key;
	while (1)
	{
		fread(&s[index], sizeof(stu), 1, fp);
		if (feof(fp))
			break;
		index++;
	}
	//关闭文件
	fclose(fp);
	while (1)
	{
		printf("当前学生人数为：%d人，是否要插入数据(Y|N)\n", index);
		getchar();
		key = getchar();
		if (key == 'Y')
		{
			printf("请输入：编号\t姓名\t必修课\t选修课\t实验课\n");
			scanf("%d%s%d%d%d", &s[index].id, s[index].name,
				&s[index].expe, &s[index].elec, &s[index].requ);

			//计算总分
			s[index].sum = s[index].expe + s[index].elec + s[index].requ;

			FILE* fp = fopen(FILENAME, "wb+");
			if (!fp)
			{
				printf("打开学生信息数据失败\n");
				return;
			}
			//index+1 表示元素个数
			fwrite(s, sizeof(stu), index + 1, fp);
			printf("插入数据成功\n");
			fclose(fp);
			index++;
		}
		else
			return;
	}
	

}
//显示学生信息
void show_student()
{
	FILE* fp = fopen(FILENAME, "rb");
	if (fp == NULL)
	{
		printf("读取学生信息失败\n");
		return;
	}
	int index = 0;
	//一直读文件 直到文件结尾
	while (1)
	{
		fread(&s[index], sizeof(stu), 1, fp);
		if (feof(fp))//文件结尾判断
			break;
		index++;
	}

	fclose(fp);
	//printf("当前人数为：%d人\n", index);

	if (index == 0)
	{
		printf("未找到学生信息记录\n");
		return;
	}
	printf("编号\t姓名\t必修课\t选修课\t实验课\t总成绩\n");
	//通过全局变量记录学生人数
	idx = index;
	for (int i = 0; i < index; i++)
	{
		printf("%d\t%s\t%d\t%d\t%d\t%d\n",s[i].id, s[i].name,
			s[i].expe, s[i].elec, s[i].requ, s[i].sum);
	}
}
//修改学生信息
void modify_student()
{
	//显示学生信息
	show_student();
	int id;
	printf("请输入要修改学生信息的编号：\n");
	scanf("%d", &id);
	for (int i = 0; i < idx; i++)
	{
		if (id == s[i].id)
		{
			printf("找到该名学生！\n");
			//i表示当前学员的信息
			printf("请输入：编号\t姓名\t必修课\t选修课\t实验课\n");
			scanf("%d%s%d%d%d", &s[i].id, s[i].name,
				&s[i].expe, &s[i].elec, &s[i].requ);

			//更新当前学生总成绩
			s[i].sum = s[i].elec + s[i].expe + s[i].requ;

			FILE* fp = fopen(FILENAME, "wb");
			if (!fp)
			{
				printf("打开学生信息数据失败\n");
				return;
			}
			fwrite(s, sizeof(stu), idx, fp);

			fclose(fp);
			printf("修改学生信息成功\n");

			//show_student();
			return;
		}
	}
	printf("未找到该名学生！\n");

}
//删除学生信息
void delete_student()
{
	//1、找到学生编号
	//2、依次覆盖之前内容 清空最后一个数据
	//3、总人数-1  写入文件中
	show_student();
	int id;
	printf("请输入要删除学生信息的编号：\n");
	scanf("%d", &id);

	for (int i = 0; i < idx; i++)
	{
		if (id == s[i].id)
		{
			//printf("找到要删除的学生信息\n");
			//判断是否是最后一名学生
			if (i == idx - 1)
			{
				//清空内存
				memset(&s[i], 0, sizeof(stu));
			}
			while (i < idx - 1)
			{
				//将后一名学生信息覆盖于前一名学生
				s[i] = s[i + 1];
				i++;
			}
			memset(&s[i], 0, sizeof(stu));

			idx--;//总人数-1
			FILE* fp = fopen(FILENAME, "wb");
			if (!fp)
			{
				printf("打开学生信息失败\n");
				return;
			}

			fwrite(s, sizeof(stu), idx, fp);

			printf("删除学生信息成功\n");
			fclose(fp);
			return;
		}
	}
	printf("未找到要删除的学生信息\n");

}
//插入学生信息
void insert_info()
{
	show_student();
	int id;
	printf("请输入插入学生信息的编号：\n");
	scanf("%d", &id);
	for (int i = 0; i < idx; i++)
	{
		if (id == s[i].id)
		{
			int temp = idx;
			//插入数据为值为i  s[i]
			//i=i+1  将找到的数据下一个位置作为插入的位置
			i = i + 1;
			while (temp > i)
			{
				s[temp] = s[temp - 1];
				temp--;
			}

			printf("请输入：编号\t姓名\t必修课\t选修课\t实验课\n");
			scanf("%d%s%d%d%d", &s[i].id, s[i].name,
				&s[i].expe, &s[i].elec, &s[i].requ);

			s[i].sum = s[i].expe + s[i].elec + s[i].requ;

			FILE* fp = fopen(FILENAME, "wb");
			if (!fp)
			{
				printf("打开学员信息失败\n");
				return;
			}
			fwrite(s, sizeof(stu), idx + 1, fp);
			fclose(fp);
			printf("插入学员数据成功\n");
			return;
		}
	}
	printf("未找到插入位置，插入失败\n");

}
//查询学生信息
void search_student()
{
	printf("请输入查询学生信息编号：\n");
	int id;
	scanf("%d", &id);
	FILE* fp = fopen(FILENAME, "rb");
	if (!fp)
	{
		printf("打开学生信息失败\n");
		return;
	}
	//结构体数组元素下标
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
	//	printf(printf("未找到学员信息,查找失败\n"));
	//	return;
	//}

	for (int i = 0; i < index; i++)
	{
		if (id == s[i].id)
		{
			printf("找到该名学生数据：\n");
			printf("编号\t姓名\t必修课\t选修课\t实验课\t总成绩\n");
				printf("%d\t%s\t%d\t%d\t%d\t%d\n", s[i].id, s[i].name,
					s[i].expe, s[i].elec, s[i].requ, s[i].sum);
				return;
		}
	}

	printf("未找到该名学生数据：\n");

}
//学生成绩排序
void order_student()
{
	printf("学生成绩排序\n");
}
//显示学生人数
void total_student()
{
	printf("显示学生人数");
}