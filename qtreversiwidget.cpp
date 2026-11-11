#include "qtreversiwidget.h"

#include <algorithm>
#include <cstdlib>

#include <QMouseEvent>
#include <QPainter>

#include "reversiboard.h"
#include "reversiwidget.h"

#include "reversimove.h"


ribi::reversi::QtWidget::QtWidget(QWidget* parent, Qt::WindowFlags f)
  : QWidget(parent,f),
    m_reversi(new Widget(4)),
    m_color_player1(    QColor(255,  0,  0)),
    m_color_player2(    QColor(  0,  0,255)),
    m_color_square_even(QColor( 32, 32, 32)),
    m_color_square_odd( QColor( 64, 64, 64)),
    m_show_valid_moves{false}
{
  //Allows this widget to respond to mouse moving over it
  this->setMouseTracking(true);
}

void ribi::reversi::QtWidget::NewGame(const int size)
{
  m_reversi.reset(new Widget(size));
  update();
  emit signal_changed();
}

void ribi::reversi::QtWidget::Pass()
{
  const boost::shared_ptr<MovePass> move{new MovePass};
  m_reversi->DoMove(move);
  update();
  emit signal_changed();
}

void ribi::reversi::QtWidget::SetShowValidMoves(const bool show) noexcept
{
  m_show_valid_moves = show;
  update();
}

void ribi::reversi::QtWidget::mousePressEvent(QMouseEvent * e)
{
  const int sz = m_reversi->GetBoard()->GetSize();
  const int x = (e->pos().x() * sz) / this->width();
  const int y = (e->pos().y() * sz) / this->height();
  if (x < 0 || y < 0 || x >= sz || y >= sz) return;

  const boost::shared_ptr<MovePlacePiece> move {
    new MovePlacePiece(x,y)
  };

  if (m_reversi->CanDoMove(move))
  {
     m_reversi->DoMove(move);
     update();
     emit signal_changed();
  }
}

void ribi::reversi::QtWidget::paintEvent(QPaintEvent *)
{

  QPainter painter(this);
  const int width  = this->width();
  const int height = this->height();
  const int sz = m_reversi->GetBoard()->GetSize();
  QBrush brush = painter.brush();
  brush.setStyle(Qt::SolidPattern);
  for (int row=0; row!=sz; ++row)
  {
    const int y1 = (height * (row + 0)) / sz;
    const int y2 = (height * (row + 1)) / sz;
    for (int col=0; col!=sz; ++col)
    {
      const int x1 = (width * (col + 0)) / sz;
      const int x2 = (width * (col + 1)) / sz;
      switch (m_reversi->GetBoard()->Get(col,row))
      {
        case Square::player1: brush.setColor(m_color_player1); break;
        case Square::player2: brush.setColor(m_color_player2); break;
        case Square::empty  : brush.setColor((col + row) % 2 ? m_color_square_odd : m_color_square_even); break;

      }
      painter.setBrush(brush);
      painter.drawRect(x1,y1,x2-x1,y2-y1);
    }
  }
  if (m_show_valid_moves)
  {
    const Player player = m_reversi->GetCurrentPlayer();
    brush.setColor(player == Player::player1 ? m_color_player1 : m_color_player2);
    painter.setBrush(brush);
    for (const auto& p: m_reversi->GetBoard()->GetValidMoves(player))
    {
      const int x1 = (width  * (p.first  + 0)) / sz;
      const int x2 = (width  * (p.first  + 1)) / sz;
      const int y1 = (height * (p.second + 0)) / sz;
      const int y2 = (height * (p.second + 1)) / sz;
      const int r = std::max(2, (x2 - x1) / 8);
      painter.drawEllipse(QPoint((x1 + x2) / 2, (y1 + y2) / 2), r, r);
    }
  }
}
