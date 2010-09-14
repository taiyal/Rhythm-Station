/*
 * Converted from http://www.cs.rit.edu/~ncs/color/t_convert.html
*/

uniform sampler2D tex;

uniform float hue_shift;
uniform float sat_shift;

uniform vec4 add_color;
uniform vec4 mult_color;

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
	if (color.g == 0.0)
		return vec4(vec3(color.b),color.a);

	color.r /= 60.0;
	float i = floor(color.r);

	tmp.x = color.r - i;
	tmp.y = color.b * (1.0 - color.g);
	tmp.z = color.b * (1.0 - color.g * tmp.x);
	tmp.w = color.b * (1.0 - color.g * ( 1.0 - tmp.x));

	// else if is implicit since the previous would return if true.
	if (i == 0.0)
		return vec4(color.b, tmp.w, tmp.y, color.a);
	if (i == 1.0)
		return vec4(tmp.z, color.b, tmp.y, color.a);
	if (i == 2.0)
		return vec4(tmp.y, color.b, tmp.w, color.a);
	if (i == 3.0)
		return vec4(tmp.y, tmp.z, color.b, color.a);
	if (i == 4.0)
		return vec4(tmp.w, tmp.y, color.b, color.a);
	return vec4(color.b, tmp.y, tmp.z, color.a);
}

void main()
{
	vec4 texture = texture2D(tex, gl_TexCoord[0].st);
	/*
	 * This seems to mess with the brightness for some reason.
	 * Additionally, it seems to make add_color not work on black.
	 * I'm not sure what's going on here.
	 */
	texture = toHSV(texture);
	texture.x += hue_shift;
	texture.y += sat_shift;
	texture = toRGB(texture);
	texture *= mult_color; // vec4(1.0);
	texture += add_color; // vec4(0.2);

	gl_FragColor = texture;
}
