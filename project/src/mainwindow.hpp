#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QSpinBox>
#include <QComboBox>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
private:
  QComboBox * m_difficultyCombo = nullptr;
  QSpinBox * m_alienRow = nullptr;
  QSpinBox * m_alienCol = nullptr;
  QSpinBox * m_obstacleCount = nullptr;

  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QOpenGLWidget * m_glWidget = nullptr;

private slots:
  void OnStartClicked();
  void OnExitClicked();
};
