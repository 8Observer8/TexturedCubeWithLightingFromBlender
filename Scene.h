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

#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QMatrix4x4>
#include "Cube.h"

class Scene : public QOpenGLWidget
{
public:
    Scene( QWidget *parent = 0 );
    ~Scene();

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

    void wheelEvent( QWheelEvent *event );

    void scalePlus();
    void scaleMinus();

    QOpenGLShaderProgram m_program;
    int m_vertexAttrLoc;
    int m_textureAttrLoc;
    int m_textureUniformLoc;
    int m_normalAttrLoc;

    int m_lightPosLoc;

    int m_mvMatrixLoc;
    int m_projMatrixLoc;
    int m_normalMatrixLoc;

    Cube *m_cube;

    QPoint m_mousePosition;
    float m_xRot;
    float m_zRot;
    float m_scale;

    QMatrix4x4 m_world;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_proj;
};

#endif // SCENE_H
