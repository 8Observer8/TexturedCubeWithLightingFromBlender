#include "Scene.h"
#include "MeshLoader.h"
#include <QDir>
#include <iostream>

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_xRot( 0.0f ),
    m_zRot( 0.0f ),
    m_scale( 1.0f )
{

}

Scene::~Scene()
{
    makeCurrent();
    delete m_cube;
    doneCurrent();
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() )
    {
        std::cerr << "Error: unable to link a shader program." << std::endl;
        return;
    }

    m_vertexAttrLoc = m_program.attributeLocation( "vertexAttr" );
    m_normalAttrLoc = m_program.attributeLocation( "normalAttr" );
    m_textureAttrLoc = m_program.attributeLocation( "textureAttr" );

    m_textureUniformLoc = m_program.uniformLocation( "textureUniform" );

    m_mvMatrixLoc = m_program.uniformLocation( "mvMatrix" );
    m_projMatrixLoc = m_program.uniformLocation( "projMatrix" );
    m_normalMatrixLoc = m_program.uniformLocation( "normalMatrix" );

    if ( !m_program.bind() )
    {
        std::cerr << "Error: unable to bind a shader program." << std::endl;
        return;
    }
    m_lightPosLoc = m_program.uniformLocation( "lightPos" );
    m_program.setUniformValue( m_lightPosLoc, QVector3D( 0.0f, 0.0f, 50.0f ) );
    m_program.release();

    QString fileName = QDir::currentPath() + QString( "/Models/TexturedCube.obj" );
    MeshLoader loader( fileName );

    if ( !loader.isSuccessfully )
        return;

    m_cube = new Cube( &m_program, m_vertexAttrLoc, m_normalAttrLoc, m_textureAttrLoc, m_textureUniformLoc );
    if ( !m_cube->fillFromLoader( &loader ) )
        return;

    m_camera.setToIdentity();
    m_camera.translate( 0.0f, 0.0f, -5.0f );

    glEnable( GL_DEPTH_TEST );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    m_world.setToIdentity();
    m_world.rotate( m_xRot, 1.0f, 0.0f, 0.0f );
    m_world.rotate( m_zRot, 0.0f, 0.0f, 1.0f );
    m_world.scale( m_scale );
    m_program.setUniformValue( m_mvMatrixLoc, m_camera * m_world );

    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program.setUniformValue( m_normalMatrixLoc, normalMatrix );

    m_program.setUniformValue( m_projMatrixLoc, m_proj );

    if ( m_cube != 0 )
        m_cube->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    if ( h == 0 )
        h = 1;

    glViewport( 0, 0, w, h );

    m_proj.setToIdentity();
    m_proj.perspective( 45.0f, float( w ) / float( h ), 0.01f, 500.0f );
}

void Scene::mousePressEvent( QMouseEvent *event )
{
    m_mousePosition = event->pos();
}

void Scene::mouseMoveEvent( QMouseEvent *event )
{
    m_xRot += 180.0f * ( float ) ( event->y() - m_mousePosition.y() ) / height();
    m_zRot += 180.0f * ( float ) ( event->x() - m_mousePosition.x() ) / width();

    m_mousePosition = event->pos();

    update();
}

void Scene::wheelEvent( QWheelEvent *event )
{
    if ( event->delta() > 0 )
        scalePlus();
    else if ( event->delta() < 0 )
        scaleMinus();

    update();
}

void Scene::scalePlus()
{
    m_scale *= 1.1f;
}

void Scene::scaleMinus()
{
    m_scale /= 1.1f;
}
