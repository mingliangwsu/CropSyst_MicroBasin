BORLANDPATH = "C:\program files\Borland\cbuilder5"

TASM = TASM32
TLIB = tlib
TLINK = ilink32
LIBPATH = $(BORLANDPATH)\LIB
INCLUDEPATH = $(BORLANDPATH)\INCLUDE

DIFF = sdiff
PRE =

CC = bcc32 -W- -v- -H- -3 -N -Og -Oi -Ov -f -I$(INCLUDEPATH)

.cpp.obj:
   $(CC) -c {$< }

everything:    	test_exs.exe formtest.exe lstst.exe strtst.exe 

str_lobj = str.obj myexcept.obj format.obj liststr.obj gstring.obj str_fns.obj commline.obj

str.lib:       	$(str_lobj)
   $(TLIB) $@ /P32 /u $(str_lobj)

test_exs_obj = test_exs.obj

test_exs.exe:  	$(test_exs_obj) str.lib
   $(TLINK) /x/L$(LIBPATH)/Gn -Tpe -ap -c @&&|
c0x32.obj $(test_exs_obj),$@,, str.lib import32.lib cw32.lib
|

formtest_obj = formtest.obj

formtest.exe:  	$(formtest_obj) str.lib
   $(TLINK) /x/L$(LIBPATH)/Gn -Tpe -ap -c @&&|
c0x32.obj $(formtest_obj),$@,, str.lib import32.lib cw32.lib
|

lstst_obj = lstst.obj

lstst.exe:     	$(lstst_obj) str.lib
   $(TLINK) /x/L$(LIBPATH)/Gn -Tpe -ap -c @&&|
c0x32.obj $(lstst_obj),$@,, str.lib import32.lib cw32.lib
|

strtst_obj = strtst.obj

strtst.exe:    	$(strtst_obj) str.lib
   $(TLINK) /x/L$(LIBPATH)/Gn -Tpe -ap -c @&&|
c0x32.obj $(strtst_obj),$@,, str.lib import32.lib cw32.lib
|

str.obj:       	str.cpp include.h str.h myexcept.h

myexcept.obj:  	myexcept.cpp include.h myexcept.h

format.obj:    	format.cpp include.h str.h format.h myexcept.h

liststr.obj:   	liststr.cpp include.h str.h gstring.h str_fns.h myexcept.h

gstring.obj:   	gstring.cpp include.h str.h gstring.h myexcept.h str_fns.h

str_fns.obj:   	str_fns.cpp str.h str_fns.h include.h myexcept.h

commline.obj:  	commline.cpp include.h myexcept.h str.h commline.h str_fns.h

test_exs.obj:  	test_exs.cpp include.h str.h myexcept.h

formtest.obj:  	formtest.cpp include.h str.h format.h myexcept.h

lstst.obj:     	lstst.cpp include.h str.h gstring.h myexcept.h str_fns.h

strtst.obj:    	strtst.cpp include.h str.h str_fns.h myexcept.h

test_exs.txx:  	test_exs.exe
		$(PRE)test_exs > test_exs.txx
		$(DIFF) test_exs.txt test_exs.txx

formtest.txx:  	formtest.exe
		$(PRE)formtest > formtest.txx
		$(DIFF) formtest.txt formtest.txx

lstst.txx:     	lstst.exe
		$(PRE)lstst > lstst.txx
		$(DIFF) lstst.txt lstst.txx

strtst.txx:    	strtst.exe
		$(PRE)strtst > strtst.txx
		$(DIFF) strtst.txt strtst.txx

