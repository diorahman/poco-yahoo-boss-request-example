POCODIR=/home/diorahman/Experiments/misc/poco/poco-1.6.1-all
INCLUDE=-I $(POCODIR)/NetSSL_OpenSSL/include -I $(POCODIR)/Net/include -I $(POCODIR)/Foundation/include -I $(POCODIR)/Crypto/include 
LIBS=-L $(POCODIR)/lib/Linux/x86_64 -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoCrypto -lPocoUtil -lPocoJSON -lPocoXML -lssl -lcrypto

app: main.cpp
	g++ $(INCLUDE) $(LIBS) main.cpp -o app

clean: 
	rm -fr app

.PHONY: clean
