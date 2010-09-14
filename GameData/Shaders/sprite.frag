uniform sampler2D tex;

uniform float hue_shift;
uniform float sat_shift;

uniform vec4 add_color;
uniform vec4 mult_color;

/*
 * HSV <-> RGB
 * Converted from http://www.cs.rit.edu/~ncs/color/t_convert.html
*/

vec4 toHSV( vec4 color )
{
	float h, s, v;
	float fMin, fMax, delta;

	// compute V
	fMin = min(min(color.r, color.g), color.b);
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

vec4 toRGB( vec4 color )
{
	/*
	 * color.r = H
	 * color.g = S
	 * color.b = V
	*/
	vec4 tmp;

	// using while x > y here locks up my video driver.
	if (color.r >= 360.0)
		color.r -= 360.0;

	// no saturation, skip the rest.
	if (clamp(color.g,0.0,1.0) == 0.0)
		return vec4(vec3(color.b),color.a);

	color.r /= 60.0;
	int i = int(floor(color.r));

	tmp.r = color.r - floor(color.r);
	tmp.g = color.b * (1.0 - color.g);
	tmp.b = color.b * (1.0 - color.g * tmp.r);
	tmp.a = color.b * (1.0 - color.g * (1.0 - tmp.r));

	// else if is implicit since the previous would return if true.
	if (i == 0)
		return vec4(color.b, tmp.a, tmp.g, color.a);
	if (i == 1)
		return vec4(tmp.b, color.b, tmp.g, color.a);
	if (i == 2)
		return vec4(tmp.g, color.b, tmp.a, color.a);
	if (i == 3)
		return vec4(tmp.g, tmp.b, color.b, color.a);
	if (i == 4)
		return vec4(tmp.a, tmp.g, color.b, color.a);
	return vec4(color.b, tmp.g, tmp.b, color.a);
}

void main()
{
	vec4 texture = texture2D(tex, gl_TexCoord[0].st);
	texture *= mult_color; // vec4(1.0);
//	texture += add_color; // vec4(0.2);

	/*
	 * This seems to mess with the brightness for some reason.
	 * Additionally, it seems to make add_color not work on black.
	 * I'm not sure what's going on here.
	 * Workaround: multiply/add stuff before color shifting.
	 */
	texture = toHSV(texture);
	texture.r += hue_shift;
	texture.g += sat_shift;
	texture = toRGB(texture);

	gl_FragColor = texture;
}
