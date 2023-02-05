#include "sewerclient.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "sewer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    SewerClient w;
    // ¹ýÂË´°¿Ú°´Å¥ [2/5/2023]
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinimizeButtonHint;
	flags |= Qt::WindowCloseButtonHint;
	w.setWindowFlags(flags);

    w.show();
    return a.exec();
}
