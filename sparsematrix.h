#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>  
#include <iomanip>
using namespace std;

//ϡ�����
template<typename T>
class SparseMatrix
{
public:
    void init(int row, int column);  //��ʼ��������Ϣ
    int getRows() const; //�����
    int getCols() const; //�����.
    void setData(int row, int col, T value);//����ֵ
    T getData(int row, int col) const; //�õ�ֵ
    void eraseRow(int row); //ɾ����
    void eraseCol(int col); //ɾ����

    SparseMatrix<T> operator+(const SparseMatrix<T>& matrix); //��
    SparseMatrix<T> operator-(const SparseMatrix<T>& matrix); //��
    SparseMatrix<T> operator*(const SparseMatrix<T>& matrix); //��
    SparseMatrix<T> transpose() const; //ת��
    void print() const; //���
public:
    template<class T>
    struct Item
    {
        int col;//�ڼ���
        int row;//�ڼ���
        T val;//ֵ
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
                auto it = pvector->m_matrix.begin();//����һ��������,ָ����ʼλ��
                while (it != pvector->m_matrix.end())//δ�����һ��Ԫ��ʱ
                {
                    if (it->row == pos / pvector->getCols() && it->col == pos % pvector->getCols())//����������ֵ
                        return it->val;

                    if(it->val == 0)                //δ�����0���ṩ�޸ĵ����
                        return it->val;
                    ++it;//����������ƶ�
                }
                if (it == pvector->m_matrix.end())    //˵����λ��Ϊ0����û�д���
                {
                    struct Item<T> item = { pos % pvector->getCols(), pos / pvector->getCols(),0 };  //����һ��item��Ϊ��λ�õ��޸����
                    pvector->m_matrix.push_back(item);      //��ӽ�m_matrix
                    return pvector->m_matrix.back().val;    //������ӵĽӿ�
                }
            }
            else
            {
                cout << "�±�Խ�磡" << endl;
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
    int width() const;                                          // ����ÿ����Ԫ�ص����������
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
    auto it = m_matrix.begin();//����һ��������,ָ����ʼλ��
    while (it != m_matrix.end())//δ�����һ��Ԫ��ʱ
    {
        if (it->row == row && it->col == col)//����������ֵ
            return it->val;
        ++it;//����������ƶ�
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
        cout << "�±�Խ�磡" << endl;
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
                if (i->row > row)           //�������Ԫ�ص���������Ҫɾ������������Ԫ��������һ
                    i->row--;
                ++i;
            }
        }
        m_row--;
    }
    else
    {
        cout << "�±�Խ�磡" << endl;
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
                if (i->col > col)               //�������Ԫ�ص���������Ҫɾ������������Ԫ��������һ
                    i->col--;
                ++i;
            }
        }
        m_column--;
    }
    else
    {
        cout << "�±�Խ�磡" << endl;
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
                if (j->val + i->val == 0)               //��ӵ���0��������
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
                if (j->val - i->val == 0)               //�������0��������
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