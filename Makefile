rstation: clean
	g++ -Wall RStation/*.h RStation/*.cpp -lGL -lGLEW -lglfw -lpng -lz -lopenal -lalut -lvorbisfile -o rstation

clean:
	rm -f rstation
