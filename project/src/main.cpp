#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "mainwindow.hpp"

int main(int argc, char ** argv)
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow mw;
  mw.show();
  return a.exec();
}
