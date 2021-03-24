#define _CRT_SECURE_NO_WARNINGS 1   // 解决VS2019 scanf不安全报错问题

#ifndef _TABLE_
#define _TABLE_

/* 一.定义顺序表 */
//结构体 Table:表类型
typedef struct {
	int* head;  // 1 指针 存储申请的内存首地址
	int length; // 2 长度 记录当前顺序表元素个数
	int size;   // 3 大小 记录当前的顺序表最大长度
}Table;

/* 函数声明 */

// 创建一个顺序表
// 参数: 初始长度
Table CreatTable(int SIZE);

// 给所有元素初始值
// 参数: 表指针 (表以创建完成,只需向表中存储内容)
Table* SetTable(Table* ptable);

// 插入一个元素
// 参数: 表指针,插入值,插入位置坐标 
Table* addNum(Table* ptable, int num, int pos);

// 输出所有元素值
// 参数: 表/表指针(此处用表作为参数_防止改变实参的值)
void displayTable(Table table);

// 删除元素 (按照下标删除 返回指针)
// 参数: 表指针,下标
Table* delNum(Table* ptable, int pos);

// 查找元素 按数值查找(只返回找到的第一个) 返回下标
// 参数: 表,数值
int findWithNum(Table table, int num);

// 更改元素 按照下标更改元素 返回指针
// 参数: 表指针 下标 值
Table* changeNum(Table* ptable, int pos, int num);

#endif