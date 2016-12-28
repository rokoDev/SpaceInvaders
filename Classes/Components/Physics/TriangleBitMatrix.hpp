//
//  TriangleBitMatrix.hpp
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

#ifndef TriangleBitMatrix_hpp
#define TriangleBitMatrix_hpp

#include <vector>

class TriangleBitMatrix {
private:
    size_t m_rows;
    size_t m_sizeInBits;
    size_t m_sizeInBytes;
    unsigned char * m_pArray;
    std::vector<size_t> m_setBitIndexes;
    
    bool get(size_t bit_index) const;
    void set(size_t bit_index, const bool val);
public:
    ~TriangleBitMatrix();
    TriangleBitMatrix(const size_t rows = 0, const size_t supposedMaxSetBitCount = 100);
    TriangleBitMatrix(const TriangleBitMatrix & other);
    TriangleBitMatrix & operator=(const TriangleBitMatrix & other);
    TriangleBitMatrix(TriangleBitMatrix && other);
    TriangleBitMatrix & operator=(TriangleBitMatrix && other);
    
    size_t getRowCount() const;
    bool get(size_t row, size_t col) const;
    void set(size_t row, size_t col, const bool val);
    void resetAllBits();
};

#endif /* TriangleBitMatrix_hpp */
