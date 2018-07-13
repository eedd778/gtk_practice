test.exe: main.cpp
	g++ -o test.exe main.cpp `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-3.0` -export-dynamic -lpthread
clean:
	rm -f *.o *.exe
