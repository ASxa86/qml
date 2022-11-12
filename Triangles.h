#pragma once

#include <QQuickItem>

class Triangles : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(QQmlComponent* delegate READ getDelegate WRITE setDelegate)
	QML_ELEMENT

public:
	Triangles(QQuickItem* parent = nullptr);

	void componentComplete() override;
	QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

	void setDelegate(QQmlComponent* x);
	QQmlComponent* getDelegate() const;

private:
	QQmlComponent* delegate{};
	std::vector<std::chrono::duration<float>> frames;
	std::chrono::steady_clock::time_point start{};
	int frameCount{};
};
