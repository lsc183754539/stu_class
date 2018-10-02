#pragma once//防止头文件重复包含

typedef struct _STUDENT
{
	int id;//编号
	char name[21];//姓名
	int elec;//选修课
	int expe;//必修课
	int requ;//实验课
	int sum;//总分
}stu;