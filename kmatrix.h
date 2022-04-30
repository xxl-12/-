#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>  
#include <iomanip>
using namespace std;

//常规矩阵
template<typename T>
class KMatrix
{
public:
    KMatrix() :m_row(0), m_column(0), m_matrix(0){}
    void init(int row_count, int col_count);
    int getRows() const;
    int getCols() const;
    void setData(int row, int col, T value);
    T getData(int row, int col) const;
    void erase_row(int row);
    void erase_col(int col);
    void print() const;
    KMatrix operator+(const KMatrix<T>& matrix);                //运算符重载“+”为矩阵加法
    KMatrix operator-(const KMatrix<T>& matrix);                //运算符重载“-”为矩阵减法
    KMatrix operator*(const KMatrix<T>& matrix);                //运算符重载“*”重载为叉乘
    KMatrix transpose() const;                                  //转置
public:

    class Iterator
    {
    private:
        int pos;
        KMatrix<T>* pvector;
    public:
        Iterator() {}
        Iterator(KMatrix<T>* vect, int index)
        {
            pvector = vect;
            pos = index;
        }

        void operator+=(int offset)
        {
            pos += offset;
        }
        void operator++()
        {
            operator+=(1);
        }
        void operator-=(int offset)
        {
            pos -= offset;
        }
        void operator--()
        {
            operator-=(1);
        }
        T& operator*()
        {
            if (pos < pvector->getRows()*pvector->getCols())
                return  pvector->getMatrix()[pos/pvector->getCols()][pos%pvector->getCols()];
            else
                return  pvector->getMatrix()[0][0];
        }
        bool operator==(const Iterator& iter)
        {
            return pos == iter.pos;
        }
        bool operator!=(const Iterator& iter)
        {
            return !operator==(iter);
        }
    };

    Iterator begin()
    {
        return Iterator(this,0);
    }
    Iterator end()
    {
        return Iterator(this,m_column*m_row);
    }


private:
    void push_row(int row,T value);                                     //向某一行追加元素提高效率
    void set_size(int row, int col);                                    //设置矩阵大小
    vector<int> width() const;                                          // 计算每列中元素的最大输出宽度
    vector<vector<T>>& getMatrix();
private:
    int m_row;
    int m_column;
    vector<vector<T>> m_matrix;
};

template<typename T>
vector<vector<T>>& KMatrix<T>::getMatrix()
{
    return this->m_matrix;
}
template<typename T>
void KMatrix<T>::init(int row_count, int col_count)
{
    m_column = col_count;
    m_row = row_count;
    m_matrix.resize(row_count);                               //row_count行
    for (size_t i = 0; i < m_matrix.size(); i++) {
        m_matrix[i].resize(col_count);                        //每一行都是col_count列
    }
}

template<typename T>
int KMatrix<T>::getRows() const
{
    return m_row;
}

template<typename T>
int KMatrix<T>::getCols() const
{
    return m_column;
}

template<typename T>
void KMatrix<T>::setData(int row, int col, T value)
{
    if (row < m_row && col < m_column)
        m_matrix[row][col] = value;
    else
        cout << "下标越界！" << endl;
}

template<typename T>
void KMatrix<T>::print() const
{
    vector<int>width = this->width();
    for (int j = 0; j < m_row; j++)
    {
        for (int i = 0; i < m_column; i++)
        {
            cout <<setw(width[i]+ size_t(3))<< m_matrix[j][i];
        }
        cout << endl;
    }
}
template<typename T>
T KMatrix<T>::getData(int row, int col) const
{
    if (row < m_row && col < m_column)
    {
        return m_matrix[row][col];
    }
    else
    {
        cout << "下标越界！" << endl;
        return -1;
    }
}
template<typename T>
void KMatrix<T>::erase_row(int row)
{
    if (row < m_row)
    {
        m_matrix.erase(m_matrix.begin()+row);
        m_row--;
    }
    else
    {
        cout << "下标越界！" << endl;
    }
}

template<typename T>
void KMatrix<T>::erase_col(int col)
{
    if (col < m_column)
    {
        for (int i = 0; i < m_row; i++)
        {
            m_matrix[i].erase(m_matrix[i].begin() + col);
        }
        m_column--;
    }
    else
        cout << "下标越界！" << endl;
}
template <typename T>
void KMatrix<T>::push_row(int row, T value)
{
    m_matrix[row].push_back(value);                             //向某一行追加元素提高效率
}
template<typename T>
void KMatrix<T>::set_size(int row, int col)
{
    m_column = col;
    m_row = row;
    m_matrix.resize(row);
}
template <typename T>
KMatrix<T> KMatrix<T>::operator+(const KMatrix<T>& matrix)                //运算符重载“+”为矩阵加法
{
    /*matrix leagality check*/
    if (this->m_row != matrix.getRows() || this->m_column != matrix.getCols())
    {
        return *this;
    }

    KMatrix<T> outMatrix;
    outMatrix.set_size(this->m_row, this->m_column);
    for (int i = 0; i < this->m_row; i++)
    {
        for (int j = 0; j < this->m_column; j++)
        {
            outMatrix.push_row(i,this->m_matrix[i][j] + matrix.m_matrix[i][j]);
        }
    }

    return outMatrix;
}

template <typename T>
KMatrix<T>  KMatrix<T>::operator-(const  KMatrix<T>& matrix)                //运算符重载“-”为矩阵减法
{
    /*matrix leagality check*/
    if (this->m_row != matrix.getRows() || this->m_column != matrix.getCols())
    {
        return *this;
    }

    KMatrix<T> outMatrix;
    outMatrix.set_size(this->m_row, this->m_column);
    for (int i = 0; i < this->m_row; i++)
    {
        for (int j = 0; j < this->m_column; j++)
        {
            outMatrix.push_row(i, this->m_matrix[i][j] - matrix.m_matrix[i][j]);
        }
    }

    return outMatrix;
}

template <typename T>
KMatrix<T> KMatrix<T>::operator*(const KMatrix<T>& matrix)                    //运算符重载*重载为叉乘
{
    /*matrix leagality check*/
    if (this->m_column != matrix.getRows())
    {
        cout << "operator*():input ileagal" << endl;
        return *this;
    }

    KMatrix<T> outMatrix;
    outMatrix.set_size(this->m_row, matrix.getCols());
    T tempData;
    for (int j = 0; j < m_row; j++)
    {
        for (int k = 0; k < matrix.m_column; k++)
        {
            tempData = 0;
            for (int i = 0; i < m_column; i++)
            {
                tempData += this->m_matrix[j][i] * matrix.m_matrix[i][k];
            }
            outMatrix.push_row(j, tempData);
        }
    }
    return outMatrix;
}

template <typename T>
KMatrix<T> KMatrix<T>::transpose() const
{
    KMatrix<T> outMatrix;
    outMatrix.set_size(this->m_column, this->m_row);
    if (this->m_matrix.empty()) 
        return *this;


    for (int i = 0; i < this->m_column; ++i)
    {
        for (int j = 0; j < this->m_row; ++j)
        {
            outMatrix.push_row(i,this->m_matrix[j][i]);
        }
    }

    return outMatrix;
}
// 返回矩阵所有元素的最大值
template <typename T>
vector<int> KMatrix<T>::width() const
{
    vector<int>width;
    int max;
    for (int i = 0; i < this->m_column; ++i)
    {
        max = 0;
        for (int j = 0; j < this->m_row; ++j)
        {
            string str = to_string(m_matrix[j][i]);
            if (str.length() > max)
                max = str.length();
        }
        width.push_back(max);
    }
    return width;
}