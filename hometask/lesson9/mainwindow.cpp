#include "mainwindow.hpp"
#include <iostream>
#include <sstream>

#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

#include "gl_widget.hpp"
#include "PugiXML/pugixml.cpp"
#include "game.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  // Window parameters
  setFixedSize(640, 480);
  setWindowTitle("Space Invaders");
  // Background
  /*QPalette Pal(palette());
  Pal.setColor(QPalette::Background, QColor(7, 47, 69));
  setAutoFillBackground(true);
  setPalette(Pal);*/

  // Main menu layout
  QWidget * menuWidget = new QWidget(this);
  setCentralWidget(menuWidget);

  // Title
  QLabel * label = new QLabel("SPACE INVADERS", menuWidget);
  label->setGeometry(150, 20, 346, 45);
  label->setFont(QFont("Arial", 40));
  /*Pal.setColor(label->foregroundRole(), Qt::white);
  label->setPalette(Pal);*/

  // Settings box
  QGroupBox * box = new QGroupBox("Settings", menuWidget);
  box->setGeometry(70, 80, 500, 170);
  QFormLayout * layout = new QFormLayout(box);
  layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

  pugi::xml_document doc;
  doc.load_file("settings.xml");

  auto gm = doc.child("game");
  // Difficulty
  m_difficultyCombo = new QComboBox();
  m_difficultyCombo->addItem("Easy");
  m_difficultyCombo->addItem("Normal");
  m_difficultyCombo->addItem("Hard");
  m_difficultyCombo->addItem("Nightmare");
  if (gm.attribute("difficulty"))
    m_difficultyCombo->setCurrentIndex(gm.attribute("difficulty").as_int());
  layout->addRow("Difficulty", m_difficultyCombo);

  auto al = doc.child("alien");
  // Aliens in row
  m_alienRow = new QSpinBox();
  m_alienRow->setRange(1, 10);
  if (al.attribute("row"))
    m_alienRow->setValue(al.attribute("row").as_int());
  else
    m_alienRow->setValue(5);
  layout->addRow("Aliens in row", m_alienRow);
  // Aliens in column
  m_alienCol = new QSpinBox();
  m_alienCol->setRange(1, 3);
  if (al.attribute("col"))
    m_alienCol->setValue(al.attribute("col").as_int());
  else
    m_alienCol->setValue(2);
  layout->addRow("Aliens in column", m_alienCol);

  auto obst = doc.child("obstacle");
  // Obstacle count
  m_obstacleCount = new QSpinBox();
  m_obstacleCount->setRange(1, 3);
  if (obst.attribute("count"))
    m_obstacleCount->setValue(obst.attribute("count").as_int());
  else
    m_obstacleCount->setValue(3);
  layout->addRow("Obstacle count", m_obstacleCount);

  // Start game
  QPushButton * startButton = new QPushButton("Start", menuWidget);
  startButton->setGeometry(220, 280, 200, 50);
  connect(startButton, SIGNAL(clicked()), this, SLOT(OnStartClicked()));
  // Exit
  QPushButton * exitButton = new QPushButton("Exit", menuWidget);
  exitButton->setGeometry(220, 340, 200, 50);
  connect(exitButton, SIGNAL(clicked()), this, SLOT(OnExitClicked()));
}

MainWindow::~MainWindow()
{}

void MainWindow::OnStartClicked()
{
  // Save settings to file
  pugi::xml_document tree;
  auto gm = tree.append_child("game");
  gm.append_attribute("difficulty") = m_difficultyCombo->currentIndex();
  auto al = tree.append_child("alien");
  al.append_attribute("row") = m_alienRow->value();
  al.append_attribute("col") = m_alienCol->value();
  auto obst = tree.append_child("obstacle");
  obst.append_attribute("count") = m_obstacleCount->value();
  tree.save_file("settings.xml");

  // Apply settings
  Settings::GameDifficulty(m_difficultyCombo->currentIndex());
  Settings::alienRow = m_alienRow->value();
  Settings::alienCol = m_alienCol->value();
  Settings::obstacleCount = m_obstacleCount->value();
  Game::Instance().Start();
  LOG(LOG_INFO) << Game::Instance();

  // Space
  m_glWidget = new GLWidget(this, qRgb(20, 20, 50));
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  setCentralWidget(m_glWidget);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  m_timer->start();
  setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::OnExitClicked()
{
  close();
}
