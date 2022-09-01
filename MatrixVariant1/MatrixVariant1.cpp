#include <iostream>
#include <fstream>
using namespace std;


template <class T>
class Matrix 
{	
private:
	int row, col;
	T** matrix;
	

public:
	Matrix()
	{
		row = col = 0;
		matrix = nullptr;
	}

	Matrix(int _row, int _col)
	{
		row = _row;
		col = _col;
		//выделить память для строк 
		 matrix = new T * [row];//(T**)
		//выделить память для столбиков в строках 
		for (int i=0; i < row; i++) {
			matrix[i] = new T[col];
		}
		//заполнить все нулями
		for (int i=0; i < row; i++){
			for (int j=0; j < col; j++)
				matrix[i][j] = 0;
			
		}
		cout <<"constructor " << this<<endl;
	}

	Matrix(const Matrix & other): row(other.row), col(other.col) {

		matrix = new T * [row];
		for (int i = 0; i < row ; i++)
			matrix[i] = new T[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				matrix[i][j] = other.matrix[i][j];

		}
		cout << "copy "<< this<<endl;
	}

	~Matrix()
	{
		for (int i = 0; i < row; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		cout <<"distruct "<< this<<endl;

	}

	//Методы доступа 
	T GetMij(int i, int j)
	{
		if ((row > 0) && (col > 0)) 
			return matrix[i][j];
		
		else 
			return 0;
	
	}

	int GetRow()
	{
		return (row);
	}
	int GetCol()
	{
		return (col);
	}
	

	void SetMij(int i, int j, T value)
	{
		if ((i < 0) || (i >= row))
			return;
		if ((j < 0) || (j >= col))
			return;
		matrix[i][j] = value;
	}




	void Print()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cout << matrix[i][j] << "\t";
			cout << endl;
		}
		cout << "---------------------" << endl << endl;
	}


	void Rand(int M)
	{
		for (int i = 0; i < row; i++) 
			for (int j = 0; j < col; j++)
				matrix[i][j] = rand()%M;	
	}

	//Бинарные операции (+, -, *, = =, !=, =)

	Matrix operator +( Matrix & other)
	{
		Matrix temp(other.GetRow(), other.GetCol());
		for (int i = 0; i < other.GetRow(); i++)
			for (int j = 0; j < other.GetCol(); j++)
				temp.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
		return temp;
	}


	Matrix operator -(Matrix& other)
	{
		Matrix temp(other.GetRow(), other.GetCol());
		for (int i = 0; i < other.GetRow(); i++)
			for (int j = 0; j < other.GetCol(); j++)
				temp.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
		return temp;
	}

	Matrix operator *(T num)
	{
		Matrix temp(this->GetRow(), this->GetCol());
		for (int i = 0; i < temp.GetRow(); i++)
			for (int j = 0; j < temp.GetCol(); j++)
				temp.matrix[i][j] = this->matrix[i][j] * num;
		return temp;
	}

	friend Matrix operator *(T num, Matrix &other)
	{
		Matrix temp(other.GetRow(), other.GetCol());
		for (int i = 0; i < temp.GetRow(); i++)
			for (int j = 0; j < temp.GetCol(); j++)
				temp.matrix[i][j] = other.matrix[i][j] * num;
		return temp;
	}


	Matrix operator *(Matrix &other)
	{
		if (this->GetCol() != other.GetRow()) 
		{
			throw std::exception("smth");
		}
		Matrix temp(this->GetRow(), other.GetCol());
		for (int i = 0; i < temp.GetRow(); i++) {
			for (int j = 0; j < temp.GetCol(); j++) {
				for (int k = 0; k < this->GetCol(); k++) {
					temp.matrix[i][j] += (this->matrix[i][k] * other.matrix[k][j]);
				}
			}
		}
		return temp;
	}


	bool operator ==( Matrix & other) 
	{
		if (this->GetCol()!=other.GetCol() || this->GetRow()!=other.GetRow()) {
			return false;
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (this->matrix[i][j] != other.matrix[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator !=(Matrix & other)
	{
		return!(*this == other);
	}

	Matrix & operator =(Matrix& other)
	{
		if (this == &other) {
			return *this;
		}
		if (this->row != other.row || this->col != other.col) {
			for (int i = 0; i < this->row; i++) {
				delete[] this->matrix[i];
			}
			delete[] this->matrix;
		}

		row = other.row;
		col = other.col;


		matrix = new T * [other.row];
		for (int i = 0; i < other.row; i++)
			matrix[i] = new T[other.col];

		for (int i = 0; i < other.row; i++)
			for (int j = 0; j < other.col; j++)
				matrix[i][j] = other.matrix[i][j];


		return *this;
	}

	friend ostream& operator <<(ostream& os, Matrix<T>& m)
	{
		for (int i = 0; i < m.GetRow(); i++)
		{
			for (int j = 0; j < m.GetCol(); j++)
				os << m.matrix[i][j] << "\t";
			os << endl;
		}
		return os;
	}

};

//Перегрузить операторы ввода / вывода в поток >> , << так, чтобы можно было вводить матрицы и из файла, и
//	из консоли / выводить матрицы в консоль и в файл





int main()
{
	//Matrix<int> M();
	//Matrix<int> M1(3,3);
	//M1.Rand(10);
	//Matrix<int>M2(3,3);
	//M2.Print();
	//M1.Print();
	//int down = M1.GetMij(0,0);
	//cout << down;
	//M1.SetMij(0, 0, 12);
	//M1.Print();

	//Matrix<int> M1(3, 3);
	//Matrix<int> M2(3, 3);
	//M1.Rand(10);
	//M2.Rand(10);
	//M1.Print();
	//M2.Print();
	////Matrix<int>M3 = M1 - M2;
	////M1.Print();
	////M2.Print();
	////M3.Print();
	////Matrix<int>M4 = M3 * 2;
	////Matrix<int>M5 = 2* M3;
	////M5.Print();
	////bool Check = M5 != M4;
	////cout << Check;
	////bool Check2 = M1 != M2;
	////cout << Check2;
	////bool Check3 = M5 == M4;
	////cout << Check3;
	////bool Check4 = M1 == M2;
	////cout << Check4;
	//Matrix<int> M10 = M1 * M2;
	//Matrix<int> M11(2, 2);
	//M10.Print();
	//M10 = M11;
	//M10.Print();
	
	Matrix<int> M1(2, 3);
	Matrix<int> M2(3, 2);
	M1.Rand(10);
	M2.Rand(10);
	M1.Print();
	M2.Print();
	Matrix<int >M3 = M1 * M2;
	M3.Print();
	cout << M3;
	



	//проблемы с деструкторм если не квадратная матрица 

}


