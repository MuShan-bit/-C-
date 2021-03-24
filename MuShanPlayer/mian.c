#include<stdio.h>
#include"Table.h"

int main() {
	// 创建顺序表
	Table t;
	t = CreatTable(5);
	// 给初始值
	SetTable(&t);
	// 输出顺序表
	displayTable(t);
	// 插入值;
	addNum(&t, 13, 3); //在顺序表t中的下标为3的位置插入数值13;
	// 输出顺序表
	displayTable(t);
	// 按位置删除值并输出(链式操作_两个函数写在一起_作用:装逼)   在顺序表t中的下标为3的位置删除数值;
	displayTable(*delNum(&t, 3));
	// 查找 (测试方法,如果找到数值4_找到则删除并输出)
	displayTable(*delNum(&t, findWithNum(t, 4)));   //又是一个装逼的代码
	// 修改
	displayTable(*changeNum(&t, 3, 1314)); //把顺序表t中下标为3的数值更改为1314后输出;

	return 0;
} 