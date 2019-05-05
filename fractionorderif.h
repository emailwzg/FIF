#ifndef FRACTIONORDERIF_H
#define FRACTIONORDERIF_H

#include <QtGui>
#include "ui_fractionorderif.h"
#include "CalFO.h"

class FractionOrderIF : public QMainWindow
{
	Q_OBJECT

public:
	FractionOrderIF(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FractionOrderIF();

private:
	Ui::FractionOrderIFClass ui;
	QString fileName_s;
	QString fileNamei_s;
	void ibm2ieee(void *to, const void *from, int len);
	void ieee2ibm(void *to, const void *from, int len);

private slots:
	void on_Processing_IF_pc_Modify_clicked();
	void on_Processing_AIF_pc_clicked();
	
	void on_Processing_FO_pc_clicked();
	void on_Processing_IF_pc_clicked();
	
	void on_Processing_FO_clicked();
	void on_Processing_IF_clicked();
	void on_SelecteSEGY_i_clicked();
	void on_SelecteSEGY_clicked();
	
	

};

#endif // FRACTIONORDERIF_H
