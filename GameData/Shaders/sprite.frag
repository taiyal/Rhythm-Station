uniform sampler2D tex;
uniform vec4 glow;
uniform vec4 color;

vec4 toHSV(vec4 c)
{
	vec4 hsv;

	float fMin = min(min(c.r, c.g), c.b);
	float fMax = max(max(c.r, c.g), c.b);
	hsv.b = fMax;

	float delta = fMax - fMin;

	if (fMin == 0.0 && fMax == 0.0)
		return vec4(vec3(0.0),c.a);

	if (fMax != 0.0)
		hsv.g = delta / fMax;
	else
	{
		hsv.g = 0.0;
		hsv.r = -1.0;
		return vec4(hsv.rgb,1.0);
	}

	// hue
	if (c.r == fMax)
		// yellow/magenta
		hsv.r = (c.g - c.b) / delta;
	else if (c.g == fMax)
		// cyan/yellow
		hsv.r = 2.0 + (c.b - c.r) / delta;
	else
		// magenta/cyan
		hsv.r = 4.0 + (c.r - c.g) / delta;
	hsv.r *= 60.0; // degrees

	while (hsv.r < 0.0)
		hsv.r += 360.0;

	return hsv;
}

vec4 toRGB(vec4 hsv)
{
	vec4 tmp, rgb, hsva;
	hsva = vec4(hsv.r/60.0,hsv.g,hsv.b,hsv.a);

	if (hsva.g == 0.0)
		return vec4(hsva.b, hsva.b, hsva.b, hsva.a);

	float i = floor(hsv.r);
	tmp.r = hsv.r - i;
	tmp.g = hsv.b * (1.0-hsv.g);
	tmp.b = hsv.b * (1.0-hsv.g*tmp.r);
	tmp.a = hsv.b * (1.0-hsv.g*(1.0-tmp.r));

	if (i == 0.0)
		return vec4(hsva.b,tmp.a,tmp.g,hsva.a);
	else if (i == 1.0)
		return vec4(tmp.b,hsva.b,tmp.g,hsva.a);
	else if (i == 2.0)
		return vec4(tmp.g,hsva.b,tmp.a,hsva.a);
	else if (i == 3.0)
		return vec4(tmp.g,tmp.b,hsva.b,hsva.a);
	else if (i == 4.0)
		return vec4(tmp.a,tmp.g,hsva.b,hsva.a);
	else
		return vec4(hsva.b,tmp.g,tmp.b,hsva.a);
}

/*
in lua:
function ColorToHSV(c)
	local r = c[1]
	local g = c[2]
	local b = c[3]
	-- alpha requires error checking sometimes.
	local a = HasAlpha(c)

	local h = 0
	local s = 0
	local v = 0

	local min = math.min( r, g, b )
	local max = math.max( r, g, b )
	v = max

	local delta = max - min

	-- xxx: how do we deal with complete black?
	if min == 0 and max == 0 then
		-- we have complete darkness; make it cheap.
		return {
			Hue = 0,
			Sat = 0,
			Value = 0,
			Alpha = a
		}
	end

	if max ~= 0 then
		s = delta / max -- rofl deltamax :|
	else
		-- r = g = b = 0; s = 0, v is undefined
		s = 0
		h = -1
		return {
			Hue = h,
			Sat = s,
			Value = v,
			Alpha = 1
		}
	end

	if r == max then
		h = ( g - b ) / delta     -- yellow/magenta
	elseif g == max then
		h = 2 + ( b - r ) / delta -- cyan/yellow
	else
		h = 4 + ( r - g ) / delta -- magenta/cyan
	end

	h = h * 60 -- degrees

	if h < 0 then
		h = h + 360
	end

	return {
		Hue = h,
		Sat = s,
		Value = v,
		Alpha = a
	}
end

-- HSVToColor(hsv)
-- Converts a set of HSV values to a color. hsv is a table.
-- See also: HSV(h, s, v)
function HSVToColor(hsv)
	local i
	local f, q, p, t
	local r, g, b
	local h, s, v

	local a

	s = hsv.Sat
	v = hsv.Value

	if hsv.Alpha then
		a = hsv.Alpha
	else
		a = 0
	end

	if s == 0 then
		return { v, v, v, a }
	end

	h = hsv.Hue / 60

	i = math.floor(h)
	f = h - i
	p = v * (1-s)
	q = v * (1-s*f)
	t = v * (1-s*(1-f))

	if i == 0 then
		return { v, t, p, a }
	elseif i == 1 then
		return { q, v, p, a }
	elseif i == 2 then
		return { p, v, t, a }
	elseif i == 3 then
		return { p, q, v, a }
	elseif i == 4 then
		return { t, p, v, a }
	else
		return { v, p, q, a }
	end
end
*/

void main()
{
	vec4 texture = texture2D(tex, gl_TexCoord[0].st);
	vec4 test = toHSV(texture);
//	test.r = 90.0;
	test = toRGB(test);
	gl_FragColor = (test * color) + glow;
}