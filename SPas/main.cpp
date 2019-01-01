#include <QtWidgets/QApplication>
//#include <QTextCodec>
#include "sp_media_parser_qt.h"

//NOTICE THIS CODE USE THE VERSION OF FFMPEG IS 3.4

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	SPas w;
	w.show();
	return a.exec();
}
