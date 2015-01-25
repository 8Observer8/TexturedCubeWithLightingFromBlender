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

#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <string>
#include <vector>
#include <map>
#include "MeshLoader.h"

class Cube
{
public:
    Cube( QOpenGLShaderProgram *program, int vertexAttrLoc, int normalAttrLoc,
          int textureAttrLoc, int textureUniformLoc );
    ~Cube();

    void draw();

    bool fillFromLoader( const MeshLoader *loader );

    std::vector<float> verticesForFront;
    std::vector<float> textureCoordsForFront;
    std::vector<float> normalsForFront;

    std::vector<float> verticesForBack;
    std::vector<float> textureCoordsForBack;
    std::vector<float> normalsForBack;

    std::vector<float> verticesForLeft;
    std::vector<float> textureCoordsForLeft;
    std::vector<float> normalsForLeft;

    std::vector<float> verticesForRight;
    std::vector<float> textureCoordsForRight;
    std::vector<float> normalsForRight;

    std::vector<float> verticesForTop;
    std::vector<float> textureCoordsForTop;
    std::vector<float> normalsForTop;

    std::vector<float> verticesForBottom;
    std::vector<float> textureCoordsForBottom;
    std::vector<float> normalsForBottom;

    std::map<std::string, std::string> fileNames;

private:
    void draw( const std::vector<float> &vertices,
               const std::vector<float> &normals,
               const std::vector<float> &textureCoords,
               QOpenGLTexture *texture );

    QOpenGLShaderProgram *m_program;
    int m_vertexAttrLoc;
    int m_normalAttrLoc;
    int m_textureAttrLoc;
    int m_textureUniformLoc;

    QOpenGLTexture *m_textureOfFront;
    QOpenGLTexture *m_textureOfBack;
    QOpenGLTexture *m_textureOfRight;
    QOpenGLTexture *m_textureOfLeft;
    QOpenGLTexture *m_textureOfTop;
    QOpenGLTexture *m_textureOfBottom;
};

#endif // CUBE_H
