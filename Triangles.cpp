#include "Triangles.h"

#include <QQuickWindow>
#include <QSGFlatColorMaterial>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGMaterial>

Triangles::Triangles(QQuickItem* parent) : QQuickItem{parent}
{
	this->setFlag(QQuickItem::Flag::ItemHasContents);
}

void Triangles::setDelegate(QQmlComponent* x)
{
	this->delegate = x;
}

QQmlComponent* Triangles::getDelegate() const
{
	return this->delegate;
}

void Triangles::componentComplete()
{
	this->QQuickItem::componentComplete();

	for(auto i = 0; i < 100; i++)
	{
		if(this->delegate != nullptr)
		{
			auto obj = this->delegate->create();
			auto item = qobject_cast<QQuickItem*>(obj);
			item->setParentItem(this);
			item->setPosition({(float)i, (float)i});
			obj->setParent(this);
		}
	}

	// QObject::connect(
	//	this->window(), &QQuickWindow::beforeFrameBegin, this,
	//	[this]
	//	{
	//		if(this->start == std::chrono::steady_clock::time_point{})
	//		{
	//			this->start = std::chrono::steady_clock::now();
	//		}

	//		auto now = std::chrono::steady_clock::now();
	//		const std::chrono::duration<float> elapsed = now - this->start;
	//		this->start = now;

	//		this->frames.push_back(elapsed);

	//		const auto sum = std::accumulate(std::begin(this->frames), std::end(this->frames), std::chrono::duration<float>::zero());
	//		const auto avg = sum / this->frames.size();
	//		const auto fps = 1.0F / avg.count();

	//		qDebug() << "FPS: " << QString::number(fps, 'f', 2);
	//	},
	//	Qt::DirectConnection);
}

QSGNode* Triangles::updatePaintNode(QSGNode* old, UpdatePaintNodeData*)
{
	if(this->start == std::chrono::steady_clock::time_point{})
	{
		this->start = std::chrono::steady_clock::now();
	}

	auto now = std::chrono::steady_clock::now();
	const std::chrono::duration<float> elapsed = now - this->start;
	this->start = now;

	this->frames.push_back(elapsed);

	const auto sum = std::accumulate(std::begin(this->frames), std::end(this->frames), std::chrono::duration<float>::zero());
	const auto avg = sum / this->frames.size();
	const auto fps = 1.0F / avg.count();

	qDebug() << "FPS: " << QString::number(fps, 'f', 2);
	this->update();

	return nullptr;
}
