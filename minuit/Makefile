MINUIT=Minuit2-5.28.00
OBJS=main.o AbsFunction.o TestFunction.o MinuitWrapper.o

all: $(OBJS) 
	libtool --mode=link g++ -std=c++11 -g -O2 -Wall -fopenmp -L/usr/local/lib -o test $(OBJS) $(MINUIT)/src/libMinuit2.la

%.o: %.cxx
	g++-v4.8.0 -std=c++11 -c $< -g -O2 -Wall -fopenmp -I$(MINUIT)/inc -o $@

clean:
	rm *.o