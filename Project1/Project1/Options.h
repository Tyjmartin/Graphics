#ifndef OPTIONS
#define OPTIONS


// Interface for options
class Options{
public:

	const int height = 600;
	const int width = 800;
	int bgColor[3];
	bool randSpeed;
	bool running;
	bool rotate;
	bool spray;
	bool color;

	Options();
};


#endif