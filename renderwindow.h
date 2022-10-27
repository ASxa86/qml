/****************************************************************************
**
** Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company.
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

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QOffscreenSurface>
#include <QQuickWindow>
#include <QWindow>
#include <SFML/Graphics.hpp>

class QOpenGLContext;
class QQuickRenderControl;
class QQmlComponent;
class QQuickItem;

class RenderWindow : public QQuickWindow
{
public:
	RenderWindow(QQuickRenderControl &x);
	~RenderWindow();

protected:
	void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

private:
	sf::ContextSettings settings{24, 8};
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Sprite sprite;
	void syncScene();
	void draw();

	void onQmlComponentLoadingComplete();
	void updateRootItemSize();
	void createTexture();

	QOpenGLContext *m_context;
	QOffscreenSurface surface;
	QQuickRenderControl *m_renderControl;
	QQmlComponent *m_qmlComponent;
	QQuickItem *m_rootItem;
};

#endif // RENDERWINDOW_H
