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
