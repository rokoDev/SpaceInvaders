//
//  TriangleBitMatrix.cpp
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

#include "TriangleBitMatrix.hpp"
#include <climits>
#include "Helper.hpp"

TriangleBitMatrix::~TriangleBitMatrix()
{
    delete [] m_pArray;
}

TriangleBitMatrix::TriangleBitMatrix(const size_t rows, const size_t supposedMaxSetBitCount):
m_rows(rows),
m_sizeInBits((rows*rows-rows)/2+rows),
m_sizeInBytes(ceil((double)(m_sizeInBits) / (double)CHAR_BIT)),
m_pArray(nullptr),
m_setBitIndexes(supposedMaxSetBitCount)
{
    if (rows) {
        m_pArray = new unsigned char[m_sizeInBytes]();
    }
    else {
        m_sizeInBytes = 0;
    }
    
}

TriangleBitMatrix::TriangleBitMatrix(const TriangleBitMatrix & other)
{
    m_pArray = new unsigned char[other.m_sizeInBytes]();
    m_rows = other.m_rows;
    m_sizeInBytes = other.m_sizeInBytes;
    m_sizeInBits = other.m_sizeInBits;
    m_setBitIndexes = other.m_setBitIndexes;
}

TriangleBitMatrix & TriangleBitMatrix::operator=(const TriangleBitMatrix & other)
{
    if (this != &other) {
        
        delete [] m_pArray;
        
        m_pArray = new unsigned char[other.m_sizeInBytes]();
        m_rows = other.m_rows;
        m_sizeInBytes = other.m_sizeInBytes;
        m_sizeInBits = other.m_sizeInBits;
        m_setBitIndexes = other.m_setBitIndexes;
    }
    
    return *this;
}

TriangleBitMatrix::TriangleBitMatrix(TriangleBitMatrix && other):
m_rows{std::move(other.m_rows)},
m_sizeInBytes{std::move(other.m_sizeInBytes)},
m_sizeInBits{std::move(other.m_sizeInBits)},
m_setBitIndexes{std::move(other.m_setBitIndexes)}
{
    m_pArray = other.m_pArray;
    other.m_pArray = nullptr;
}

TriangleBitMatrix & TriangleBitMatrix::operator=(TriangleBitMatrix && other)
{
    if (this != &other) {
        
        delete [] m_pArray;
        
        m_rows = std::move(other.m_rows);
        m_sizeInBytes = std::move(other.m_sizeInBytes);
        m_sizeInBits = std::move(other.m_sizeInBits);
        m_setBitIndexes = std::move(other.m_setBitIndexes);
        m_pArray = other.m_pArray;
        other.m_pArray = nullptr;
    }
    
    return *this;
}

size_t TriangleBitMatrix::getRowCount() const
{
    return m_rows;
}

bool TriangleBitMatrix::get( size_t row,  size_t col) const
{
    CCASSERT(m_pArray, "TriangleBitMatrix::m_pArray is nullptr!");
    CCASSERT(row <= m_rows, "row index is out of bounds");
    CCASSERT(col <= m_rows, "col index is out of bounds");
    
    if (col > row) {
        std::swap(row, col);
    }
    
    size_t bit_index = ((1 + row) * row) / 2 + col - 1;
    return get(bit_index);
}

void TriangleBitMatrix::set(size_t row, size_t col, const bool val)
{
    CCASSERT(m_pArray, "TriangleBitMatrix::m_pArray is nullptr!");
    CCASSERT(row <= m_rows, "row index is out of bounds");
    CCASSERT(col <= m_rows, "col index is out of bounds");
    
    if (col > row) {
        std::swap(row, col);
    }
    
    size_t bit_index = (1 + row) * row / 2 + col - 1;
    set(bit_index, val);
}

inline bool TriangleBitMatrix::get(size_t bit_index) const
{
    return *(m_pArray+bit_index/CHAR_BIT) & (1_uchar << (bit_index%CHAR_BIT));
}

inline void TriangleBitMatrix::set(size_t bit_index, const bool val)
{
    if (val) {
        *(m_pArray+bit_index/CHAR_BIT) |= 1_uchar << (bit_index%CHAR_BIT);
        m_setBitIndexes.push_back(bit_index);
    }
    else {
        *(m_pArray+bit_index/CHAR_BIT) &= ~(1_uchar << (bit_index%CHAR_BIT));
    }
}

void TriangleBitMatrix::resetAllBits()
{
    for (auto & val : m_setBitIndexes) {
        set(val, false);
    }
    m_setBitIndexes.clear();
}

