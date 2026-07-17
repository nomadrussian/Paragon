#version 330 core
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D atlasTexture;
uniform float distanceRange;

float median(vec3 a)
{
    return max(min(a.x, a.y), min(max(a.x, a.y), a.z));
}

void main()
{
    vec3 pixel = texture(atlasTexture, vec2(texCoord.x, 1.0 - texCoord.y)).rgb;
    float signedDistance = median(pixel);
    float screenSignedDistance = (signedDistance - 0.5) * distanceRange;
    float antiAliasingWidth = fwidth(screenSignedDistance);
    float alpha = smoothstep(-antiAliasingWidth, antiAliasingWidth, screenSignedDistance);
    fragColor = vec4(1.0, 1.0, 1.0, alpha);
}
