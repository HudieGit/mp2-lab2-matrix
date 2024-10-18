// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size){ // конструктор
      if (sz < 0 || sz > MAX_VECTOR_SIZE) {
          throw out_of_range("Vector is incorrect");
      }
     pMem = new T[sz];// {}; // У типа T д.б. конструктор по умолчанию //хотя бы тут все нормально
  }
  TDynamicVector(T* arr, size_t s) : sz(s){
      if (sz < 0 || sz > MAX_VECTOR_SIZE) {
          throw out_of_range("vector is incorrect");
    }
    pMem = new T[sz];
    for (int i = 0; i < sz; i++) {
        pMem[i] = arr[i];
    } 
  }
  TDynamicVector(const TDynamicVector& v){ //конструктор копирования
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept{ // конструктор перемещения (передача памяти)
      sz = v.sz;
      pMem = std::move(v.pMem);
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector(){
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v){ // оператор присваивания
      if (this == &v) {
          return *this;
      }
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept{
      if (this == &v) {
          return *this;
      }
      delete[] pMem;
      pMem = std::move(v.pMem);
      sz = v.sz;
      sz = 0;
      pMem = nullptr;
      return *this; // а почему в прошлом методе не написали изначально? странно
  }

  // индексация
  T& operator[](size_t ind){
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const{
      return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind){
      if (ind < 0 || ind > sz - 1) {
          throw out_of_range("Index is incorrect");
      }
      return this->pMem[ind];
  }
  const T& at(size_t ind) const{
      if (ind < 0 || ind > sz - 1) {
          throw out_of_range("Index is incorrect");
      }
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept {
      if (this == &v) {
          return 1;
      }
      if (sz != v.sz) {
          return 0;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return 0;
          }
          return 1;
      }
  }
  bool operator!=(const TDynamicVector& v) const noexcept{
      return !(*this == v);
  }
  // скалярные операции
  TDynamicVector operator+(T val) {
      TDynamicVector<T> result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(double val){
      TDynamicVector<T> result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(double val){
      TDynamicVector<T> result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v){
      if (sz != v.sz) {
          throw logic_error("Vectors don't match in length");
      }
      TDynamicVector<T> result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }
      return result;
    }
  TDynamicVector operator-(const TDynamicVector& v){
    if (sz != v.sz) {
        throw logic_error("Vectors don't match in length");
    }
    TDynamicVector<T> result(sz);
    for (int i = 0; i < sz; i++) {
        result.pMem[i] = pMem[i] - v.pMem[i];
    }
    return result;
  }
   T operator*(const TDynamicVector& v) { //noexcept(noexcept(T())) - Сысоевские приколы?
      if (sz != v.sz) {
          throw logic_error("Vectors don't match in length");
      }

      T result = 0;
      for (int i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
      return result;
  }
  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept{
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v){
      for (size_t i = 0; i < v.sz; i++) {
          istr >> v.pMem[i]; // требуется оператор>> для типа T
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v){
      for (size_t i = 0; i < v.sz; i++) {
         ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    }
    return ostr;
  }

  size_t size() const noexcept{
      return sz;
  }

};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s){
        if (s < 0 || s > MAX_MATRIX_SIZE) {
            throw out_of_range("matrix size is incorrect");
        }
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz);
        }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept{
      if (this == &m) { // если сравниваем буквально с тем же
          return 1;
      }
      if (sz != m.sz) {
          return 0;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) {
              return 0;
          }
      }
      return 1;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val){
      TDynamicMatrix<T> result(sz);
      result.pMem = pMem * val;
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v){
      if (sz != v.size()) {
          throw logic_error("");
      }
      TDynamicMatrix<T> result(sz);
      for (int i = 0; i < sz; i++) {
          result[i] = pMem[i] * v;
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m){
      if (sz != m.size()) {
          throw logic_error();
      }

      TDynamicMatrix<T> result(rz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + m.pMem[i];
      }

      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m){
      if (sz != m.size()) {
          throw logic_error();
      }

      TDynamicMatrix<T> result(rz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - m.pMem[i];
      }

      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m){ //мяу мяу, мяу мяу мяу....
      if (sz != m.size()) {
          throw logic_error();
      }

      TDynamicMatrix<T> result(rz);
      //зануление матрицы результата
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              result.pMem[i][j] = 0;
          }
      }

      //умножение...
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++) {
                  result.pMem[i][j] += pMem[i][j] * m.pMem[j][k];
              }
          }
      }
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v){
      for (int i = 0; i < v.sz; i++) {
          std::cout << v.pMem[i] << endl;
      }
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v){
      for (int i = 0; i < v.sz; i++) {
          std::cout << v.pMem[i] << endl;
      }
      return ostr;
  }

  size_t SizeMatrix() const noexcept{
      return sz;
  }
};

#endif
