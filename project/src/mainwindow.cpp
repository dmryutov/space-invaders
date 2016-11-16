#include "mainwindow.hpp"
#include <iostream>
#include <sstream>

#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

#include "game.hpp"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  // From example
  /*m_glWidget = new GLWidget(this, qRgb(20, 20, 50));
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  setCentralWidget(m_glWidget);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  m_timer->start();*/

  // Window parameters
  setFixedSize(640, 480);
  setWindowTitle("Space Invaders");

  // Main menu layout
  QWidget * menuWidget = new QWidget(this);
  setCentralWidget(menuWidget);

  // Title
  QLabel * label = new QLabel("SPACE INVADERS", menuWidget);
  label->setGeometry(150, 20, 346, 45);
  label->setFont(QFont("Arial", 40));

  // Settings box
  QGroupBox * box = new QGroupBox("Settings", menuWidget);
  box->setGeometry(70, 80, 500, 170);
  QFormLayout * layout = new QFormLayout(box);
  layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

  // Difficulty
  QComboBox * difficultyCombo = new QComboBox();
  difficultyCombo->addItem("Easy");
  difficultyCombo->addItem("Normal");
  difficultyCombo->addItem("Hard");
  difficultyCombo->addItem("Nightmare");
  connect(difficultyCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(OnDifficultyChanged(int)));
  layout->addRow("Difficulty", difficultyCombo);
  // Aliens in row
  m_alienRow = new QSpinBox();
  m_alienRow->setRange(1, 10);
  m_alienRow->setValue(5);
  layout->addRow("Aliens in row", m_alienRow);
  // Aliens in column
  m_alienCol = new QSpinBox();
  m_alienCol->setRange(1, 3);
  m_alienCol->setValue(2);
  layout->addRow("Aliens in column", m_alienCol);
  // Obstacle count
  m_obstacleCount = new QSpinBox();
  m_obstacleCount->setRange(1, 3);
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

void MainWindow::OnDifficultyChanged(int value)
{
  Settings::GameDifficulty(value);
}

void MainWindow::OnStartClicked()
{
  Settings::alienRow = m_alienRow->value();
  Settings::alienCol = m_alienCol->value();
  Settings::obstacleCount = m_obstacleCount->value();
  Game::Instance().Start();
  LOG(LOG_INFO) << Game::Instance();
}

void MainWindow::OnExitClicked()
{
  close();
}
