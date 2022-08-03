#error obsolete
/*
   This set of classes are being replaced by
   colormap.*
   gif_anim.*
   gif_image.*
   gif_file.*

*/

#include <conio.h> // for easywin multitasking
#include <corn/std/std_fstream.h>
#include <corn/corn.h>
#include <corn/image/gif/oldgif.h>

/*______*/  unsigned int GIF_read_word(FILE *infile)
/*______*/  {
/*______*/    unsigned char buffer[3];
/*______*/    if (fread(&buffer, 1, 2, infile) != 2)
/*______*/       cerr << "read word error" << endl;;
/*______*/
/*______*/    unsigned int result = buffer[1];
/*______*/    result <<= 8;
/*______*/    result |= buffer[0];
/*______*/
/*______*/    return result;
/*______*/  };
/*______*/
/*______*/  void GIF_write_word(FILE *outfile, unsigned int word)
/*______*/  {
/*______*/      byte upper = (word >> 8) & 0xff;
/*______*/      byte lower = word & 0xFF;
/*______*/  
/*______*/      fputc(lower,outfile);
/*______*/      fputc(upper,outfile);
/*______*/  }
/*______*/  
/*______*/  color_map::color_map(byte i_color_resolution,byte i_bits_per_pixel)
/*______*/  :color_resolution(i_color_resolution)
/*______*/  ,bits_per_pixel(i_bits_per_pixel)
/*______*/  ,num_colors(1 << i_bits_per_pixel)
/*______*/  {
/*______*/  };
/*______*/
/*______*/  color_map::color_map(CORN::Color_ramp &color_ramp)
/*______*/  :color_resolution(4)  // I think
/*______*/  ,bits_per_pixel(8)
/*______*/  ,num_colors(1 << 8)
/*______*/  {
/*______*/     int colors_in_ramp = color_ramp.get_colors();
/*______*/     float color_ramp_step = // float because
/*______*/     (colors_in_ramp > num_colors)
/*______*/     ? colors_in_ramp / num_colors
/*______*/     : 1;

/*______*/     red[0]   = 0;  // Default background color is black.
/*______*/     green[0] = 0;
/*______*/     blue[0]  = 0;

/*______*/     float color_ramp_index = 1;
/*______*/     for (int color_map_index = 1 // Leave index 0 for background color
/*______*/         ;color_map_index < num_colors
/*______*/         ;color_map_index++)
/*______*/     {
/*______*/        red[color_map_index] = color_ramp.get_color((uint16)color_ramp_index).Red();
/*______*/        green[color_map_index] = color_ramp.get_color((uint16)color_ramp_index).Green();
/*______*/        blue[color_map_index] = color_ramp.get_color((uint16)color_ramp_index).Blue();
/*______*/        color_ramp_index += color_ramp_step;
/*______*/     }
/*______*/  };
/*______*/
/*______*/  void color_map::read(FILE *infile)
/*______*/  {
/*______*/  	for (int i = 0; i < num_colors; i++)
/*______*/  	{ red[i]   = fgetc(infile);
/*______*/  	  green[i] = fgetc(infile);
/*______*/  	  blue[i]  = fgetc(infile);
/*______*/  	};
/*______*/  };
/*______*/  
/*______*/  void color_map::write(FILE *outfile)
/*______*/  {
/*______*/  	for (int i = 0; i < num_colors; i++)
/*______*/  	{ fputc(red[i],outfile);
/*______*/  	  fputc(green[i] ,outfile);
/*______*/  	  fputc(blue[i],outfile);
/*______*/  	};
/*______*/  };
/*______*/  
/*______*/  int color_map::find(byte r, byte g, byte b)
/*______*/  {
/*______*/     int i;
/*______*/  //   int min_dr = 0xff;
/*______*/  //   int min_dg = 0xff;
/*______*/  //   int min_db = 0xff;
/*______*/     int min_avg = 0xff;
/*______*/     int index = 0;
/*______*/     for (i = 0; i < num_colors; i++)
/*______*/     {
/*______*/       int dr = abs(r - red[i]);
/*______*/       int dg = abs(g - green[i]);
/*______*/       int db = abs(b - blue[i]);
/*______*/       int avg = (dr + dg + db) /3;
/*______*/       if (avg < min_avg)
/*______*/       {
/*______*/          min_avg = avg;
/*______*/          index = i;
/*______*/       };
/*______*/     };
/*______*/     return index;
/*______*/  };
/*______*/  
/*______*/  void color_map::union_colors(color_map *color_map_2,byte recolor1[],byte recolor2[])
/*______*/  {
/*______*/    int i;
/*______*/  
/*______*/    // At this time I am not modifying the base image's color map
/*______*/    for (i = 0; i < num_colors; i++)
/*______*/    {
/*______*/  	  recolor1[i] = i;
/*______*/  	  recolor2[i] = i;
/*______*/    };
/*______*/  
/*______*/  
/*______*/    if ((num_colors + color_map_2->num_colors) <= 256)
/*______*/    {
/*______*/  	  // Add the second color map to the end of the color map.
/*______*/  	  for (i = 0; i < color_map_2->num_colors; i++)
/*______*/  	  { recolor2[i] = num_colors + i;
/*______*/         color_map_2->red[i+num_colors] = color_map_2->red[i];
/*______*/         color_map_2->green[i+num_colors] = color_map_2->green[i];
/*______*/         color_map_2->blue[i+num_colors] = color_map_2->blue[i];
/*______*/         red[i+num_colors] = color_map_2->red[i];
/*______*/         green[i+num_colors] = color_map_2->green[i];
/*______*/         blue[i+num_colors] = color_map_2->blue[i];
/*______*/  	  };
/*______*/       num_colors = num_colors + color_map_2->num_colors;
/*______*/    }
/*______*/    else
/*______*/    { int colors_reused = 0;
/*______*/  	 for (i = 0; i < color_map_2->num_colors; i++)
/*______*/  	 { recolor2[i] = 255;
/*______*/        int min_dr = 256;
/*______*/        int min_dg = 256;
/*______*/        int min_db = 256;
/*______*/        for (int j = 0; j < num_colors; j++)
/*______*/  		{ int dr = abs(red[j]   - color_map_2->red[i]);
/*______*/  		  int dg = abs(green[j] - color_map_2->green[i]);
/*______*/  		  int db = abs(blue[j]  - color_map_2->blue[i]);
/*______*/  
/*______*/  #define SAME_COLOR_RANGE 10
/*______*/  		  if (dr < min_dr && dg < min_dg && db < min_db)
/*______*/          {
/*______*/  			  // If the second image color is similar to this first color
/*______*/  			  // then substitute the color
/*______*/  			  recolor2[i] = j;
/*______*/             colors_reused += 1;
/*______*/             min_dr = dr;
/*______*/             min_dg = dg;
/*______*/             min_db = db;
/*______*/          };
/*______*/  //        else // can't permit more than 255 color.
/*______*/  //           recolor2[i] = (num_colors < 256) ? num_colors++ : 255;
/*______*/  		};
/*______*/  	 };
/*______*/  //    cout << "Colors reused:" << colors_reused << endl; for debugging
/*______*/    };
/*______*/  };
/*______*/  
/*______*/  void color_map::copy_from(color_map &map)
/*______*/  {
/*______*/     int i;
/*______*/     for (i = 0; i < 256; i++)
/*______*/     {
/*______*/       red[i] = map.red[i];
/*______*/       green[i] = map.green[i];
/*______*/       blue[i] = map.blue[i];
/*______*/     };
/*______*/  
/*______*/     color_resolution = map.color_resolution;
/*______*/     bits_per_pixel = map.bits_per_pixel;
/*______*/  
/*______*/  	num_colors = map.num_colors;
/*______*/     sorted = map.sorted;
/*______*/  };
/*______*/  
/*______*/  ///////////////////////////////////////////////////////
/*______*/  #define NO_SUCH_CODE		4098    /* Impossible code, to signal empty. */
/*______*/  
/*______*/  LZ_decompresser::LZ_decompresser(FILE *in_file)
/*______*/  {
/*______*/  //	 unsigned int *Prefix;
/*______*/  
/*______*/  	 byte CodeSize = fgetc(in_file);
/*______*/  
/*______*/  	 Buf[0] = 0;			      /* Input Buffer empty. */
/*______*/  	 BitsPerPixel = CodeSize;
/*______*/  	 ClearCode = (1 << BitsPerPixel);
/*______*/  	 EOFCode = ClearCode + 1;
/*______*/  	 RunningCode = EOFCode + 1;
/*______*/  	 RunningBits = BitsPerPixel + 1;	 /* Number of bits per code. */
/*______*/  	 MaxCode1 = 1 << RunningBits;     /* Max. code + 1. */
/*______*/  	 StackPtr = 0;		    /* No pixels on the pixel stack. */
/*______*/  	 LastCode = NO_SUCH_CODE;
/*______*/  	 CrntShiftState = 0;	/* No information in CrntShiftDWord. */
/*______*/  	 CrntShiftDWord = 0;
/*______*/  
/*______*/  	 for (int i = 0; i < LZ_MAX_CODE; i++)
/*______*/  		Prefix[i] = NO_SUCH_CODE;
/*______*/  };
/*______*/  
/*______*/  // ******************************************************************************
/*______*/  // Routine to trace the Prefixes linked list until we get a prefix which is    *
/*______*/  // not code, but a pixel value (less than ClearCode). Returns that pixel value.*
/*______*/  // If image is defective, we might loop here forever, so we limit the loops to *
/*______*/  // the maximum possible if image O.k. - LZ_MAX_CODE times.		      *
/*______*/  // ******************************************************************************
/*______*/  
/*______*/  int LZ_decompresser::GetPrefixChar
/*______*/  (unsigned int *Prefix, int Code, int ClearCode)
/*______*/  {
/*______*/  	int i = 0;
/*______*/  
/*______*/  	while (Code > ClearCode && i++ <= LZ_MAX_CODE)
/*______*/  		Code = Prefix[Code];
/*______*/  	return Code;
/*______*/  }
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // *   This routines read one gif data block at a time and buffers it internally *
/*______*/  // * so that the decompression routine could access it.			      *
/*______*/  // *   The routine returns the next byte from its internal buffer (or read next  *
/*______*/  // * block in if buffer empty) and returns GIF_OK if succesful.		      *
/*______*/  // ******************************************************************************/
/*______*/  int LZ_decompresser::buffered_input(FILE *File, byte *Buf,byte *NextByte)
/*______*/  {
/*______*/  	if (Buf[0] == 0)
/*______*/  	{	/* Needs to read the next buffer - this one is empty: */
/*______*/  		if (fread(Buf, 1, 1, File) != 1)
/*______*/  		{	//RGIFERROR = D_GIF_ERR_READ_FAILED;
/*______*/  			return GIF_ERROR;
/*______*/  		}
/*______*/  		if (fread(&Buf[1], 1, Buf[0], File) != Buf[0])
/*______*/  		{	//RGIFERROR = D_GIF_ERR_READ_FAILED;
/*______*/  			return GIF_ERROR;
/*______*/  		}
/*______*/  		*NextByte = Buf[1];
/*______*/  		Buf[1] = 2;	   /* We use now the second place as last char read! */
/*______*/  		Buf[0]--;
/*______*/  	}
/*______*/  	else
/*______*/  	{	*NextByte = Buf[Buf[1]++];
/*______*/  		Buf[0]--;
/*______*/  	}
/*______*/  	return GIF_OK;
/*______*/  };
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // *   The LZ decompression input routine:					      *
/*______*/  // *   This routine is responsable for the decompression of the bit stream from  *
/*______*/  // * 8 bits (bytes) packets, into the real codes.				      *
/*______*/  // *   Returns GIF_OK if read succesfully.					      *
/*______*/  // ******************************************************************************/
/*______*/  int LZ_decompresser::decompress_input(FILE *File,int &Code)
/*______*/  {
/*______*/  	 byte NextByte;
/*______*/  	 static unsigned int CodeMasks[] = {
/*______*/  	0x0000, 0x0001, 0x0003, 0x0007,
/*______*/  	0x000f, 0x001f, 0x003f, 0x007f,
/*______*/  	0x00ff, 0x01ff, 0x03ff, 0x07ff,
/*______*/  	0x0fff
/*______*/  	 };
/*______*/  
/*______*/  	 while (CrntShiftState < RunningBits)
/*______*/  	 {	/* Needs to get more bytes from input stream for next code: */
/*______*/  		if (buffered_input(File, Buf, &NextByte) == GIF_ERROR)
/*______*/  		{	return GIF_ERROR;
/*______*/  		}
/*______*/  		CrntShiftDWord |=
/*______*/  			((unsigned long) NextByte) << CrntShiftState;
/*______*/  		CrntShiftState += 8;
/*______*/  	 }
/*______*/  	 Code = CrntShiftDWord & CodeMasks[RunningBits];
/*______*/  
/*______*/  	 CrntShiftDWord >>= RunningBits;
/*______*/  	 CrntShiftState -= RunningBits;
/*______*/  
/*______*/  // 	 /* If code cannt fit into RunningBits bits, must raise its size. Note */
/*______*/  // 	 /* however that codes above 4095 are used for special signaling.      */
/*______*/  	 if (++RunningCode > MaxCode1 &&
/*______*/  			RunningBits < LZ_BITS)
/*______*/  	 { MaxCode1 <<= 1;
/*______*/  		RunningBits++;
/*______*/  	 }
/*______*/  	 return GIF_OK;
/*______*/  }
/*______*/  
/*______*/  
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // *   The LZ decompression routine:					      *
/*______*/  // *   This version decompress the given gif file into Line of length LineLen.   *
/*______*/  // *   This routine can be called few times (one per scan line, for example), in *
/*______*/  // * order the complete the whole image.					      *
/*______*/  // ******************************************************************************/
/*______*/  int LZ_decompresser::decompress_line(FILE *in_file,byte Line[], int LineLen)
/*______*/  {
/*______*/  	int CrntPrefix;
/*______*/  //	int i = 0, j, CrntCode, EOFCode, ClearCode, CrntPrefix, LastCode, StackPtr;
/*______*/  //	byte *Stack, *Suffix;
/*______*/  //	unsigned int *Prefix;
/*______*/  
/*______*/  	int i = 0;
/*______*/  
/*______*/  	if (StackPtr != 0)
/*______*/  	{ // Let pop the stack off before continueing to read the gif file:
/*______*/  		while (StackPtr != 0 && i < LineLen)
/*______*/  			Line[i++] = Stack[--StackPtr];
/*______*/  	};
/*______*/  
/*______*/  	while (i < LineLen)
/*______*/  	{ /* Decode LineLen items. */
/*______*/  		if (decompress_input(in_file,CrntCode) == GIF_ERROR)
/*______*/  			 return GIF_ERROR;
/*______*/  
/*______*/  		if (CrntCode == EOFCode)
/*______*/  		{
/*______*/  			/* Note however that usually we will not be here as we will stop */
/*______*/  			/* decoding as soon as we got all the pixel, or EOF code will    */
/*______*/  			/* not be read at all, and DGifGetLine/Pixel clean everything.   */
/*______*/  
/*______*/  			if (i != LineLen - 1 || PixelCount != 0)
/*______*/  			{	//RGIFERROR = D_GIF_ERR_EOF_TOO_SOON;
/*______*/  				return GIF_ERROR;
/*______*/  			}
/*______*/  			i++;
/*______*/  		}
/*______*/  		else if (CrntCode == ClearCode)
/*______*/  		{	/* We need to start over again: */
/*______*/  			int j;
/*______*/  			for (j = 0; j < LZ_MAX_CODE; j++)
/*______*/  				Prefix[j] = NO_SUCH_CODE;
/*______*/  			RunningCode = EOFCode + 1;
/*______*/  			RunningBits = BitsPerPixel + 1;
/*______*/  			MaxCode1 = 1 << RunningBits;
/*______*/  			LastCode = NO_SUCH_CODE;
/*______*/  		}
/*______*/  		else
/*______*/  		{	/* Its regular code - if in pixel range simply add it to output  */
/*______*/  			/* stream, otherwise trace to codes linked list until the prefix */
/*______*/  			/* is in pixel range:					     */
/*______*/  			if (CrntCode < ClearCode)
/*______*/  			{
/*______*/  				/* This is simple - its pixel scalar, so add it to output:   */
/*______*/  				Line[i++] = CrntCode;
/*______*/  			}
/*______*/  			else
/*______*/  			{
/*______*/  				/* Its a code to needed to be traced: trace the linked list  */
/*______*/  				/* until the prefix is a pixel, while pushing the suffix     */
/*______*/  				/* pixels on our stack. If we done, pop the stack in reverse */
/*______*/  				/* (thats what stack is good for!) order to output.	     */
/*______*/  
/*______*/  				if (Prefix[CrntCode] == NO_SUCH_CODE)
/*______*/  				{	/* Only allowed if CrntCode is exactly the running code: */
/*______*/  					/* In that case CrntCode = XXXCode, CrntCode or the	     */
/*______*/  					/* prefix code is last code and the suffix char is	     */
/*______*/  					/* exactly the prefix of last code!			     */
/*______*/  					if (CrntCode == RunningCode - 2)
/*______*/  					{	CrntPrefix = LastCode;
/*______*/  						Suffix[RunningCode - 2] = Stack[StackPtr++]
/*______*/  							= GetPrefixChar(Prefix,LastCode, ClearCode);
/*______*/  					}
/*______*/  					else
/*______*/  					{	//RGIFERROR = D_GIF_ERR_IMAGE_DEFECT;
/*______*/  						return GIF_ERROR;
/*______*/  					}
/*______*/  				}
/*______*/  				else
/*______*/  					CrntPrefix = CrntCode;
/*______*/  
/*______*/  				/* Now (if image is O.K.) we should not get and NO_SUCH_CODE */
/*______*/  				/* During the trace. As we might loop forever, in case of    */
/*______*/  				/* defective image, we count the number of loops we trace    */
/*______*/  				/* and stop if we got LZ_MAX_CODE. obviously we can not      */
/*______*/  				/* loop more than that.					     */
/*______*/  				int j = 0;
/*______*/  				while (j++ <= LZ_MAX_CODE &&
/*______*/  						 CrntPrefix > ClearCode &&
/*______*/  						 CrntPrefix <= LZ_MAX_CODE)
/*______*/  				{	Stack[StackPtr++] =	Suffix[CrntPrefix];
/*______*/  					CrntPrefix = Prefix[CrntPrefix];
/*______*/  				}
/*______*/  
/*______*/  				if (j >= LZ_MAX_CODE || CrntPrefix > LZ_MAX_CODE)
/*______*/  				{	//RGIFERROR = D_GIF_ERR_IMAGE_DEFECT;
/*______*/  					return GIF_ERROR;
/*______*/  				}
/*______*/  				/* Push the last character on stack: */
/*______*/  				Stack[StackPtr++] = CrntPrefix;
/*______*/  
/*______*/  				/* Now lets pop all the stack into output: */
/*______*/  				while (StackPtr != 0 && i < LineLen)
/*______*/  					Line[i++] = Stack[--StackPtr];
/*______*/  			}
/*______*/  			if (LastCode != NO_SUCH_CODE)
/*______*/  			{	Prefix[RunningCode - 2] = LastCode;
/*______*/  
/*______*/  				if (CrntCode == RunningCode - 2)
/*______*/  				{	/* Only allowed if CrntCode is exactly the running code: */
/*______*/  					/* In that case CrntCode = XXXCode, CrntCode or the	     */
/*______*/  					/* prefix code is last code and the suffix char is	     */
/*______*/  					/* exactly the prefix of last code!			     */
/*______*/  					Suffix[RunningCode - 2] =
/*______*/  						GetPrefixChar(Prefix, LastCode, ClearCode);
/*______*/  				}
/*______*/  				else
/*______*/  				{	Suffix[RunningCode - 2] =
/*______*/  						GetPrefixChar(Prefix, CrntCode, ClearCode);
/*______*/  				}
/*______*/  			}
/*______*/  			LastCode = CrntCode;
/*______*/  		}
/*______*/  	}
/*______*/  
/*______*/  	LastCode = LastCode;
/*______*/  	StackPtr = StackPtr;
/*______*/  
/*______*/  	return GIF_OK;
/*______*/  };
/*______*/  ///////////////////////////////////////////////////////
/*______*/  
/*______*/  #define FLUSH_OUTPUT		4096	/* Impossible code, to signal flush. */
/*______*/  #define FIRST_CODE		4097    /* Impossible code, to signal first. */
/*______*/  
/*______*/  LZ_compresser::LZ_compresser(FILE *out_file,int bits_per_pixel,long i_PixelCount)
/*______*/  : PixelCount(i_PixelCount)
/*______*/  {
/*______*/     byte code =(bits_per_pixel < 2) ? 2 : bits_per_pixel;
/*______*/     fputc(code,out_file);
/*______*/  
/*______*/     Buf[0] = 0;			  /* Nothing was output yet. */
/*______*/     BitsPerPixel = bits_per_pixel;
/*______*/     ClearCode = (1 << BitsPerPixel);
/*______*/     EOFCode = ClearCode + 1;
/*______*/     RunningCode = EOFCode + 1;
/*______*/     RunningBits = BitsPerPixel + 1;	 /* Number of bits per code. */
/*______*/     MaxCode1 = 1 << RunningBits;	   /* Max. code + 1. */
/*______*/     CrntCode = FIRST_CODE;	   /* Signal that this is first one! */
/*______*/     CrntShiftState = 0;      /* No information in CrntShiftDWord. */
/*______*/     CrntShiftDWord = 0;
/*______*/  
/*______*/     /* Clear hash table and send Clear to make sure the decoder do the same. */
/*______*/     hash_table.clear();
/*______*/     if (compress_output(out_file,ClearCode) == GIF_ERROR);
/*______*/  }
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // *   The LZ compression routine:						      *
/*______*/  // *   This version compress the given buffer Line of length LineLen.	      *
/*______*/  // *   This routine can be called few times (one per scan line, for example), in *
/*______*/  // * order the complete the whole image.					      *
/*______*/  // ******************************************************************************/
/*______*/  #define ZL_MAX_CODE	4095		/* Biggest code possible in 12 bits. */
/*______*/  int LZ_compresser::compress_line(FILE *out_file, byte *Line, int LineLen)
/*______*/  {
/*______*/    // int i = 0,
/*______*/    unsigned int local_CrntCode;
/*______*/    int NewCode;
/*______*/    unsigned long NewKey;
/*______*/    //  GifPixelType Pixel;
/*______*/    //  GifHashTableType *HashTable;
/*______*/  
/*______*/    byte Pixel;
/*______*/  
/*______*/    int i = 0;
/*______*/    if (CrntCode == FIRST_CODE)		  /* Its first time! */
/*______*/        local_CrntCode = Line[i++];
/*______*/    else
/*______*/        local_CrntCode = CrntCode;     /* Get last code in compression. */
/*______*/  
/*______*/    while (i < LineLen)
/*______*/    {   /* Decode LineLen items. */
/*______*/        Pixel = Line[i++];		      /* Get next pixel from stream. */
/*______*/        /* Form a new unique key to search hash table for the code combines  */
/*______*/        /* CrntCode as Prefix string with Pixel as postfix char.	     */
/*______*/        NewKey = (((unsigned long) local_CrntCode) << 8) + Pixel;
/*______*/        if ((NewCode = hash_table.exists(NewKey)) >= 0)
/*______*/        {
/*______*/           /* This Key is already there, or the string is old one, so	     */
/*______*/           /* simple take new code as our CrntCode:			     */
/*______*/           local_CrntCode = NewCode;
/*______*/        }
/*______*/        else
/*______*/        {  /* Put it in hash table, output the prefix code, and make our    */
/*______*/  	      /* CrntCode equal to Pixel.					     */
/*______*/           if (compress_output(out_file, local_CrntCode) == GIF_ERROR)
/*______*/              return GIF_ERROR; //RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
/*______*/           local_CrntCode = Pixel;
/*______*/  
/*______*/           /* If however the HashTable if full, we send a clear first and   */
/*______*/     	   /* Clear the hash table.					     */
/*______*/           if (RunningCode >= ZL_MAX_CODE)
/*______*/           { /* Time to do some clearance: */
/*______*/              if (compress_output(out_file,ClearCode) == GIF_ERROR)
/*______*/                 return GIF_ERROR;  //RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
/*______*/              RunningCode = EOFCode + 1;
/*______*/              RunningBits = BitsPerPixel + 1;
/*______*/              MaxCode1 = 1 << RunningBits;
/*______*/              hash_table.clear();
/*______*/           }
/*______*/           else
/*______*/           { /* Put this unique key with its relative Code in hash table: */
/*______*/              hash_table.insert(NewKey, RunningCode++);
/*______*/           }
/*______*/        }
/*______*/    }
/*______*/    /* Preserve the current state of the compression algorithm: */
/*______*/    CrntCode = local_CrntCode;
/*______*/  
/*______*/    if (PixelCount == 0)
/*______*/    {
/*______*/        /* We are done - output last Code and flush output buffers: */
/*______*/        if (compress_output(out_file, local_CrntCode) == GIF_ERROR)
/*______*/           return GIF_ERROR; // RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
/*______*/  
/*______*/        if (compress_output(out_file, EOFCode) == GIF_ERROR)
/*______*/           return GIF_ERROR; // RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
/*______*/        if (compress_output(out_file,FLUSH_OUTPUT) == GIF_ERROR)
/*______*/           return GIF_ERROR; //  RGIFERROR = E_GIF_ERR_DISK_IS_FULL;
/*______*/    }
/*______*/    return GIF_OK;
/*______*/  };
/*______*/  
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // *   The LZ compression output routine:					      *
/*______*/  // *   This routine is responsable for the compression of the bit stream into    *
/*______*/  // * 8 bits (bytes) packets.						      *
/*______*/  // *   Returns GIF_OK if written succesfully.				      *
/*______*/  // ******************************************************************************/
/*______*/  int LZ_compresser::compress_output(FILE *out_file,int Code)
/*______*/  {
/*______*/     int retval = GIF_OK;
/*______*/  
/*______*/     if (Code == FLUSH_OUTPUT)
/*______*/     {
/*______*/       while (CrntShiftState > 0)
/*______*/       { /* Get Rid of what is left in DWord, and flush it. */
/*______*/         if (buffered_output(out_file,Buf,CrntShiftDWord & 0xff) == GIF_ERROR)
/*______*/  		    retval = GIF_ERROR;
/*______*/  	    CrntShiftDWord >>= 8;
/*______*/  	    CrntShiftState -= 8;
/*______*/  	   }
/*______*/        CrntShiftState = 0;			   /* For next time. */
/*______*/        if (buffered_output(out_file, Buf, FLUSH_OUTPUT) == GIF_ERROR)
/*______*/           retval = GIF_ERROR;
/*______*/     }
/*______*/     else
/*______*/     {  CrntShiftDWord |= ((long) Code) << CrntShiftState;
/*______*/           CrntShiftState += RunningBits;
/*______*/           while (CrntShiftState >= 8)
/*______*/           {  /* Dump out full bytes: */
/*______*/              if (buffered_output(out_file, Buf, CrntShiftDWord & 0xff) == GIF_ERROR)
/*______*/                 retval = GIF_ERROR;
/*______*/              CrntShiftDWord >>= 8;
/*______*/              CrntShiftState -= 8;
/*______*/           }
/*______*/     };
/*______*/  
/*______*/     /* If code cannt fit into RunningBits bits, must raise its size. Note */
/*______*/     /* however that codes above 4095 are used for special signaling.      */
/*______*/     if (RunningCode >= MaxCode1 && Code <= 4095)
/*______*/       MaxCode1 = 1 << ++RunningBits;
/*______*/  
/*______*/     return retval;
/*______*/  };
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // *   This routines buffers the given characters until 255 characters are ready *
/*______*/  // * to be output. If Code is equal to -1 the buffer is flushed (EOF).	      *
/*______*/  // *   The buffer is Dumped with first byte as its size, as GIF format requires. *
/*______*/  // *   Returns GIF_OK if written succesfully.				      *
/*______*/  // ******************************************************************************/
/*______*/  int LZ_compresser::buffered_output(FILE *out_file, byte *Buf, int c)
/*______*/  {
/*______*/     if (c == FLUSH_OUTPUT)
/*______*/     {  // Flush everything out.
/*______*/        if (Buf[0] != 0 && fwrite(Buf, 1, Buf[0]+1, out_file) != Buf[0] + 1)
/*______*/           return GIF_ERROR;
/*______*/        // Mark end of compressed data, by an empty block (see GIF doc):
/*______*/        fputc(0,out_file);
/*______*/     }
/*______*/     else
/*______*/     {
/*______*/        if (Buf[0] == 255)
/*______*/        { // Dump out this buffer - it is full:
/*______*/           if (fwrite(Buf, 1, Buf[0] + 1, out_file) != Buf[0] + 1)
/*______*/              return GIF_ERROR;
/*______*/           Buf[0] = 0;
/*______*/        };
/*______*/        Buf[++Buf[0]] = c;
/*______*/     };
/*______*/     return GIF_OK;
/*______*/  };
/*______*/  
/*______*/  
/*______*/  
/*______*/  ///////////////////////////////////////////////////////
/*______*/  
/*______*/  void GIF_control_extension::read(FILE *in_file)
/*______*/  {
/*______*/    // extension introducer and graphic control label
/*______*/    // will already have been read in order to determine
/*______*/    // that this is a graphic control extension.
/*______*/    fgetc(in_file);  // block size is not used, should be 4
/*______*/  
/*______*/    byte packed = fgetc(in_file);
/*______*/    disposal_method = (packed & 0x1C) >> 2;
/*______*/    user_input = (packed & 0x02) != 0;
/*______*/    use_transparent_color = packed & 0x01;
/*______*/  
/*______*/    delay_time = GIF_read_word(in_file);
/*______*/    transparent_color = fgetc(in_file);
/*______*/    fgetc(in_file);  // block terminator, should be 0
/*______*/  
/*______*/    enabled = true;
/*______*/  };
/*______*/  
/*______*/  void GIF_control_extension::write(FILE *out_file)
/*______*/  {
/*______*/    fputc(GIF_extension_introducer,out_file);
/*______*/    fputc(GIF_graphic_control_extension,out_file);
/*______*/    fputc(4,out_file); // size of the control block
/*______*/    byte packed
/*______*/    = ((byte)disposal_method << 2)
/*______*/    | (user_input ? 0x02 : 0x00)
/*______*/    | (use_transparent_color ? 0x01 : 0x00);
/*______*/  
/*______*/    fputc(packed,out_file);
/*______*/    GIF_write_word(out_file,delay_time);
/*______*/    fputc(transparent_color,out_file);
/*______*/    fputc(0,out_file);
/*______*/  };
/*______*/
/*______*/
/*______*/  ///////////////////////////////////////////////////////
/*______*/  GIF_image::GIF_image(FILE *in_file,color_map *i_global_color_table
/*______*/    , GIF_control_extension i_graphic_control)
/*______*/  :left(0)
/*______*/  ,top(0)
/*______*/  ,width(0)
/*______*/  ,height(0)
/*______*/  ,local_color_table(0)
/*______*/  ,global_color_table(i_global_color_table)
/*______*/  ,interlaced(0)
/*______*/  ,matrix(0)
/*______*/  ,modified(0)
/*______*/  ,graphic_control(i_graphic_control)
/*______*/  {
/*______*/
/*______*/    read(in_file);
/*______*/    // color_table = must follow read
/*______*/    color_table = local_color_table ? local_color_table : global_color_table;
/*______*/  };
/*______*/
/*______*/  GIF_image::GIF_image(unsigned int i_width, unsigned int i_height,
/*______*/           unsigned int i_left ,unsigned int i_top )
/*991115*/     :CORN_container_item()
/*______*/     ,width(i_width)
/*______*/     ,height(i_height)
/*______*/     ,left(i_left)
/*______*/     ,top(i_top)
/*______*/     ,local_color_table(0)
/*______*/  	,global_color_table(0)
/*______*/  	,color_table(0)
/*______*/     ,interlaced(0)
/*______*/     ,matrix(0)
/*______*/     ,modified(1)
/*______*/     { matrix = (byte **)malloc(height*sizeof(byte **));
/*______*/       for (int i = 0; i < height; i++)
/*______*/         matrix[i] = (byte *)malloc(width*sizeof(byte));
/*______*/        clear();
/*______*/     };
/*______*/
/*______*/  void GIF_image::write(FILE *out_file)
/*______*/  {
/*______*/     if (graphic_control.enabled)
/*______*/        graphic_control.write(out_file);
/*______*/
/*______*/     fputc(GIF_image_separator,out_file);
/*______*/
/*______*/  	GIF_write_word(out_file,left);
/*______*/  	GIF_write_word(out_file,top);
/*______*/  	GIF_write_word(out_file,width);
/*______*/  	GIF_write_word(out_file,height);
/*______*/
/*______*/  	byte packed
/*______*/     = (local_color_table ? 0x80 : 0x00)
/*______*/     | (interlaced ? 0x40 : 0x00)
/*______*/     | (local_color_table && local_color_table->sorted ? 0x02 : 0x00)
/*______*/     | (local_color_table ? (local_color_table->bits_per_pixel -1) : 0x00);
/*______*/
/*______*/     fputc(packed,out_file);
/*______*/  
/*______*/  	if (local_color_table)
/*______*/  		local_color_table->write(out_file);
/*______*/  
/*______*/  	LZ_compresser *compresser = new LZ_compresser
/*______*/     (out_file,color_table->bits_per_pixel
/*______*/     ,((long) width * (long) height));  // Reset decompress algorithm parameters.
/*______*/
/*______*/  	int row;
/*______*/  	for (row = 0; row < height; row++)
/*______*/     { kbhit();  // let easywin multitask
/*______*/  //     cout << '\r' << row; for debugging
/*______*/       compresser->PixelCount -= width;
/*______*/
/*______*/  	  if (matrix[row])
/*______*/          compresser->compress_line(out_file,matrix[row],width);
/*______*/     };
/*______*/
/*______*/     delete compresser;
/*______*/  };
/*______*/  
/*______*/  GIF_image::~GIF_image()
/*______*/  {
/*______*/    int row;
/*______*/  
/*______*/    for (row = 0; row < height; row++)
/*______*/       free (matrix[row]);
/*______*/    free (matrix);
/*______*/    matrix = 0;
/*______*/  
/*______*/    if (local_color_table)
/*______*/      delete local_color_table;
/*______*/  };
/*______*/  
/*______*/  void GIF_image::read(FILE *in_file)
/*______*/  {
/*______*/  
/*______*/  	left 	 = GIF_read_word(in_file);
/*______*/  	top 	 = GIF_read_word(in_file);
/*______*/  	width  = GIF_read_word(in_file);
/*______*/  	height = GIF_read_word(in_file);
/*______*/  
/*______*/  	byte packed = fgetc(in_file);
/*______*/  
/*______*/  	byte bits_per_pixel =(packed & 0x07) + 1;
/*______*/  	int color_table_size = (1 << bits_per_pixel);
/*______*/  
/*______*/  	interlaced = (packed & 0x40);
/*______*/  	bool has_local_color_table = (packed  & 0x80);
/*______*/  
/*______*/  	if (has_local_color_table)
/*______*/  		color_table = local_color_table = new color_map(in_file);
/*______*/     else
/*______*/        local_color_table = 0;
/*______*/  
/*______*/  	long PixelCount = (long) width * (long) height;
/*______*/  
/*______*/  	LZ_decompresser *decompresser = new LZ_decompresser(in_file);  // Reset decompress algorithm parameters.
/*______*/  
/*______*/  	matrix = (byte **)malloc(sizeof(byte *) * height);
/*______*/  	int row;
/*______*/  	for (row = 0; row < height; row++)
/*______*/  	{
/*______*/  	  matrix[row] = (byte *)malloc(sizeof(byte)*width);
/*______*/       kbhit(); // let easywin multitask.
/*______*/  	  if (matrix[row])
/*______*/          decompresser->decompress_line(in_file,matrix[row],width);
/*______*/       else
/*______*/       {
/*______*/          cerr << "Unable to allocate row:" << row << endl;
/*______*/          break;
/*______*/       };
/*______*/  	};
/*______*/  
/*______*/     delete decompresser;
/*______*/  };
/*______*/  
/*______*/  
/*______*/  
/*______*/  void GIF_image::line(int c1,int r1,int c2,int r2,byte color)
/*______*/  {
/*______*/  #ifdef DDA
/*______*/    int error = 0;
/*______*/    int deltax = c2 - c1;
/*______*/    int deltay = r2 - r1;
/*______*/  
/*______*/    if (deltay < 0)
/*______*/    {
/*______*/      int h_c1 = c1;
/*______*/      c1 = c2;
/*______*/      c2 = h_c1;
/*______*/      int h_r1 = r1;
/*______*/      r1 = r2;
/*______*/      r2 = h_r1;
/*______*/      deltay=-deltay;
/*______*/      deltax=-deltax;
/*______*/    };
/*______*/  
/*______*/    int c = c1;
/*______*/    int r = r1;
/*______*/    int i;
/*______*/    if (deltax >= 0)
/*______*/    {
/*______*/       if (deltax >= deltay)
/*______*/       {  for (i = 1; i < deltax; i++)
/*______*/              if (error < 0)
/*______*/              { c+= 1;
/*______*/                 point(c,r,color);
/*______*/                 error += deltay;
/*______*/              }
/*______*/              else
/*______*/              { c+= 1;
/*______*/                 r+= 1;
/*______*/                 point(c,r,color);
/*______*/                 error  += deltay - deltax;
/*______*/              };
/*______*/       }
/*______*/       else
/*______*/       {
/*______*/         for (i = 1 ; i < deltay;i++)
/*______*/           if (error < 0)
/*______*/           {
/*______*/              c+= 1;
/*______*/              r += 1;
/*______*/              point(c,r,color);
/*______*/              error += deltay - deltax;
/*______*/           }
/*______*/           else
/*______*/           { r += 1;
/*______*/             point(c,r,color);
/*______*/             error -= deltax;
/*______*/           }
/*______*/       }
/*______*/    }
/*______*/    else
/*______*/      if (deltax >= deltay)
/*______*/      {
/*______*/        for (i= 1; i< deltax; i++)
/*______*/           if (error < 0)
/*______*/           { c-= 1;
/*______*/             point(c,r,color);
/*______*/             error += deltay;
/*______*/           }
/*______*/           else
/*______*/           { c -= 1;
/*______*/             r -= 1;
/*______*/             point(c,r,color);
/*______*/             error += deltax+deltay;
/*______*/           };
/*______*/      }
/*______*/      else
/*______*/        for (i = 1; i < deltay ; i++)
/*______*/              if (error < 0)
/*______*/              { c -= 1;
/*______*/                r -= 1;
/*______*/                point (c,r,color);
/*______*/                error += deltax + deltay;
/*______*/              }
/*______*/              else
/*______*/              { r += 1;
/*______*/                point(c,r,color);
/*______*/                error += deltax;
/*______*/              };
/*______*/      point(c2,r2,color);
/*______*/  
/*______*/  #else
/*______*/  
/*______*/     if (r2 < r1)
/*______*/     {
/*______*/       int h_c1 = c1;
/*______*/       c1 = c2;
/*______*/       c2 = h_c1;
/*______*/       int h_r1 = r1;
/*______*/       r1 = r2;
/*______*/       r2 = h_r1;
/*______*/     };
/*______*/  
/*______*/     int deltax = c2 - c1;
/*______*/     int deltay = r2 - r1;
/*______*/  
/*______*/     if (deltay == 0)
/*______*/        for (int c = c1; c <= c2; c++)
/*______*/           point(c,r1,color);
/*______*/     else
/*______*/        if (deltax == 0)
/*______*/           for (int r = r1; r <= r2; r++)
/*______*/              point(c1,r,color);
/*______*/     else
/*______*/     if ((deltax > deltay))
/*______*/     {
/*______*/       float slope = (float)deltay / (float)deltax;
/*______*/       for (int c = 0; c < deltax; c++)
/*______*/       {
/*______*/         int r = (float)c * slope;
/*______*/         point(c1+c,r1+r,color);
/*______*/       };
/*______*/     }
/*______*/     else
/*______*/     {
/*______*/       float slope = (float)deltax / (float)deltay;
/*______*/       for (int r = 0; r < deltay; r++)
/*______*/       {
/*______*/         int c = (float)r * slope;
/*______*/         point(c1+c,r1+r,color);
/*______*/       };
/*______*/     }
/*______*/  
/*______*/  #endif
/*______*/  };
/*______*/  
/*______*/  void GIF_image::recolor(byte new_colors[])
/*______*/  {
/*______*/    for (int i = 0; i < height; i++)
/*______*/  	  for (int j = 0; j < width; j++)
/*______*/  	  { byte old_color = matrix[i][j];
/*______*/         if (old_color > 255) // this shouldn't happen
/*______*/            old_color = 0;
/*______*/         byte new_color = new_colors[old_color];
/*______*/     
/*______*/  // 		 if (new_color == 255) // The color has been removed, use an adjacent color
/*______*/  // 			new_color = j ? matrix[i][j-1] : matrix[i][j+1];
/*______*/  
/*______*/  		 point(j,i,new_color);
/*______*/  	  }
/*______*/  };
/*______*/  
/*______*/
/*______*/  void GIF_image::overlay_image(GIF_image &image_to_overlay,int col,int row)
/*______*/  { // static to save stack;
/*______*/    static byte map_colors_1[256];
/*______*/    static byte map_colors_2[256];
/*______*/  
/*______*/  
/*______*/    color_table->union_colors(image_to_overlay.color_table,map_colors_1,map_colors_2);
/*______*/  
/*______*/    //recolor(map_colors_1);
/*______*/  
/*______*/    image_to_overlay.recolor(map_colors_2);
/*______*/  
/*______*/    int i;
/*______*/    int j;
/*______*/    for (i = 0; i < image_to_overlay.height; i++)
/*______*/  	  for (j = 0; j < image_to_overlay.width; j++)
/*______*/  	  {
/*______*/  		 matrix[i+row+image_to_overlay.top][j+col+image_to_overlay.left]
/*______*/         = image_to_overlay.matrix[i][j];
/*______*/  	  };
/*______*/  };
/*______*/  
/*______*/  static bool deleted_colors[256];
/*______*/  
/*______*/  void color_map::remove_duplicate_colors(byte recolor[])
/*______*/  {
/*______*/    int i,j;
/*______*/    for (i = 0; i < 256; i++)
/*______*/       recolor[i] = i;
/*______*/    int new_num_colors = num_colors;
/*______*/    new_num_colors = 255;
/*______*/    for (i = 0 ;i < 255; i++)
/*______*/    {
/*______*/       if (deleted_colors[i])
/*______*/       {  new_num_colors -= 1;
/*______*/          for (j = i; j <  255; j++)
/*______*/          { red[j]   = red[j+1];
/*______*/            green[j] = green[j+1];
/*______*/            blue[j]  = blue[j+1];
/*______*/            if (recolor[j] > i)
/*______*/               recolor[j] = recolor[j] -1;
/*______*/
/*______*/            deleted_colors[j] = deleted_colors[j+1];
/*______*/            deleted_colors[255] = 0;
/*______*/  
/*______*/          };
/*______*/          i -= 1;
/*______*/       };
/*______*/    };
/*______*/    num_colors = new_num_colors;
/*______*/  };
/*______*/  
/*______*/  void color_map::quantize(int max_colors, byte recolor[])
/*______*/  {
/*______*/     int i,j;
/*______*/  
/*______*/  //     not used
/*______*/  //    static long frequency[256];
/*______*/  //    for (i = 0; i < 256; i++)
/*______*/  //      frequence[i] = 0;
/*______*/  //
/*______*/  //    for (i = 0; i < height; i++)
/*______*/  //      for (j = 0; j < width ; j++)
/*______*/  //         frequency[matrix[i][j]] += 1;
/*______*/  
/*______*/  
/*______*/     for (i = 0; i < 256; i++)
/*______*/     {
/*______*/        deleted_colors[i] = 0;
/*______*/        recolor[i] = i;
/*______*/     };
/*______*/     int num_deleted = 0;
/*______*/     int tolerance = 10;
/*______*/     while ((num_colors - num_deleted) > max_colors)
/*______*/     {
/*______*/        for (i = 0; (i < 256) ; i++)
/*______*/        if (!deleted_colors[i])
/*______*/        {
/*______*/           byte min_dr = 255; byte min_dg = 255; byte min_db = 255;
/*______*/           int min_index = 255;
/*______*/           for (j = i+1; j < 256; j++)
/*______*/           {
/*______*/              if (i != j)
/*______*/              { byte dr = abs(red[j] - red[i]);
/*______*/                byte dg = abs(green[j] - green[i]);
/*______*/                byte db = abs(blue[j] - blue[i]);
/*______*/                if ((dr < min_dr) && (dg < min_dg) && (db < min_db) &&
/*______*/                    (dr < tolerance) && (dg < tolerance) && (db < tolerance)
/*______*/                    && (!deleted_colors[j]))
/*______*/                {
/*______*/                   min_dr = dr; min_dg = dg; min_db = db;
/*______*/                   min_index = j;
/*______*/                };
/*______*/              };
/*______*/           };
/*______*/           if (min_index < 255)
/*______*/           {
/*______*/             deleted_colors[min_index] = 1;
/*______*/             recolor[min_index] = i;
/*______*/           }
/*______*/        };
/*______*/        tolerance += 1;
/*______*/        num_deleted = 0;
/*______*/        for (i = 0; i < 256; i++)
/*______*/           num_deleted += deleted_colors[i];
/*______*/     };
/*______*/  };
/*______*/  
/*______*/  void GIF_image::quantize(int max_colors = 128)
/*______*/  {
/*______*/     static byte new_colors[256];
/*______*/     color_table->quantize(max_colors,new_colors);
/*______*/     recolor(new_colors);
/*______*/  
/*______*/     color_table->remove_duplicate_colors(new_colors);
/*______*/     recolor(new_colors);
/*______*/  
/*______*/     color_table->num_colors = max_colors;
/*______*/  };
/*______*/  
/*______*/  void GIF_image::set_torus(int col, int row,byte color)
/*______*/  {
/*______*/     // This function set the color at x,y
/*______*/     // if X is < 0 or X > width, the dimensions are wrapped around
/*______*/  
/*______*/     if (row < 0)       row = height + row;
/*______*/     if (row >= height) row = row - height;
/*______*/     if (col < 0)       col = width + col;
/*______*/     if (col >= width)  col = col - width;
/*______*/  
/*______*/     matrix[row][col] = color;
/*______*/  };
/*______*/  
/*______*/  byte GIF_image::get_torus(int col, int row)
/*______*/  {
/*______*/     // This function returns the color at x,y
/*______*/     // if X is < 0 or X > width, the dimensions are wrapped around
/*______*/
/*______*/     if (row < 0)       row = height + row;
/*______*/     if (row >= height) row = row - height;
/*______*/     if (col < 0)       col = width + col;
/*______*/     if (col >= width)  col = col - width;
/*______*/  
/*______*/     return matrix[row][col];
/*______*/  };
/*______*/  
/*______*/  
/*______*/  ///////////////////////////////////////////////////////
/*______*/  
/*______*/  GIF::GIF(const char *i_filename)
/*______*/  :filename(i_filename)
/*______*/  ,screen_width(0)
/*______*/  ,screen_height(0)
/*______*/  ,background_color(0)
/*______*/  ,pixel_aspect_ratio(0)
/*______*/  ,global_color_table(0)
/*991115*/  ,images()
//991115obs ,current_image(0)
//991115obs ,num_images(0)
/*______*/  ,last_graphic_control()
/*______*/  ,file(0)
/*______*/  {
//991115obs 	for (int i = 0; i < MAX_IMAGES;i++)
//991115obs 		images[i] = 0;
/*______*/     read();
/*______*/  };
/*______*/  
/*______*/  // Output file
/*______*/  GIF::GIF(const char *i_filename,unsigned int i_screen_width ,unsigned int i_screen_height )
/*______*/  :filename(i_filename)
/*______*/  ,screen_height(i_screen_height)
/*______*/  ,screen_width(i_screen_width)
/*______*/  ,background_color(0)
/*______*/  ,pixel_aspect_ratio(0)
/*______*/  ,global_color_table(0)
/*991115*/  ,images()
//991115obs ,num_images(0)
//991115obs ,current_image(0)
/*______*/  ,file(0)
/*______*/  {
/*______*/    file = fopen(i_filename,"wb");
/*______*/  };
/*______*/
/*______*/  int GIF_skip_extension_block(FILE *in_file)
/*______*/  {
/*______*/      byte extension_length = fgetc(in_file);
/*______*/      if (extension_length)
/*______*/      { byte buf[256];
/*______*/        if (fread(&buf, 1, extension_length,in_file) != extension_length)
/*______*/           return GIF_ERROR;
/*______*/        buf[extension_length] = 0;
/*______*/  //      cout << buf << endl; for debugging
/*______*/      };
/*______*/      return GIF_OK;
/*______*/  };
/*______*/  
/*______*/  int GIF_skip_comment(FILE *in_file)
/*______*/  {
/*______*/      byte extension_code = fgetc(in_file);
/*______*/      GIF_skip_extension_block(in_file);
/*______*/  };
/*______*/
/*______*/  void GIF::read()
/*______*/  {
/*______*/    FILE *in_file = fopen(filename.c_str(),"rb");
/*______*/    if (in_file)
/*______*/    {
/*______*/
/*______*/    char gif_version[7];
/*______*/    fread(&gif_version,sizeof(char),6,in_file);
/*______*/    gif_version[6] = 0;
/*______*/    // Check here for valid gif header
/*______*/
/*______*/    // read screen width
/*______*/    screen_width  = GIF_read_word(in_file);
/*______*/    screen_height = GIF_read_word(in_file);
/*______*/
/*______*/    byte packed_field  = fgetc(in_file);
/*______*/
/*______*/    byte color_resolution = (((packed_field & 0x70) + 1) >> 4) + 1;
/*______*/    byte bits_per_pixel = (packed_field & 0x07) + 1;
/*______*/    bool global_color_map_enabled = packed_field & 0x80;
/*______*/
/*______*/    background_color   = fgetc(in_file);
/*______*/    pixel_aspect_ratio = fgetc(in_file);
/*______*/
/*______*/    if (global_color_map_enabled)
/*______*/    {
/*______*/  	  global_color_table = new color_map(color_resolution,bits_per_pixel);
/*______*/  	  global_color_table->read(in_file);
/*______*/    }
/*______*/    else
/*______*/       global_color_table = 0;
/*______*/
/*______*/    while (!feof(in_file))
/*______*/    {
/*______*/  	 byte record_type = fgetc(in_file);
/*______*/  	 switch(record_type)
/*______*/  	 {
/*______*/  		case GIF_image_separator :  // ','
/*______*/  		   images.append(new GIF_image(in_file,global_color_table,last_graphic_control));
//991115obs 			 current_image = images[num_images] = new GIF_image(in_file,global_color_table,last_graphic_control);
//991115obs 			 num_images += 1;
/*______*/            last_graphic_control.enabled = false;
/*______*/  		break;
/*______*/  		case GIF_extension_introducer : // '!'
/*______*/        {
/*______*/            byte extension_code = fgetc(in_file);
/*______*/            switch (extension_code)
/*______*/            { case GIF_graphic_control_extension :
/*______*/                 last_graphic_control.read(in_file);
/*______*/              break;
/*______*/              case GIF_application_extension :
/*______*/              {  byte length = fgetc(in_file);
/*______*/                 char extension_label[50];
/*______*/                 fread (&extension_label,1,length,in_file);
/*______*/                 byte block_length = fgetc(in_file);
/*______*/                 if (strncmp(extension_label,"NETSCAPE2.0",block_length) == 0)
/*______*/                 {  fgetc(in_file); // Should be 1
/*______*/                    animation_iterations = GIF_read_word(in_file);
/*______*/                 }
/*______*/                 else // I don't know what the extension is so just throw it away.
/*______*/                 {  char *buffer = (char *)malloc(block_length +1);
/*______*/                    fread(&buffer,1,block_length,in_file);
/*______*/                    free(buffer);
/*______*/                 }
/*______*/                 fgetc(in_file); // should be 0 the block terminator
/*______*/              }
/*______*/              break;
/*______*/              default :
/*______*/                GIF_skip_extension_block(in_file);
/*______*/                byte block_terminator = fgetc(in_file);
/*______*/              break;
/*______*/            };
/*______*/  			 // num_extensions += 1;
/*______*/  			 // extensions[num_extensions] = new extension(in_file);
/*______*/        }
/*______*/  		break;
/*______*/  		case GIF_comment_extension :
/*______*/           GIF_skip_comment(in_file);
/*______*/  		break;
/*______*/  		case GIF_trailer : // ';'
/*______*/  			// TERMINATE_RECORD_TYPE;
/*______*/           return;
/*______*/  		default:
/*______*/  //		 *Type = UNDEFINED_RECORD_TYPE;
/*______*/  //		 RGIFERROR = D_GIF_ERR_WRONG_RECORD;
/*______*/  		 return; // GIF_ERROR;
/*______*/  	 };
/*______*/    };
/*______*/    fclose(in_file);
/*______*/    };
/*______*/  };
/*______*/  
/*______*/  void GIF::write_global()
/*______*/  {
/*______*/    char gif_version[7] = "GIF89a";
/*______*/    fwrite(&gif_version,1,6,file);
/*______*/
/*______*/    // read screen width
/*______*/    GIF_write_word(file,screen_width);
/*______*/    GIF_write_word(file,screen_height);
/*______*/
/*______*/    byte has_color_table =  global_color_table ? 0x80 : 0x00;
/*______*/    byte color_res_bits = (global_color_table ? ((global_color_table->color_resolution - 1) << 4) : 0x00);
/*______*/    byte color_table_sorted = ((global_color_table && global_color_table->sorted) ? 0x04 : 0x00);
/*______*/    byte color_table_bits_per_pixel = (global_color_table ? (global_color_table->bits_per_pixel -1) : 0x00);
/*______*/
/*______*/    byte packed_field = has_color_table | color_res_bits | color_table_sorted | color_table_bits_per_pixel;
/*______*/
/*______*/    fputc(packed_field,file);
/*______*/
/*______*/    fputc(background_color,file);
/*______*/    fputc(pixel_aspect_ratio,file);
/*______*/
/*______*/    if (global_color_table)
/*______*/  	  global_color_table->write(file);
/*______*/
/*______*/    // Animation control block follows the global color table
/*______*/    if (animation)
/*______*/       write_animation_control_block();
/*______*/  };
/*______*/
/*______*/  void GIF::write_close()
/*______*/  {
/*______*/    fputc(GIF_trailer,file);
/*______*/    fclose(file);
/*______*/    file = 0;
/*______*/  };
/*______*/
/*______*/  void GIF::write_it()
/*______*/  {
/*______*/    write_global();
/*______*/
/*991115*/     for (GIF_image *image = (GIF_image *)images.move_to_head()
/*991115*/         ;image
/*991115*/         ;image = (GIF_image *)images.move_to_next())
/*991115*/     {
/*991115*/        image->write(file);
/*991115*/     };
//991115obs   int i;
//991115obs   for (i = 0; i < num_images; i++)
//991115obs   { images[i]->write(file);
//991115obs   };
/*______*/    write_close();
/*______*/  };
/*______*/  
/*______*/  void GIF::write_animation_control_block()
/*______*/  {
/*______*/    fputc(GIF_extension_introducer,file);
/*______*/    fputc(GIF_application_extension,file);
/*______*/    fputc(0x0B,file); // animation extension length
/*______*/    char netscape2_0[11] = "NETSCAPE2.0";
/*______*/    fwrite(&netscape2_0,1,11,file);
/*______*/    fputc(0x03,file); // length of animation block
/*______*/    fputc(0x01,file);
/*______*/    GIF_write_word(file, animation_iterations);
/*______*/    fputc(0x00,file);
/*______*/  };
/*______*/  
/*______*/  void GIF::write_current_image()
/*______*/  {
/*991115*/     GIF_image *current_image = (GIF_image *)images.current();
/*991115*/     if (current_image)
/*______*/        current_image->write(file);
/*______*/  };
/*______*/  
/*______*/  GIF::~GIF()
/*______*/  {
/*______*/    if (global_color_table) delete global_color_table;
/*991115*/     images.delete_all();
//991115obs   int i;
//991115obs   for (i = 0; i < num_images; i++)
//991115obs      delete images[i];
//991115obs   current_image = 0;  // Don't dispose current image!
/*______*/    if (file) fclose(file);
/*______*/  }
/*______*/  ////////////////////////////////////////////////////////////
/*______*/  
/*______*/  
/*______*/  #define PROGRAM_NAME	"GIF_LIBRARY"
/*______*/  
/*______*/  /* #define  DEBUG_HIT_RATE    Debug number of misses per hash Insert/Exists. */
/*______*/  
/*______*/  #ifdef	DEBUG_HIT_RATE
/*______*/  static long NumberOfTests = 0,
/*______*/  	    NumberOfMisses = 0;
/*______*/  #endif
/*______*/  
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // * Initialize HashTable - allocate the memory needed and clear it.	      *
/*______*/  // ******************************************************************************/
/*______*/  GIF_hash_table::GIF_hash_table()
/*______*/  {
/*______*/     clear();
/*______*/  };
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // * Routine to clear the HashTable to an empty state.			      *
/*______*/  // * This part is a little machine depended. Use the commented part otherwise.   *
/*______*/  // ******************************************************************************/
/*______*/  void GIF_hash_table::clear()
/*______*/  {
/*______*/     memset(HTable, 0xFF, HT_SIZE * sizeof(long));
/*______*/  };
/*______*/
/*______*/  // /******************************************************************************
/*______*/  // * Routine to insert a new Item into the HashTable. The data is assumed to be  *
/*______*/  // * new one.								      *
/*______*/  // ******************************************************************************/
/*______*/  void GIF_hash_table::insert(unsigned long Key, int Code)
/*______*/  {
/*______*/      int HKey = KeyItem(Key);
/*______*/  
/*______*/  #ifdef DEBUG_HIT_RATE
/*______*/  	NumberOfTests++;
/*______*/  	NumberOfMisses++;
/*______*/  #endif /* DEBUG_HIT_RATE */
/*______*/  
/*______*/      while (HT_GET_KEY(HTable[HKey]) != 0xFFFFFL)
/*______*/      {
/*______*/  #ifdef DEBUG_HIT_RATE
/*______*/  	    NumberOfMisses++;
/*______*/  #endif /* DEBUG_HIT_RATE */
/*______*/        HKey = (HKey + 1) & HT_KEY_MASK;
/*______*/      };
/*______*/      HTable[HKey] = HT_PUT_KEY(Key) | HT_PUT_CODE(Code);
/*______*/  }
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // * Routine to test if given Key exists in HashTable and if so returns its code *
/*______*/  // * Returns the Code if key was found, -1 if not.				      *
/*______*/  // ******************************************************************************/
/*______*/  int GIF_hash_table::exists(unsigned long Key)
/*______*/  {
/*______*/     int HKey = KeyItem(Key);
/*______*/  
/*______*/     unsigned long HTKey;
/*______*/  
/*______*/  
/*______*/  #ifdef DEBUG_HIT_RATE
/*______*/     NumberOfTests++;
/*______*/  	NumberOfMisses++;
/*______*/  #endif /* DEBUG_HIT_RATE */
/*______*/  
/*______*/     while
/*______*/      ((HTKey = HT_GET_KEY(HTable[HKey])) != 0xFFFFFL)
/*______*/      //&& (HKey < (HT_SIZE-2)))
/*______*/     {
/*______*/         kbhit();
/*______*/  #ifdef DEBUG_HIT_RATE
/*______*/  	    NumberOfMisses++;
/*______*/  #endif /* DEBUG_HIT_RATE */
/*______*/        if (Key == HTKey)
/*______*/           return HT_GET_CODE(HTable[HKey]);
/*______*/        HKey = (HKey + 1) & HT_KEY_MASK;
/*______*/     };
/*______*/  
/*______*/     return -1;
/*______*/  };
/*______*/  
/*______*/  // /******************************************************************************
/*______*/  // * Routine to generate an HKey for the hashtable out of the given unique key.  *
/*______*/  // * The given Key is assumed to be 20 bits as follows: lower 8 bits are the     *
/*______*/  // * new postfix character, while the upper 12 bits are the prefix code.	      *
/*______*/  // * Because the average hit ratio is only 2 (2 hash references per entry),      *
/*______*/  // * evaluating more complex keys (such as twin prime keys) does not worth it!   *
/*______*/  // ******************************************************************************/
/*______*/  int GIF_hash_table::KeyItem(unsigned long Item)
/*______*/  {
/*______*/      return ((Item >> 12) ^ Item) & HT_KEY_MASK;
/*______*/  }
/*______*/  
/*______*/  #ifdef	DEBUG_HIT_RATE
/*______*/  // /******************************************************************************
/*______*/  // * Debugging routine to print the hit ratio - number of times the hash table   *
/*______*/  // * was tested per operation. This routine was used to test the KeyItem routine *
/*______*/  // ******************************************************************************/
/*______*/  void GIF_hash_table::PrintHitRatio(void)
/*______*/  {
/*______*/      printf("Hash Table Hit Ratio is %ld/%ld = %ld%%.\n",
/*______*/  	NumberOfMisses, NumberOfTests,
/*______*/  	NumberOfMisses * 100 / NumberOfTests);
/*______*/  }
/*______*/  #endif	/* DEBUG_HIT_RATE */
/*______*/  
/*______*/  ///////////////////////////////////////////////////////////////////////////////
/*______*/
/*______*/  void GIF_animation::commit_current_frame()
/*______*/  {  int r;       // should be iint16
/*______*/     int c;      // should be iint16
/*991115*/     GIF_image *current_image = (GIF_image *)images.current();
/*______*/        if (prev_frame)
/*______*/        {  // optimized curr_frame to prev_frame
/*______*/           // There are two optimizations that occur:
/*______*/           // 1. The new image reduced to only that rectangle of the
/*______*/           //    current images that is different from the previous frame.
/*______*/           // 2. Colours that are the same as the previous frame are replaced
/*______*/           //    buy transparent color.
/*______*/           int top_row_differs = screen_height;
/*______*/           int left_col_differs = screen_width;
/*______*/           int bottom_row_differs = 0;
/*______*/           int right_col_differs = 0;
/*______*/           byte transparent_color = current_image->graphic_control.transparent_color;
/*______*/           bool has_a_difference = false;
/*______*/           for ( r = 0; (r < screen_height); r ++)
/*______*/           {
/*______*/              for ( c = 0; (c < screen_width); c++)
/*______*/              {
/*______*/                 if (current_image->get_torus(c,r) !=
/*______*/                     prev_frame->get_torus(c,r))
/*______*/                 {
/*______*/                    top_row_differs = CORN_min(top_row_differs,r);
/*______*/                    bottom_row_differs = CORN_max(bottom_row_differs,r);
/*______*/                    left_col_differs = CORN_min(left_col_differs,c);
/*______*/                    right_col_differs = CORN_max(right_col_differs,c);
/*______*/                    has_a_difference = true;
/*______*/                 };
/*______*/              };
/*______*/           };
/*______*/
/*______*/  //         // temporarily disabling frame size optimizations
/*______*/  //         top_row_differs = 0;
/*______*/  //         bottom_row_differs = screen_height;
/*______*/  //         left_col_differs = 0;
/*______*/  //         right_col_differs = screen_width;
/*______*/  
/*______*/           if (has_a_difference)
/*______*/           {
/*______*/              int optimized_rows = bottom_row_differs - top_row_differs;
/*______*/              int optimized_cols = right_col_differs - left_col_differs;
/*______*/              GIF_image optimized(
/*______*/                 optimized_cols+1,optimized_rows+1,
/*______*/                 left_col_differs,top_row_differs
/*______*/                 );
/*______*/
/*______*/              optimized.global_color_table =
/*______*/              optimized.color_table =
/*______*/                 global_color_table;
/*______*/
/*______*/              optimized.graphic_control.disposal_method = GIF_control_extension::DONT_DISPOSE;
/*______*/              optimized.graphic_control.user_input = false;
/*______*/              optimized.graphic_control.use_transparent_color = true;
/*______*/              optimized.graphic_control.transparent_color = 0;
/*______*/              optimized.graphic_control.enabled = true;
/*______*/              optimized.graphic_control.delay_time = current_image->graphic_control.delay_time;
/*______*/
/*______*/              int or = 0;
/*______*/              for ( r = top_row_differs; r <= bottom_row_differs; r ++)
/*______*/              {
/*______*/                 int oc = 0;
/*______*/                 for ( c = left_col_differs; c <= right_col_differs; c++)
/*______*/                 {
/*______*/                    byte curr_pix_color = current_image->get_torus(c,r);
/*______*/                    byte prev_pix_color = prev_frame->get_torus(c,r);
/*______*/
/*______*/                    optimized.point(oc,or,
/*______*/  //                  (curr_pix_color == prev_pix_color)
/*______*/  //                  ? transparent_color   temporarily disabled
/*______*/  //                  :
/*______*/                       curr_pix_color);
/*______*/                    oc++;
/*______*/                 };
/*______*/                 or ++;
/*______*/              };
/*______*/
/*______*/
/*______*/              // write optimized frame
/*______*/              GIF_image *hold_image = current_image;
/*______*/              current_image = &optimized;
/*______*/              write_current_image();
/*______*/              current_image = hold_image;   // At this point optimized is automatically disposed so we remove the reference
/*______*/           };
/*______*/        }
/*______*/        else
//991115obs          if (current_image) // check now down in write_current_image
/*______*/               write_current_image();
/*______*/
/*______*/        delete prev_frame;
/*______*/        prev_frame = current_image;
/*______*/        current_image = 0;
/*______*/  };
/*______*/
/*______*/  GIF_image &GIF_animation::new_frame(int16 delay_time)
/*______*/  {
/*______*/        commit_current_frame();
/*991115*/        GIF_image *
/*______*/           current_image = new GIF_image(screen_width,screen_height);
/*______*/
/*______*/        current_image->global_color_table =
/*______*/           current_image->color_table =
/*______*/              global_color_table;
/*______*/
/*______*/        // These image options are required to implement optimized animations
/*______*/        current_image->graphic_control.disposal_method = GIF_control_extension::DONT_DISPOSE;
/*______*/        current_image->graphic_control.user_input = false;
/*______*/        current_image->graphic_control.use_transparent_color = true;
/*______*/        current_image->graphic_control.transparent_color = 0;
/*______*/        current_image->graphic_control.enabled = true;
/*______*/        current_image->graphic_control.delay_time = delay_time;
/*______*/
/*______*/        return *current_image;
/*______*/  };
/*______*/
/*______*/  void GIF_image::clear(byte clear_color)
/*______*/  {
/*______*/     for (int row = 0; row < height ; row++)
/*______*/        for (int col = 0; col < width; col++)
/*______*/        {
/*______*/           matrix[row][col] = clear_color;
/*______*/        };
/*______*/  };

/*______*/  inline void GIF_image::point(int col,int row,byte color)
/*______*/  {
/*______*/     if ((row >= 0) && (row < height) && (col >= 0) && (col < width ))
/*______*/        matrix[row][col] = color;
/*______*/  };

