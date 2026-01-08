uniform sampler2D tex;
uniform float u_enabled;
out vec4 FragColor;
uniform float u_bw_enabled;
uniform float u_inversion_enabled;
uniform float u_distort_enabled;
uniform float u_time;
void main()
{
    vec2 uv = gl_FragCoord.xy / u_screen;
    vec4 col = texture(tex, uv);
	
	if (u_distort_enabled > 0.5)
    {
        vec2 displaceFactor = vec2(sin(uv.y * 16.0) * 0.020, 0.0);
        float offset = 0.05; 
        float r = texture(tex, uv - vec2(offset, 0.0) + displaceFactor).r;
        float b = texture(tex, uv + vec2(offset, 0.0) + displaceFactor).b;
        vec4 centralSample = texture(tex, uv + displaceFactor);
        float g = centralSample.g;
        float a = centralSample.a;

        col = vec4(r, g, b, a);

        vec4 grey = vec4(0.5, 0.5, 0.5, a);
        col = mix(grey, col, 0.8);
    }
    else
    {
        col = texture(tex, uv);
    }
	
    if (u_bw_enabled > 0.5)
    {
        float gray = dot(col.rgb, vec3(0.2126, 0.7152, 0.0722));
        col.rgb = vec3(gray);
    }
    if (u_inversion_enabled > 0.5)
    {
        col.rgb = 1.0 - col.rgb;
    }
    FragColor = col;
}
