#include "scanlinezbufferview.h"

ScanlineZbufferView::ScanlineZbufferView(QWidget *parent)
	: QGraphicsView(parent),
	  lbtnPressing(false),
	  zbuffer(zbuffer),
	  step(10)

{
	qscene = new QGraphicsScene;
}

ScanlineZbufferView::~ScanlineZbufferView()
{
	if (qscene)
		delete qscene;
}


void ScanlineZbufferView::displayImage(){
	qscene->addPixmap(QPixmap::fromImage(image));
	resize(qscene->width() + 10, qscene->height() + 10);
	setScene(qscene);
}

void ScanlineZbufferView::mousePressEvent(QMouseEvent* e)
{
	lastPt = e->pos();
	lbtnPressing = true;
}

void ScanlineZbufferView::mouseReleaseEvent(QMouseEvent* e)
{
	lbtnPressing = false;
}

void ScanlineZbufferView::mouseMoveEvent(QMouseEvent* e)
{
	if (lbtnPressing == 0) return;
	float dx = (e->pos().x() - lastPt.x()) / step;
	float dy = (e->pos().y() - lastPt.y()) / step;
	lastPt = e->pos();
	if (fabs(dx) > fabs(dy))
	{
		image = zbuffer.ScanlineZbuffer(zbuffer.scene, dx, 0.f, 1.f);
		displayImage();
	}
	else
	{
		image = zbuffer.ScanlineZbuffer(zbuffer.scene, 0.f, dy, 1.f);
		displayImage();
	}
}