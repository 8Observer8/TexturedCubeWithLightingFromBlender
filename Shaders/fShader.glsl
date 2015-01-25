/*
    The Cube Example

    Copyright (C) 2014  Enzhaev Ivan

    Email: 8observer8@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
