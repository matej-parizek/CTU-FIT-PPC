/*** PPC - HW03 ***/
/* Tento soubor se odevzdava. Zde implementujte vsechny potrebne funkce */

#include "matrix.hpp"

using namespace std;

/*** FUNCTION FOR GETITNG NUMBER TO ALL POSITION IN DATA  ***/

void inputData(Matrix *matrix,int number ){
    for (int i = 0; i < matrix->ncols*matrix->nrows; ++i) {
        matrix->data.at(i)=number;
    }
}
void plusData(Matrix *matrix,int number ){
    for (int i = 0; i < matrix->ncols*matrix->nrows; ++i) {
        matrix->data.at(i)+=number;
    }
}
void nasobeniDat(Matrix *matrix,int number ){
    for (int i = 0; i < matrix->ncols*matrix->nrows; ++i) {
        matrix->data.at(i)*=number;
    }
}

/*** CONSTRUCTORS & DESTRUCTOR ***/
Matrix::Matrix(int nrow, int ncol)
{
    if(nrow<0 || ncol<0)
        throw matrix_negative_size();
    nrows=nrow; ncols=ncol;
    data.resize(nrow*ncol);
    inputData(this,0);
}

Matrix::Matrix(int rowscols)
{
    if(rowscols<0)
        throw matrix_negative_size();
    ncols=rowscols;nrows=rowscols;
    data.resize(rowscols*rowscols);
    inputData(this,0);
}

Matrix::Matrix(const Matrix &m)
{
    nrows=m.nrows; ncols=m.ncols; data.assign(m.data.begin(),m.data.end());
}

Matrix::Matrix(const std::vector<value> &v)
{
    Matrix matrix=Matrix((int)v.size());
    matrix.eye();
    for (int i = 0; i < matrix.nrows; ++i) {
        for (int j = 0; j < matrix.ncols; ++j) {
            if(i==j)
                matrix(i,j)=v.at(i);
        }
    }
    (*this)=matrix;
}


Matrix::~Matrix()
{
    this->data.clear();
}

/*** L1 Matrix:: FUNCTIONS ***/
void Matrix::zeros()
{
    inputData(this,0);
}

void Matrix::uniform(value element)
{
    inputData(this,element);
}

void Matrix::eye()
{
    int count=0,diagonal=0;
    for (int i = 0; i < (int)data.size(); ++i) {
        if(count==diagonal)
            data.at(i)=1;
        else
            data.at(i)=0;
        if(count==ncols-1){
            count=0;
            diagonal++;
            continue;
        }
        count++;
    }
}

void Matrix::bias(value b)
{
    plusData(this,b);
}

/*** L2 Matrix:: FUNCTIONS ***/

void Matrix::scale(value s)
{
    nasobeniDat(this,s);

}

void Matrix::transpose()
{
    Matrix matrix=Matrix(this->ncols, this->nrows);
    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            matrix(j,i)= (*this)(i,j);
        }
    }
    (*this)=matrix;
}

/*** L3 Matrix:: FUNCTIONS ***/

void Matrix::changedim(int rows, int cols)
{
    if(rows<0 || cols<0)
        throw matrix_negative_size();
    Matrix matrix= Matrix(rows,cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(i< this->nrows && j< this->ncols)
                matrix(i,j)=(*this)(i,j);
        }
    }
    (*this)=matrix;
}



/*** L1 Matrix:: Operators ***/
value Matrix::operator () (int row, int col) const
{
    if(row> this->nrows-1|| row<0) {
        throw std::out_of_range("Row index is out of range");
    }
    if(col> this->ncols-1 || col<0) {
        throw std::out_of_range("Column index is out of range");
    }
    return this->data.at((row* this->ncols)+col);;
}

value & Matrix::operator () (int row, int col)
{
    if(row> this->nrows-1|| row<0)
        throw std::out_of_range("Row index is out of range");
    if(col> this->ncols-1 || col<0)
        throw std::out_of_range("Column index is out of range");
    return (*this).data.at((row* this->ncols)+col);
}

bool Matrix::operator==(const Matrix &m)
{
    if(this->ncols!=m.ncols || this->nrows!=m.nrows || m.data.size()!= this->data.size())
        return false;
    for (int i = 0; i < (int)this->data.size(); ++i) {
        if(this->data.at(i)!=m.data.at(i))
            return false;
    }
    return true;
}

Matrix & Matrix::operator=(const Matrix &m)
{
    this->ncols =m.ncols;
    this->nrows=m.nrows;
    this->data.assign(m.data.begin(),m.data.end());
    return *this ;
}

/*** L3 Matrix:: Operators ***/
std::vector<value> Matrix::operator () (void) const
{
    vector<value> vector;
    for (int i = 0; i < this->ncols; ++i) {
        for (int j = 0; j < this->nrows; ++j) {
            if(j==i)
                vector.push_back((*this)(i,j));
        }
    }
    return vector;
}


/*** L1 NON-MEMBER FUNCTIONS/OPERATORS ***/

std::ostream & operator<<(std::ostream &os, const Matrix &m)
{
    if((int)m.data.size()==0)
        return os<<endl;
    int count=0;
    for (int i = 0; i < (int)m.data.size(); ++i) {
        if(count==m.ncols-1 ) {
            if(count==0)
                os<<setw(5)<<right<<m.data.at(i)<<" "<<endl;
            else
                os<<setw(6)<<right<<" "+to_string(m.data.at(i))<<" "<<endl;
            count=0;
            continue;
        }
        else if(count<m.ncols-1 && count!=0)
            os<<setw(6)<<right<<" "+to_string(m.data.at(i));
        else if(count==0)
            os<<setw(5)<<right<<to_string(m.data.at(i));
        count++;
    }
    return os;
}

void extractInt(Matrix & m, string line, int *counter){
    stringstream ss;
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());

    ss<<line;
    string tmp;
    int cols=0;
    int numb;
    while (!ss.eof()){
        ss>>tmp;
        if(stringstream(tmp)>>numb){
            m.data.at(*counter)=numb;
            cols++;
            *counter+=1;
        }
        tmp="";
    }

    if(cols!=m.ncols) {
        delete &m;
        throw matrix_in_bad_body();
    }
}

void loadMatrixFile(Matrix & m, string fname)
{
    ifstream myfile;
    myfile.open (fname);
    if(!myfile) {
        throw cannot_open_file();
    }
    string line,headerLine;
    int count=0, row, col;
    stringstream ss;

    //get header data
    getline(myfile, line, '\n');
    ss<< line;
    string tmp;
    while (!ss.eof()) {
        ss>>tmp;
        int buff;
        if(stringstream(tmp)>>buff ){
            if(count==0)
                row=buff;
            if(count==1)
                col=buff;
            if(count>1) {
                throw matrix_in_bad_header();
            }
            count++;
        }

        tmp="";
    }
    if(count<2) {
        throw matrix_in_bad_header();
    }
    //get data of matrix
    int counter=0;
    Matrix *matrix= new Matrix(row,col);
    int cRow=0;
    while (getline(myfile, line, '\n')) {
        extractInt(*matrix,line, &counter);
        cRow++;
    }
    if(row*col!=counter ) {
        delete matrix;
        throw matrix_in_bad_body();
    }

    m=*matrix;
    delete matrix;
    myfile.close();
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{

    if(lhs.data.size()!=rhs.data.size() || lhs.nrows!=rhs.nrows || lhs.ncols!=rhs.ncols)
       throw matrix_bad_sizes();
    Matrix matrix= Matrix(lhs.nrows,lhs.ncols);
    for (int i = 0; i <(int) lhs.data.size(); ++i) {
        matrix.data.at(i)=lhs.data.at(i)+rhs.data.at(i);
    }

    return matrix;
}

Matrix operator+(const value & lhs, const Matrix &rhs)
{
    Matrix matrix= Matrix(rhs.nrows,rhs.ncols);
    for (int i = 0; i <(int) rhs.data.size(); ++i) {
        matrix.data.at(i)=lhs+rhs.data.at(i);
    }
    return matrix;
}

Matrix operator+(const Matrix &lhs, const value & rhs) 
{
    Matrix matrix= Matrix(lhs.nrows,lhs.ncols);
    for (int i = 0; i <(int) lhs.data.size(); ++i) {
        matrix.data.at(i)=rhs+lhs.data.at(i);
    }
    return matrix;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{
    if(lhs.data.size()!=rhs.data.size() || lhs.nrows!=rhs.nrows || lhs.ncols!=rhs.ncols)
        throw matrix_bad_sizes();
    Matrix matrix= Matrix(lhs.nrows,lhs.ncols);
    for (int i = 0; i <(int) lhs.data.size(); ++i) {
        matrix.data.at(i)=lhs.data.at(i)-rhs.data.at(i);
    }
    return matrix;
}

Matrix operator-(const value & lhs, const Matrix &rhs)
{
    Matrix matrix= Matrix(rhs.nrows,rhs.ncols);
    for (int i = 0; i <(int) rhs.data.size(); ++i) {
        matrix.data.at(i)=lhs-rhs.data.at(i);
    }
    return matrix;
}

Matrix operator-(const Matrix &lhs, const value & rhs) 
{
    Matrix matrix= Matrix(lhs.nrows,lhs.ncols);
    for (int i = 0; i <(int) lhs.data.size(); ++i) {
        matrix.data.at(i)=lhs.data.at(i)-rhs;
    }
    return matrix;

}

/*** L2 NON-MEMBER FUNCTIONS/OPERATORS ***/

Matrix nasobeniMatic(const Matrix A, const Matrix B){
    int counter=0;
    Matrix C=Matrix(A.nrows,(B).ncols);
    for (int i = 0; i <(int) A.nrows; i++)
    {
        for (int j = 0; j < B.ncols; j++)
        {
            int n = 0;
            for (int k = 0; k < B.nrows; k++)
            {
                n+=(A)(i,k)*(B)(k,j);
            }
            C.data.at(counter)=n;
            counter+=1;
        }
    }
    return C;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
    if(lhs.ncols!=rhs.nrows)
        throw matrix_bad_sizes();

    Matrix matrix=nasobeniMatic(lhs,rhs);
    return matrix;
}

Matrix operator*(const value & lhs, const Matrix &rhs)
{
    Matrix matrix= Matrix(rhs);
    nasobeniDat(&matrix,lhs);
    return matrix;
}

Matrix operator*(const Matrix &lhs, const value & rhs) 
{
    Matrix matrix=Matrix(lhs);
    nasobeniDat(&matrix,rhs);
    return  matrix;
}

Matrix hadamard(const Matrix &lhs, const Matrix &rhs)
{
    if(lhs.data.size()!=rhs.data.size() || lhs.nrows!=rhs.nrows || lhs.ncols!=rhs.ncols)
        throw matrix_bad_sizes();
    Matrix matrix= Matrix(lhs.nrows,lhs.ncols);
    for (int i = 0; i <(int) lhs.data.size(); ++i) {
        matrix.data.at(i)=lhs.data.at(i)*rhs.data.at(i);
    }
    return matrix;
}

bool kontrola(const Matrix &m){
    for (int i = 0; i < (int)m.data.size(); ++i) {
        if(m.data.at(i)<0)
            return false;
    }
    return true;
}

Matrix power(const Matrix &m, unsigned int pow)
{
    if(m.ncols!=m.nrows)
        throw matrix_bad_sizes();
    Matrix matrix= Matrix(m);
    if(pow==0) {
        matrix.eye();
        return matrix;
    }
    for (unsigned int i = 0; i < pow-1; ++i) {
        matrix=matrix*m;
    }
    return matrix;
}

/*** L3 NON-MEMBER FUNCTIONS/OPERATORS ***/

Matrix horzcat(const Matrix &lhs, const Matrix &rhs)
{
    int min;
    if(lhs.nrows<rhs.nrows)
        min=lhs.nrows;
    else
        min=rhs.nrows;
    if(lhs.nrows!=rhs.nrows)
        throw matrix_bad_sizes();
    Matrix matrix= Matrix(min,lhs.ncols+rhs.ncols);
    for (int i = 0; i < (int)matrix.nrows; ++i) {
        for (int j = 0; j <matrix.ncols ; ++j) {
            if(j<lhs.ncols) {
                 matrix(i,j)=lhs(i,j);
            }
            else{
                int index=j-lhs.ncols;
                matrix(i,j)=rhs(i,index);
            }
        }
    }
    return matrix;
}

Matrix vertcat(const Matrix &top, const Matrix &bot)
{
    int min;
    if(top.ncols<bot.ncols)
        min=top.ncols;
    else
        min=bot.ncols;
    if(bot.ncols!=top.ncols)
        throw matrix_bad_sizes();
    Matrix matrix= Matrix(top.nrows+bot.nrows,min);
    for (int i = 0; i < (int)matrix.nrows; ++i) {
        for (int j = 0; j <matrix.ncols ; ++j) {
            if(i<top.nrows)
                matrix(i,j)=top(i,j);
            else{
                int index=i-top.nrows;
                matrix(i,j)=bot(index,j);
            }
        }
    }
    return matrix;
}

Matrix blkdiag (const Matrix & lhs, const Matrix & rhs)
{
    Matrix matrix= Matrix(lhs.nrows+rhs.nrows,lhs.ncols+rhs.ncols);
    if(matrix.nrows!=matrix.ncols  || (rhs.ncols!=rhs.nrows ) || lhs.nrows!=lhs.ncols)
        throw matrix_bad_sizes();
    for (int i = 0; i < (int)matrix.nrows; ++i) {
        for (int j = 0; j <matrix.ncols ; ++j) {
            if(i<lhs.nrows && j<lhs.nrows)
                matrix(i,j)=lhs(i,j);
            if(i>=lhs.nrows && j>=lhs.nrows){
                int index1=i-lhs.nrows;
                int index2=j-lhs.ncols;
                matrix(i,j)=rhs(index1,index2);
            }
        }
    }
    return matrix;
}

Matrix blkdiag (const value & lhs, const Matrix & rhs) 
{
    Matrix matrix= Matrix(1+rhs.nrows,1+rhs.ncols);
    if(matrix.nrows!=matrix.ncols)
        throw matrix_bad_sizes();
    for (int i = 0; i < (int)matrix.nrows; ++i) {
        for (int j = 0; j <matrix.ncols ; ++j) {
            if(i==0 && j==0)
                matrix(i,j)=lhs;
            if(i>0 && j>0){
                int index1=i-1;
                int index2=j-1;
                matrix(i,j)=rhs(index1,index2);
            }
        }
    }
    return matrix;

}

Matrix blkdiag (const Matrix & lhs, const value & rhs) 
{
    Matrix matrix= Matrix(1+lhs.nrows,1+lhs.ncols);
    if(matrix.nrows!=matrix.ncols)
        throw matrix_bad_sizes();
    for (int i = 0; i < (int)matrix.nrows; ++i) {
        for (int j = 0; j <matrix.ncols ; ++j) {
            if(i==matrix.nrows-1 && j==matrix.ncols-1)
                matrix(i,j)=rhs;
            if(i<matrix.nrows-1 && j<matrix.ncols-1){
                matrix(i,j)=lhs(i,j);
            }
        }
    }
    return matrix;
}

Matrix blkdiag (const value & lhs, const value & rhs) 
{
    return Matrix(0);
}

Matrix kronecker(const Matrix &lhs, const Matrix &rhs)
{
    Matrix matrix=Matrix(0);
    for (int i = 0; i < lhs.nrows; ++i) {
        Matrix mat;
        for (int j = 0; j < lhs.ncols; ++j) {
            if(j==0)
                mat=lhs(i,j)*rhs;
            else
                mat=horzcat(mat,lhs(i,j)*rhs);
        }
        if(i==0)
            matrix=mat;
        else
            matrix=vertcat(matrix,mat);
    }
    return matrix;
}



