# Change these
cxxtestpath = /info/cprog11/cxxtest/
testcode    = own_test.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: testcode.cpp
	g++ --std=c++11 -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o

clean:
	touch runtest01 testcode.cpp
	rm runtest0* testcode.cpp

