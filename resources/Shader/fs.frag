uniform sampler2D texture;

void main()
{
    // multiply it by the color
	vec4 pixel = gl_Color;
	pixel.r=1.0;
	pixel.g=1.0;
	pixel.b=1.0;
	pixel.a=0.0;
    gl_FragColor = pixel + texture2D(texture, gl_TexCoord[0].st);
}