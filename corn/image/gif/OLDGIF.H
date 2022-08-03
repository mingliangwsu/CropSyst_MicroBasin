#ifndef CORN_GIF_H
#define CORN_GIF_H
/*

Roger Nelson  GIF class

  loosely based on giflib version 1.0 by Gershon Elber,  Jun 1989   *

  971228 Added GIF_animation class to simply animation generation.

*/

#include <stdio.h>
#include <corn/file_sys/file.h>
#include <corn/image/clrramp.h>
#include <corn/container/bilist.h>

// The following are for the hash table
#ifdef __MSDOS__
#include <io.h>
#include <alloc.h>
#include <sys\stat.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif /* __MSDOS__ */

#include <fcntl.h>
#include <string.h>


#define GIF_ERROR	0
#define GIF_OK		1


#define GIF_plain_text_extension       0x01
#define GIF_extension_introducer       0x21
#define GIF_image_separator            0x2C
#define GIF_trailer                    0x3B
#define GIF_graphic_control_extension  0xF9
#define GIF_comment_extension          0xFE
#define GIF_application_extension      0xFF

#define byte unsigned char

// The maximum number of images that
// can be stored in the image file.
//#define MAX_IMAGES 20

/*______*/  class color_map
/*______*/  {
/*______*/  
/*______*/  public:
/*______*/    byte color_resolution;
/*______*/    byte bits_per_pixel;
/*______*/  
/*______*/  public:
/*______*/  	int num_colors;
/*______*/  	byte red[256];
/*______*/  	byte green[256];
/*______*/  	byte blue[256];
/*______*/  
/*______*/  	bool sorted;
/*______*/  
/*______*/  public:
/*______*/  
/*______*/  	color_map(FILE *in_file){read(in_file);};
//	color_map(int i_num_colors);
/*______*/  	color_map(byte i_color_resolution,byte i_bits_per_pixel);
/*______*/
/*991115*/     color_map(CORN::Color_ramp &color_ramp);
/*______*/     // Create a color map given a color ramp.
/*______*/     // Color 0 is reserved for background color.
/*______*/     // If color ramp has move than 255 colors they will be quantized.
/*______*/
/*______*/  	void read(FILE *in_file);  // reads the color map from the GIF file.
/*______*/  	void write(FILE *out_file); // writes the color map to the GIF file.
/*______*/
/*______*/  	void sort(unsigned long count[],unsigned char change_to[]);
/*______*/  	// Count are the number of pixels in the image with the color of
/*______*/  	// the respective index.
/*______*/  	// change_to are the colors the respective index should be changed to
/*______*/  	// after doing the sort.
/*______*/  
/*______*/     void quantize(int max_colors, byte recolor[]);
/*______*/  	void union_colors(color_map *color_map_2,byte recolor1[],byte recolor2[]);
/*______*/     void remove_duplicate_colors(byte recolor[]);
/*______*/     int find(byte r, byte g, byte b);
/*______*/     void copy_from(color_map &map);
/*______*/
/*991220*/     inline void set_color(uint8 index, byte i_red,byte i_green, byte i_blue)
/*______*/     {  red[index]   = i_red;
/*______*/        green[index] = i_green;
/*______*/        blue[index]  = i_blue;
/*______*/     };
/*______*/  };

/*______*/  class GIF_control_extension
/*______*/  {
/*______*/  public:
/*______*/     enum Disposal_method
/*______*/     { NO_DISPOSAL
/*______*/                 // 0 No disposal specified. The decoder is
/*______*/                 //   not required to take any action.
/*______*/     , DONT_DISPOSE
/*______*/                 // 1 Do not dispose. The graphic is to be left in place.
/*______*/     , RESTORE_TO_BACKGROUND
/*______*/                 // 2 Restore to background color. The area used by the
/*______*/                 //   graphic must be restored to the background color.
/*______*/     , RESTORE_TO_PREVIOUS
/*______*/                 // 3 Restore to previous. The decoder is required to
/*______*/                 //   restore the area overwritten by the graphic with
/*______*/                 //   what was there prior to rendering the graphic.
/*______*/                 // 4-7 -    To be defined.
/*______*/     };
/*______*/  public:
/*______*/     Disposal_method disposal_method;
/*______*/     bool user_input;
/*______*/     bool use_transparent_color;
/*______*/     unsigned int delay_time; // number of hundreths of a second
/*______*/     byte transparent_color;
/*______*/
/*______*/  public:
/*______*/     bool enabled;
/*______*/
/*______*/  public:
/*______*/     inline GIF_control_extension()
/*______*/     : enabled(0)
/*______*/     , disposal_method(NO_DISPOSAL)
/*______*/     , user_input(0)
/*______*/     , use_transparent_color(0)
/*______*/     , delay_time(0) // no delay
/*______*/     , transparent_color(0)
/*______*/     {};
/*______*/
/*______*/     //
/*______*/     inline GIF_control_extension(GIF_control_extension *copy)
/*______*/     : enabled(copy->enabled)
/*______*/     , disposal_method(copy->disposal_method)
/*______*/     , user_input(copy->user_input)
/*______*/     , use_transparent_color(copy->use_transparent_color)
/*______*/     , delay_time(copy->delay_time)
/*______*/     , transparent_color(copy->transparent_color)
/*______*/     {};
/*______*/
/*______*/     void read(FILE *in_file);
/*______*/     void write(FILE *out_file);
/*______*/  };
/*______*/
/*______*/  #define LZ_MAX_CODE	4095		/* Biggest code possible in 12 bits. */
/*______*/  #define LZ_BITS		12
/*______*/
/*______*/  class LZ_decompresser
/*______*/  {
/*______*/   int FileState,
/*______*/  	FileHandle,			     /* Where all this data goes to! */
/*______*/  	BitsPerPixel,	    /* Bits per pixel (Codes uses at list this + 1). */
/*______*/  	ClearCode,				       /* The CLEAR LZ code. */
/*______*/  	EOFCode,				         /* The EOF LZ code. */
/*______*/  	RunningCode,		    /* The next code algorithm can generate. */
/*______*/  	RunningBits,/* The number of bits required to represent RunningCode. */
/*______*/  	MaxCode1,  /* 1 bigger than max. possible code, in RunningBits bits. */
/*______*/  	LastCode,		        /* The code before the current code. */
/*______*/  	CrntCode,				  /* Current algorithm code. */
/*______*/  	StackPtr,		         /* For character stack (see below). */
/*______*/  	CrntShiftState;		        /* Number of bits in CrntShiftDWord. */
/*______*/  	 unsigned long CrntShiftDWord,     /* For bytes decomposition into codes. */
/*______*/  		  PixelCount;		       /* Number of pixels in image. */
//	 FILE *File;						  /* File as stream. */
/*______*/  	 byte Buf[256];	       /* Compressed input is buffered here. */
/*______*/  	 byte Stack[LZ_MAX_CODE];	 /* Decoded pixels are stacked here. */
/*______*/  	 byte Suffix[LZ_MAX_CODE+1];	       /* So we can trace the codes. */
/*______*/  	 unsigned int Prefix[LZ_MAX_CODE+1];
/*______*/  public:
/*______*/  	LZ_decompresser(FILE *in_file);
/*______*/  
/*______*/  	int buffered_input(FILE *File, byte *Buf,byte *NextByte);
/*______*/  
/*______*/  	int decompress_input(FILE *File,int &Code);
/*______*/
/*______*/  	int decompress_line(FILE *in_file,byte Line[], int LineLen);
/*______*/  	int GetPrefixChar(unsigned int *Prefix, int Code, int ClearCode);
/*______*/  
/*______*/  };
/*______*/  
//////////////////////////////////////////////////////
/*______*/  
/*______*/  #define HT_SIZE			8192	   /* 12bits = 4096 or twice as big! */
/*______*/  #define HT_KEY_MASK		0x1FFF	/* 13bits keys */
/*______*/  #define HT_KEY_NUM_BITS		13		/* 13bits keys */
/*______*/  #define HT_MAX_KEY		8191	/* 13bits - 1, maximal code possible */
/*______*/  #define HT_MAX_CODE		4095	/* Biggest code possible in 12 bits. */
/*______*/  
/* The 32 bits of the long are divided into two parts for the key & code:   */
/* 1. The code is 12 bits as our compression algorithm is limited to 12bits */
/* 2. The key is 12 bits Prefix code + 8 bit new char or 20 bits.	    */
/*______*/  #define HT_GET_KEY(l)	(l >> 12)
/*______*/  #define HT_GET_CODE(l)	(l & 0x0FFF)
/*______*/  #define HT_PUT_KEY(l)	(l << 12)
/*______*/  #define HT_PUT_CODE(l)	(l & 0x0FFF)
/*______*/
/*______*/  class GIF_hash_table
/*______*/  {
/*______*/      unsigned long HTable[HT_SIZE];
/*______*/
/*______*/  public:
/*______*/     GIF_hash_table();
/*______*/
/*______*/     void clear();
/*______*/     //clear the hash table to an empty state.
/*______*/
/*______*/     void insert(unsigned long Key, int Code);
/*______*/     //insert one item into data structure.
/*______*/
/*______*/     int exists(unsigned long Key);
/*______*/     //test if item exists in data structure.
/*______*/     int KeyItem(unsigned long Item);
/*______*/  };
/*______*/
//////////////////////////////////////////////////////
/*______*/  class LZ_compresser
/*______*/  {
/*______*/     byte Buf[256];	   /* Compressed input is buffered here. */
/*______*/     int BitsPerPixel;	/* Bits per pixel (Codes uses at list this + 1). */
/*______*/     int ClearCode;		/* The CLEAR LZ code. */
/*______*/     int EOFCode;		/* The EOF LZ code. */
/*______*/     int RunningCode;	/* The next code algorithm can generate. */
/*______*/     int RunningBits;  /* The number of bits required to represent RunningCode. */
/*______*/     int MaxCode1;     /* 1 bigger than max. possible code, in RunningBits bits. */
/*______*/     int CrntCode;		/* Current algorithm code. */
/*______*/     int CrntShiftState; /* Number of bits in CrntShiftDWord. */
/*______*/     unsigned long CrntShiftDWord;     /* For bytes decomposition into codes. */
/*______*/  public:
/*______*/     long PixelCount;
/*______*/     GIF_hash_table hash_table;
/*______*/  public:
/*______*/     LZ_compresser(FILE *out_file,int bits_per_pixel,long PixelCount);
/*______*/     int compress_line(FILE *out_file, byte *Line, int LineLen);
/*______*/     int buffered_output(FILE *out_file, byte *Buf, int c);
/*______*/     int compress_output(FILE *out_file,int Code);
/*______*/  
/*______*/  };
/*______*/  
/*______*/  class GIF_image
/*991115*/  : public CORN_container_item
/*______*/  {
/*______*/  public:
/*______*/  	unsigned int left;    // 0 indexed
/*______*/  	unsigned int top;	// 0 indexed
/*______*/  	unsigned int width;
/*______*/  	unsigned int height;
/*______*/  	color_map  *local_color_table;   // 0 if not local color table
/*______*/  	color_map  *global_color_table;
/*______*/  	color_map  *color_table;         // points to either the local or the global color table
/*______*/
/*______*/  	bool interlaced;
/*______*/  	byte **matrix;
/*______*/  	bool modified;
/*______*/
/*______*/     GIF_control_extension graphic_control;
/*______*/
/*______*/  public:
/*______*/  	GIF_image(unsigned int i_width, unsigned int i_height,
/*______*/           unsigned int i_left = 0,unsigned int i_top = 0);
/*______*/  	GIF_image(FILE *in_file,color_map *i_global_color_table
/*______*/       ,GIF_control_extension i_graphic_control);
/*______*/     ~GIF_image();
/*______*/  	void read(FILE *in_file);  // reads the image from the GIF file
/*______*/  	void write(FILE *out_file); // writes the image to the GIF file
/*______*/ public: // Image accessors
/*______*/     void set_torus(int col, int row,byte color);
/*______*/  
/*______*/     byte get_torus(int col, int row);
/*______*/     // This function returns the color at x,y
/*______*/     // if X is < 0 or X > width, the dimensions are wrapped around
/*______*/
/*______*/  public: // Drawing primatives
/*______*/  	inline void point(int col,int row,byte color); 
/*______*/  	void line(int col1,int row1,int col2,int row2,byte color);
/*______*/     void clear(byte clear_color = 0);
/*______*/
/*______*/     inline void set_transparent_color(uint8 color_index)
/*______*/     {  graphic_control.enabled = true;
/*______*/        graphic_control.use_transparent_color = true;
/*______*/        graphic_control.transparent_color = color_index;
/*______*/     };
/*______*/
/*______*/  public: // Advanced drawing
/*______*/  	void overlay_image(GIF_image &image_to_overlay,int col,int row);
/*______*/
/*______*/  public: // Color optimization
/*______*/  	//void change_colors(byte new_colors[]);
/*______*/     void recolor(byte new_colors[]);
/*______*/     void quantize(int max_colors);
/*______*/  };
//______________________________________________________________________________
/*______*/  class GIF
/*______*/  {
/*______*/  public:
/*______*/  	File_name filename;
/*______*/  	unsigned int screen_width;
/*______*/  	unsigned int screen_height;
/*______*/  	byte background_color;
/*______*/  	byte pixel_aspect_ratio;
/*______*/
               //*______*/  				Aspect Ratio = (Pixel Aspect Ratio + 15) / 64
               //*______*/
               //*______*/  				The Pixel Aspect Ratio is defined to be the quotient of the pixel's
               //*______*/  				width over its height.  The value range in this field allows
               //*______*/  				specification of the widest pixel of 4:1 to the tallest pixel of
               //*______*/  				1:4 in increments of 1/64th.
/*______*/  	color_map *global_color_table;  // 0 if no color table.
/*______*/     bool animation;
/*______*/     unsigned int animation_iterations;
/*991115*/     CORN_bidirectional_list images;                                               //991115
/*______*/     GIF_control_extension last_graphic_control;
/*______*/     FILE *file;
/*______*/  public:
/*______*/     // Open an existing file
/*______*/  	GIF(const char *i_filename);
/*______*/
/*______*/     // Create a new file
/*______*/     GIF(const char *i_filename,unsigned int i_screen_width ,unsigned int i_screen_height );
/*______*/     ~GIF();
/*______*/
/*______*/  	void read();
/*______*/  	void write_it();
/*______*/
/*______*/     void write_global();
/*______*/     // The GIF header, global color map (if any)
/*______*/     // and animation control (if any)
/*______*/
/*______*/     void write_current_image();
/*______*/  
/*______*/     void write_close();
/*______*/
/*______*/
/*______*/  private:
/*______*/     //int skip_extension(FILE *in_file);
/*______*/
/*______*/
/*______*/     void write_animation_control_block();
/*______*/     //woid read_animation_control_block();  not implemented yet
/*______*/  public: // Graphic control extension accessors
/*______*/     inline void set_transparent_color(uint8 color_index)
/*______*/     {  last_graphic_control.enabled = true;
/*______*/        last_graphic_control.use_transparent_color = true;
/*______*/        last_graphic_control.transparent_color = color_index;
/*______*/     };
/*______*/  };
/*______*/
/*______*/  class GIF_animation : public GIF
/*______*/  {
/*______*/     GIF_image *prev_frame;   // pointer to the previous frame (unoptimized)
/*______*/  //   GIF_image *curr_frame;   // pointer to the current frame (unoptimized)
/*______*/  
/*______*/  public:
/*______*/  
/*______*/     // Open an existing file
/*______*/  	inline GIF_animation(const CORN_filename &i_filename)
/*______*/     : GIF(i_filename)
/*______*/     , prev_frame(0)
/*______*/     {};
/*______*/
/*______*/     // Create a new file
/*______*/     inline GIF_animation
/*______*/     (const CORN_filename &i_filename
/*______*/     ,color_map *i_color_map        // The color map is relinquished to the GIF object
/*______*/                                    // Do not try to delete/free it.
/*______*/     ,unsigned int i_screen_width   // should be int16
/*______*/     ,unsigned int i_screen_height  // should be int16
/*______*/     ,uint16 i_number_of_frames
/*______*/     ,uint16 i_iterations = 0        // The number of times to repeat the display of the animation (0 indicates continuous looping)
/*______*/     )
/*______*/     : GIF(i_filename,i_screen_width,i_screen_height)
/*______*/     , prev_frame(0)
/*______*/     {
/*______*/        animation = true;
/*______*/        animation_iterations = i_iterations;
/*______*/        global_color_table = i_color_map;
/*______*/        write_global();
/*______*/     }
/*______*/     inline ~GIF_animation()
/*______*/     {
/*______*/        commit_current_frame();
/*______*/        write_close();
/*______*/     }
/*______*/     void commit_current_frame();
/*______*/     GIF_image &new_frame(int16 delay_time);
/*______*/  };
//______________________________________________________________________________
extern unsigned int GIF_read_word(FILE *infile);
extern void GIF_write_word(FILE *outfile, unsigned int word);
extern int GIF_skip_extension_block(FILE *in_file);
extern int GIF_skip_comment(FILE *in_file);

#endif
