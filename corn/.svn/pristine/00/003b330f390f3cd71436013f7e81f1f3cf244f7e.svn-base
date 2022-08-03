CXX = CC
CXXFLAGS = -O2

DIFF = ./sdiff
PRE = ./


.SUFFIXES:
.SUFFIXES: .a .o .c .cpp

.cpp.o:
		rm -f $*.cxx
		ln $*.cpp $*.cxx  
		$(CXX) $(CXXFLAGS) -c $*.cxx
		rm $*.cxx  

everything:    	test_exs formtest lstst strtst 

str_lobj = str.o myexcept.o format.o liststr.o gstring.o str_fns.o commline.o

libstr.a:      	$(str_lobj)
		$(AR) -cr $@ $(str_lobj)
		ranlib $@

test_exs_obj = test_exs.o

test_exs:      	$(test_exs_obj) libstr.a
		$(CXX) -o $@ $(test_exs_obj) -L. -lstr -lm

formtest_obj = formtest.o

formtest:      	$(formtest_obj) libstr.a
		$(CXX) -o $@ $(formtest_obj) -L. -lstr -lm

lstst_obj = lstst.o

lstst:         	$(lstst_obj) libstr.a
		$(CXX) -o $@ $(lstst_obj) -L. -lstr -lm

strtst_obj = strtst.o

strtst:        	$(strtst_obj) libstr.a
		$(CXX) -o $@ $(strtst_obj) -L. -lstr -lm

str.o:         	str.cpp include.h str.h myexcept.h

myexcept.o:    	myexcept.cpp include.h myexcept.h

format.o:      	format.cpp include.h str.h format.h myexcept.h

liststr.o:     	liststr.cpp include.h str.h gstring.h str_fns.h myexcept.h

gstring.o:     	gstring.cpp include.h str.h gstring.h myexcept.h str_fns.h

str_fns.o:     	str_fns.cpp str.h str_fns.h include.h myexcept.h

commline.o:    	commline.cpp include.h myexcept.h str.h commline.h str_fns.h

test_exs.o:    	test_exs.cpp include.h str.h myexcept.h

formtest.o:    	formtest.cpp include.h str.h format.h myexcept.h

lstst.o:       	lstst.cpp include.h str.h gstring.h myexcept.h str_fns.h

strtst.o:      	strtst.cpp include.h str.h str_fns.h myexcept.h

test_exs.txx:  	test_exs
		$(PRE)test_exs > test_exs.txx
		$(DIFF) test_exs.txt test_exs.txx

formtest.txx:  	formtest
		$(PRE)formtest > formtest.txx
		$(DIFF) formtest.txt formtest.txx

lstst.txx:     	lstst
		$(PRE)lstst > lstst.txx
		$(DIFF) lstst.txt lstst.txx

strtst.txx:    	strtst
		$(PRE)strtst > strtst.txx
		$(DIFF) strtst.txt strtst.txx

