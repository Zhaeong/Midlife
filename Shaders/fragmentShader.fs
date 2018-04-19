#version 330 core
in vec3 pointColor;

out vec4 FragColor;

uniform float customColor;

void main()
{
   //FragColor = vec4(pointColor, 1.0f);
   FragColor = vec4(pointColor.x, pointColor.y, customColor, 1.0f);

   //FragColor = vec4(customColor, customColor, customColor, 1.0f);


}
