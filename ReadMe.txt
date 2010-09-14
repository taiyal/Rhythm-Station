===============================================================================
|| RStation
===============================================================================
[Compiling]
You shouldn't have any trouble building with MSVC 2008 - provided the project
files are up to date. The Xcode project is almost always up to date and should
work just fine at any given time (unless otherwise noted).

[Development]
Don't worry about adding stubs and hacks - just try to get the job done and get
to it later. Currently the code is rather messy and I am working to improve it
and flesh out some of the stubs. As for coding style, just follow the source
in the file you're in, generally I write code like so:
[code]
// single line comment
if(foo)
	bar = baz;

/*
 * Multi-line comment.
 */
void foo(_bar) : baz()
{
	baz = _bar;
	
	// * on the right
	int *var = new int[1];
	delete var;
}

class Test : public Stuff
{
public:
	Test();
	virtual ~Test();
};
[/code]
Note, variable names should use hungarian notation if it isn't obvious by the
name what it would be anyways. Example: vpActors for a vector of pointers to
Actors. However one would assume that deltaTime is always a float, so no "f"
prefix is needed. For multi-word variables use underscores for space, for'
vars passed in as arguments prefix names with underscores, and CamelCase funcs.

The code is a bit inconsistent right now, I apologize.

[Contact]
Feel free to drop by #rhythm-station on irc.freenode.net! If you would like to
contact me directly you can do it there, though github, or through email at
shakesoda+rstation at gmail dot com.

[Compiling on Linux/gcc]
Make sure you've installed:
- gl, glew, libglfw
- libpng14, zlib
- openal, freealut, vorbisfile
