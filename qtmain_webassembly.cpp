#include <QApplication>
#include "qtreversiwebdialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::reversi::QtReversiWebDialog w;
#ifdef Q_OS_WASM
  w.showFullScreen();
#else
  w.show();
#endif
  return a.exec();
}
