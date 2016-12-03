#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QVector2D>

class TexturedRect
{
public:
  TexturedRect() = default;
  ~TexturedRect();

  bool Initialize(QOpenGLFunctions * functions);
  void Render(QOpenGLTexture * texture, QVector2D const & position,
              QSize const & size, QSize const & screenSize, float rate, bool blink = false, int frame = 1, int frameCount = 1);

private:
  QOpenGLFunctions * m_functions = nullptr;
  QOpenGLShader * m_vertexShader = nullptr;
  QOpenGLShader * m_fragmentShader = nullptr;
  QOpenGLShaderProgram * m_program = nullptr;

  QOpenGLBuffer m_vbo;

  int m_positionAttr = 0;
  int m_texCoordAttr = 0;
  int m_modelViewProjectionUniform = 0;
  int m_textureUniform = 0;
  int m_time = 0;
  float m_posx = 0;
  float m_frame = 0;
  float m_frameCount = 0;
};
