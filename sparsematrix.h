#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>  
#include <iomanip>
using namespace std;

//稀疏矩阵
template<typename T>
class SparseMatrix
{
public:
    void init(int row, int column);  //初始化行列信息
    int getRows() const; //获得行
    int getCols() const; //获得列.
    void setData(int row, int col, T value);//设置值
    T getData(int row, int col) const; //得到值
    void eraseRow(int row); //删除行
    void eraseCol(int col); //删除行

    SparseMatrix<T> operator+(const SparseMatrix<T>& matrix); //加
    SparseMatrix<T> operator-(const SparseMatrix<T>& matrix); //减
    SparseMatrix<T> operator*(const SparseMatrix<T>& matrix); //乘
    SparseMatrix<T> transpose() const; //转置
    void print() const; //输出
public:
    template<class T>
    struct Item
    {
        int col;//第几列
        int row;//第几行
        T val;//值
    };

    class Iterator
    {
    private:
        int pos;
        SparseMatrix<T>* pvector;
    public:
        Iterator() {}
        Iterator(SparseMatrix<T>* vect, int index)
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
            if (pos < pvector->getRows() * pvector->getCols())
            {
                auto it = pvector->m_matrix.begin();//定义一个迭代器,指向起始位置
                while (it != pvector->m_matrix.end())//未到最后一个元素时
                {
                    if (it->row == pos / pvector->getCols() && it->col == pos % pvector->getCols())//行列相等输出值
                        return it->val;

                    if(it->val == 0)                //未储存的0，提供修改的入口
                        return it->val;
                    ++it;//迭代器向后移动
                }
                if (it == pvector->m_matrix.end())    //说明该位置为0，且没有储存
                {
                    struct Item<T> item = { pos % pvector->getCols(), pos / pvector->getCols(),0 };  //生成一个item作为该位置的修改入口
                    pvector->m_matrix.push_back(item);      //添加进m_matrix
                    return pvector->m_matrix.back().val;    //返回添加的接口
                }
            }
            else
            {
                cout << "下标越界！" << endl;
            }
            return pvector->m_matrix.front().val;
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
        return Iterator(this, 0);
    }
    Iterator end()
    {
        return Iterator(this, m_column * m_row);
    }
private:
    int m_row;
    int m_column;
    vector<Item<T>> m_matrix;
    int width() const;                                          // 计算每列中元素的最大输出宽度
};


template<typename T>
void SparseMatrix<T>::init(int row_count, int col_count)
{
    m_column = col_count;
    m_row = row_count;
}

template<typename T>
void SparseMatrix<T>::print() const
{
    for (int j = 0; j < m_row; j++)
    {
        for (int i = 0; i < m_column; i++)
        {
            cout << setw(width()+ size_t(3))<< this->getData(j,i);
        }
        cout << endl;
    }
}

template<typename T>
T SparseMatrix<T>::getData(int row, int col) const
{
    auto it = m_matrix.begin();//定义一个迭代器,指向起始位置
    while (it != m_matrix.end())//未到最后一个元素时
    {
        if (it->row == row && it->col == col)//行列相等输出值
            return it->val;
        ++it;//迭代器向后移动
    }
    return 0;
}
template<typename T>
int SparseMatrix<T>::getRows() const
{
    return m_row;
}

template<typename T>
int SparseMatrix<T>::getCols() const
{
    return m_column;
}

template<typename T>
void SparseMatrix<T>::setData(int row, int col, T value)
{
    if (row < m_row && col < m_column)
    {
        if (value!=0)
        {
            struct Item<T> item = { col,row,value };
            m_matrix.push_back(item);
        }
    }
    else
    {
        cout << "下标越界！" << endl;
    }
}

template<typename T>
void SparseMatrix<T>::eraseRow(int row)
{
    if (row < m_row)
    {
        for (typename vector<Item<T>>::iterator i = m_matrix.begin(); i != m_matrix.end(); )
        {
            if (i->row == row)
            {
                i = m_matrix.erase(i);
            }
            else
            {
                if (i->row > row)           //如果其他元素的行数大于要删除的行数，该元素行数减一
                    i->row--;
                ++i;
            }
        }
        m_row--;
    }
    else
    {
        cout << "下标越界！" << endl;
    }
}

template<typename T>
void SparseMatrix<T>::eraseCol(int col)
{
    if (col < m_column)
    {
        for (typename vector<Item<T>>::iterator i = m_matrix.begin(); i != m_matrix.end(); )
        {
            if (i->col == col)
            {
                i = m_matrix.erase(i);
            }
            else
            {
                if (i->col > col)               //如果其他元素的列数大于要删除的列数，该元素列数减一
                    i->col--;
                ++i;
            }
        }
        m_column--;
    }
    else
    {
        cout << "下标越界！" << endl;
    }
}

template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& matrix)
{
    /*matrix leagality check*/
    if (this->m_row != matrix.getRows() || this->m_column != matrix.getCols())
    {
        return *this;
    }
    SparseMatrix<T> outMatrix;
    outMatrix.init(this->m_row, this->m_column);
    for (auto i = m_matrix.begin(); i != m_matrix.end(); ++i)
    {
        struct Item<T> item = { i->col,i->row,i->val };
        outMatrix.m_matrix.push_back(item);
    }
    for (auto i = matrix.m_matrix.begin(); i != matrix.m_matrix.end(); ++i)
    {
        auto j = outMatrix.m_matrix.begin();
        for (; j != outMatrix.m_matrix.end(); )
        {
            if (j->col == i->col && j->row == i->row)
            {
                if (j->val + i->val == 0)               //相加等于0，不储存
                {
                    j = outMatrix.m_matrix.erase(j);
                }
                else
                {
                    j->val = j->val + i->val;
                }
                break;
            }
            ++j;
        }
        if (j == outMatrix.m_matrix.end())
        {
            struct Item<T> item = { i->col,i->row,i->val };
            outMatrix.m_matrix.push_back(item);
        }

    }
    return outMatrix;
}

template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator-(const SparseMatrix<T>& matrix)
{
    /*matrix leagality check*/
    if (this->m_row != matrix.getRows() || this->m_column != matrix.getCols())
    {
        return *this;
    }
    SparseMatrix<T> outMatrix;
    outMatrix.init(this->m_row, this->m_column);
    for (auto i = m_matrix.begin(); i != m_matrix.end(); ++i)
    {
        struct Item<T> item = { i->col,i->row,i->val };
        outMatrix.m_matrix.push_back(item);
    }
    for (auto i = matrix.m_matrix.begin(); i != matrix.m_matrix.end(); ++i)
    {
        auto j = outMatrix.m_matrix.begin();
        for (; j != outMatrix.m_matrix.end(); )
        {
            if (j->col == i->col&& j->row == i->row)
            {
                if (j->val - i->val == 0)               //相减等于0，不储存
                {
                    j = outMatrix.m_matrix.erase(j);
                }
                else
                {
                    j->val = j->val - i->val;
                }
                break;
            }
            ++j;
        }
        if( j == outMatrix.m_matrix.end())
        {
           struct Item<T> item = { i->col,i->row,-(i->val) };
           outMatrix.m_matrix.push_back(item);
        }

    }
    return outMatrix;

}
template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix<T>& matrix)
{
    /*matrix leagality check*/
    if (this->m_column != matrix.getRows())
    {
        cout << "operator*():input ileagal" << endl;
        return *this;
    }
    SparseMatrix<T> outMatrix;
    outMatrix.init(this->m_row, matrix.getCols());  
    for (auto i = m_matrix.begin(); i != m_matrix.end(); ++i)
    {
        for (auto j = matrix.m_matrix.begin(); j != matrix.m_matrix.end(); ++j)
        {
            if (i->col == j->row)
            {
                auto k = outMatrix.m_matrix.begin();
                for (; k != outMatrix.m_matrix.end(); ++k)
                {
                    if (i->row == k->row && j->col == k->col)
                    {
                        k->val = k->val + i->val * j->val;
                        break;
                    }
                }
                if (k == outMatrix.m_matrix.end())
                {
                    struct Item<T> item = { j->col,i->row,i->val * j->val };
                    outMatrix.m_matrix.push_back(item);
                }

            }
        }
    }
    return outMatrix;
}

template<typename T>
SparseMatrix<T> SparseMatrix<T>::transpose() const
{
    SparseMatrix<T> outMatrix;
    outMatrix.init(this->m_column, this->m_row);
    if (this->m_matrix.empty())
        return *this;

    for (auto i = m_matrix.begin(); i != m_matrix.end(); ++i)
    {
        struct Item<T> item = { i->row,i->col,i->val};
        outMatrix.m_matrix.push_back(item);
    }
    return outMatrix;
}

template<typename T>
int SparseMatrix<T>::width() const
{
    int max = 0;
    for (auto i = m_matrix.begin(); i != m_matrix.end(); ++i)
    {
        string str = to_string(i->val);
        if ((int)str.length() > max)
            max = str.length();
    }
    return max;
}