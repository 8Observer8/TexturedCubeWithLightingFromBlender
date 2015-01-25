attribute highp vec4 vertexAttr;
attribute highp vec2 textureAttr;
attribute highp vec3 normalAttr;

uniform highp mat4 mvMatrix;
uniform highp mat4 projMatrix;
uniform highp mat3 normalMatrix;

varying highp vec3 vertex;
varying highp vec3 normal;
varying highp vec2 textureCoords;

void main()
{
    gl_Position = projMatrix * mvMatrix * vertexAttr;

    vertex = vertexAttr.xyz;
    textureCoords = textureAttr;
    normal = normalMatrix * normalAttr;
}
