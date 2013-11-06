/**
 * @file matrix.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <stdexcept>
#include <vector>
namespace oacpp {
    
template<class T>
class matrix {
   private:
      size_t rows;  // number of rows
      size_t cols;  // number of columns
      std::vector<T> elements; // array of elements
   public:
       size_t rowsize() const {return rows;}
       size_t colsize() const {return cols;}
      
      T& operator()( size_t i, size_t j ) {
          return elements[i*cols+j];
      }
      const T& operator()( size_t i, size_t j ) const {
         return elements[i*cols+j];
      }
      const T& element(size_t i, size_t j) const {
         return elements[i*cols+j];
      }
      T& element(size_t i, size_t j) {
         return elements[i*cols+j];
      }
      T& element(size_t loc)
      {
          return elements[loc];
      }
      const T& element(size_t loc) const
      {
          return elements[loc];
      }
      T* data()
      {
          return elements.data();
      }
      // constructors
      matrix(){rows = 0; cols=0; elements = std::vector<T>();}
      matrix( size_t rows, size_t cols );
      matrix( size_t rows, size_t cols, const T* elementArray );
      matrix( size_t rows, size_t cols, std::vector<T> elementVector );
      matrix( const matrix<T>& );
      // destructor
      ~matrix();

      // assignment
      matrix<T>& operator=( const matrix<T>& );

      // comparison
      bool operator==( const matrix<T>& ) const;

      // vector operations
      std::vector<T> getrow(size_t i) const
      {
          std::vector<T> a = std::vector<T>(cols);
          for (size_t j = 0; j < cols; j++)
          {
              a[j] = elements[i*cols + j];
          }
          return a;
      }
      matrix<T> getRowMatrix( size_t i ) const
      {
          // the simple method has an extra loop of assignment
          //std::vector<T> a = this->getrow(i);
          //return matrix<T>(1,cols,a);
          matrix<T> a(1,cols);
          for (size_t j = 0; j < cols; j++)
          {
              a(0,j) = elements[i*cols + j];
          }
          return a;
      };
      
      std::vector<T> getcol(size_t j) const
      {
          std::vector<T> a = std::vector<T>(rows);
          for (size_t i = 0; i < rows; i++)
          {
              a[i] = elements[i*cols + j];
          }
          return a;
      };
      
      matrix<T> getColumnMatrix( size_t j ) const
      {
          matrix<T> a(rows,1);
          for (size_t i = 0; i < rows; i++)
          {
              a(i,0) = elements[i*cols + j];
          }
          return a;
      };
      
      void fill(T x)
      {
          elements.assign(rows*cols, x);
      };
      
      void clear()
      {
          elements.clear();
          rows = 0;
          cols = 0;
      };
      
      bool isEmpty()
      {
          return elements.empty();
      };
};

template<class T>
matrix<T>::matrix( size_t rows, size_t cols)
  : rows(rows), cols(cols)
{
   if ( rows == 0 || cols == 0 )
   {
      throw std::range_error("attempt to create a degenerate matrix");
   }
   elements = std::vector<T>(rows*cols);
}

template<class T>
matrix<T>::matrix( size_t rows, size_t cols, const T* elementArray)
  : rows(rows), cols(cols)
{
    if ( rows == 0 || cols == 0 )
    {
       throw std::range_error("attempt to create a degenerate matrix");
    }
    // initialize from array
    elements = std::vector<T>(rows*cols);
   
    for (size_t i = 0; i < rows*cols; i++)
    {
       elements[i] = elementArray[i];
    }
}

template<class T>
matrix<T>::matrix( size_t rows, size_t cols, std::vector<T> elementVector)
  : rows(rows), cols(cols)
{
    if ( rows == 0 || cols == 0 )
    {
       throw std::range_error("attempt to create a degenerate matrix");
    }
    if (elementVector.size() != rows*cols)
    {
        throw std::range_error("Input element Vector is not the right size");
    }
    elements.assign(elementVector.begin(), elementVector.end());
}

template<class T>
matrix<T>::matrix( const matrix<T>& cp )
  : rows(cp.rows), cols(cp.cols), elements(cp.elements)
{
}

template<class T>
matrix<T>::~matrix()
{
}

template<class T>
matrix<T>& matrix<T>::operator=( const matrix<T>& cp )
{
   if (cp.rows != rows || cp.cols != cols )
   {
       rows = cp.rows;
       cols = cp.cols;
       elements.resize(rows*cols);
   }
   for (size_t i = 0; i < rows*cols; i++)
   {
      elements[i] = cp.elements[i];
   }
   return *this;
}

template<class T>
bool matrix<T>::operator==(const matrix<T>& cp) const
{
    if (cp.rows != rows || cp.cols != cols)
    {
        return false;
    }
    for (size_t i = 0; i < rows*cols; i++)
    {
        if (elements[i] != cp.elements[i])
        {
            return false;
        }
    }
    return true;
}

} // end namespace

#endif	/* MATRIX_H */

