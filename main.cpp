#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char** argv)
{
	QGuiApplication app{ argc, argv };

	//QQuickWindow::setGraphicsApi(QSGRendererInterface::GraphicsApi::OpenGL);

	QQmlApplicationEngine engine;
	engine.load(QUrl::fromLocalFile(":/qml/main.qml"));

	//QQuickView view;
	//view.setSource(QUrl::fromLocalFile("D:/qml/main.qml"));
	//view.show();

	return app.exec();
}
