#include <rlib/gif.h>
#include <corn/std/std_iostream.h>

int main()
{
  GIF test("\\gquest\\images\\m100_256.gif");
  test.filename.assign("test1.gif");
/*
  int i,j;
  for (i = 0; i < test.current_image->height; i++)
  {
     for (j = 0; j < test.current_image->width; j++)
       cout << (int)(test.current_image->matrix[i][j]) << ' ';
     cout << endl;
  };
*/
  test.write();
};

