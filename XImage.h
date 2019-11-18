#pragma once

#include <QtWidgets/QWidget>
#include "ui_XImage.h"

class XImage : public QWidget
{
	Q_OBJECT

public:
	XImage(QWidget *parent = Q_NULLPTR);
	void ViewImage(QImage *img);

public slots://�źŲ�
	void Open();
	void Deal();

private:
	Ui::XImageClass ui;
	QImage *img = NULL;//���ͼƬ
	QImage imgDeal;//������������ͼƬ
};
