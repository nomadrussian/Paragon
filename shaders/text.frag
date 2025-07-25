#version 330 core
in vec2 fragUV;
out vec4 fragColor;

uniform sampler2D fontAtlas;
uniform vec4 textColor;
uniform float pxRange;
uniform float pixelBias;

float median(float r, float g, float b) {
    return max(min(r,g), min(max(r,g), b));
}

void main() {
    vec3 sample = texture(fontAtlas, fragUV).rgb;
    float sd = median(sample.r, sample.g, sample.b);
    float screenDist = sd * pxRange - pxRange * 0.5 + pixelBias;
    float smoothing = fwidth(screenDist);
    float alpha = smoothstep(-smoothing, smoothing, screenDist);
    fragColor = vec4(textColor.rgb, alpha * textColor.a);
}
