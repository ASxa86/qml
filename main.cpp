#include <QtCore/QTimer>
#include <QtGui/QGuiApplication>
#include <QtGui/QOffScreenSurface>
#include <QtGui/QOpenGLContext>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickGraphicsDevice>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickRenderControl>
#include <QtQuick/QQuickRenderTarget>
#include <QtQuick/QQuickView>
#include <QtQuick/QSGRendererInterface>
#include <iostream>

// int main(int argc, char** argv)
//{
//	QGuiApplication app{argc, argv};
//
//	// QQuickWindow::setGraphicsApi(QSGRendererInterface::GraphicsApi::OpenGL);
//
//	// QQmlApplicationEngine engine;
//	// engine.load(QUrl::fromLocalFile("D:/dev/qml/main.qml"));
//
//	QQuickView view;
//	view.setSource(QUrl::fromLocalFile("D:/dev/qml/main.qml"));
//	view.show();
//
//	return app.exec();
// }

#include <wingdi.h>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
	QGuiApplication app{argc, argv};

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	sf::RenderWindow window{sf::VideoMode{1280, 720}, "QML", 7, settings};
	window.setActive(true);

	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setColor(sf::Color::Red);

	QSize size;
	size.setHeight(static_cast<int>(texture.getSize().y));
	size.setWidth(static_cast<int>(texture.getSize().x));

	QQuickWindow::setGraphicsApi(QSGRendererInterface::GraphicsApi::OpenGL);
	QQuickRenderControl control;

	QTimer timer;
	timer.setSingleShot(true);
	timer.setInterval(5);

	QQuickWindow view{&control};
	view.setSurfaceType(QSurface::SurfaceType::OpenGLSurface);

	QSurfaceFormat format;
	format.setStencilBufferSize(8);
	format.setDepthBufferSize(24);
	view.setFormat(format);

	auto hglrc = wglGetCurrentContext();
	auto context = QNativeInterface::QWGLContext::fromNative(hglrc, window.getSystemHandle());

	QOffscreenSurface surface;
	surface.setFormat(context->format());
	surface.create();

	QQmlEngine engine;
	engine.setIncubationController(view.incubationController());

	QObject::connect(&view, &QQuickWindow::sceneGraphInitialized,
					 [&]
					 {
						 context->makeCurrent(&surface);
						 auto target = QQuickRenderTarget::fromOpenGLTexture(texture.getNativeHandle(), size);
						 view.setRenderTarget(target);
					 });

	QObject::connect(&timer, &QTimer::timeout,
					 [&]
					 {
						 context->makeCurrent(&surface);
						 control.beginFrame();
						 control.polishItems();
						 control.sync();
						 control.render();
						 control.endFrame();

						 window.setActive(true);
						 window.clear();
						 window.draw(sprite);
						 window.display();
					 });

	QObject::connect(&control, &QQuickRenderControl::renderRequested,
					 [&]
					 {
						 if(timer.isActive() == false)
						 {
							 timer.start();
						 }
					 });

	QObject::connect(&control, &QQuickRenderControl::sceneChanged,
					 [&]
					 {
						 if(timer.isActive() == false)
						 {
							 timer.start();
						 }
					 });

	QObject::connect(&view, &QQuickWindow::sceneGraphError,
					 [=](QQuickWindow::SceneGraphError error, const QString& message)
					 { std::cout << "!!!!!!!! ERROR - QML Scene Graph: " << error << message.toStdString(); });

	QObject::connect(&engine, &QQmlEngine::warnings,
					 [=](QList<QQmlError> warnings)
					 {
						 foreach(const QQmlError& warning, warnings)
						 {
							 std::cout << "!!!! QML WARNING : " << warning.toString().toStdString() << "  ";
						 }
					 });

	QQmlComponent component{&engine, QUrl::fromLocalFile(R"(D:\dev\qml\main.qml)")};

	while(component.isLoading() == true)
		;

	auto root = component.create();
	auto rootItem = qobject_cast<QQuickItem*>(root);
	rootItem->setParentItem(view.contentItem());
	rootItem->forceActiveFocus();

	rootItem->setSize(size);
	view.resize(size);

	context->makeCurrent(&surface);
	view.setGraphicsDevice(QQuickGraphicsDevice::fromOpenGLContext(context));
	control.initialize();

	return app.exec();
}
