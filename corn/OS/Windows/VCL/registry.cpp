#pragma hdrstop
#include <corn/OS/Windows/VCL/registry.h>

namespace CORN
{

Registry::Registry(const char *HKEY_CURRENT_USER_subkey)
: TRegIniFile(HKEY_CURRENT_USER_subkey)
{
};

void Registry::register_extension
(const char *extension
,const char *description
,const char *program
,const char *icon
)
{
   RootKey = HKEY_CLASSES_ROOT;

   char dot_ext[100];
   dot_ext[0] = '.';
   dot_ext[1] = 0;
   strcat(dot_ext,extension);
   WriteString(dot_ext, "", extension);
   WriteString(extension, "", description);

   char key[256];
   strcpy(key,extension);
   strcat(key,"\\DefaultIcon");
   WriteString(key, "", icon);

   strcpy(key,extension);
   strcat(key,"\\Shell");
    char ext_default_action[256];
   strcpy(ext_default_action,extension);
   strcat(ext_default_action,"_default_action");
   WriteString(key, "", ext_default_action);

   strcpy(key,extension);
   strcat(key,"\\Shell\\First_Action");
   char open_app[256];
   strcpy(open_app,"Open ");
   strcat(open_app,description);
   WriteString(key, "",open_app);

   strcpy(key,extension);
   strcat(key,"\\Shell\\First_Action\\command");
   char prog_arg[256];
   strcpy(prog_arg,program);
   strcat(prog_arg," \"%1\"");
   WriteString(key, "", prog_arg);

   strcpy(key,extension);
   strcat(key,"\\Shell\\");
   strcat(key,ext_default_action);
   WriteString(key, "", open_app);

   strcat(key,"\\command");
   WriteString(key, "", prog_arg);


/*template
   reginifile->WriteString(".NewExt", "", "NewExt");
   reginifile->WriteString("NewExt", "", "Your description of NewExt files");
   reginifile->WriteString("NewExt\\DefaultIcon", "", "C:\\MyApp.Exe,0");
   reginifile->WriteString("NewExt\\Shell", "", "This_Is_Our_Default_Action");
   reginifile->WriteString("NewExt\\Shell\\First_Action", "","This is our first action");
   reginifile->WriteString("NewExt\\Shell\\First_Action\\command", "", "C:\\MyApp.Exe /LotsOfParamaters %1");
   reginifile->WriteString("NewExt\\Shell\\This_Is_Our_Default_Action", "", "This is our default action");
   reginifile->WriteString("NewExt\\Shell\\This_Is_Our_Default_Action\\command", "", "C:\\MyApp.Exe %1");
   reginifile->WriteString("NewExt\\Shell\\Second_Action", "", "This is our second action");
   reginifile->WriteString("NewExt\\Shell\\Second_Action\\command", "", "C:\\MyApp.Exe /TonsOfParameters %1");
*/


};
};

