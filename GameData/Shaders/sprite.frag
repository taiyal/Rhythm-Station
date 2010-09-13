/*
 * Converted from http://www.cs.rit.edu/~ncs/color/t_convert.html
 */

uniform sampler2D tex;
uniform vec4 glow;
uniform vec4 color;

vec4 toHSV( vec4 color )
{
	float h, s, v;
	float fMin, fMax, delta;
	
	// compute V
	fMin = min(max(color.r, color.g), color.b);
	fMax = max(max(color.r, color.g), color.b);
	v = fMax;
	
	// compute S
	delta = fMax - fMin;
	if (fMax != 0.0)
		s = delta / fMax;
	else
		return vec4(h,0.0,-1.0,color.a);
	
	// compute H
	if (color.r == fMax)
		// between yellow & magenta
		h = (color.g - color.b) / delta;
	else if (color.g == fMax)
		// between cyan & yellow
		h = 2.0 + ( color.b - color.r ) / delta;
	else
		// between magenta & cyan
		h = 4.0 + ( color.r - color.g ) / delta;

	// degrees
	h *= 60.0;
	if( h < 0.0 )
		h += 360.0;
	
	return vec4(h,s,v,color.a);
}

void main()
{
	vec4 texture = texture2D(tex, gl_TexCoord[0].st);
	vec4 test = toHSV(texture);
//	test.r = 90.0;
//	test = toRGB(test);
	gl_FragColor = (test * color) + glow;
}