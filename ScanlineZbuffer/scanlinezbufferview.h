#ifndef SCANLINEZBUFFERVIEW_H
#define SCANLINEZBUFFERVIEW_H

#include <QGraphicsView>
#include "Zbuffer.h"
#include <qevent.h>

class ScanlineZbufferView : public QGraphicsView
{ 
	Q_OBJECT

public:
	
	Zbuffer &zbuffer;

	/// show image
	QImage image;
	QGraphicsScene *qscene;
	
	/// mouse event
	bool lbtnPressing;
	QPointF lastPt;
	int step;
public:
	ScanlineZbufferView(QWidget *parent = 0);
    ~ScanlineZbufferView();
	void displayImage();
	void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
private:
    
};

#endif // SCANLINEZBUFFERVIEW_H
