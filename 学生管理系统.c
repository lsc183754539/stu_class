#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"student_func.h"



int main()
{
	//1�����̿���
	//2���ӿڶԽ�

	int id;
	while (1)
	{
		menu();
		scanf("%d", &id);

		switch (id)
		{
		case 1:
			insert_student();
			break;
		case 2:
			show_student();
			break;
		case 3:	
			modify_student();
			break;
		case 4:
			delete_student();
			break;
		case 5:
			insert_info();
			break;
		case 6: 
			search_student();
			break;
		case 7:
			order_student();
			break;
		case 8:
			total_student();
			break;
		case 0:
			return 0;//exit(0);//�˳�����
		default:
			printf("�����������������\n");
			break;
		}

		//printf("�����������...\n");
		system("pause");
	}

	return EXIT_SUCCESS;
}
