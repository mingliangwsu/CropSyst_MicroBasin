#include "corn/image/gif/gif_lz.h"
#ifdef _Windows
#include <conio.h>
#endif

// The following are for the hash table
#ifdef __MSDOS__
#include <io.h>
#include <alloc.h>
#else
#include <sys/types.h>
#endif /* __MSDOS__ */
#include <sys/stat.h>

#define NO_SUCH_CODE      4098    /* Impossible code, to signal empty. */
//______________________________________________________________________________
LZ_decompresser::LZ_decompresser(istream &in_strm)
{
//    unsigned int *Prefix;

    nat8 CodeSize = in_strm.get();

    Buf[0] = 0;               /* Input Buffer empty. */
    BitsPerPixel = CodeSize;
    ClearCode = (1 << BitsPerPixel);
    EOFCode = ClearCode + 1;
    RunningCode = EOFCode + 1;
    RunningBits = BitsPerPixel + 1;    /* Number of bits per code. */
    MaxCode1 = 1 << RunningBits;     /* Max. code + 1. */
    StackPtr = 0;          /* No pixels on the pixel stack. */
    LastCode = NO_SUCH_CODE;
    CrntShiftState = 0;   /* No information in CrntShiftDWord. */
    CrntShiftDWord = 0;

    for (int i = 0; i < LZ_MAX_CODE; i++)
      Prefix[i] = NO_SUCH_CODE;
}
//______________________________________________________________________________
// Routine to trace the Prefixes linked list until we get a prefix which is
// not code, but a pixel value (less than ClearCode). Returns that pixel value.
// If image is defective, we might loop here forever, so we limit the loops to
// the maximum possible if image O.k. - LZ_MAX_CODE times.
int LZ_decompresser::GetPrefixChar
(unsigned int *Prefix, int Code, int ClearCode)
{
   int i = 0;

   while (Code > ClearCode && i++ <= LZ_MAX_CODE)
      Code = Prefix[Code];
   return Code;
}
//______________________________________________________________________________
// This routines read one gif data block at a time and buffers it internally
// so that the decompression routine could access it.
// The routine returns the next nat8 from its internal buffer (or read next
// block in if buffer empty) and returns GIF_OK if succesful.
int LZ_decompresser::buffered_input(istream &in_strm, nat8 *Buf,nat8 *NextByte)
{
   if (Buf[0] == 0)
   {   /* Needs to read the next buffer - this one is empty: */
      in_strm.read(&Buf[0],1);
      if (in_strm.gcount() != 1)
      {   //RGIFERROR = D_GIF_ERR_READ_FAILED;
         return GIF_ERROR;
      }
      in_strm.read(&Buf[1],Buf[0]);
      if (in_strm.gcount() != Buf[0]) //(fread(&Buf[1], 1, Buf[0], File) != Buf[0])
      {   //RGIFERROR = D_GIF_ERR_READ_FAILED;
         return GIF_ERROR;
      }
      *NextByte = Buf[1];
      Buf[1] = 2;      /* We use now the second place as last char read! */
      Buf[0]--;
   }
   else
   {   *NextByte = Buf[Buf[1]++];
      Buf[0]--;
   }
   return GIF_OK;
}
//______________________________________________________________________________
// The LZ decompression input routine:
// This routine is responsable for the decompression of the bit stream from
// 8 bits (bytes) packets, into the real codes.
// Returns GIF_OK if read succesfully.
int LZ_decompresser::decompress_input(istream &in_strm,int &Code)
{
    nat8 NextByte;
    static unsigned int CodeMasks[] = {
   0x0000, 0x0001, 0x0003, 0x0007,
   0x000f, 0x001f, 0x003f, 0x007f,
   0x00ff, 0x01ff, 0x03ff, 0x07ff,
   0x0fff
    };

    while (CrntShiftState < RunningBits)
    {   /* Needs to get more bytes from input stream for next code: */
      if (buffered_input(in_strm, Buf, &NextByte) == GIF_ERROR)
      {   return GIF_ERROR;
      }
      CrntShiftDWord |=
         ((unsigned long) NextByte) << CrntShiftState;
      CrntShiftState += 8;
    }
    Code = CrntShiftDWord & CodeMasks[RunningBits];

    CrntShiftDWord >>= RunningBits;
    CrntShiftState -= RunningBits;

//     /* If code cannt fit into RunningBits bits, must raise its size. Note */
//     /* however that codes above 4095 are used for special signaling.      */
    if (++RunningCode > MaxCode1 &&
         RunningBits < LZ_BITS)
    { MaxCode1 <<= 1;
      RunningBits++;
    }
    return GIF_OK;
}
//______________________________________________________________________________
// The LZ decompression routine:
// This version decompress the given gif file into Line of length LineLen.
// This routine can be called few times (one per scan line, for example), in
// order the complete the whole image.
int LZ_decompresser::decompress_line(istream &in_strm,nat8 Line[], int LineLen)
{
   int CrntPrefix;
//   int i = 0, j, CrntCode, EOFCode, ClearCode, CrntPrefix, LastCode, StackPtr;
//   nat8 *Stack, *Suffix;
//   unsigned int *Prefix;

   int i = 0;

   if (StackPtr != 0)
   { // Let pop the stack off before continueing to read the gif file:
      while (StackPtr != 0 && i < LineLen)
         Line[i++] = Stack[--StackPtr];
   }

   while (i < LineLen)
   { /* Decode LineLen items. */
      if (decompress_input(in_strm,CrntCode) == GIF_ERROR)
          return GIF_ERROR;

      if (CrntCode == EOFCode)
      {
         /* Note however that usually we will not be here as we will stop */
         /* decoding as soon as we got all the pixel, or EOF code will    */
         /* not be read at all, and DGifGetLine/Pixel clean everything.   */

         if (i != LineLen - 1 || PixelCount != 0)
         {   //RGIFERROR = D_GIF_ERR_EOF_TOO_SOON;
            return GIF_ERROR;
         }
         i++;
      }
      else if (CrntCode == ClearCode)
      {   /* We need to start over again: */
         int j;
         for (j = 0; j < LZ_MAX_CODE; j++)
            Prefix[j] = NO_SUCH_CODE;
         RunningCode = EOFCode + 1;
         RunningBits = BitsPerPixel + 1;
         MaxCode1 = 1 << RunningBits;
         LastCode = NO_SUCH_CODE;
      }
      else
      {   /* Its regular code - if in pixel range simply add it to output  */
         /* stream, otherwise trace to codes linked list until the prefix */
         /* is in pixel range:                    */
         if (CrntCode < ClearCode)
         {
            /* This is simple - its pixel scalar, so add it to output:   */
            Line[i++] = CrntCode;
         }
         else
         {
            /* Its a code to needed to be traced: trace the linked list  */
            /* until the prefix is a pixel, while pushing the suffix     */
            /* pixels on our stack. If we done, pop the stack in reverse */
            /* (thats what stack is good for!) order to output.        */

            if (Prefix[CrntCode] == NO_SUCH_CODE)
            {   /* Only allowed if CrntCode is exactly the running code: */
               /* In that case CrntCode = XXXCode, CrntCode or the        */
               /* prefix code is last code and the suffix char is        */
               /* exactly the prefix of last code!              */
               if (CrntCode == RunningCode - 2)
               {   CrntPrefix = LastCode;
                  Suffix[RunningCode - 2] = Stack[StackPtr++]
                     = GetPrefixChar(Prefix,LastCode, ClearCode);
               }
               else
               {   //RGIFERROR = D_GIF_ERR_IMAGE_DEFECT;
                  return GIF_ERROR;
               }
            }
            else
               CrntPrefix = CrntCode;

            /* Now (if image is O.K.) we should not get and NO_SUCH_CODE */
            /* During the trace. As we might loop forever, in case of    */
            /* defective image, we count the number of loops we trace    */
            /* and stop if we got LZ_MAX_CODE. obviously we can not      */
            /* loop more than that.                    */
            int j = 0;
            while (j++ <= LZ_MAX_CODE &&
                   CrntPrefix > ClearCode &&
                   CrntPrefix <= LZ_MAX_CODE)
            {   Stack[StackPtr++] =   Suffix[CrntPrefix];
               CrntPrefix = Prefix[CrntPrefix];
            }

            if (j >= LZ_MAX_CODE || CrntPrefix > LZ_MAX_CODE)
            {   //RGIFERROR = D_GIF_ERR_IMAGE_DEFECT;
               return GIF_ERROR;
            }
            /* Push the last character on stack: */
            Stack[StackPtr++] = CrntPrefix;

            /* Now lets pop all the stack into output: */
            while (StackPtr != 0 && i < LineLen)
               Line[i++] = Stack[--StackPtr];
         }
         if (LastCode != NO_SUCH_CODE)
         {   Prefix[RunningCode - 2] = LastCode;

            if (CrntCode == RunningCode - 2)
            {   /* Only allowed if CrntCode is exactly the running code: */
               /* In that case CrntCode = XXXCode, CrntCode or the        */
               /* prefix code is last code and the suffix char is        */
               /* exactly the prefix of last code!              */
               Suffix[RunningCode - 2] =
                  GetPrefixChar(Prefix, LastCode, ClearCode);
            }
            else
            {   Suffix[RunningCode - 2] =
                  GetPrefixChar(Prefix, CrntCode, ClearCode);
            }
         }
         LastCode = CrntCode;
      }
   }

   LastCode = LastCode;
   StackPtr = StackPtr;

   return GIF_OK;
}
//______________________________________________________________________________

#define FLUSH_OUTPUT      4096   /* Impossible code, to signal flush. */
#define FIRST_CODE      4097    /* Impossible code, to signal first. */

LZ_compresser::LZ_compresser(ostream &out_strm,int bits_per_pixel,long i_PixelCount)
: PixelCount(i_PixelCount)
{
   /*180214moved to caller
   nat8 code =(bits_per_pixel < 2) ? 2 : bits_per_pixel;
   out_strm.put(code);   // min code size
   */

   Buf[0] = 0;           /* Nothing was output yet. */
   BitsPerPixel = bits_per_pixel;
   ClearCode = (1 << BitsPerPixel);
   EOFCode = ClearCode + 1;
   RunningCode = EOFCode + 1;
   RunningBits = BitsPerPixel + 1;    /* Number of bits per code. */
   MaxCode1 = 1 << RunningBits;      /* Max. code + 1. */
   CrntCode = FIRST_CODE;      /* Signal that this is first one! */
   CrntShiftState = 0;      /* No information in CrntShiftDWord. */
   CrntShiftDWord = 0;

   /* Clear hash table and send Clear to make sure the decoder do the same. */
   hash_table.clear();
   if (compress_output(out_strm,ClearCode) == GIF_ERROR);
}
//______________________________________________________________________________
// The LZ compression routine:
// This version compress the given buffer Line of length LineLen.
// This routine can be called few times (one per scan line, for example), in
// order the complete the whole image.
#define ZL_MAX_CODE   4095
// Biggest code possible in 12 bits.
int LZ_compresser::compress_line(ostream &out_strm, const nat8 *Line, int LineLen)
{
   if (!Line) return GIF_ERROR;
  // int i = 0,
  unsigned int local_CrntCode;
  int NewCode;
  unsigned long NewKey;
  //  GifPixelType Pixel;
  //  GifHashTableType *HashTable;

  nat8 Pixel;

  int i = 0;
  if (CrntCode == FIRST_CODE)        /* Its first time! */
      local_CrntCode = Line[i++];
  else
      local_CrntCode = CrntCode;     /* Get last code in compression. */

  while (i < LineLen)
  {   /* Decode LineLen items. */
      Pixel = Line[i++];            /* Get next pixel from stream. */
      /* Form a new unique key to search hash table for the code combines  */
      /* CrntCode as Prefix string with Pixel as postfix char.        */
      NewKey = (((unsigned long) local_CrntCode) << 8) + Pixel;
      if ((NewCode = hash_table.exists(NewKey)) >= 0)
      {
         /* This Key is already there, or the string is old one, so        */
         /* simple take new code as our CrntCode:              */
         local_CrntCode = NewCode;
      }
      else
      {  /* Put it in hash table, output the prefix code, and make our    */
         /* CrntCode equal to Pixel.                    */
         if (compress_output(out_strm, local_CrntCode) == GIF_ERROR)
            return GIF_ERROR; //RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
         local_CrntCode = Pixel;

         /* If however the HashTable if full, we send a clear first and   */
         /* Clear the hash table.                    */
         if (RunningCode >= ZL_MAX_CODE)
         { /* Time to do some clearance: */
            if (compress_output(out_strm,ClearCode) == GIF_ERROR)
               return GIF_ERROR;  //RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
            RunningCode = EOFCode + 1;
            RunningBits = BitsPerPixel + 1;
            MaxCode1 = 1 << RunningBits;
            hash_table.clear();
         }
         else
         { /* Put this unique key with its relative Code in hash table: */
            hash_table.insert(NewKey, RunningCode++);
         }
      }
  }
  /* Preserve the current state of the compression algorithm: */
  CrntCode = local_CrntCode;

  if (PixelCount == 0)
  {
      /* We are done - output last Code and flush output buffers: */
      if (compress_output(out_strm, local_CrntCode) == GIF_ERROR)
         return GIF_ERROR; // RGIFERROR = E_GIF_ERR_DISK_IS_FULL;

      if (compress_output(out_strm, EOFCode) == GIF_ERROR)
         return GIF_ERROR; // RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
      if (compress_output(out_strm,FLUSH_OUTPUT) == GIF_ERROR)
         return GIF_ERROR; //  RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
  }
  return GIF_OK;
}
//______________________________________________________________________________
// The LZ compression output routine:
// This routine is responsable for the compression of the bit stream into
// 8 bits (bytes) packets.
// Returns GIF_OK if written succesfully.
int LZ_compresser::compress_output(ostream &out_strm,int Code)
{
   int retval = GIF_OK;

   if (Code == FLUSH_OUTPUT)
   {
     while (CrntShiftState > 0)
     { /* Get Rid of what is left in DWord, and flush it. */
       if (buffered_output(out_strm,Buf,CrntShiftDWord & 0xff) == GIF_ERROR)
          retval = GIF_ERROR;
       CrntShiftDWord >>= 8;
       CrntShiftState -= 8;
      }
      CrntShiftState = 0;            /* For next time. */
      if (buffered_output(out_strm, Buf, FLUSH_OUTPUT) == GIF_ERROR)
         retval = GIF_ERROR;
   }
   else
   {  CrntShiftDWord |= ((long) Code) << CrntShiftState;
         CrntShiftState += RunningBits;
         while (CrntShiftState >= 8)
         {  /* Dump out full bytes: */
            if (buffered_output(out_strm, Buf, CrntShiftDWord & 0xff) == GIF_ERROR)
               retval = GIF_ERROR;
            CrntShiftDWord >>= 8;
            CrntShiftState -= 8;
         }
   }

   // If code cannt fit into RunningBits bits, must raise its size. Note
   // however that codes above 4095 are used for special signaling.
   if (RunningCode >= MaxCode1 && Code <= 4095)
     MaxCode1 = 1 << ++RunningBits;

   return retval;
}
//______________________________________________________________________________
// This routines buffers the given characters until 255 characters are ready
// to be output. If Code is equal to -1 the buffer is flushed (EOF).
// The buffer is Dumped with first nat8 byte as its size, as GIF format requires.
// Returns GIF_OK if written succesfully.
int LZ_compresser::buffered_output(ostream &out_strm, nat8 *Buf, int c)
{
   if (c == FLUSH_OUTPUT)
   {  // Flush everything out.
      if (Buf[0] != 0)
      {  out_strm.write(Buf, Buf[0]+1);
      }
      // Mark end of compressed data, by an empty block (see GIF doc):
      out_strm.put((nat8)0);
   }
   else
   {
      if (Buf[0] == 255)
      { // Dump out this buffer - it is full:
         out_strm.write(Buf, Buf[0] + 1);
         Buf[0] = 0;
      }
      Buf[++Buf[0]] = c;
   }
   return GIF_OK;
}
/* #define  DEBUG_HIT_RATE    Debug number of misses per hash Insert/Exists. */
#ifdef   DEBUG_HIT_RATE
static long NumberOfTests = 0,
       NumberOfMisses = 0;
#endif
//______________________________________________________________________________
// Initialize HashTable - allocate the memory needed and clear it.
GIF_hash_table::GIF_hash_table()
{
   clear();
}
//______________________________________________________________________________
// clear the HashTable to an empty state.
// This part is a little machine depended. Use the commented part otherwise.
void GIF_hash_table::clear()
{
   memset(HTable, 0xFF, HT_SIZE * sizeof(long));
}
//______________________________________________________________________________
// Routine to insert a new Item into the HashTable. The data is assumed to be
// new one.
void GIF_hash_table::insert(unsigned long Key, int Code)
{
    int HKey = KeyItem(Key);

#ifdef DEBUG_HIT_RATE
   NumberOfTests++;
   NumberOfMisses++;
#endif /* DEBUG_HIT_RATE */

    while (HT_GET_KEY(HTable[HKey]) != 0xFFFFFL)
    {
#ifdef DEBUG_HIT_RATE
       NumberOfMisses++;
#endif /* DEBUG_HIT_RATE */
      HKey = (HKey + 1) & HT_KEY_MASK;
    }
    HTable[HKey] = HT_PUT_KEY(Key) | HT_PUT_CODE(Code);
}
//______________________________________________________________________________
// Routine to test if given Key exists in HashTable and if so returns its code
// Returns the Code if key was found, -1 if not.
int GIF_hash_table::exists(unsigned long Key)
{
   int HKey = KeyItem(Key);
   unsigned long HTKey;
#ifdef DEBUG_HIT_RATE
   NumberOfTests++;
   NumberOfMisses++;
#endif /* DEBUG_HIT_RATE */

   while
    ((HTKey = HT_GET_KEY(HTable[HKey])) != 0xFFFFFL)
    //&& (HKey < (HT_SIZE-2)))
   {
      #ifdef _Windows
      // Allow multitasking
       kbhit();
      #endif
#ifdef DEBUG_HIT_RATE
       NumberOfMisses++;
#endif /* DEBUG_HIT_RATE */
      if (Key == HTKey)
         return HT_GET_CODE(HTable[HKey]);
      HKey = (HKey + 1) & HT_KEY_MASK;
   }

   return -1;
}
//______________________________________________________________________________
// Routine to generate an HKey for the hashtable out of the given unique key.
// The given Key is assumed to be 20 bits as follows: lower 8 bits are the
// new postfix character, while the upper 12 bits are the prefix code.
// Because the average hit ratio is only 2 (2 hash references per entry),
// evaluating more complex keys (such as twin prime keys) does not worth it!
int GIF_hash_table::KeyItem(unsigned long Item)
{
    return ((Item >> 12) ^ Item) & HT_KEY_MASK;
}
//______________________________________________________________________________
#ifdef   DEBUG_HIT_RATE
// Debugging routine to print the hit ratio - number of times the hash table
// was tested per operation. This routine was used to test the KeyItem routine
void GIF_hash_table::PrintHitRatio(void)
{
   printf("Hash Table Hit Ratio is %ld/%ld = %ld%%.\n",
   NumberOfMisses, NumberOfTests,
   NumberOfMisses * 100 / NumberOfTests);
}
#endif   /* DEBUG_HIT_RATE */
//______________________________________________________________________________

