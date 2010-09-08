uniform sampler2D tex;

void main()
{
	vec4 texture = texture2D(tex, gl_TexCoord[0].st);
	gl_FragColor = texture + vec4(vec3(0.2),0.0);
}