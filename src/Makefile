BASEDIR := $(shell pwd)
CURLIBNAME=-L$(BASEDIR)/include/libcurl.a
REDISLIBNAME=-L$(BASEDIR)/include/libredisclient.a
TESTAPPLIBS = $(REDISLIBNAME) -lstdc++ -lcurl -lpthread -lboost_thread-mt
CXX = g++
CFLAGS = -Wall -Werror
LDFLAGS = -lcurl
appout:test_client.cpp CurlHttpGet.cpp anet.c
	$(CXX) -o appout test_client.cpp anet.c CurlHttpGet.cpp $(INCLUDE) $(LDLIB)  $(LDBIN) $(LDFLAGS) $(CURLIBNAME) $(TESTAPPLIBS)
clean:
	rm -rf *.o out appout

