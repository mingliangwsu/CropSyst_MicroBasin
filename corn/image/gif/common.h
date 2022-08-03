#ifndef CORN_GIF_COMMON_H
#define CORN_GIF_COMMON_H

#define GIF_ERROR	0
#define GIF_OK		1
#ifndef primitiveH
#  include <corn/primitive.h>
#endif

#define GIF_plain_text_extension       (uint8)0x01
#define GIF_extension_introducer       (uint8)0x21
#define GIF_image_separator            (uint8)0x2C
#define GIF_trailer                    (uint8)0x3B
#define GIF_graphic_control_extension  (uint8)0xF9
#define GIF_comment_extension          (uint8)0xFE
#define GIF_application_extension      (uint8)0xFF

#endif