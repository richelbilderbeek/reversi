#include "qtreversiwebdialog.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "qtreversiwidget.h"
#include "reversiboard.h"
#include "reversiwidget.h"

ribi::reversi::QtReversiWebDialog::QtReversiWebDialog(QWidget* parent)
  : QWidget(parent),
    m_board{new QtWidget},
    m_status{new QLabel},
    m_pass{new QPushButton("Pass")},
    m_size{new QComboBox}
{
  setWindowTitle("Reversi");
  setStyleSheet(
    "QWidget { background-color: rgb(0, 96, 0); color: white; }"
    "QPushButton:disabled { color: gray; }"
  );

  m_board->setFixedSize(400, 400);
  m_board->SetShowValidMoves(true);
  m_status->setAlignment(Qt::AlignCenter);
  QFont f = m_status->font();
  f.setPointSize(14);
  m_status->setFont(f);

  for (const int sz: {4, 6, 8, 10}) {
    m_size->addItem(QString("%1 x %1").arg(sz), sz);
  }
  m_size->setCurrentIndex(2);
  QPushButton* const new_game{new QPushButton("New game")};

  QHBoxLayout* const buttons{new QHBoxLayout};
  buttons->addWidget(m_pass);
  buttons->addStretch();
  buttons->addWidget(m_size);
  buttons->addWidget(new_game);

  QVBoxLayout* const layout{new QVBoxLayout(this)};
  layout->addWidget(m_status);
  layout->addWidget(m_board, 0, Qt::AlignCenter);
  layout->addLayout(buttons);

  connect(m_board, &QtWidget::signal_changed, this, &QtReversiWebDialog::OnChanged);
  connect(m_pass, &QPushButton::clicked, m_board, &QtWidget::Pass);
  connect(new_game, &QPushButton::clicked, this, &QtReversiWebDialog::OnNewGame);

  OnNewGame();
}

void ribi::reversi::QtReversiWebDialog::OnChanged()
{
  const Widget& game = m_board->GetGame();
  const Board& board = *game.GetBoard();
  const int n_red = board.Count(Square::player1);
  const int n_blue = board.Count(Square::player2);
  const Player player = game.GetCurrentPlayer();
  const Player other = player == Player::player1 ? Player::player2 : Player::player1;
  const bool can_move = !board.GetValidMoves(player).empty();
  const bool other_can_move = !board.GetValidMoves(other).empty();
  const QString score = QString("Red %1 - %2 Blue").arg(n_red).arg(n_blue);

  if (!can_move && !other_can_move)
  {
    QString result = "Draw";
    if (n_red > n_blue) result = "Red wins";
    if (n_blue > n_red) result = "Blue wins";
    m_status->setText(QString("Game over: %1! %2").arg(result, score));
    m_pass->setEnabled(false);
    return;
  }
  const QString name = player == Player::player1 ? "Red" : "Blue";
  m_status->setText(
    can_move
    ? QString("%1 to move. %2").arg(name, score)
    : QString("%1 cannot move and must pass. %2").arg(name, score)
  );
  m_pass->setEnabled(!can_move);
}

void ribi::reversi::QtReversiWebDialog::OnNewGame()
{
  m_board->NewGame(m_size->currentData().toInt());
}
