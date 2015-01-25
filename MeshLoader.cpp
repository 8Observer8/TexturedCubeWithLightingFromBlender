#include "MeshLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <QStringList>
#include <QDebug>

MeshLoader::MeshLoader( const QString &fileName ) :
    isSuccessfully( true )
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( fileName.toStdString(), aiProcess_Triangulate );

    if ( scene == 0 )
    {
        std::cerr << "Error: unable to open the file " << fileName.toStdString() << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( ( scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ) ||
         ( !scene->mRootNode ) )
    {
        std::cerr << "Error: the file wasn't successfully opened " << fileName.toStdString() << std::endl;
        isSuccessfully = false;
        return;
    }

    aiNode *node0 = scene->mRootNode->mChildren[0];
    aiNode *node1 = scene->mRootNode->mChildren[1];
    aiNode *node2 = scene->mRootNode->mChildren[2];
    aiNode *node3 = scene->mRootNode->mChildren[3];
    aiNode *node4 = scene->mRootNode->mChildren[4];
    aiNode *node5 = scene->mRootNode->mChildren[5];

    if ( !node0 || !node1 || !node2 || !node3 || !node4 || !node5 )
    {
        std::cerr << "Error: 'node* == 0' in the constructor 'MeshLoader::MeshLoader'" << std::endl;
        isSuccessfully = false;
        return;
    }

    aiMesh *mesh0 = scene->mMeshes[node0->mMeshes[0]];
    aiMesh *mesh1 = scene->mMeshes[node1->mMeshes[0]];
    aiMesh *mesh2 = scene->mMeshes[node2->mMeshes[0]];
    aiMesh *mesh3 = scene->mMeshes[node3->mMeshes[0]];
    aiMesh *mesh4 = scene->mMeshes[node4->mMeshes[0]];
    aiMesh *mesh5 = scene->mMeshes[node5->mMeshes[0]];

    if ( !mesh0 || !mesh1 || !mesh2 || !mesh3 || !mesh4 || !mesh5 )
    {
        std::cerr << "Error: 'node* == 0' in the constructor 'MeshLoader::MeshLoader'" << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( !fillContainers( mesh0, scene ) ||
         !fillContainers( mesh1, scene ) ||
         !fillContainers( mesh2, scene ) ||
         !fillContainers( mesh3, scene ) ||
         !fillContainers( mesh4, scene ) ||
         !fillContainers( mesh5, scene ) )
    {
         isSuccessfully = false;
         return;
    }
}

MeshLoader::~MeshLoader()
{

}

bool MeshLoader::fillContainers( const aiMesh *mesh, const aiScene *scene )
{
    aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

    aiString nameOfMaterial;
    mat->Get( AI_MATKEY_NAME, nameOfMaterial );

    aiString pathToImage;
    mat->GetTexture( aiTextureType_DIFFUSE, 0, &pathToImage);

    QStringList listOfImageNames = QString( pathToImage.C_Str() ).split( "\\" );

    if ( listOfImageNames.size() <= 1 )
    {
        std::cerr << "Error: 'listOfImageNames.size() <= 1' in the function 'void MeshLoader::fillContainers'" << std::endl;
        return false;
    }

    if ( std::string( nameOfMaterial.C_Str() ) == std::string( "Front" ) )
    {
        fileNames["front"] = listOfImageNames[listOfImageNames.size()-1].toStdString();
        if ( !fillTextureCoords( mesh, textureCoordsForFront ) )
            return false;
        fillVertices( mesh, verticesForFront );
        fillNormals( mesh, normalsForFront );
    }
    else if ( std::string( nameOfMaterial.C_Str() ) == std::string( "Back" ) )
    {
        fileNames["back"] = listOfImageNames[listOfImageNames.size()-1].toStdString();
        if ( !fillTextureCoords( mesh, textureCoordsForBack ) )
            return false;
        fillVertices( mesh, verticesForBack );
        fillNormals( mesh, normalsForBack );
    }
    else if ( std::string( nameOfMaterial.C_Str() ) == std::string( "Right" ) )
    {
        fileNames["right"] = listOfImageNames[listOfImageNames.size()-1].toStdString();
        if ( !fillTextureCoords( mesh, textureCoordsForRight ) )
            return false;
        fillVertices( mesh, verticesForRight );
        fillNormals( mesh, normalsForRight );
    }
    else if ( std::string( nameOfMaterial.C_Str() ) == std::string( "Left" ) )
    {
        fileNames["left"] = listOfImageNames[listOfImageNames.size()-1].toStdString();
        if ( !fillTextureCoords( mesh, textureCoordsForLeft ) )
            return false;
        fillVertices( mesh, verticesForLeft );
        fillNormals( mesh, normalsForLeft );
    }
    else if ( std::string( nameOfMaterial.C_Str() ) == std::string( "Top" ) )
    {
        fileNames["top"] = listOfImageNames[listOfImageNames.size()-1].toStdString();
        if ( !fillTextureCoords( mesh, textureCoordsForTop ) )
            return false;
        fillVertices( mesh, verticesForTop );
        fillNormals( mesh, normalsForTop );
    }
    else if ( std::string( nameOfMaterial.C_Str() ) == std::string( "Bottom" ) )
    {
        fileNames["bottom"] = listOfImageNames[listOfImageNames.size()-1].toStdString();
        if ( !fillTextureCoords( mesh, textureCoordsForBottom ) )
            return false;
        fillVertices( mesh, verticesForBottom );
        fillNormals( mesh, normalsForBottom );
    }

    return true;
}

void MeshLoader::fillVertices( const aiMesh *mesh,
                               std::vector<float> &vertices )
{
    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        vertices.push_back( mesh->mVertices[i].x );
        vertices.push_back( mesh->mVertices[i].y );
        vertices.push_back( mesh->mVertices[i].z );
    }
}

bool MeshLoader::fillTextureCoords( const aiMesh *mesh, std::vector<float> &textureCoords )
{
    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        if ( mesh->mTextureCoords[0] == 0 )
        {
            std::cerr << "Error: 'mesh->mTextureCoords[0] == 0' in "
                         "the function 'void MeshLoader::fillTextureCoords'";
            return false;
        }
        textureCoords.push_back( mesh->mTextureCoords[0][i].x );
        textureCoords.push_back( mesh->mTextureCoords[0][i].y );
    }

    return true;
}

void MeshLoader::fillNormals( const aiMesh *mesh, std::vector<float> &normals )
{
    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        normals.push_back( mesh->mNormals[i].x );
        normals.push_back( mesh->mNormals[i].y );
        normals.push_back( mesh->mNormals[i].z );
    }
}

