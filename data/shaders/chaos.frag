uniform sampler2D tex;
uniform float u_enabled;
out vec4 FragColor;
uniform float u_bw_enabled;
uniform float u_inversion_enabled;
void main()
{
    vec2 uv = gl_FragCoord.xy / u_screen;
    vec4 col = texture(tex, uv);

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
