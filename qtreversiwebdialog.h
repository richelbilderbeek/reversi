#ifndef QTREVERSIWEBDIALOG_H
#define QTREVERSIWEBDIALOG_H

#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;

namespace ribi {
namespace reversi {

class QtWidget;

///The main window of the online (WebAssembly) version:
///a board, a status line and buttons to pass and start a new game
class QtReversiWebDialog : public QWidget
{
  Q_OBJECT
public:
  explicit QtReversiWebDialog(QWidget* parent = nullptr);

private slots:
  void OnChanged();
  void OnNewGame();

private:
  QtWidget* m_board;
  QLabel* m_status;
  QPushButton* m_pass;
  QComboBox* m_size;
};

} //~namespace reversi
} //~namespace ribi

#endif // QTREVERSIWEBDIALOG_H
