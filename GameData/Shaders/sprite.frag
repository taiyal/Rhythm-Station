uniform sampler2D tex;
uniform vec4 glow;
uniform vec4 color;

void main()
{
	vec4 texture = texture2D(tex, gl_TexCoord[0].st);
	gl_FragColor = (texture * color) + glow;
}