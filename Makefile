rstation: clean
	g++ -Wall RStation/*.h RStation/*.cpp -lGL -lGLEW -lglfw -lpng -lz -lopenal -lalut -o rstation

clean:
	rm rstation
