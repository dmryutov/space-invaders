#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QSpinBox>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
private:
  QSpinBox * m_alienRow;
  QSpinBox * m_alienCol;
  QSpinBox * m_obstacleCount;

  // From example
  /*QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QOpenGLWidget * m_glWidget = nullptr;*/

private slots:
  void OnDifficultyChanged(int);
  void OnStartClicked();
  void OnExitClicked();
};

#endif // MAINWINDOW_H
