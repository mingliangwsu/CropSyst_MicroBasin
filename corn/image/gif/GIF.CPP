#error this file obsolete, the classes have been put in separate units

#include <conio.h> // for easywin multitasking
#include <fstream>
#include <stdio.h>
#include <iostream>
// #include "corn/std/std_fstream.h'
// #include "corn/corn.h"
#include "corn/image/gif/gif.h"
#include "corn/primitive.h"
#define byte nat8
namespace CORN {
//______________________________________________________________________________
unsigned int GIF_read_word(FILE *infile)
{
  unsigned char buffer[3];
  if (fread(&buffer, 1, 2, infile) != 2)
     std::cerr << "read word error" << std::endl;
  unsigned int result = buffer[1];
  result <<= 8;
  result |= buffer[0];
  return result;
}
//______________________________________________________________________________
void GIF_write_word(FILE *outfile, unsigned int word)
{
    byte upper = (word >> 8) & 0xff;
    byte lower = word & 0xFF;
    fputc(lower,outfile);
    fputc(upper,outfile);
}
//______________________________________________________________________________
/*moved to color_map.h
color_map::color_map(byte i_color_resolution,byte i_bits_per_pixel)
:color_resolution(i_color_resolution)
,bits_per_pixel(i_bits_per_pixel)
,num_colors(1 << i_bits_per_pixel)
{
}
//______________________________________________________________________________
color_map::color_map(Color_ramp &color_ramp)
:color_resolution(4)  // I think
,bits_per_pixel(8)
,num_colors(1 << 8)
{
   int colors_in_ramp = color_ramp.get_colors();
   float color_ramp_step = // float because
   (colors_in_ramp > num_colors)
   ? colors_in_ramp / num_colors
   : 1;
   red[0]   = 0;  // Default background color is black.
   green[0] = 0;
   blue[0]  = 0;
   float color_ramp_index = 1;
   for (int color_map_index = 1 // Leave index 0 for background color
       ;color_map_index < num_colors
       ;color_map_index++)
   {
      red[color_map_index] = color_ramp.get_color((uint16)color_ramp_index).Red();
      green[color_map_index] = color_ramp.get_color((uint16)color_ramp_index).Green();
      blue[color_map_index] = color_ramp.get_color((uint16)color_ramp_index).Blue();
      color_ramp_index += color_ramp_step;
   }
}
*/
//______________________________________________________________________________
/*moved to color_map.cpp
void color_map::read(FILE *infile)
{
   for (int i = 0; i < num_colors; i++)
   { red[i]   = fgetc(infile);
     green[i] = fgetc(infile);
     blue[i]  = fgetc(infile);
   }
}
//______________________________________________________________________________
void color_map::write(FILE *outfile)
{
   for (int i = 0; i < num_colors; i++)
   { fputc(red[i],outfile);
     fputc(green[i] ,outfile);
     fputc(blue[i],outfile);
   }
}
//______________________________________________________________________________
int color_map::find(byte r, byte g, byte b)
{
   int i;
//   int min_dr = 0xff;
//   int min_dg = 0xff;
//   int min_db = 0xff;
   int min_avg = 0xff;
   int index = 0;
   for (i = 0; i < num_colors; i++)
   {
     int dr = abs(r - red[i]);
     int dg = abs(g - green[i]);
     int db = abs(b - blue[i]);
     int avg = (dr + dg + db) /3;
     if (avg < min_avg)
     {
        min_avg = avg;
        index = i;
     }
   }
   return index;
}
//______________________________________________________________________________
void color_map::union_colors(color_map *color_map_2,byte recolor1[],byte recolor2[])
{
  int i;

  // At this time I am not modifying the base image's color map
  for (i = 0; i < num_colors; i++)
  {
     recolor1[i] = i;
     recolor2[i] = i;
  }


  if ((num_colors + color_map_2->num_colors) <= 256)
  {
     // Add the second color map to the end of the color map.
     for (i = 0; i < color_map_2->num_colors; i++)
     { recolor2[i] = num_colors + i;
       color_map_2->red[i+num_colors] = color_map_2->red[i];
       color_map_2->green[i+num_colors] = color_map_2->green[i];
       color_map_2->blue[i+num_colors] = color_map_2->blue[i];
       red[i+num_colors] = color_map_2->red[i];
       green[i+num_colors] = color_map_2->green[i];
       blue[i+num_colors] = color_map_2->blue[i];
     }
     num_colors = num_colors + color_map_2->num_colors;
  }
  else
  { int colors_reused = 0;
    for (i = 0; i < color_map_2->num_colors; i++)
    { recolor2[i] = 255;
      int min_dr = 256;
      int min_dg = 256;
      int min_db = 256;
      for (int j = 0; j < num_colors; j++)
      { int dr = abs(red[j]   - color_map_2->red[i]);
        int dg = abs(green[j] - color_map_2->green[i]);
        int db = abs(blue[j]  - color_map_2->blue[i]);

#define SAME_COLOR_RANGE 10
        if (dr < min_dr && dg < min_dg && db < min_db)
        {
           // If the second image color is similar to this first color
           // then substitute the color
           recolor2[i] = j;
           colors_reused += 1;
           min_dr = dr;
           min_dg = dg;
           min_db = db;
        }
//        else // can't permit more than 255 color.
//           recolor2[i] = (num_colors < 256) ? num_colors++ : 255;
      }
    }
//    cout << "Colors reused:" << colors_reused << endl; for debugging
  }
}
//______________________________________________________________________________
void color_map::copy_from(color_map &map)
{
   int i;
   for (i = 0; i < 256; i++)
   {
     red[i] = map.red[i];
     green[i] = map.green[i];
     blue[i] = map.blue[i];
   }

   color_resolution = map.color_resolution;
   bits_per_pixel = map.bits_per_pixel;

   num_colors = map.num_colors;
   sorted = map.sorted;
}
//______________________________________________________________________________
*/
/*moved to gif_lz
#define NO_SUCH_CODE      4098
//Impossible code, to signal empty.

LZ_decompresser::LZ_decompresser(FILE *in_file)
{
//    unsigned int *Prefix;

    byte CodeSize = fgetc(in_file);

    Buf[0] = 0;               //Input Buffer empty.
    BitsPerPixel = CodeSize;
    ClearCode = (1 << BitsPerPixel);
    EOFCode = ClearCode + 1;
    RunningCode = EOFCode + 1;
    RunningBits = BitsPerPixel + 1;    //Number of bits per code.
    MaxCode1 = 1 << RunningBits;     // Max. code + 1.
    StackPtr = 0;          // No pixels on the pixel stack.
    LastCode = NO_SUCH_CODE;
    CrntShiftState = 0;   // No information in CrntShiftDWord.
    CrntShiftDWord = 0;

    for (int i = 0; i < LZ_MAX_CODE; i++)
      Prefix[i] = NO_SUCH_CODE;
}
//______________________________________________________________________________
// ******************************************************************************
// Routine to trace the Prefixes linked list until we get a prefix which is    *
// not code, but a pixel value (less than ClearCode). Returns that pixel value.*
// If image is defective, we might loop here forever, so we limit the loops to *
// the maximum possible if image O.k. - LZ_MAX_CODE times.            *
// ******************************************************************************

int LZ_decompresser::GetPrefixChar
(unsigned int *Prefix, int Code, int ClearCode)
{
   int i = 0;

   while (Code > ClearCode && i++ <= LZ_MAX_CODE)
      Code = Prefix[Code];
   return Code;
}
//______________________________________________________________________________
// ******************************************************************************
// *   This routines read one gif data block at a time and buffers it internally *
// * so that the decompression routine could access it.               *
// *   The routine returns the next byte from its internal buffer (or read next  *
// * block in if buffer empty) and returns GIF_OK if succesful.            *
// ******************************************************************************
int LZ_decompresser::buffered_input(FILE *File, byte *Buf,byte *NextByte)
{
   if (Buf[0] == 0)
   {   //  Needs to read the next buffer - this one is empty:
      if (fread(Buf, 1, 1, File) != 1)
      {   //RGIFERROR = D_GIF_ERR_READ_FAILED;
         return GIF_ERROR;
      }
      if (fread(&Buf[1], 1, Buf[0], File) != Buf[0])
      {   //RGIFERROR = D_GIF_ERR_READ_FAILED;
         return GIF_ERROR;
      }
      *NextByte = Buf[1];
      Buf[1] = 2;      // We use now the second place as last char read!
      Buf[0]--;
   }
   else
   {   *NextByte = Buf[Buf[1]++];
      Buf[0]--;
   }
   return GIF_OK;
}
//______________________________________________________________________________
// ******************************************************************************
// *   The LZ decompression input routine:                     *
// *   This routine is responsable for the decompression of the bit stream from  *
// * 8 bits (bytes) packets, into the real codes.                  *
// *   Returns GIF_OK if read succesfully.                     *
// ******************************************************************************
int LZ_decompresser::decompress_input(FILE *File,int &Code)
{
    byte NextByte;
    static unsigned int CodeMasks[] = {
   0x0000, 0x0001, 0x0003, 0x0007,
   0x000f, 0x001f, 0x003f, 0x007f,
   0x00ff, 0x01ff, 0x03ff, 0x07ff,
   0x0fff
    }

    while (CrntShiftState < RunningBits)
    {   // Needs to get more bytes from input stream for next code:
      if (buffered_input(File, Buf, &NextByte) == GIF_ERROR)
      {   return GIF_ERROR;
      }
      CrntShiftDWord |=
         ((unsigned long) NextByte) << CrntShiftState;
      CrntShiftState += 8;
    }
    Code = CrntShiftDWord & CodeMasks[RunningBits];

    CrntShiftDWord >>= RunningBits;
    CrntShiftState -= RunningBits;

//      If code cannt fit into RunningBits bits, must raise its size. Note
//      however that codes above 4095 are used for special signaling.
    if (++RunningCode > MaxCode1 &&
         RunningBits < LZ_BITS)
    { MaxCode1 <<= 1;
      RunningBits++;
    }
    return GIF_OK;
}
//______________________________________________________________________________
// ******************************************************************************
// *   The LZ decompression routine:                     *
// *   This version decompress the given gif file into Line of length LineLen.   *
// *   This routine can be called few times (one per scan line, for example), in *
// * order the complete the whole image.                     *
// ******************************************************************************
int LZ_decompresser::decompress_line(FILE *in_file,byte Line[], int LineLen)
{
   int CrntPrefix;
//   int i = 0, j, CrntCode, EOFCode, ClearCode, CrntPrefix, LastCode, StackPtr;
//   byte *Stack, *Suffix;
//   unsigned int *Prefix;

   int i = 0;

   if (StackPtr != 0)
   { // Let pop the stack off before continueing to read the gif file:
      while (StackPtr != 0 && i < LineLen)
         Line[i++] = Stack[--StackPtr];
   }

   while (i < LineLen)
   { //Decode LineLen items.
      if (decompress_input(in_file,CrntCode) == GIF_ERROR)
          return GIF_ERROR;

      if (CrntCode == EOFCode)
      {
         /* Note however that usually we will not be here as we will stop
         /* decoding as soon as we got all the pixel, or EOF code will
         /* not be read at all, and DGifGetLine/Pixel clean everything.

         if (i != LineLen - 1 || PixelCount != 0)
         {   //RGIFERROR = D_GIF_ERR_EOF_TOO_SOON;
            return GIF_ERROR;
         }
         i++;
      }
      else if (CrntCode == ClearCode)
      {   /* We need to start over again:
         int j;
         for (j = 0; j < LZ_MAX_CODE; j++)
            Prefix[j] = NO_SUCH_CODE;
         RunningCode = EOFCode + 1;
         RunningBits = BitsPerPixel + 1;
         MaxCode1 = 1 << RunningBits;
         LastCode = NO_SUCH_CODE;
      }
      else
      {   /* Its regular code - if in pixel range simply add it to output
         /* stream, otherwise trace to codes linked list until the prefix
         /* is in pixel range:
         if (CrntCode < ClearCode)
         {
            /* This is simple - its pixel scalar, so add it to output:
            Line[i++] = CrntCode;
         }
         else
         {
            /* Its a code to needed to be traced: trace the linked list
            /* until the prefix is a pixel, while pushing the suffix
            /* pixels on our stack. If we done, pop the stack in reverse
            /* (thats what stack is good for!) order to output.

            if (Prefix[CrntCode] == NO_SUCH_CODE)
            {   /* Only allowed if CrntCode is exactly the running code:
               /* In that case CrntCode = XXXCode, CrntCode or the
               /* prefix code is last code and the suffix char is
               /* exactly the prefix of last code!
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

            /* Now (if image is O.K.) we should not get and NO_SUCH_CODE
            /* During the trace. As we might loop forever, in case of
            /* defective image, we count the number of loops we trace
            /* and stop if we got LZ_MAX_CODE. obviously we can not
            /* loop more than that.
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
            /* Push the last character on stack:
            Stack[StackPtr++] = CrntPrefix;

            /* Now lets pop all the stack into output:
            while (StackPtr != 0 && i < LineLen)
               Line[i++] = Stack[--StackPtr];
         }
         if (LastCode != NO_SUCH_CODE)
         {   Prefix[RunningCode - 2] = LastCode;

            if (CrntCode == RunningCode - 2)
            {   /* Only allowed if CrntCode is exactly the running code:
               /* In that case CrntCode = XXXCode, CrntCode or the
               /* prefix code is last code and the suffix char is
               /* exactly the prefix of last code!
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
#define FLUSH_OUTPUT      4096   /* Impossible code, to signal flush.
#define FIRST_CODE      4097    /* Impossible code, to signal first.
//______________________________________________________________________________
LZ_compresser::LZ_compresser(FILE *out_file,int bits_per_pixel,long i_PixelCount)
: PixelCount(i_PixelCount)
{
   byte code =(bits_per_pixel < 2) ? 2 : bits_per_pixel;
   fputc(code,out_file);

   Buf[0] = 0;           /* Nothing was output yet.
   BitsPerPixel = bits_per_pixel;
   ClearCode = (1 << BitsPerPixel);
   EOFCode = ClearCode + 1;
   RunningCode = EOFCode + 1;
   RunningBits = BitsPerPixel + 1;    /* Number of bits per code.
   MaxCode1 = 1 << RunningBits;      /* Max. code + 1.
   CrntCode = FIRST_CODE;      /* Signal that this is first one!
   CrntShiftState = 0;      /* No information in CrntShiftDWord.
   CrntShiftDWord = 0;

   /* Clear hash table and send Clear to make sure the decoder do the same.
   hash_table.clear();
   if (compress_output(out_file,ClearCode) == GIF_ERROR);
}
//______________________________________________________________________________
// /******************************************************************************
// *   The LZ compression routine:                        *
// *   This version compress the given buffer Line of length LineLen.         *
// *   This routine can be called few times (one per scan line, for example), in *
// * order the complete the whole image.                     *
// *****************************************************************************
#define ZL_MAX_CODE   4095      /* Biggest code possible in 12 bits.
int LZ_compresser::compress_line(FILE *out_file, byte *Line, int LineLen)
{
  // int i = 0,
  unsigned int local_CrntCode;
  int NewCode;
  unsigned long NewKey;
  //  GifPixelType Pixel;
  //  GifHashTableType *HashTable;

  byte Pixel;

  int i = 0;
  if (CrntCode == FIRST_CODE)        /* Its first time!
      local_CrntCode = Line[i++];
  else
      local_CrntCode = CrntCode;     /* Get last code in compression.

  while (i < LineLen)
  {   /* Decode LineLen items.
      Pixel = Line[i++];            /* Get next pixel from stream.
      /* Form a new unique key to search hash table for the code combines
      /* CrntCode as Prefix string with Pixel as postfix char.
      NewKey = (((unsigned long) local_CrntCode) << 8) + Pixel;
      if ((NewCode = hash_table.exists(NewKey)) >= 0)
      {
         /* This Key is already there, or the string is old one, so
         /* simple take new code as our CrntCode:
         local_CrntCode = NewCode;
      }
      else
      {  /* Put it in hash table, output the prefix code, and make our
         /* CrntCode equal to Pixel.
         if (compress_output(out_file, local_CrntCode) == GIF_ERROR)
            return GIF_ERROR; //RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
         local_CrntCode = Pixel;

         /* If however the HashTable if full, we send a clear first and
         /* Clear the hash table.
         if (RunningCode >= ZL_MAX_CODE)
         { /* Time to do some clearance:
            if (compress_output(out_file,ClearCode) == GIF_ERROR)
               return GIF_ERROR;  //RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
            RunningCode = EOFCode + 1;
            RunningBits = BitsPerPixel + 1;
            MaxCode1 = 1 << RunningBits;
            hash_table.clear();
         }
         else
         { /* Put this unique key with its relative Code in hash table:
            hash_table.insert(NewKey, RunningCode++);
         }
      }
  }
  /* Preserve the current state of the compression algorithm:
  CrntCode = local_CrntCode;

  if (PixelCount == 0)
  {
      /* We are done - output last Code and flush output buffers:
      if (compress_output(out_file, local_CrntCode) == GIF_ERROR)
         return GIF_ERROR; // RGIFERROR = E_GIF_ERR_DISK_IS_FULL;

      if (compress_output(out_file, EOFCode) == GIF_ERROR)
         return GIF_ERROR; // RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
      if (compress_output(out_file,FLUSH_OUTPUT) == GIF_ERROR)
         return GIF_ERROR; //  RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
  }
  return GIF_OK;
}
//______________________________________________________________________________
// /******************************************************************************
// *   The LZ compression output routine:                     *
// *   This routine is responsable for the compression of the bit stream into    *
// * 8 bits (bytes) packets.                        *
// *   Returns GIF_OK if written succesfully.                  *
// *****************************************************************************
int LZ_compresser::compress_output(FILE *out_file,int Code)
{
   int retval = GIF_OK;

   if (Code == FLUSH_OUTPUT)
   {
     while (CrntShiftState > 0)
     { /* Get Rid of what is left in DWord, and flush it.
       if (buffered_output(out_file,Buf,CrntShiftDWord & 0xff) == GIF_ERROR)
          retval = GIF_ERROR;
       CrntShiftDWord >>= 8;
       CrntShiftState -= 8;
      }
      CrntShiftState = 0;            /* For next time.
      if (buffered_output(out_file, Buf, FLUSH_OUTPUT) == GIF_ERROR)
         retval = GIF_ERROR;
   }
   else
   {  CrntShiftDWord |= ((long) Code) << CrntShiftState;
         CrntShiftState += RunningBits;
         while (CrntShiftState >= 8)
         {  /* Dump out full bytes:
            if (buffered_output(out_file, Buf, CrntShiftDWord & 0xff) == GIF_ERROR)
               retval = GIF_ERROR;
            CrntShiftDWord >>= 8;
            CrntShiftState -= 8;
         }
   }

   /* If code cannt fit into RunningBits bits, must raise its size. Note
   /* however that codes above 4095 are used for special signaling.
   if (RunningCode >= MaxCode1 && Code <= 4095)
     MaxCode1 = 1 << ++RunningBits;

   return retval;
}
//______________________________________________________________________________
// /******************************************************************************
// *   This routines buffers the given characters until 255 characters are ready *
// * to be output. If Code is equal to -1 the buffer is flushed (EOF).         *
// *   The buffer is Dumped with first byte as its size, as GIF format requires. *
// *   Returns GIF_OK if written succesfully.                  *
// *****************************************************************************
int LZ_compresser::buffered_output(FILE *out_file, byte *Buf, int c)
{
   if (c == FLUSH_OUTPUT)
   {  // Flush everything out.
      if (Buf[0] != 0 && fwrite(Buf, 1, Buf[0]+1, out_file) != Buf[0] + 1)
         return GIF_ERROR;
      // Mark end of compressed data, by an empty block (see GIF doc):
      fputc(0,out_file);
   }
   else
   {
      if (Buf[0] == 255)
      { // Dump out this buffer - it is full:
         if (fwrite(Buf, 1, Buf[0] + 1, out_file) != Buf[0] + 1)
            return GIF_ERROR;
         Buf[0] = 0;
      }
      Buf[++Buf[0]] = c;
   }
   return GIF_OK;
}
//______________________________________________________________________________
*/
/* moved to control
void GIF_control_extension::read(FILE *in_file)
{
  // extension introducer and graphic control label
  // will already have been read in order to determine
  // that this is a graphic control extension.
  fgetc(in_file);  // block size is not used, should be 4

  byte packed = fgetc(in_file);
  disposal_method = (packed & 0x1C) >> 2;
  user_input = (packed & 0x02) != 0;
  use_transparent_color = packed & 0x01;

  delay_time = GIF_read_word(in_file);
  transparent_color = fgetc(in_file);
  fgetc(in_file);  // block terminator, should be 0

  enabled = true;
}
//______________________________________________________________________________
void GIF_control_extension::write(FILE *out_file)
{
  fputc(GIF_extension_introducer,out_file);
  fputc(GIF_graphic_control_extension,out_file);
  fputc(4,out_file); // size of the control block
  byte packed
  = ((byte)disposal_method << 2)
  | (user_input ? 0x02 : 0x00)
  | (use_transparent_color ? 0x01 : 0x00);

  fputc(packed,out_file);
  GIF_write_word(out_file,delay_time);
  fputc(transparent_color,out_file);
  fputc(0,out_file);
}
*/
//______________________________________________________________________________
/*moved to GIF_image
GIF_image::GIF_image(FILE *in_file,color_map *i_global_color_table
  , GIF_control_extension i_graphic_control)
:left(0)
,top(0)
,width(0)
,height(0)
,local_color_table(0)
,global_color_table(i_global_color_table)
,interlaced(0)
,matrix(0)
,modified(0)
,graphic_control(i_graphic_control)
{

  read(in_file);
  // color_table = must follow read
  color_table = local_color_table ? local_color_table : global_color_table;
}

GIF_image::GIF_image(unsigned int i_width, unsigned int i_height,
         unsigned int i_left ,unsigned int i_top )
   :CORN_container_item()
   ,width(i_width)
   ,height(i_height)
   ,left(i_left)
   ,top(i_top)
   ,local_color_table(0)
   ,global_color_table(0)
   ,color_table(0)
   ,interlaced(0)
   ,matrix(0)
   ,modified(1)
   { matrix = (byte **)malloc(height*sizeof(byte **));
     for (int i = 0; i < height; i++)
       matrix[i] = (byte *)malloc(width*sizeof(byte));
      clear();
   }
//______________________________________________________________________________
void GIF_image::write(FILE *out_file)
{
   if (graphic_control.enabled)
      graphic_control.write(out_file);

   fputc(GIF_image_separator,out_file);

   GIF_write_word(out_file,left);
   GIF_write_word(out_file,top);
   GIF_write_word(out_file,width);
   GIF_write_word(out_file,height);

   byte packed
   = (local_color_table ? 0x80 : 0x00)
   | (interlaced ? 0x40 : 0x00)
   | (local_color_table && local_color_table->sorted ? 0x02 : 0x00)
   | (local_color_table ? (local_color_table->bits_per_pixel -1) : 0x00);

   fputc(packed,out_file);

   if (local_color_table)
      local_color_table->write(out_file);

   LZ_compresser *compresser = new LZ_compresser
   (out_file,color_table->bits_per_pixel
   ,((long) width * (long) height));  // Reset decompress algorithm parameters.

   int row;
   for (row = 0; row < height; row++)
   { kbhit();  // let easywin multitask
//     cout << '\r' << row; for debugging
     compresser->PixelCount -= width;

     if (matrix[row])
        compresser->compress_line(out_file,matrix[row],width);
   }

   delete compresser;
}
//______________________________________________________________________________
GIF_image::~GIF_image()
{
  int row;

  for (row = 0; row < height; row++)
     free (matrix[row]);
  free (matrix);
  matrix = 0;

  if (local_color_table)
    delete local_color_table;
}
//______________________________________________________________________________
void GIF_image::read(FILE *in_file)
{

   left     = GIF_read_word(in_file);
   top     = GIF_read_word(in_file);
   width  = GIF_read_word(in_file);
   height = GIF_read_word(in_file);

   byte packed = fgetc(in_file);

   byte bits_per_pixel =(packed & 0x07) + 1;
   int color_table_size = (1 << bits_per_pixel);

   interlaced = (packed & 0x40);
   bool has_local_color_table = (packed  & 0x80);

   if (has_local_color_table)
      color_table = local_color_table = new color_map(in_file);
   else
      local_color_table = 0;

   long PixelCount = (long) width * (long) height;

   LZ_decompresser *decompresser = new LZ_decompresser(in_file);  // Reset decompress algorithm parameters.

   matrix = (byte **)malloc(sizeof(byte *) * height);
   int row;
   for (row = 0; row < height; row++)
   {
     matrix[row] = (byte *)malloc(sizeof(byte)*width);
     kbhit(); // let easywin multitask.
     if (matrix[row])
        decompresser->decompress_line(in_file,matrix[row],width);
     else
     {
        cerr << "Unable to allocate row:" << row << endl;
        break;
     }
   }

   delete decompresser;
}


//______________________________________________________________________________
void GIF_image::line(int c1,int r1,int c2,int r2,byte color)
{
#ifdef DDA
  int error = 0;
  int deltax = c2 - c1;
  int deltay = r2 - r1;

  if (deltay < 0)
  {
    int h_c1 = c1;
    c1 = c2;
    c2 = h_c1;
    int h_r1 = r1;
    r1 = r2;
    r2 = h_r1;
    deltay=-deltay;
    deltax=-deltax;
  }

  int c = c1;
  int r = r1;
  int i;
  if (deltax >= 0)
  {
     if (deltax >= deltay)
     {  for (i = 1; i < deltax; i++)
            if (error < 0)
            { c+= 1;
               point(c,r,color);
               error += deltay;
            }
            else
            { c+= 1;
               r+= 1;
               point(c,r,color);
               error  += deltay - deltax;
            }
     }
     else
     {
       for (i = 1 ; i < deltay;i++)
         if (error < 0)
         {
            c+= 1;
            r += 1;
            point(c,r,color);
            error += deltay - deltax;
         }
         else
         { r += 1;
           point(c,r,color);
           error -= deltax;
         }
     }
  }
  else
    if (deltax >= deltay)
    {
      for (i= 1; i< deltax; i++)
         if (error < 0)
         { c-= 1;
           point(c,r,color);
           error += deltay;
         }
         else
         { c -= 1;
           r -= 1;
           point(c,r,color);
           error += deltax+deltay;
         }
    }
    else
      for (i = 1; i < deltay ; i++)
            if (error < 0)
            { c -= 1;
              r -= 1;
              point (c,r,color);
              error += deltax + deltay;
            }
            else
            { r += 1;
              point(c,r,color);
              error += deltax;
            }
    point(c2,r2,color);

#else

   if (r2 < r1)
   {
     int h_c1 = c1;
     c1 = c2;
     c2 = h_c1;
     int h_r1 = r1;
     r1 = r2;
     r2 = h_r1;
   }

   int deltax = c2 - c1;
   int deltay = r2 - r1;

   if (deltay == 0)
      for (int c = c1; c <= c2; c++)
         point(c,r1,color);
   else
      if (deltax == 0)
         for (int r = r1; r <= r2; r++)
            point(c1,r,color);
   else
   if ((deltax > deltay))
   {
     float slope = (float)deltay / (float)deltax;
     for (int c = 0; c < deltax; c++)
     {
       int r = (float)c * slope;
       point(c1+c,r1+r,color);
     }
   }
   else
   {
     float slope = (float)deltax / (float)deltay;
     for (int r = 0; r < deltay; r++)
     {
       int c = (float)r * slope;
       point(c1+c,r1+r,color);
     }
   }

#endif
}
//______________________________________________________________________________
void GIF_image::recolor(byte new_colors[])
{
  for (int i = 0; i < height; i++)
     for (int j = 0; j < width; j++)
     { byte old_color = matrix[i][j];
       if (old_color > 255) // this shouldn't happen
          old_color = 0;
       byte new_color = new_colors[old_color];

//        if (new_color == 255) // The color has been removed, use an adjacent color
//          new_color = j ? matrix[i][j-1] : matrix[i][j+1];

       point(j,i,new_color);
     }
}

//______________________________________________________________________________
void GIF_image::overlay_image(GIF_image &image_to_overlay,int col,int row)
{ // static to save stack;
  static byte map_colors_1[256];
  static byte map_colors_2[256];


  color_table->union_colors(image_to_overlay.color_table,map_colors_1,map_colors_2);

  //recolor(map_colors_1);

  image_to_overlay.recolor(map_colors_2);

  int i;
  int j;
  for (i = 0; i < image_to_overlay.height; i++)
     for (j = 0; j < image_to_overlay.width; j++)
     {
       matrix[i+row+image_to_overlay.top][j+col+image_to_overlay.left]
       = image_to_overlay.matrix[i][j];
     }
}
//______________________________________________________________________________
*/
/*moved to color_map
static bool deleted_colors[256];
//______________________________________________________________________________
void color_map::remove_duplicate_colors(byte recolor[])
{
  int i,j;
  for (i = 0; i < 256; i++)
     recolor[i] = i;
  int new_num_colors = num_colors;
  new_num_colors = 255;
  for (i = 0 ;i < 255; i++)
  {
     if (deleted_colors[i])
     {  new_num_colors -= 1;
        for (j = i; j <  255; j++)
        { red[j]   = red[j+1];
          green[j] = green[j+1];
          blue[j]  = blue[j+1];
          if (recolor[j] > i)
             recolor[j] = recolor[j] -1;

          deleted_colors[j] = deleted_colors[j+1];
          deleted_colors[255] = 0;

        }
        i -= 1;
     }
  }
  num_colors = new_num_colors;
}
//______________________________________________________________________________
void color_map::quantize(int max_colors, byte recolor[])
{
   int i,j;

//     not used
//    static long frequency[256];
//    for (i = 0; i < 256; i++)
//      frequence[i] = 0;
//
//    for (i = 0; i < height; i++)
//      for (j = 0; j < width ; j++)
//         frequency[matrix[i][j]] += 1;


   for (i = 0; i < 256; i++)
   {
      deleted_colors[i] = 0;
      recolor[i] = i;
   }
   int num_deleted = 0;
   int tolerance = 10;
   while ((num_colors - num_deleted) > max_colors)
   {
      for (i = 0; (i < 256) ; i++)
      if (!deleted_colors[i])
      {
         byte min_dr = 255; byte min_dg = 255; byte min_db = 255;
         int min_index = 255;
         for (j = i+1; j < 256; j++)
         {
            if (i != j)
            { byte dr = abs(red[j] - red[i]);
              byte dg = abs(green[j] - green[i]);
              byte db = abs(blue[j] - blue[i]);
              if ((dr < min_dr) && (dg < min_dg) && (db < min_db) &&
                  (dr < tolerance) && (dg < tolerance) && (db < tolerance)
                  && (!deleted_colors[j]))
              {
                 min_dr = dr; min_dg = dg; min_db = db;
                 min_index = j;
              }
            }
         }
         if (min_index < 255)
         {
           deleted_colors[min_index] = 1;
           recolor[min_index] = i;
         }
      }
      tolerance += 1;
      num_deleted = 0;
      for (i = 0; i < 256; i++)
         num_deleted += deleted_colors[i];
   }
}
//______________________________________________________________________________
*/
/*moved to gif_image
void GIF_image::quantize(int max_colors = 128)
{
   static byte new_colors[256];
   color_table->quantize(max_colors,new_colors);
   recolor(new_colors);

   color_table->remove_duplicate_colors(new_colors);
   recolor(new_colors);

   color_table->num_colors = max_colors;
}
//______________________________________________________________________________
void GIF_image::set_torus(int col, int row,byte color)
{
   // This function set the color at x,y
   // if X is < 0 or X > width, the dimensions are wrapped around

   if (row < 0)       row = height + row;
   if (row >= height) row = row - height;
   if (col < 0)       col = width + col;
   if (col >= width)  col = col - width;

   matrix[row][col] = color;
}
//______________________________________________________________________________
byte GIF_image::get_torus(int col, int row)
{
   // This function returns the color at x,y
   // if X is < 0 or X > width, the dimensions are wrapped around

   if (row < 0)       row = height + row;
   if (row >= height) row = row - height;
   if (col < 0)       col = width + col;
   if (col >= width)  col = col - width;

   return matrix[row][col];
}
//______________________________________________________________________________
*/
GIF::GIF(const CORN_filename &i_filename)
:filename(i_filename)
,screen_width(0)
,screen_height(0)
,background_color(0)
,pixel_aspect_ratio(0)
,global_color_table(0)
,images()                                                                        //991115
,last_graphic_control()
,file(0)
{
   read();
}
//______________________________________________________________________________
// Output file
GIF::GIF(const CORN_filename &i_filename,unsigned int i_screen_width ,unsigned int i_screen_height )
:filename(i_filename)
,screen_height(i_screen_height)
,screen_width(i_screen_width)
,background_color(0)
,pixel_aspect_ratio(0)
,global_color_table(0)
,images()                                                                        //991115
,file(0)
{
  file = fopen(i_filename.c_str(),"wb");
}
//______________________________________________________________________________
int GIF_skip_extension_block(FILE *in_file)
{
    byte extension_length = fgetc(in_file);
    if (extension_length)
    { byte buf[256];
      if (fread(&buf, 1, extension_length,in_file) != extension_length)
         return GIF_ERROR;
      buf[extension_length] = 0;
//      cout << buf << endl; for debugging
    }
    return GIF_OK;
}
//______________________________________________________________________________
int GIF_skip_comment(FILE *in_file)
{
    byte extension_code = fgetc(in_file);
    GIF_skip_extension_block(in_file);
}
//______________________________________________________________________________
void GIF::read()
{
  FILE *in_file = fopen(filename.c_str(),"rb");
  if (in_file)
  {

  char gif_version[7];
  fread(&gif_version,sizeof(char),6,in_file);
  gif_version[6] = 0;
  // Check here for valid gif header

  // read screen width
  screen_width  = GIF_read_word(in_file);
  screen_height = GIF_read_word(in_file);

  byte packed_field  = fgetc(in_file);

  byte color_resolution = (((packed_field & 0x70) + 1) >> 4) + 1;
  byte bits_per_pixel = (packed_field & 0x07) + 1;
  bool global_color_map_enabled = packed_field & 0x80;

  background_color   = fgetc(in_file);
  pixel_aspect_ratio = fgetc(in_file);

  if (global_color_map_enabled)
  {
     global_color_table = new color_map(color_resolution,bits_per_pixel);
     global_color_table->read(in_file);
  }
  else
     global_color_table = 0;

  while (!feof(in_file))
  {
    byte record_type = fgetc(in_file);
    switch(record_type)
    {
      case GIF_image_separator :  // ','
         images.append(new GIF_image(in_file,global_color_table,last_graphic_control));
          last_graphic_control.enabled = false;
      break;
      case GIF_extension_introducer : // '!'
      {
          byte extension_code = fgetc(in_file);
          switch (extension_code)
          { case GIF_graphic_control_extension :
               last_graphic_control.read(in_file);
            break;
            case GIF_application_extension :
            {  byte length = fgetc(in_file);
               char extension_label[50];
               fread (&extension_label,1,length,in_file);
               byte block_length = fgetc(in_file);
               if (strncmp(extension_label,"NETSCAPE2.0",block_length) == 0)
               {  fgetc(in_file); // Should be 1
                  animation_iterations = GIF_read_word(in_file);
               }
               else // I don't know what the extension is so just throw it away.
               {  char *buffer = (char *)malloc(block_length +1);
                  fread(&buffer,1,block_length,in_file);
                  free(buffer);
               }
               fgetc(in_file); // should be 0 the block terminator
            }
            break;
            default :
              GIF_skip_extension_block(in_file);
              byte block_terminator = fgetc(in_file);
            break;
          }
          // num_extensions += 1;
          // extensions[num_extensions] = new extension(in_file);
      }
      break;
      case GIF_comment_extension :
         GIF_skip_comment(in_file);
      break;
      case GIF_trailer : // ';'
         // TERMINATE_RECORD_TYPE;
         return;
      default:
//       *Type = UNDEFINED_RECORD_TYPE;
//       RGIFERROR = D_GIF_ERR_WRONG_RECORD;
       return; // GIF_ERROR;
    }
  }
  fclose(in_file);
  }
}
//______________________________________________________________________________
void GIF::write_global()
{
  char gif_version[7] = "GIF89a";
  fwrite(&gif_version,1,6,file);

  // read screen width
  GIF_write_word(file,screen_width);
  GIF_write_word(file,screen_height);

  byte has_color_table =  global_color_table ? 0x80 : 0x00;
  byte color_res_bits = (global_color_table ? ((global_color_table->color_resolution - 1) << 4) : 0x00);
  byte color_table_sorted = ((global_color_table && global_color_table->sorted) ? 0x04 : 0x00);
  byte color_table_bits_per_pixel = (global_color_table ? (global_color_table->bits_per_pixel -1) : 0x00);

  byte packed_field = has_color_table | color_res_bits | color_table_sorted | color_table_bits_per_pixel;

  fputc(packed_field,file);

  fputc(background_color,file);
  fputc(pixel_aspect_ratio,file);

  if (global_color_table)
     global_color_table->write(file);

  // Animation control block follows the global color table
  if (animation)
     write_animation_control_block();
}
//______________________________________________________________________________
void GIF::write_close()
{
  fputc(GIF_trailer,file);
  fclose(file);
  file = 0;
}
//______________________________________________________________________________
void GIF::write()
{
  write_global();

   for (GIF_image *image = (GIF_image *)images.move_to_head()                    //991115
       ;image                                                                    //991115
       ;image = (GIF_image *)images.move_to_next())                              //991115
   {
      image->write(file);                                                        //991115
   }
  write_close();
}
//______________________________________________________________________________
void GIF::write_animation_control_block()
{
  fputc(GIF_extension_introducer,file);
  fputc(GIF_application_extension,file);
  fputc(0x0B,file); // animation extension length
  char netscape2_0[11] = "NETSCAPE2.0";
  fwrite(&netscape2_0,1,11,file);
  fputc(0x03,file); // length of animation block
  fputc(0x01,file);
  GIF_write_word(file, animation_iterations);
  fputc(0x00,file);
}
//______________________________________________________________________________
void GIF::write_current_image()
{
   GIF_image *current_image = (GIF_image *)images.current();                     //991115
   if (current_image)                                                            //991115
      current_image->write(file);
}
//______________________________________________________________________________
GIF::~GIF()
{
  if (global_color_table) delete global_color_table;
   images.delete_all();                                                          //991115
  if (file) fclose(file);
}
//______________________________________________________________________________


#define PROGRAM_NAME   "GIF_LIBRARY"

/* #define  DEBUG_HIT_RATE    Debug number of misses per hash Insert/Exists. */

#ifdef   DEBUG_HIT_RATE
static long NumberOfTests = 0,
       NumberOfMisses = 0;
#endif

//______________________________________________________________________________
// /******************************************************************************
// * Initialize HashTable - allocate the memory needed and clear it.         *
// *****************************************************************************
GIF_hash_table::GIF_hash_table()
{
   clear();
}
//______________________________________________________________________________
// /******************************************************************************
// * Routine to clear the HashTable to an empty state.               *
// * This part is a little machine depended. Use the commented part otherwise.   *
// *****************************************************************************
void GIF_hash_table::clear()
{  memset(HTable, 0xFF, HT_SIZE * sizeof(long));
}
//______________________________________________________________________________
// /******************************************************************************
// * Routine to insert a new Item into the HashTable. The data is assumed to be  *
// * new one.                              *
// *****************************************************************************
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
// /******************************************************************************
// * Routine to test if given Key exists in HashTable and if so returns its code *
// * Returns the Code if key was found, -1 if not.                  *
// *****************************************************************************
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
       kbhit();
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
// /******************************************************************************
// * Routine to generate an HKey for the hashtable out of the given unique key.  *
// * The given Key is assumed to be 20 bits as follows: lower 8 bits are the     *
// * new postfix character, while the upper 12 bits are the prefix code.         *
// * Because the average hit ratio is only 2 (2 hash references per entry),      *
// * evaluating more complex keys (such as twin prime keys) does not worth it!   *
// *****************************************************************************
int GIF_hash_table::KeyItem(unsigned long Item)
{
    return ((Item >> 12) ^ Item) & HT_KEY_MASK;
}
//______________________________________________________________________________
#ifdef   DEBUG_HIT_RATE
// /******************************************************************************
// * Debugging routine to print the hit ratio - number of times the hash table   *
// * was tested per operation. This routine was used to test the KeyItem routine *
// *****************************************************************************
void GIF_hash_table::PrintHitRatio(void)
{
    printf("Hash Table Hit Ratio is %ld/%ld = %ld%%.\n",
   NumberOfMisses, NumberOfTests,
   NumberOfMisses * 100 / NumberOfTests);
}
#endif   //DEBUG_HIT_RATE
//______________________________________________________________________________
void GIF_animation::commit_current_frame()
{  int r;       // should be iint16
   int c;      // should be iint16
   GIF_image *current_image = (GIF_image *)images.current();                     //991115
      if (prev_frame)
      {  // optimized curr_frame to prev_frame
         // There are two optimizations that occur:
         // 1. The new image reduced to only that rectangle of the
         //    current images that is different from the previous frame.
         // 2. Colours that are the same as the previous frame are replaced
         //    buy transparent color.
         int top_row_differs = screen_height;
         int left_col_differs = screen_width;
         int bottom_row_differs = 0;
         int right_col_differs = 0;
         byte transparent_color = current_image->graphic_control.transparent_color;
         bool has_a_difference = false;
         for ( r = 0; (r < screen_height); r ++)
         {
            for ( c = 0; (c < screen_width); c++)
            {
               if (current_image->get_torus(c,r) !=
                   prev_frame->get_torus(c,r))
               {
                  top_row_differs = CORN_min(top_row_differs,r);
                  bottom_row_differs = CORN_max(bottom_row_differs,r);
                  left_col_differs = CORN_min(left_col_differs,c);
                  right_col_differs = CORN_max(right_col_differs,c);
                  has_a_difference = true;
               }
            }
         }

//         // temporarily disabling frame size optimizations
//         top_row_differs = 0;
//         bottom_row_differs = screen_height;
//         left_col_differs = 0;
//         right_col_differs = screen_width;

         if (has_a_difference)
         {
            int optimized_rows = bottom_row_differs - top_row_differs;
            int optimized_cols = right_col_differs - left_col_differs;
            GIF_image optimized(
               optimized_cols+1,optimized_rows+1,
               left_col_differs,top_row_differs
               );

            optimized.global_color_table =
            optimized.color_table =
               global_color_table;

            optimized.graphic_control.disposal_method = GIF_control_extension::DONT_DISPOSE;
            optimized.graphic_control.user_input = false;
            optimized.graphic_control.use_transparent_color = true;
            optimized.graphic_control.transparent_color = 0;
            optimized.graphic_control.enabled = true;
            optimized.graphic_control.delay_time = current_image->graphic_control.delay_time;

            int or = 0;
            for ( r = top_row_differs; r <= bottom_row_differs; r ++)
            {
               int oc = 0;
               for ( c = left_col_differs; c <= right_col_differs; c++)
               {
                  byte curr_pix_color = current_image->get_torus(c,r);
                  byte prev_pix_color = prev_frame->get_torus(c,r);
                  optimized.point(oc,or,curr_pix_color);
                  oc++;
               }
               or ++;
            }
            // write optimized frame
            GIF_image *hold_image = current_image;
            current_image = &optimized;
            write_current_image();
            current_image = hold_image;   // At this point optimized is automatically disposed so we remove the reference
         }
      }
      else write_current_image();
      delete prev_frame;
      prev_frame = current_image;
      current_image = 0;
}
//______________________________________________________________________________
GIF_image &GIF_animation::new_frame(int16 delay_time)
{
      commit_current_frame();
      GIF_image *                                                                //991115
         current_image = new GIF_image(screen_width,screen_height);

      current_image->global_color_table =
         current_image->color_table =
            global_color_table;

      // These image options are required to implement optimized animations
      current_image->graphic_control.disposal_method = GIF_control_extension::DONT_DISPOSE;
      current_image->graphic_control.user_input = false;
      current_image->graphic_control.use_transparent_color = true;
      current_image->graphic_control.transparent_color = 0;
      current_image->graphic_control.enabled = true;
      current_image->graphic_control.delay_time = delay_time;
      return *current_image;
}
//______________________________________________________________________________
void GIF_image::clear(byte clear_color)
{
   for (int row = 0; row < height ; row++)
      for (int col = 0; col < width; col++)
         matrix[row][col] = clear_color;
}
//______________________________________________________________________________
void GIF_image::point(int col,int row,byte color)
{
   if ((row >= 0) && (row < height) && (col >= 0) && (col < width ))
      matrix[row][col] = color;
}
//______________________________________________________________________________
} // namespace CORN

