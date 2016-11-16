#include "textured_rect.hpp"

#include <QPainter>
#include <QPaintEngine>
#include <math.h>

TexturedRect::~TexturedRect()
{
  delete m_program;
  delete m_vertexShader;
  delete m_fragmentShader;
  m_vbo.destroy();
}

bool TexturedRect::Initialize(QOpenGLFunctions * functions)
{
  m_functions = functions;
  if (m_functions == nullptr) return false;

  m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
  char const * vsrc =
    "attribute highp vec3 a_position;\n"
    "attribute highp vec2 a_texCoord;\n"
    "uniform mediump mat4 u_modelViewProjection;\n"
    "varying highp vec2 v_texCoord;\n"
    "void main(void)\n"
    "{\n"
    "  gl_Position = u_modelViewProjection * vec4(a_position, 1.0);\n"
    "  v_texCoord = a_texCoord;\n"
    "}\n";
  if (!m_vertexShader->compileSourceCode(vsrc)) return false;

  m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
  char const * fsrc =
    "varying highp vec2 v_texCoord;\n"
    "uniform sampler2D tex;\n"
    "void main(void)\n"
    "{\n"
    "  highp vec4 color = texture2D(tex, v_texCoord);\n"
    "  gl_FragColor = clamp(color, 0.0, 1.0);\n"
    "}\n";
  if (!m_fragmentShader->compileSourceCode(fsrc)) return false;

  m_program = new QOpenGLShaderProgram();
  m_program->addShader(m_vertexShader);
  m_program->addShader(m_fragmentShader);
  if (!m_program->link()) return false;

  m_positionAttr = m_program->attributeLocation("a_position");
  m_texCoordAttr = m_program->attributeLocation("a_texCoord");
  m_modelViewProjectionUniform = m_program->uniformLocation("u_modelViewProjection");
  m_textureUniform = m_program->uniformLocation("tex");

  m_vbo.create();
  std::vector<float> data
  {
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 1.0f,

    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 1.0f
  };
  m_vbo.bind();
  m_vbo.allocate(data.data(), data.size() * sizeof(float));
  m_vbo.release();

  return true;
}

void TexturedRect::Render(QOpenGLTexture * texture, QVector2D const & position,
                          QSize const & size, QSize const & screenSize)
{
  if (texture == nullptr) return;

  QMatrix4x4 mvp;
  mvp.translate(2.0f * position.x() / screenSize.width() - 1.0f,
                2.0f * position.y() / screenSize.height() - 1.0f);
  mvp.scale(static_cast<float>(size.width()) / screenSize.width(),
            static_cast<float>(size.height()) / screenSize.height());

  m_program->bind();
  m_program->setUniformValue(m_textureUniform, 0); // use texture unit 0
  m_program->setUniformValue(m_modelViewProjectionUniform, mvp);
  texture->bind();
  m_program->enableAttributeArray(m_positionAttr);
  m_program->enableAttributeArray(m_texCoordAttr);
  m_vbo.bind();
  m_program->setAttributeBuffer(m_positionAttr, GL_FLOAT, 0, 3, 5 * sizeof(float));
  m_program->setAttributeBuffer(m_texCoordAttr, GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
  m_vbo.release();
  m_functions->glDrawArrays(GL_TRIANGLES, 0, 6);
  m_program->disableAttributeArray(m_positionAttr);
  m_program->disableAttributeArray(m_texCoordAttr);
  m_program->release();
}
