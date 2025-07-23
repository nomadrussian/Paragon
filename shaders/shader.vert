#version 430 core
layout (location = 0) in vec3 aPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec4 color;

void main()
{
    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
