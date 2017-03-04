#version 330
out vec4 fColor;
in vec2 tCoord;

uniform sampler2D image;
uniform bool horizontal;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, tCoord).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, tCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, tCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, tCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, tCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    fColor = vec4(result, 1.0);
}