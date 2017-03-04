#version 330 core
out vec4 FragColor;
in vec2 tCoord;

uniform sampler2D scene;
uniform sampler2D blur;
uniform float exposure;

void main()
{             
    const float gamma = 2.2;
    vec3 bColor = texture(blur, tCoord).rgb;      
    vec3 sColor = texture(scene, tCoord).rgb;
    //hdrColor += scene; // additive blending
    // tone mapping
    //vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    //result = pow(result, vec3(1.0 / gamma));
    //FragColor = vec4(result, 1.0f);
    FragColor = vec4(bColor, 1.0f);
}  