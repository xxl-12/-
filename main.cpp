#include<iostream>
#include"kmatrix.h"
#include"sparsematrix.h"
using namespace std;

int main()
{
	//常规矩阵测试
#if 0

	KMatrix<int> kmatrix1, kmatrix2, kmatrix3;

	cout << "初始化一个3*4的矩阵1" << endl;
	kmatrix1.init(3, 4);				
	kmatrix1.print();

	cout << "设置(1，2)的值为3" << endl;
	kmatrix1.setData(1, 2, 3);
	kmatrix1.print();

	cout << "设置(4，2)的值(越界测试)" << endl;
	kmatrix1.setData(1, 2, 3);
	kmatrix1.print();

	cout << "矩阵1行数：" << kmatrix1.getRows() << "  矩阵1列数：" << kmatrix1.getCols() << endl;

	cout << "矩阵1随机赋值" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			kmatrix1.setData(i, j, rand()%1000);
		}
	}
	kmatrix1.print();

	cout << "生成一个4*5的矩阵2" << endl;
	kmatrix2.init(4, 5);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			kmatrix2.setData(i, j, rand() % 100);
		}
	}
	kmatrix2.print();

	cout << "矩阵2删除第0行和第0列" << endl;
	kmatrix2.erase_col(0);
	kmatrix2.erase_row(0);
	kmatrix2.print();

	cout << "矩阵1,2相加" << endl;
	kmatrix3 = kmatrix1 + kmatrix2;
	kmatrix3.print();

	cout << "矩阵1-2" << endl;
	kmatrix3 = kmatrix1 - kmatrix2;
	kmatrix3.print();

	cout << "矩阵1删除第3列" << endl;
	kmatrix1.erase_col(3);
	kmatrix1.print();

	cout << "矩阵1*2" << endl;
	kmatrix3 = kmatrix1 * kmatrix2;
	kmatrix3.print();

	cout << "矩阵2的转置" << endl;
	kmatrix3 = kmatrix2.transpose();
	kmatrix3.print();
	cout << "矩阵2的转置通过迭代器遍历" << endl;
	for (auto i = kmatrix3.begin(); i != kmatrix3.end(); ++i)
	{
		cout << *i << endl;
	}
#endif
	//稀疏矩阵测试
#if 1
	SparseMatrix<int> matrix1, matrix2 , matrix3;
	cout << "初始化一个3*4的矩阵1" << endl;
	matrix1.init(3, 4);
	matrix1.print();

	cout << "设置(1，2)的值为3，设置(0，2)的值为9，设置(1，3)的值为7" << endl;
	matrix1.setData(1, 2, 3);
	matrix1.setData(0, 2, 9);
	matrix1.setData(1, 3, 7);
	matrix1.print();

	cout << "设置(4，2)的值(越界测试)" << endl;
	matrix1.setData(4, 2, 3);
	matrix1.print();

	cout << "矩阵1行数：" << matrix1.getRows() << "  矩阵1列数：" << matrix1.getCols() << endl;

	cout << "生成一个4*5的矩阵2" << endl;
	matrix2.init(4, 5);
	matrix2.setData(3, 2, 3);
	matrix2.setData(0, 4, 9);
	matrix2.setData(1, 3, 7);
	matrix2.print();

	cout << "矩阵2删除第0行和第0列" << endl;
	matrix2.eraseCol(0);
	matrix2.eraseRow(0);
	matrix2.print();

	cout << "矩阵1,2相加" << endl;
	matrix3 = matrix1 + matrix2;
	matrix3.print();

	cout << "矩阵1-2" << endl;
	matrix3 = matrix1 - matrix2;
	matrix3.print();

	cout << "矩阵1删除第3列" << endl;
	matrix1.eraseCol(3);
	matrix1.print();

	cout << "矩阵1*2" << endl;
	matrix3 = matrix1 * matrix2;
	matrix3.print();

	cout << "矩阵2的转置" << endl;
	matrix3 = matrix2.transpose();
	matrix3.print();

	cout << "矩阵2的转置通过迭代器遍历" << endl;
	for (auto i = matrix3.begin(); i != matrix3.end(); ++i)
	{
		cout << *i << endl;
	}

#endif

}