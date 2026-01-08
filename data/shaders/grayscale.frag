uniform sampler2D tex;
uniform float u_enabled;
out vec4 FragColor;
void main()
{
    vec2 uv = gl_FragCoord.xy / u_screen;
    vec4 col = texture(tex, uv);

    if (u_enabled > 0.5)
    {
        float gray = dot(col.rgb, vec3(0.2126, 0.7152, 0.0722));
        FragColor = vec4(vec3(gray), col.a);
    }
    else
    {
        FragColor = col;
    }
}
