# MatrixVariant1
Курсовая за 3 сем . Вариант 1
______
## Constructor
Matrix() Конструктор по умолчанию 

Matrix(int) Конструктор кдиничной квадратной матрицы 

Matrix(int, int) Конструктор матрицы NxM

Matrix(Matrix) Конструктор копирования


## Binary operations

Matrix<double> M1 = M2 + M3

Matrix<double> M1 = M2 - M3

Matrix<double> M1 = M2 * M3

Matrix<double> M1 = M2 * T

Matrix<double> M1 = T * M3

Matrix<double> M1 = M3

bool test = M2 == M3

bool test = M2 != M3

## Read from file

std::ifstream fin("input.txt");

fin >> M1;

## Write to file

std::ofstream fout("output.txt");

fout << M1;

## Eigen values/vectors

EigPairs(Matrix)

Реализует процесс поиска собственных чисел и собственных векторов линейного оператора
Собственные числа при выводе ответа отсортированы по убыванию Собственные векторы при выводе результата соответствуют порядку собственных чисел.
