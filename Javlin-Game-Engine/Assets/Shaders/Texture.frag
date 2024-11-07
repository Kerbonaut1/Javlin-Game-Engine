#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoords);
    //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // as a debug we draw the texcoords
    //FragColor = vec4(TexCoords, 0.0f, 1.0f);
}
