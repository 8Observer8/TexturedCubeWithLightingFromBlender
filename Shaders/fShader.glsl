uniform highp vec3 lightPos;
uniform sampler2D textureUniform;

varying highp vec3 vertex;
varying highp vec3 normal;
varying highp vec2 textureCoords;

void main()
{
    highp vec3 L = normalize( lightPos - vertex );
    highp float diffuse = max( dot( normalize( normal ), L ), 0.0 );
    highp vec3 col = texture2D( textureUniform, textureCoords ).xyz;
    highp vec3 c = clamp( col * 0.2 + col * 0.8 * diffuse, 0.0, 1.0 );
    gl_FragColor = vec4( c, 1.0 );
}
