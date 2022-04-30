#include<iostream>
#include"kmatrix.h"
#include"sparsematrix.h"
using namespace std;

int main()
{
	//����������
#if 0

	KMatrix<int> kmatrix1, kmatrix2, kmatrix3;

	cout << "��ʼ��һ��3*4�ľ���1" << endl;
	kmatrix1.init(3, 4);				
	kmatrix1.print();

	cout << "����(1��2)��ֵΪ3" << endl;
	kmatrix1.setData(1, 2, 3);
	kmatrix1.print();

	cout << "����(4��2)��ֵ(Խ�����)" << endl;
	kmatrix1.setData(1, 2, 3);
	kmatrix1.print();

	cout << "����1������" << kmatrix1.getRows() << "  ����1������" << kmatrix1.getCols() << endl;

	cout << "����1�����ֵ" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			kmatrix1.setData(i, j, rand()%1000);
		}
	}
	kmatrix1.print();

	cout << "����һ��4*5�ľ���2" << endl;
	kmatrix2.init(4, 5);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			kmatrix2.setData(i, j, rand() % 100);
		}
	}
	kmatrix2.print();

	cout << "����2ɾ����0�к͵�0��" << endl;
	kmatrix2.erase_col(0);
	kmatrix2.erase_row(0);
	kmatrix2.print();

	cout << "����1,2���" << endl;
	kmatrix3 = kmatrix1 + kmatrix2;
	kmatrix3.print();

	cout << "����1-2" << endl;
	kmatrix3 = kmatrix1 - kmatrix2;
	kmatrix3.print();

	cout << "����1ɾ����3��" << endl;
	kmatrix1.erase_col(3);
	kmatrix1.print();

	cout << "����1*2" << endl;
	kmatrix3 = kmatrix1 * kmatrix2;
	kmatrix3.print();

	cout << "����2��ת��" << endl;
	kmatrix3 = kmatrix2.transpose();
	kmatrix3.print();
	cout << "����2��ת��ͨ������������" << endl;
	for (auto i = kmatrix3.begin(); i != kmatrix3.end(); ++i)
	{
		cout << *i << endl;
	}
#endif
	//ϡ��������
#if 1
	SparseMatrix<int> matrix1, matrix2 , matrix3;
	cout << "��ʼ��һ��3*4�ľ���1" << endl;
	matrix1.init(3, 4);
	matrix1.print();

	cout << "����(1��2)��ֵΪ3������(0��2)��ֵΪ9������(1��3)��ֵΪ7" << endl;
	matrix1.setData(1, 2, 3);
	matrix1.setData(0, 2, 9);
	matrix1.setData(1, 3, 7);
	matrix1.print();

	cout << "����(4��2)��ֵ(Խ�����)" << endl;
	matrix1.setData(4, 2, 3);
	matrix1.print();

	cout << "����1������" << matrix1.getRows() << "  ����1������" << matrix1.getCols() << endl;

	cout << "����һ��4*5�ľ���2" << endl;
	matrix2.init(4, 5);
	matrix2.setData(3, 2, 3);
	matrix2.setData(0, 4, 9);
	matrix2.setData(1, 3, 7);
	matrix2.print();

	cout << "����2ɾ����0�к͵�0��" << endl;
	matrix2.eraseCol(0);
	matrix2.eraseRow(0);
	matrix2.print();

	cout << "����1,2���" << endl;
	matrix3 = matrix1 + matrix2;
	matrix3.print();

	cout << "����1-2" << endl;
	matrix3 = matrix1 - matrix2;
	matrix3.print();

	cout << "����1ɾ����3��" << endl;
	matrix1.eraseCol(3);
	matrix1.print();

	cout << "����1*2" << endl;
	matrix3 = matrix1 * matrix2;
	matrix3.print();

	cout << "����2��ת��" << endl;
	matrix3 = matrix2.transpose();
	matrix3.print();

	cout << "����2��ת��ͨ������������" << endl;
	for (auto i = matrix3.begin(); i != matrix3.end(); ++i)
	{
		cout << *i << endl;
	}

#endif

}