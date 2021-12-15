#version 300 es
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    color = vec4 (1,1,1,1); /*texture(ourTexture, TexCoord);*/
}
