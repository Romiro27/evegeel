#version 330
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    color = vec4 (0.5,1.0,1.0,1.0); /*texture(ourTexture, TexCoord);*/
}
