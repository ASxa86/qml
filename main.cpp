#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include "Triangles.h"

int main(int argc, char** argv)
{
	qmlRegisterType<Triangles>("Triangles", 1, 0, "Triangles");

	QGuiApplication app{argc, argv};

	QSurfaceFormat format;
	format.setSwapInterval(0);
	QSurfaceFormat::setDefaultFormat(format);

	// QQuickWindow::setGraphicsApi(QSGRendererInterface::GraphicsApi::OpenGL);

	QQmlApplicationEngine engine;
	engine.load(QUrl::fromLocalFile("C:/dev/qml/main.qml"));

	// QQuickView view;
	// view.setSource(QUrl::fromLocalFile("D:/qml/main.qml"));
	// view.show();

	return app.exec();
}
