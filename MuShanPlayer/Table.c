#include"Table.h"
#include<stdlib.h>
#include<stdio.h>

#define _CRT_SECURE_NO_WARNINGS 1   // 解决VS2019 scanf不安全报错问题

// /* 函数定义 */

// 创建一个(int型数据)顺序表
// 参数:初始长度
Table CreatTable(int SIZE) {
	Table table;

	//创建一个空的顺序表,动态申请内存(存储空间)
	table.head = (int*)malloc(sizeof(int) * SIZE); // malloc用于申请动态内存,详情见往期文章:指针(三)动态内存
	//判断:  malloc()函数如果申请失败返回NULL(0)
	if (!table.head) // table.head==NULL 与 !table.head 判断等价
	{
		printf("动态内存申请失败!!\n");
		exit(0); //结束程序代码
	}
	//当动态内存申请成功时:
	table.length = 0;   // 长度初始化为 0(开始顺序表内未存储元素_因此初始化长度为0)
	table.size = SIZE;  // 大小初始化为 SIZE (size为内存大小)

	return table;
}

// 给所有元素初始值
// 参数: 表指针 (表以创建完成,只需向表中存储内容)
Table* SetTable(Table* ptable) {
	printf("向表内输入%d个整数:", ptable->size);
	// size_t类型产生:typedef unsigned int size_t;(非负整型变量)
	// "->" :指针取结构体子数据
	for (size_t i = 0; i < ptable->size; i++) // 遍历整个表
	{
		scanf("%d",&ptable->head[i]);   // 赋值并通过i增加不断偏移头指针
		ptable->length++;               // 每添加一个元素,顺序表长度增加一
	}
	return ptable;
}

// 插入一个元素
// 参数:表指针,插入值,插入位置下标 
Table* addNum(Table* ptable, int num, int pos) {
	// 判断参数是否可以执行(插入位置超出范围)
	// 插入范围: pos(0 --- ptable->length)
	if (pos < 0 || pos >ptable->length) {
		printf("参数错误! 表中无法找到插入位置\n");
		return ptable;
	}
	// 能够插入
	// 判断是否有存储空间_如果存储空间不足则扩容
	if (ptable->length >= ptable->size) {
		printf("表指针内存不足! 开始扩容....\n");
		// 扩容:(动态内存扩容具体内容见往期文章_指针(三)动态内存)
		// 1. 记录原来的内存
		int* pTemp = ptable->head; // 只有head涉及内存,无需Table*只需使用int*即可

		// 2. 申请新的内存
		ptable->head = (int*)calloc(sizeof(int), ptable->size *= 2); // 以2倍方式扩容并更改size值
		// 判断扩容是否成功(内容与Table.c_16行代码类似)
		if (!ptable->head) {
			printf("动态内存申请失败! 未成功扩容_未添加元素");
			// 未成功扩容则把原来的内存恢复(不能丢弃)
			ptable->head = pTemp;
			return ptable;
		}
		// 3. 拷贝新的内存
		for (size_t i = 0; i < ptable->length; i++)
		{
			ptable->head[i] = pTemp[i];
		}
		// 4. 释放原来的内存
		free(pTemp);
		// 5. 置空
		pTemp = NULL;   //防止变成野指针
	}
	// 插入:
	// 1.后移(先移动后面的元素)
	for (int i = ptable->length; i >= pos; i--)
	{
		ptable->head[i + 1] = ptable->head[i];
	}
	// 2.插入
	ptable->head[pos] = num;
	// 3.更改长度
	ptable->length++;
	return ptable;
}

// 输出所有元素值
// 参数: 表/表指针(此处用表作为参数_防止改变实参的值)
void displayTable(Table table) {
	printf("顺序表中存储的元素是:\n");
	for (size_t i = 0; i < table.length; i++)
	{
		printf("%d ", table.head[i]);
	}
	printf("\ntable.size = %d , table.length = %d ;\n\n", table.size, table.length);
}

// 删除元素 (按照下标删除 返回指针)
// 参数: 表指针,下标
Table* delNum(Table* ptable, int pos) {
	// 判断参数是否可以执行(删除位置超出范围)
	if (pos >= ptable->length || pos < 0) {
		printf("参数错误! 表中无法找到删除位置\n");
		return ptable;
	}
	// 删除
	for (int i = pos; i < ptable->length; i++)
	{
		ptable->head[i] = ptable->head[i + 1];
	}
	// 改变长度
	ptable->length--;
	// 判断是否缩减大小
	if (ptable->length <= ptable->size / 2 && ptable->size % 2 == 0) {
		// 满足缩减条件
		printf("以满足内存缩减条件,正在重新分配内存...\n");
		// 缩减内存:
		// 1. 记录原来内存
		int* ptemp = ptable->head;
		// 2. 申请新的内存
		ptable->head = calloc(sizeof(int), ptable->size /= 2);
		// 判断缩减是否成功
		if (!ptable->head) {
			printf("动态内存申请失败! 未成功缩减");
			// 未成功缩减则把原来的内存恢复(不能丢弃)
			ptable->head = ptemp;
			return ptable;
		}
		// 3. 拷贝新的内存
		for (size_t i = 0; i < ptable->length; i++)
		{
			ptable->head[i] = ptemp[i];
		}
		// 4. 释放原来的内存
		free(ptemp);
		// 5. 置空
		ptemp = NULL;
	}
	
	return ptable;
}

// 查找元素 按数值查找(只返回找到的第一个) 返回下标
// 参数: 表,数值
int findWithNum(Table table, int num) {
	for (int i = 0; i < table.length; i++)
	{
		if (num == table.head[i]) {
			return i;
		}
	}
	return -1; // 找不到返回-1 程序员查找代码规范!!
}

// 更改元素 按照下标更改元素 返回指针
// 参数: 表指针 下标 值
Table* changeNum(Table* ptable, int pos, int num) {
	// 判断参数是否可以执行(更改位置超出范围)
	if (pos > ptable->length - 1 || pos < 0) {
		printf("参数错误! 表中无法找到修改位置_修改失败\n");
		return ptable;
	}
	ptable->head[pos] = num;
	return ptable;
}