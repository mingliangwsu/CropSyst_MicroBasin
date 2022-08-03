#ifndef GIF_LZH
#define GIF_LZH
#include <corn/std/std_iostream.h>
#include <corn/image/gif/common.h>

#define LZ_MAX_CODE   4095      /* Biggest code possible in 12 bits. */
#define LZ_BITS      12
//______________________________________________________________________________
class LZ_decompresser
{
 int FileState,
   FileHandle,    /* Where all this data goes to! */
   BitsPerPixel,  /* Bits per pixel (Codes uses at list this + 1). */
   ClearCode,     /* The CLEAR LZ code. */
   EOFCode,       /* The EOF LZ code. */
   RunningCode,   /* The next code algorithm can generate. */
   RunningBits,   /* The number of bits required to represent RunningCode. */
   MaxCode1,      /* 1 bigger than max. possible code, in RunningBits bits. */
   LastCode,      /* The code before the current code. */
   CrntCode,      /* Current algorithm code. */
   StackPtr,      /* For character stack (see below). */
   CrntShiftState;              /* Number of bits in CrntShiftDWord. */
    unsigned long CrntShiftDWord,     /* For bytes decomposition into codes. */
        PixelCount;             /* Number of pixels in image. */
//    FILE *File;                    /* File as stream. */
    nat8 Buf[256];          /* Compressed input is buffered here. */
    nat8 Stack[LZ_MAX_CODE];    /* Decoded pixels are stacked here. */
    nat8 Suffix[LZ_MAX_CODE+1];          /* So we can trace the codes. */
    unsigned int Prefix[LZ_MAX_CODE+1];
public:
   LZ_decompresser(istream &in_strm);

   int buffered_input(istream &in_strm, nat8 *Buf,nat8 *NextByte);

   int decompress_input(istream &in_strm,int &Code);

   int decompress_line(istream &in_strm,nat8 Line[], int LineLen);
   int GetPrefixChar(unsigned int *Prefix, int Code, int ClearCode);

};
//______________________________________________________________________________
#define HT_SIZE         8192      /* 12bits = 4096 or twice as big! */
#define HT_KEY_MASK      0x1FFF   /* 13bits keys */
#define HT_KEY_NUM_BITS      13      /* 13bits keys */
#define HT_MAX_KEY      8191   /* 13bits - 1, maximal code possible */
#define HT_MAX_CODE      4095   /* Biggest code possible in 12 bits. */

/* The 32 bits of the long are divided into two parts for the key & code:   */
/* 1. The code is 12 bits as our compression algorithm is limited to 12bits */
/* 2. The key is 12 bits Prefix code + 8 bit new char or 20 bits.       */
#define HT_GET_KEY(l)   (l >> 12)
#define HT_GET_CODE(l)   (l & 0x0FFF)
#define HT_PUT_KEY(l)   (l << 12)
#define HT_PUT_CODE(l)   (l & 0x0FFF)
//______________________________________________________________________________
class GIF_hash_table
{
    unsigned long HTable[HT_SIZE];

public:
   GIF_hash_table();

   void clear();
   //clear the hash table to an empty state.

   void insert(unsigned long Key, int Code);
   //insert one item into data structure.

   int exists(unsigned long Key);
   //test if item exists in data structure.
   int KeyItem(unsigned long Item);
};
//______________________________________________________________________________
class LZ_compresser
{
   nat8 Buf[256];      /* Compressed input is buffered here. */
   int BitsPerPixel;   /* Bits per pixel (Codes uses at list this + 1). */
   int ClearCode;      /* The CLEAR LZ code. */
   int EOFCode;      /* The EOF LZ code. */
   int RunningCode;   /* The next code algorithm can generate. */
   int RunningBits;  /* The number of bits required to represent RunningCode. */
   int MaxCode1;     /* 1 bigger than max. possible code, in RunningBits bits. */
   int CrntCode;      /* Current algorithm code. */
   int CrntShiftState; /* Number of bits in CrntShiftDWord. */
   unsigned long CrntShiftDWord;     /* For bytes decomposition into codes. */
public:
   long PixelCount;
      // The number of pixels remaining to be writting.
      // (initially widthxheight
   GIF_hash_table hash_table;
public:
   LZ_compresser(std::ostream &out_strm,int bits_per_pixel,long PixelCount);
   int compress_line(std::ostream &out_strm, const nat8 *Line, int LineLen);
   int buffered_output(std::ostream &out_strm, nat8 *Buf, int c);
   int compress_output(std::ostream &out_strm,int Code);

};
//______________________________________________________________________________
#endif
