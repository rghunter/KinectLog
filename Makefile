all: cvDemo

CFLAGS=-fPIC -g -Wall `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
#INCLUDE = -I/usr/local/include/libfreenect
FREE_LIBS = -L/usr/local/lib -lfreenect_sync -lfreenect

cvDemo: cSync.c 
	$(CXX) $(INCLUDE) $(CFLAGS) $? -o $@ $(LIBS) $(FREE_LIBS) 

%.o: %.c
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o cvDemo
	rm -rf logs/imgFiles/*.png
	rm -rf logs/depthData.csv
