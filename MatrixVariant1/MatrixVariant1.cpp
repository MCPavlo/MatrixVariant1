#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <complex>



double pi = 2 * acos(0.0);

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

	Matrix(int n)
	{
		row = col=n;	
		matrix = new T * [row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[col];
		}
		this->eye();

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
		/*cout <<"constructor " << this<<endl;*/
	}

	Matrix(const Matrix & other): row(other.row), col(other.col) {

		matrix = new T * [row];
		for (int i = 0; i < row ; i++)
			matrix[i] = new T[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				matrix[i][j] = other.matrix[i][j];

		}
		//cout << "copy "<< this<<endl;
	}




	~Matrix()
	{
		for (int i = 0; i < row; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		/*cout <<"distruct "<< this<<endl;*/

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


	friend Matrix ColumnM(Matrix& m, int n){
		if (n<0||n>=m.col)
			throw std::exception("smth");

		Matrix M (m.row, 1);

		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < M.col; j++) {
				M.matrix[i][j] = m.matrix[i][n];
			}
		}	
		return(M);
	}

	void Column(Matrix& mat, int n) {
		if (n < 0 || n >= this->col)
			throw std::exception("smth");

		Matrix M(this->row, 1);

		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < M.col; j++) {
				M.matrix[i][j] = this->matrix[i][n];
			}
		}
		mat = M;
	}

	void SetCol(Matrix& m, int n) 
	{
		if ((m.col != 1)||(this->row!=m.row))
			throw std::exception("smth");
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < m.col; j++) {
				this->matrix[i][n] = m.matrix[i][j];
			}
		}

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

	Matrix operator +( const Matrix & other)
	{	
		if ((this->col != other.col) || (this->row != other.row))
			throw exception("smth");

		Matrix temp(other.row, other.col);
		for (int i = 0; i < other.row; i++)
			for (int j = 0; j < other.col; j++)
				temp.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
		return temp;
	}

	 
	Matrix operator -(const Matrix& other)
	{
		if ((this->col != other.col) || (this->row != other.row))
			throw exception("smth");

		Matrix temp(other.row, other.col);
		for (int i = 0; i < other.row; i++)
			for (int j = 0; j < other.col; j++)
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




	Matrix operator *(const Matrix &other)
	{
		if (this->col != other.row) 
		{
			throw std::exception("smth");
		}
		Matrix temp(this->row, other.col);
		for (int i = 0; i < temp.row; i++) {
			for (int j = 0; j < temp.col; j++) {
				for (int k = 0; k < this->col; k++) {
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

	 Matrix & operator =(  const Matrix& other)
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








	//Перегрузить операторы ввода / вывода в поток >> , << так, чтобы можно было вводить матрицы и из файла, и
	//	из консоли / выводить матрицы в консоль и в файл

	 friend ostream& operator <<(ostream& os, const Matrix& m)
	{
		for (int i = 0; i < m.row; i++)
		{
			for (int j = 0; j < m.col; j++)
				os << m.matrix[i][j] << "\t";
			os << endl;
		}
		return os;
	}


	 friend istream& operator >>(istream& is, Matrix& m)
	 {
		 for (int i = 0; i < m.row; i++)
		 {
			 for (int j = 0; j < m.col; j++)
				 is >> m.matrix[i][j];
		 }	
		 return is;
	 }

	 Matrix& eye()
	 {
		 for (int i = 0; i < row; i++) {
			 for (int j = 0; j < col; j++) {
				 if (i != j)
					 matrix[i][j] = 0;
				 else
					 matrix[i][j] = 1;

			 }
		 }

		 return *this;
	 }
	 /////////////////////////////////////////////////////////////////////////////////////////////////////////

	 friend Matrix transpose(Matrix& m) {
		 Matrix c = Matrix(m.row, m.col);
		 for (int i = 0; i < m.row; ++i)
			 for (int j = 0; j < m.col; ++j)
				 c.matrix[j][i] = m.matrix[i][j];
		
		 return c;
	 
	 }

	 friend T scalar(Matrix& first, Matrix& second)
	 {
		 if (first.col != 1 || second.col != 1 || first.row != second.row)
			 throw std::exception("smth");

		 T P = 0;
		 for (int i = 0; i < first.row; i++)
			 for (int j = 0; j < first.col; j++) {
				 P += first.matrix[i][j] * second.matrix[i][j];
			 }
		 
		 return(P);
	 }

	 friend T Length(Matrix& m) {
		 T temp = 0;
		 T  lol = 1;
		 for (int i = 0; i < m.row; i++)
			 for (int j = 0; j < m.col; j++)
				 temp = temp + m.matrix[i][j] * m.matrix[i][j];
		 temp = sqrt(temp);
		 return temp;
	 }



	 friend Matrix getNorm(Matrix& m) {
		 T temp=0;	 
		 T  lol = 1;
		 for (int i = 0; i < m.row; i++)
			 for (int j = 0; j < m.col; j++)
				 temp = temp+ m.matrix[i][j]* m.matrix[i][j];
		 temp = sqrt(temp) ;
		 Matrix Norm=(m*(lol/temp));
		 return Norm;
	 }



	   Matrix MatrixGetNorm(Matrix& m ) {
		   Matrix Matr(this->row, 1);
		   for (int i = 0; i < this->col; i++) {
			   this->Column(Matr, i);
			   Matr=getNorm(Matr);
			   m.SetCol(Matr, i);
		   }
		   /*cout << NormMatr;*/
		   return m;
	 }



	   friend Matrix projC ( Matrix& first,  Matrix & second) {
		   Matrix A;
		   T temp1 = scalar(second, first);
		  // cout << temp1<<endl<<"---------------\n";
		   T temp2 = scalar(first, first);
		   //cout << temp2 << endl << "---------------\n";
		   T temp3 = temp1/temp2;
		  // cout << temp3 << endl << "---------------\n";
		   A = first *temp3;
		   //cout << first << endl << "---------------\n";
		  // cout << A << endl << "---------------\n";
		   return(A);
	   }
	

	   friend Matrix Grama( Matrix& A, Matrix & QQQ)
	   {   
		   
		   Matrix Q(A.row, A.col);
		   Matrix R(A.row, A.col);
		   Matrix U(A.row, A.col);
		   Matrix QQ(A.row, A.col);
		   Matrix Ucol1;
		   Matrix Acol1;
		   Matrix Ucol;
		   Matrix Acol;
		   U.Column(Ucol1, 0);
		   A.Column(Acol1, 0);
		   Ucol1 = Acol1;
		   U.SetCol(Ucol1, 0);
		   for (int i = 1; i < A.col; i++) {
			  /* A.Column(Acol, i);
			   U.Column(Ucol, i);*/
			   Matrix subt(A.row, 1);
			   int j = 0;
			   Acol = ColumnM(A, i);
			   Ucol = ColumnM(U, i);
			   
			   while (j < i) {
				   Matrix uj;
				   Matrix ai;
				   uj = ColumnM(U, j);
				   ai = ColumnM(A, i);
					 Matrix proj;
					 proj = projC(uj, ai);
				   subt = subt + proj;
				   j++;
			   }
			   
			   Ucol = Acol - subt;
			   U.SetCol(Ucol, i);
		   }


			   U.MatrixGetNorm(Q);
			   R=transpose(Q)*A;	    
			   QQQ = R * Q;
			   return(QQQ);
	   }

	 

	 friend Matrix eig(const Matrix & m, int iterations = 50000)
	 {
		 Matrix TempQ1(m.col);
		 Matrix TempQ2;
		 Matrix TempQ(m.row, m.col);
		 Matrix QQ(m.row, m.col);
		 Matrix A(m.row, m.col);
		Matrix Eig(m.row, 1);
		 Matrix EigVectors(m.row,m.col);
		 
		 QQ = m;
		
		 for (int i = 0; i < iterations; i++)
		 { 
			Grama(QQ,A);
			QQ = A;

		 }
		 
		 for (int j = 0; j < QQ.row; j++) {
			 //EigValues.push_back(QQ.matrix[j][j]);
			 Eig.matrix[j][0] = QQ.matrix[j][j];//сдлеать eigvaluse как диагональ матриыц 
		 }
	/*	 sort(EigValues.rbegin(), EigValues.rend());
		 for (int k = 0; k < EigValues.size(); k++) {
		 
			 cout << EigValues[k]<<endl;
		 }*/
	/*	 cout<<"Eig:\n" << Eig;
		 cout << "EigVectors:\n" << TempQ1;
		 cout << "EigVectors:\n" << TempQ2;*/
		 cout << Eig;
		 return Eig;
	 }
///////////////////////////////////////////////////////////////////




	 friend Matrix ls_solvefwd(Matrix & L, Matrix& b) {
		 Matrix x (L.row, 1);//col
		 int i, j;
		 T tmp;
		 for (i = 0; i < L.row; i++) {
			 tmp = b.matrix[i][0];
			 for (j = 0; j < i; j++) {
				 tmp -= L.matrix[i][j] * x.matrix[j][0];
			 }
			 x.matrix[i][0] = tmp / L.matrix[i][i];
		 }
		// cout << x;
		 return x;
	 }
	
	 friend Matrix ls_solvebck(Matrix& U, Matrix& b) {
		 Matrix x (U.row, 1);
		 int i = U.row, j;
		T tmp;
		 while (i-- > 0) {
			 tmp = b.matrix[i][0];
			 for (j = i; j < U.row; j++) {
				 tmp -= U.matrix[i][j] * x.matrix[j][0];
			 }
			 x.matrix[i][0] = tmp / U.matrix[i][i];
		 }
		 //cout << x;
		 return x;
	 }

	 friend void LU(const Matrix& a, const Matrix& l, const Matrix& u) {
		 int i = 0, j = 0, k = 0;
		 for (i = 0; i < a.row; i++) {
			 for (j = 0; j < a.row; j++) {
				 if (j < i)
					 l.matrix[j][i] = 0;
				 else {
					 l.matrix[j][i] = a.matrix[j][i];
					 for (k = 0; k < i; k++) {
						 l.matrix[j][i] = l.matrix[j][i] - l.matrix[j][k] * u.matrix[k][i];
					 }
				 }
			 }
			 for (j = 0; j < a.row; j++) {
				 if (j < i)
					 u.matrix[i][j] = 0;
				 else if (j == i)
					 u.matrix[i][j] = 1;
				 else {
					 u.matrix[i][j] = a.matrix[i][j] / l.matrix[i][i];
					 for (k = 0; k < i; k++) {
						 u.matrix[i][j] = u.matrix[i][j] - ((l.matrix[i][k] * u.matrix[k][j]) / l.matrix[i][i]);
					 }
				 }
			 }
		 }
	 }
	
	 friend Matrix ls_solve(const Matrix& lu, const Matrix& b) {
		
		 Matrix L_ (lu.row, lu.col);
		 Matrix U_ (lu.row, lu.col);
		 Matrix x (lu.row, lu.col);
		 Matrix y (lu.row, lu.col);
		 Matrix P(lu.row);
		 Matrix Pb;
		 LU(lu, L_, U_);
	/*	 cout << L_ << endl << "--------------------\n";
		 cout << U_ << endl << "--------------------\n";
		 cout << x << endl << "--------------------\n";
		 cout << y << endl << "--------------------\n";*/
		 Pb = P*b;

		 // We solve L*y = P*b using forward substition
		 y = ls_solvefwd(L_, Pb);
		 //cout << ls_solvefwd(L_, b) << endl << "--------------------\n";

		 // We solve U*x=y
		  x = ls_solvebck(U_, y);
		  //cout <<"XXXXXXXXXXX" <<endl << x << endl << "--------------------\n";
		 
		 return x;
	 }





	///////////////////////////////////////////
	
	




	 friend Matrix inv(const Matrix& lup) {
		 int n = lup.col;
		 Matrix r(n,n);
		 Matrix I (lup.row);//eye
		 Matrix invx;
		 Matrix Ix;
		 int i, j;
		 for (j = 0; j < n; j++) {
			 I.Column(Ix, j);
			 invx = ls_solve(lup, Ix);
			 for (i = 0; i < invx.row; i++) {
				 r.matrix[i][j] = invx.matrix[i][0];
			 }
		 }
		 return r;
	 }







	 friend void EigPairs( Matrix & m) {
		 if (m.row != m.col)
			 throw exception("smth");

		 Matrix I(m.row);
		 Matrix StartVector(m.row, 1);
		 Matrix Temp;
		 Matrix Temp2;
		 for (int g = 0; g < StartVector.row; g++)
			 for (int gg = 0; gg < StartVector.col; gg++)
				 StartVector.matrix[g][gg] = 1;
		 Matrix Eig = eig(m);
		 vector<T> EigenValues; 
		 for (int v = 0; v < Eig.row; v++)
			 EigenValues.push_back(Eig.matrix[v][0]) ;
		 sort(EigenValues.rbegin(), EigenValues.rend());
		 Matrix EigVectors;
		 for (int i = 0; i < Eig.row; i++) {
			 Temp = inv((m - EigenValues[i] * I))* StartVector;
			 Temp2 = getNorm(Temp);

			 cout << "--------------------\n";
			 cout<<"lamda = "<< EigenValues[i] << "\n";
			 cout << Temp2 <<"--------------------\n";
		 }



	 }


	 friend Matrix MatrixRotation(Matrix& m, double angle)
	 {
		 Matrix rotation(2, 2);
		 rotation.matrix[0][0] = cos(angle);
		 rotation.matrix[0][1] = -sin(angle);
		 rotation.matrix[1][0] = sin(angle);
		 rotation.matrix[1][1] = cos(angle);
		 m = rotation;

		 return m;

	 }


	 friend Matrix MatrixReflection(Matrix& m, double angle)
	 {
		 Matrix reflection(2, 2);
		 reflection.matrix[0][0] = 1 - 2 * sin(angle) * sin(angle);
		 reflection.matrix[0][1] = 2 * sin(angle) * cos(angle);
		 reflection.matrix[1][0] = 2 * sin(angle) * cos(angle);
		 reflection.matrix[1][1] = -(1 - 2 * sin(angle) * sin(angle));
		 m = reflection;

		 return m;
	  
	 }

};








int main()
{
	Matrix<double> M1(2, 1);//Исходный вектор 
	Matrix<double> M2(2, 2);
	Matrix<double> M3(2, 2);
	Matrix<double> M4(3, 3);
	
	fstream fin("input.txt");
	fstream fout("output.txt");
	fin >> M1;//[7, 1]
	cout << M1;


	//Ввести матрицы основных элементарных преобразований на плоскости(поворот, отражение и т.п.)
	//Реализовать преобразование исходного вектора операторами, заданными с помощью матриц
	MatrixRotation(M2, pi / 2);
	cout << M2 * M1 << "----------------\n";
	MatrixReflection(M3, pi / 2);
	cout << M3 * M1 << "----------------\n";

	//Реализовать поиск и вывод собственных чисел, собственных векторов оператора, если они есть

	M4.Rand(10);
	cout << M4<<"----------------\n";;
	EigPairs(M4);



}


