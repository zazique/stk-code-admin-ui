uniform sampler2D tex;
uniform float u_enabled;
out vec4 FragColor;
uniform float u_bw_enabled;
uniform float u_inversion_enabled;
uniform float u_distort_enabled;
uniform float u_time;
uniform float u_new_distort_enabled;
uniform float u_mirror_enabled;
void main()
{
    vec2 uv = gl_FragCoord.xy / u_screen;
    if (u_mirror_enabled > 0.001) 
    {
        bool mirX = (u_mirror_enabled > 0.25 && u_mirror_enabled <= 0.5) || (u_mirror_enabled > 0.75);
        bool mirY = (u_mirror_enabled > 0.5);

        if (mirX) uv.x = 1.0 - uv.x;
        if (mirY) uv.y = 1.0 - uv.y;
    }
    vec4 col = texture(tex, uv);
    
	if (u_new_distort_enabled > 0.5)
    {
        float strength = 0.05;
        float frequency = 10.0;
        float speed = u_time * 3.0;
        vec2 uv_distorted = uv;
        uv_distorted.x += sin(uv.y * frequency + speed) * strength;
        uv_distorted.y += cos(uv.x * frequency + speed) * strength;
        float chromOffset = 0.012;
        float r = texture(tex, uv_distorted - vec2(chromOffset, 0.0)).r;
        float b = texture(tex, uv_distorted + vec2(chromOffset, 0.0)).b;
        vec4 central = texture(tex, uv_distorted);
        float g = central.g;
        float a = central.a;
        col = vec4(r, g, b, a);
        col.rgb += (fract(sin(dot(uv_distorted, vec2(12.9898, 78.233))) * 43758.5453) - 0.5) * 0.05;
    }
    
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
