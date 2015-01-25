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

#include "Cube.h"
#include <iostream>
#include <QDebug>

Cube::Cube( QOpenGLShaderProgram *program, int vertexAttrLoc,
            int normalAttrLoc, int textureAttrLoc, int textureUniformLoc) :
    m_program( program ),
    m_vertexAttrLoc( vertexAttrLoc ),
    m_normalAttrLoc( normalAttrLoc ),
    m_textureAttrLoc( textureAttrLoc ),
    m_textureUniformLoc( textureUniformLoc ),
    m_textureOfFront( 0 ),
    m_textureOfBack( 0 ),
    m_textureOfRight( 0 ),
    m_textureOfLeft( 0 ),
    m_textureOfTop( 0 ),
    m_textureOfBottom( 0 )
{

}

Cube::~Cube()
{
    if ( !m_textureOfFront )
        delete m_textureOfFront;

    if ( !m_textureOfBack )
        delete m_textureOfBack;

    if ( !m_textureOfRight )
        delete m_textureOfRight;

    if ( !m_textureOfLeft )
        delete m_textureOfLeft;

    if ( !m_textureOfTop )
        delete m_textureOfTop;

    if ( !m_textureOfBottom )
        delete m_textureOfBottom;
}

void Cube::draw()
{
    if ( ( m_textureOfFront == 0 ) ||
         ( m_textureOfBack == 0 ) ||
         ( m_textureOfLeft == 0 ) ||
         ( m_textureOfRight == 0 ) ||
         ( m_textureOfTop == 0 ) ||
         ( m_textureOfBottom == 0 ) )
    {
        return;
    }

    draw( verticesForFront, normalsForFront, textureCoordsForFront, m_textureOfFront );
    draw( verticesForBack, normalsForBack, textureCoordsForBack, m_textureOfBack );
    draw( verticesForLeft, normalsForLeft, textureCoordsForLeft, m_textureOfLeft );
    draw( verticesForRight, normalsForRight, textureCoordsForRight, m_textureOfRight );
    draw( verticesForTop, normalsForTop, textureCoordsForTop, m_textureOfTop );
    draw( verticesForBottom, normalsForBottom, textureCoordsForBottom, m_textureOfBottom );
}

void Cube::draw( const std::vector<float> &vertices,
                 const std::vector<float> &normals,
                 const std::vector<float> &textureCoords,
                 QOpenGLTexture *texture )
{
    if ( ( vertices.size() == 0 ) ||
         ( normals.size() == 0 ) ||
         ( textureCoords.size() == 0 ) )
        return;

    texture->bind();

    m_program->setAttributeArray( m_vertexAttrLoc, vertices.data(), 3 );
    m_program->setAttributeArray( m_normalAttrLoc, normals.data(), 3 );
    m_program->setAttributeArray( m_textureAttrLoc, textureCoords.data(), 2 );
    m_program->setUniformValue( m_textureUniformLoc, 0 );

    m_program->enableAttributeArray( m_vertexAttrLoc );
    m_program->enableAttributeArray( m_normalAttrLoc );
    m_program->enableAttributeArray( m_textureAttrLoc );

    glDrawArrays( GL_TRIANGLES, 0, vertices.size() / 3 );

    m_program->disableAttributeArray( m_vertexAttrLoc );
    m_program->disableAttributeArray( m_normalAttrLoc );
    m_program->disableAttributeArray( m_textureAttrLoc );
}

bool Cube::fillFromLoader( const MeshLoader *loader )
{
    verticesForFront = loader->verticesForFront;
    textureCoordsForFront = loader->textureCoordsForFront;
    normalsForFront = loader->normalsForFront;

    verticesForBack = loader->verticesForBack;
    textureCoordsForBack = loader->textureCoordsForBack;
    normalsForBack = loader->normalsForBack;

    verticesForLeft = loader->verticesForLeft;
    textureCoordsForLeft = loader->textureCoordsForLeft;
    normalsForLeft = loader->normalsForLeft;

    verticesForRight = loader->verticesForRight;
    textureCoordsForRight = loader->textureCoordsForRight;
    normalsForRight = loader->normalsForRight;

    verticesForTop = loader->verticesForTop;
    textureCoordsForTop = loader->textureCoordsForTop;
    normalsForTop = loader->normalsForTop;

    verticesForBottom = loader->verticesForBottom;
    textureCoordsForBottom = loader->textureCoordsForBottom;
    normalsForBottom = loader->normalsForBottom;

    fileNames = loader->fileNames;

    QImage image;

    image = QImage( QString( ":/Textures/" ) + QString( fileNames["front"].c_str() ) );
    if ( image.isNull() )
    {
        std::cerr << "Error: the incorrect path the front image: \"" <<
                     fileNames["front"] << "\"" << std::endl;
        return false;
    }
    m_textureOfFront = new QOpenGLTexture( image );

    image = QImage( QString( ":/Textures/" ) + QString( fileNames["back"].c_str() ) );
    if ( image.isNull() )
    {
        std::cerr << "Error: the incorrect path the back image: \"" <<
                     fileNames["back"] << "\"" << std::endl;
        return false;
    }
    m_textureOfBack = new QOpenGLTexture( image );

    image = QImage( QString( ":/Textures/" ) + QString( fileNames["left"].c_str() ) );
    if ( image.isNull() )
    {
        std::cerr << "Error: the incorrect path the left image: \"" <<
                     fileNames["left"] << "\"" << std::endl;
        return false;
    }
    m_textureOfLeft = new QOpenGLTexture( image );

    image = QImage( QString( ":/Textures/" ) + QString( fileNames["right"].c_str() ) );
    if ( image.isNull() )
    {
        std::cerr << "Error: the incorrect path the right image: \"" <<
                     fileNames["right"] << "\"" << std::endl;
        return false;
    }
    m_textureOfRight = new QOpenGLTexture( image );

    image = QImage( QString( ":/Textures/" ) + QString( fileNames["top"].c_str() ) );
    if ( image.isNull() )
    {
        std::cerr << "Error: the incorrect path the top image: \"" <<
                     fileNames["top"] << "\"" << std::endl;
        return false;
    }
    m_textureOfTop = new QOpenGLTexture( image );

    image = QImage( QString( ":/Textures/" ) + QString( fileNames["bottom"].c_str() ) );
    if ( image.isNull() )
    {
        std::cerr << "Error: the incorrect path the bottom image: \"" <<
                     fileNames["bottom"] << "\"" << std::endl;
        return false;
    }
    m_textureOfBottom = new QOpenGLTexture( image );

    return true;
}

