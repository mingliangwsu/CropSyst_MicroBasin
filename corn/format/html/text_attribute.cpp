#include <corn/format/html/text_attribute.h>

namespace HTML
{
void Font::options()
{
   Core_attribute_options::write(document);
   IL8N_options::write(document);
   size.write(document);
   point_size.write(document);
   color.write(document);
   face.write(document);
//NYI weight
};
};
