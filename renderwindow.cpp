/****************************************************************************
**
** Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company.
** Author: Giuseppe D'Angelo
** Contact: info@kdab.com
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "renderwindow.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>

#include <QQuickGraphicsDevice>
#include <QQuickItem>
#include <QQuickRenderControl>
#include <QQuickRenderTarget>

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

#include <QTimer>

RenderWindow::RenderWindow(QQuickRenderControl &x)
	: QQuickWindow{&x}, window{sf::VideoMode{600, 600}, "QML", 7, settings}, m_context(0), m_renderControl(&x), m_qmlComponent(0), m_rootItem(0)
{
	this->window.setActive(true);

	// create the GL context
	auto hglrc = wglGetCurrentContext();
	m_context = QNativeInterface::QWGLContext::fromNative(hglrc, this->window.getSystemHandle());

	this->surface.setFormat(m_context->format());
	this->surface.create();

	m_context->makeCurrent(&this->surface);

	// try to "batch" multiple scene changed signals in one sync
	QTimer *sceneSyncTimer = new QTimer(this);
	sceneSyncTimer->setInterval(5);
	sceneSyncTimer->setSingleShot(true);
	connect(sceneSyncTimer, &QTimer::timeout, this, &RenderWindow::syncScene);

	connect(this, &QQuickWindow::sceneGraphInitialized, this, &RenderWindow::createTexture);
	connect(m_renderControl, &QQuickRenderControl::sceneChanged, sceneSyncTimer, static_cast<void (QTimer::*)()>(&QTimer::start));

	connect(m_renderControl, &QQuickRenderControl::renderRequested, this, &RenderWindow::draw);

	this->setGraphicsDevice(QQuickGraphicsDevice::fromOpenGLContext(m_context));
	m_context->makeCurrent(&this->surface);
	m_renderControl->initialize();

	// load a QML scene "manually"
	QQmlEngine *engine = new QQmlEngine(this);

	if(!engine->incubationController())
		engine->setIncubationController(this->incubationController());

	m_qmlComponent = new QQmlComponent(engine, this);

	connect(m_qmlComponent, &QQmlComponent::statusChanged, this, &RenderWindow::onQmlComponentLoadingComplete);

	m_qmlComponent->loadUrl(QUrl::fromLocalFile("D:/dev/qml/main.qml"));

	// also, just for the sake of it, trigger a redraw every 500 ms no matter what
	QTimer *redrawTimer = new QTimer(this);
	connect(redrawTimer, &QTimer::timeout, this, &RenderWindow::draw);
	redrawTimer->start(500);
}

RenderWindow::~RenderWindow()
{
	m_context->makeCurrent(&this->surface);

	delete m_rootItem;
	delete m_qmlComponent;

	m_context->doneCurrent();
}

void RenderWindow::resizeEvent(QResizeEvent *e)
{
	// Simulate the "resize root item to follow window"
	updateRootItemSize();
	QWindow::resizeEvent(e);
}

void RenderWindow::syncScene()
{
	m_renderControl->beginFrame();
	m_renderControl->polishItems();

	m_renderControl->sync();
	m_renderControl->endFrame();
	draw();
}

void RenderWindow::draw()
{
	m_context->makeCurrent(&this->surface);
	// m_context->functions()->glViewport(0, 0, width() * devicePixelRatio(), height() * devicePixelRatio());

	m_renderControl->beginFrame();
	m_renderControl->render();
	m_renderControl->endFrame();

	auto image = this->texture.copyToImage();
	image.flipVertically();
	// THIS IS WORKING!!!!
	image.saveToFile("test.png");

	this->beginExternalCommands();

	// m_context->swapBuffers(&this->surface);

	// this->window.setActive(true);
	this->window.clear(sf::Color::Cyan);
	sf::Texture t;
	t.loadFromFile("test.png");
	this->sprite.setTexture(t, true);
	this->window.draw(this->sprite);
	this->window.display();

	this->endExternalCommands();
}

void RenderWindow::onQmlComponentLoadingComplete()
{
	if(m_qmlComponent->isLoading())
		return;
	if(m_qmlComponent->isError())
	{
		const QList<QQmlError> errorList = m_qmlComponent->errors();
		foreach(const QQmlError &error, errorList)
			qWarning() << error.url() << error.line() << error;

		qFatal("Unable to load QML file");
	}

	QObject *rootObject = m_qmlComponent->create();
	m_rootItem = qobject_cast<QQuickItem *>(rootObject);
	if(!m_rootItem)
		qFatal("Did not load a Qt Quick scene");

	m_rootItem->setParentItem(this->contentItem());
}

void RenderWindow::updateRootItemSize()
{
	auto size = this->texture.getSize();

	if(m_rootItem)
	{
		m_rootItem->setWidth(size.x);
		m_rootItem->setHeight(size.y);
	}

	this->setHeight(size.x);
	this->setWidth(size.y);
}

void RenderWindow::createTexture()
{
	auto size = this->window.getSize();
	this->texture.create(size.x, size.y);

	auto target = QQuickRenderTarget::fromOpenGLTexture(this->texture.getNativeHandle(), {static_cast<int>(size.x), static_cast<int>(size.y)});
	this->setRenderTarget(target);
}

void RenderWindow::mousePressEvent(QMouseEvent *e)
{
	qApp->sendEvent(this, e);
	if(!e->isAccepted())
		QWindow::mousePressEvent(e);
}

void RenderWindow::mouseMoveEvent(QMouseEvent *e)
{
	qApp->sendEvent(this, e);
	if(!e->isAccepted())
		QWindow::mousePressEvent(e);
}

void RenderWindow::mouseReleaseEvent(QMouseEvent *e)
{
	qApp->sendEvent(this, e);
	if(!e->isAccepted())
		QWindow::mousePressEvent(e);
}
