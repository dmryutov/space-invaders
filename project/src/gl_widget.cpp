#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include "mainwindow.hpp"
#include "action_manager.hpp"
#include "game.hpp"
#include "gl_widget.hpp"

// Constructor
GLWidget::GLWidget(MainWindow * mw, QColor const & background)
  : m_mainWindow(mw), m_background(background)
{
  m_mainWindow->setFixedSize(800, 600);
  setFocusPolicy(Qt::StrongFocus);
}

// Destructor
GLWidget::~GLWidget()
{
  makeCurrent();  // Set OpenGL content
  Renderer::Instance().Delete();
  doneCurrent();
}

void GLWidget::initializeGL()
{
  initializeOpenGLFunctions();
  Settings::Load(m_mainWindow);
  Renderer::Instance().Init(this);
  Game::Instance().Reset();

  m_time.start();
}

// Draw each frame
void GLWidget::paintGL()
{
  // Turn on painter
  auto & painter = Renderer::Instance().m_painter;
  if (!painter.isActive())
    painter.begin(this);

  // Set draw functions
  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);  // Set background
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear buffers
  glFrontFace(GL_CW);  // Bypass triangle in a clockwise direction
  glCullFace(GL_BACK);  // Cut back faces (invisible)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Interpolation
  Renderer::Instance().Blending(true);  // Enable blending

  // Game logic
  Game::Instance().Tick();
  if (Game::Instance().m_exitGame)
    m_mainWindow->close();

  // Turn off painter
  Renderer::Instance().Blending(false);
  if (painter.isActive())
    painter.end();

  if (!(m_frames % 100))
  {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;
  //update();  // Have sound bug with this
}

void GLWidget::resizeGL(int width, int height)
{
  Renderer::Instance().m_screenSize.setWidth(width);
  Renderer::Instance().m_screenSize.setHeight(height);
}

void GLWidget::keyPressEvent(QKeyEvent * e)
{
  ActionManager::Instance().PressKey(e->key());
}

void GLWidget::keyReleaseEvent(QKeyEvent * e)
{
  ActionManager::Instance().ReleaseKey(e->key());
}
