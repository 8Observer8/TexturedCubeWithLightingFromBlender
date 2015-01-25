/*
    The Cube Example

    Copyright (C) 2015  Enzhaev Ivan

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

#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <QString>
#include <vector>
#include <map>
#include <string>
#include <assimp/scene.h>

class MeshLoader
{
public:
    MeshLoader( const QString &fileName );
    ~MeshLoader();

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

    bool isSuccessfully;

private:
    bool fillContainers( const aiMesh *mesh, const aiScene *scene );
    void fillVertices( const aiMesh *mesh, std::vector<float> &vertices );
    bool fillTextureCoords( const aiMesh *mesh, std::vector<float> &textureCoords );
    void fillNormals( const aiMesh *mesh, std::vector<float> &normals );
};

#endif // MESHLOADER_H
