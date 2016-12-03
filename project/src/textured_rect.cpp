#include "textured_rect.hpp"

#include <QPainter>
#include <QPaintEngine>
#include <Qtime>
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

  // Shaders
  m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
  char const * vsrc =
    "attribute highp vec3 a_position;\n"
    "attribute highp vec2 a_texCoord;\n"
    "uniform mediump mat4 u_modelViewProjection;\n"
    "varying highp vec2 v_texCoord;\n"
    "uniform float frame;\n"
    "uniform float frameCount;\n"
    "void main(void)\n"
    "{\n"
    "  gl_Position = u_modelViewProjection * vec4(a_position, 1.0);\n"
    "  if (frameCount == 1.0)\n"
    "    v_texCoord = a_texCoord;\n"
    "  else\n"
    "    v_texCoord = vec2((frame + a_texCoord[0])/frameCount, a_texCoord[1]);\n"
    "}\n";
  // Shader compilation
  if (!m_vertexShader->compileSourceCode(vsrc)) return false;
  m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
  char const * fsrc =
    "varying highp vec2 v_texCoord;\n"
    "uniform sampler2D tex;\n"
    "uniform float time;\n"
    "uniform float posx;\n"
    "uniform float posy;\n"
    "void main(void)\n"
    "{\n"
    "  highp vec4 color = texture2D(tex, v_texCoord);\n"
    "  float n = time == -1.0 ? 1.0 : sin((6.14*time + posx)/10.0 + 0.5);\n"
    "  gl_FragColor = vec4(color.r, color.g, color.b, n) * color.a;\n"
    "}\n";
  if (!m_fragmentShader->compileSourceCode(fsrc)) return false;

  // Adding shaders to program
  m_program = new QOpenGLShaderProgram();
  m_program->addShader(m_vertexShader);
  m_program->addShader(m_fragmentShader);
  if (!m_program->link()) return false;

  m_positionAttr = m_program->attributeLocation("a_position");
  m_texCoordAttr = m_program->attributeLocation("a_texCoord");
  m_modelViewProjectionUniform = m_program->uniformLocation("u_modelViewProjection");
  m_textureUniform = m_program->uniformLocation("tex");  // Set texture
  m_time = m_program->uniformLocation("time");
  m_posx = m_program->uniformLocation("posx");
  m_frame = m_program->uniformLocation("frame");
  m_frameCount = m_program->uniformLocation("frameCount");

  // Create vertex (вершинный) buffer
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
  m_vbo.bind();  // Activate vertex buffer
  m_vbo.allocate(data.data(), data.size() * sizeof(float));  // Allocate memory
  m_vbo.release();

  return true;
}

void TexturedRect::Render(QOpenGLTexture * texture, QVector2D const & position,
                          QSize const & size, QSize const & screenSize, float rate, bool blink, int frame, int frameCount)
{
  if (texture == nullptr) return;

  QMatrix4x4 mvp;
  QTime t;
  t.start();

  mvp.translate(2.0f * position.x() * rate / screenSize.width() - 1.0f,
                2.0f * position.y() * rate / screenSize.height() - 1.0f);
  mvp.scale(static_cast<float>(rate * size.width()) / screenSize.width(),
            static_cast<float>(rate * size.height()) / screenSize.height());

  m_program->bind();  // Program activation
  m_program->setUniformValue(m_textureUniform, 0);  // Use 0 texture unit

  m_program->setUniformValue(m_time, blink ? (float)t.msec()/100 : -1);
  m_program->setUniformValue(m_posx, position.x());
  m_program->setUniformValue(m_frame, (float)frame);
  m_program->setUniformValue(m_frameCount, (float)frameCount);

  m_program->setUniformValue(m_modelViewProjectionUniform, mvp);
  texture->bind();  // Texture activation
  m_program->enableAttributeArray(m_positionAttr);
  m_program->enableAttributeArray(m_texCoordAttr);
  m_vbo.bind();
  m_program->setAttributeBuffer(m_positionAttr, GL_FLOAT, 0, 3, 5 * sizeof(float));  // Source, type, from, size, offset
  m_program->setAttributeBuffer(m_texCoordAttr, GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
  m_vbo.release();
  m_functions->glDrawArrays(GL_TRIANGLES, 0, 6);
  m_program->disableAttributeArray(m_positionAttr);
  m_program->disableAttributeArray(m_texCoordAttr);
  m_program->release();  // Program deactivation
}
