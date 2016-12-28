//
//  BinMacro.h
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

/***********************************************************************\
 |**************************       bin.h       **************************|
 |*************       Definitions for binary constants       ************|
 |************       Compile-time templates and macros.       ***********|
 \***********************************************************************/

#ifndef BinMacro_h
#define BinMacro_h

#ifdef __cplusplus

template <unsigned long N>
struct bin8                    /* +-- if (i==0 || i==1) ok  --+ */
{                              /* |  else compile-time error  | */
    enum {value=bin8<N/16u>::value*2+(1/((N%16u)==0 || (N%16u)==1)*(N%16u))};
};

template<>
struct bin8<0>
{
    enum {value=0};
};

/**  +++ WARNING! +++  **/
/** Don't calling macro argument as 'x' within MicroSoft Visual C++ 6! **/
#define BIN8(Y)               (bin8<0x##Y##ul>::value)
#define BIN16(Y1, Y2)         (BIN8(Y1)*256ul+BIN8(Y2))
#define BIN32(Y1, Y2, Y3, Y4) (BIN16(Y1, Y2)*65536ul+BIN16(Y3, Y4))
#define BIN64(Y1, Y2, Y3, Y4, Y5, Y6, Y7, Y8)                           \
(BIN32(Y1, Y2, Y3, Y4)*4294967296ull+    \
BIN32(Y5, Y6, Y7, Y8))
#else

/** Range checking (0 or 1) **/
#define CHECK(x)                        \
((1 / (((x) == 0 || (x) == 1))), x)

/** Get once bit **/
#define GET_N(x, n)                     \
CHECK(((x) >> ((n) * 4)) & 0xF)

/** Convert once byte (hexdecimal unsigned long constants) **/
#define BIT8(x)                         \
((GET_N(x, 0) << 0) +                  \
(GET_N(x, 1) << 1) +                  \
(GET_N(x, 2) << 2) +                  \
(GET_N(x, 3) << 3) +                  \
(GET_N(x, 4) << 4) +                  \
(GET_N(x, 5) << 5) +                  \
(GET_N(x, 6) << 6) +                  \
(GET_N(x, 7) << 7))

/** Convert of once byte constant (simple constants) **/
#define BIN8(Y)                         \
BIT8(0x##Y##UL)

/** Convert of four byte constants **/
#define BIN32(a3, a2, a1, a0)           \
((BIN8(a0) << (0 * 8)) +               \
(BIN8(a1) << (1 * 8)) +               \
(BIN8(a2) << (2 * 8)) +               \
(BIN8(a3) << (3 * 8)))

/** Convert of two byte constants **/
#define BIN16(a1, a0)                   \
BIN32(0, 0, a1, a0)

#define BIN64(a7, a6, a5, a4, a3, a2, a1, a0)             \
((unsigned long long)BIN32(a7, a6, a5, a4)<<32) + \
BIN32(a3, a2, a1, a0)

#endif

#endif


//example:
//int main()
//{
//    unsigned long  l;
//    unsigned short s;
//    unsigned char  c;
//    unsigned __int64 ll;
//    
//    c = BIN8(10101010);
//    s = BIN16(10101010, 10101010);
//    l = BIN32(10101010, 10101010, 10101010, 10101010);
//    printf("%x %u %o\n%hx %hu %ho\n%lx %lu %lo\n", c, c, c, s, s, s, l, l, l);
//    ll= BIN64(10101010, 10101010, 10101010, 10101010, 10101010, 10101010, 10101010, 10101010);
//    printf("%llx %llu %llo\n", ll, ll, ll);
//    
//    c = BIN8(01010101);
//    s = BIN16(01010101, 01010101);
//    l = BIN32(01010101, 01010101, 01010101, 01010101);
//    printf("%x %u %o\n%hx %hu %ho\n%lx %lu %lo\n", c, c, c, s, s, s, l, l, l);
//    ll= BIN64(01010101, 01010101, 01010101, 01010101, 01010101, 01010101, 01010101, 01010101);
//    printf("%llx %llu %llo\n", ll, ll, ll);
//}


