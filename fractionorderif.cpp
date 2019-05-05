#include "fractionorderif.h"


FractionOrderIF::FractionOrderIF(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	fileName_s="";
	fileNamei_s="";
}

FractionOrderIF::~FractionOrderIF()
{

}


void FractionOrderIF::on_SelecteSEGY_clicked()
{
	fileName_s = QFileDialog::getOpenFileName(this,
		tr("QFileDialog::getOpenFileName()"),tr("E:\\documents\\Fractional Order\\"),
		tr("sgy Files (*.sgy);;All Files (*)"));
	if (!fileName_s.isEmpty())
		ui.lineEdit_FName->setText(fileName_s);

}
void FractionOrderIF::on_SelecteSEGY_i_clicked()
{
	fileNamei_s = QFileDialog::getOpenFileName(this,
		tr("QFileDialog::getOpenFileName()"),tr("E:\\documents\\Fractional Order"),
		tr("sgy Files (*.sgy);;All Files (*)"));
	if (!fileName_s.isEmpty())
		ui.lineEdit_FName_i->setText(fileNamei_s);

}

void FractionOrderIF::on_Processing_FO_clicked() //FO
{
	QFile DataFile(fileName_s);
	if (!DataFile.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	
	//in
	QDataStream in_DStream(&DataFile); 
	in_DStream.setByteOrder(QDataStream::BigEndian);
	
	float f_ieeev;
	unsigned f_ibmv;
	int inline1_i=ui.lineEdit_inline1->text().toInt();
	int inline2_i=ui.lineEdit_inline2->text().toInt();
	int crossline1_i=ui.lineEdit_crossline1->text().toInt();
	int crossline2_i=ui.lineEdit_crossline2->text().toInt();
	int inlinenum_i=inline2_i-inline1_i+1;
	int crosslinenum_i=crossline2_i-crossline1_i+1;
	int samplenum_i=ui.lineEdit_samplenum->text().toInt();
	QChar segy_head(1);
	QChar trace_head(1);



	//out
	float order_1_f=1.0-(ui.lineEdit_order->text().toFloat());
	QFile SEGYFile_F(fileName_s.replace(".sgy","_"+ui.lineEdit_order->text()+"D.sgy"));
	SEGYFile_F.open(QIODevice::WriteOnly);
	QDataStream out_DStream(&SEGYFile_F);  
	out_DStream.setByteOrder(QDataStream::BigEndian);

	for (int h=0;h<1800;h++)
	{
		in_DStream>>segy_head;
		out_DStream<<segy_head;
		
	}
	//in_DStream.skipRawData(3600);
	if (!in_DStream.atEnd())
	{


		for (int i=0;i<inlinenum_i;i++)
		{
			for (int t=0;t<crosslinenum_i;t++)
			{


				for (int h=0;h<120;h++)
				{
					in_DStream>>trace_head;
					out_DStream<<trace_head;
					
				}
				//in_DStream.skipRawData(240);
				vector<float>data_fv1;				
				
				for (int v=0;v<samplenum_i;v++)
				{
					
						
					   in_DStream >>f_ibmv;
					   ibm2ieee(&f_ieeev,&f_ibmv,1);
					   data_fv1.push_back(f_ieeev);
				}

				CalFO fo_c;
				fo_c.setData1D(data_fv1);
				fo_c.order_d_1=order_1_f;
				if ((order_1_f-0)>0.0)
				{
					fo_c.runFD();
					
				}
				else
				{
					if ((order_1_f-0)>-1.0)
					{
						fo_c.run1D();
					}
					else
					{
						fo_c.run2D();
					}
					
					

				}
						
				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=fo_c.FOD[v];
					ieee2ibm(&f_ibmv,&f_ieeev,1);
					out_DStream<<f_ibmv;

				}

				data_fv1.clear();
			}		





		}


	}




	fileName_s=ui.lineEdit_FName->text();
	QMessageBox::information(this,"Cal ",tr("FO_OK"));


}

void FractionOrderIF::on_Processing_FO_pc_clicked()
{
	QFile DataFile(fileName_s);
	if (!DataFile.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};

	//in
	QDataStream in_DStream(&DataFile); 
	in_DStream.setByteOrder(QDataStream::LittleEndian);

	float f_ieeev;
	//unsigned f_ibmv;
	int inline1_i=ui.lineEdit_inline1->text().toInt();
	int inline2_i=ui.lineEdit_inline2->text().toInt();
	int crossline1_i=ui.lineEdit_crossline1->text().toInt();
	int crossline2_i=ui.lineEdit_crossline2->text().toInt();
	int inlinenum_i=inline2_i-inline1_i+1;
	int crosslinenum_i=crossline2_i-crossline1_i+1;
	int samplenum_i=ui.lineEdit_samplenum->text().toInt();
	QChar segy_head(1);
	QChar trace_head(1);



	//out
	float order_1_f=1.0-(ui.lineEdit_order->text().toFloat());
	QFile SEGYFile_F(fileName_s.replace(".sgy","_"+ui.lineEdit_order->text()+"D.sgy"));
	SEGYFile_F.open(QIODevice::WriteOnly);
	QDataStream out_DStream(&SEGYFile_F);  
	out_DStream.setByteOrder(QDataStream::LittleEndian);

	for (int h=0;h<1800;h++)
	{
		in_DStream>>segy_head;
		out_DStream<<segy_head;

	}
	//in_DStream.skipRawData(3600);
	if (!in_DStream.atEnd())
	{


		for (int i=0;i<inlinenum_i;i++)
		{
			for (int t=0;t<crosslinenum_i;t++)
			{


				for (int h=0;h<120;h++)
				{
					in_DStream>>trace_head;
					out_DStream<<trace_head;

				}
				//in_DStream.skipRawData(240);
				vector<float>data_fv1;				

				for (int v=0;v<samplenum_i;v++)
				{


					in_DStream >>f_ieeev;
					//ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv1.push_back(f_ieeev);
				}

				CalFO fo_c;
				fo_c.setData1D(data_fv1);
				fo_c.order_d_1=order_1_f;
				if ((order_1_f-0)>0.0)
				{
					fo_c.runFD();

				}
				else
				{
					if ((order_1_f-0)>-1.0)
					{
						fo_c.run1D();
					}
					else
					{
						fo_c.run2D();
					}

				}

				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=fo_c.FOD[v];
					//ieee2ibm(&f_ibmv,&f_ieeev,1);
					out_DStream<<f_ieeev;

				}

				data_fv1.clear();
			}		





		}


	}




	fileName_s=ui.lineEdit_FName->text();
	QMessageBox::information(this,"Cal ",tr("FO_OK"));


}

void FractionOrderIF::on_Processing_IF_clicked() //IF
{
	const float pi=3.1415926;
	QFile DataFile(fileName_s);
	if (!DataFile.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	QFile DataFile_i(fileNamei_s);
	if (!DataFile_i.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	//in
	QDataStream in_DStream(&DataFile); 
	in_DStream.setByteOrder(QDataStream::BigEndian);
	QDataStream in_DStream_i(&DataFile_i); 
	in_DStream_i.setByteOrder(QDataStream::BigEndian);


   
	
	float f_ieeev;
	float f_ibmv;
	int inline1_i=ui.lineEdit_inline1->text().toInt();
	int inline2_i=ui.lineEdit_inline2->text().toInt();
	int crossline1_i=ui.lineEdit_crossline1->text().toInt();
	int crossline2_i=ui.lineEdit_crossline2->text().toInt();
	int inlinenum_i=inline2_i-inline1_i+1;
	int crosslinenum_i=crossline2_i-crossline1_i+1;
	int samplenum_i=ui.lineEdit_samplenum->text().toInt();
	float eps_f=ui.lineEdit_eps->text().toFloat();
	QChar segy_head(1);
	QChar trace_head(1);

	//out
	QString order_1_s=ui.lineEdit_order->text();
	float order_1_f=1.0-(order_1_s.toFloat());
	QFile SEGYFile_F(fileName_s.replace(".sgy","_IF_"+ui.lineEdit_order->text()+"D_i.sgy"));
	SEGYFile_F.open(QIODevice::WriteOnly);
	QDataStream out_DStream(&SEGYFile_F);  
	out_DStream.setByteOrder(QDataStream::BigEndian);

	
	
    
    
	
	for (int h=0;h<1800;h++)
		{
			in_DStream>>segy_head;
			out_DStream<<segy_head;
			in_DStream_i>>segy_head;
		}
	
	//in_DStream.skipRawData(3600);
	if (!in_DStream.atEnd())
	{
		
		
		for (int i=0;i<inlinenum_i;i++)
		{
			for (int t=0;t<crosslinenum_i;t++)
			{
			
			
				
				for (int h=0;h<120;h++)
				{
						in_DStream>>trace_head;
						out_DStream<<trace_head;
						in_DStream_i>>trace_head;
				}
				
			    //in_DStream.skipRawData(240);
				vector<float>data_fv1;
				vector<float>data_fv_i;
				for (int v=0;v<samplenum_i;v++)
				{
					
					in_DStream >>f_ibmv;
					ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv1.push_back(f_ieeev);
					in_DStream_i>>f_ibmv;
					ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv_i.push_back(f_ieeev);
		
					
					
				}

				
				CalFO fo_c;
				fo_c.setData1D(data_fv1);
				fo_c.order_d_1=order_1_f;
				
				
				CalFO fo_ci;
				fo_ci.setData1D(data_fv_i);
				fo_ci.order_d_1=order_1_f;
			
				if ((order_1_f-0)>0.0)
				{
					fo_c.runFD();
					fo_ci.runFD();
				}
				else
				{
					fo_c.run1D();
					fo_ci.run1D();

				}


				vector<float> data_e;
				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=sqrt(data_fv1[v]*data_fv1[v]+data_fv_i[v]*data_fv_i[v]); 
					data_e.push_back(f_ieeev);
				}
				float max_data_e=*max_element(data_e.begin(),data_e.end());


				for (int v=0;v<samplenum_i;v++)
				{
					
				    f_ieeev=(data_fv1[v]*fo_ci.FOD[v]-data_fv_i[v]*fo_c.FOD[v])/(data_e[v]*data_e[v]+eps_f*max_data_e*max_data_e)/(2*pi); 
					ieee2ibm(&f_ibmv,&f_ieeev,1);
					out_DStream<<f_ibmv;
					
				}

				data_fv1.clear();
				data_fv_i.clear();
			}		
				
				
				
			
			
		}
		

	}

	
	

    fileName_s=ui.lineEdit_FName->text();
	fileNamei_s=ui.lineEdit_FName_i->text();
	QMessageBox::information(this,"Cal ",tr("IF_OK"));

}


void FractionOrderIF::on_Processing_IF_pc_clicked()
{

	const float pi=3.1415926;
	QFile DataFile(fileName_s);
	if (!DataFile.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	QFile DataFile_i(fileNamei_s);
	if (!DataFile_i.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	//in
	QDataStream in_DStream(&DataFile); 
	in_DStream.setByteOrder(QDataStream::LittleEndian);
	QDataStream in_DStream_i(&DataFile_i); 
	in_DStream_i.setByteOrder(QDataStream::LittleEndian);




	float f_ieeev;
	//float f_ibmv;
	int inline1_i=ui.lineEdit_inline1->text().toInt();
	int inline2_i=ui.lineEdit_inline2->text().toInt();
	int crossline1_i=ui.lineEdit_crossline1->text().toInt();
	int crossline2_i=ui.lineEdit_crossline2->text().toInt();
	int inlinenum_i=inline2_i-inline1_i+1;
	int crosslinenum_i=crossline2_i-crossline1_i+1;
	int samplenum_i=ui.lineEdit_samplenum->text().toInt();
	float eps_f=ui.lineEdit_eps->text().toFloat();
	QChar segy_head(1);
	QChar trace_head(1);

	//out
	QString order_1_s=ui.lineEdit_order->text();
	float order_1_f=1.0-(order_1_s.toFloat());
	QFile SEGYFile_F(fileName_s.replace(".sgy","_IF_"+ui.lineEdit_order->text()+"D_i.sgy"));
	SEGYFile_F.open(QIODevice::WriteOnly);
	QDataStream out_DStream(&SEGYFile_F);  
	out_DStream.setByteOrder(QDataStream::LittleEndian);

    




	for (int h=0;h<1800;h++)
	{
		in_DStream>>segy_head;
		out_DStream<<segy_head;
		in_DStream_i>>segy_head;
	}

	//in_DStream.skipRawData(3600);
	if (!in_DStream.atEnd())
	{


		for (int i=0;i<inlinenum_i;i++)
		{
			for (int t=0;t<crosslinenum_i;t++)
			{



				for (int h=0;h<120;h++)
				{
					in_DStream>>trace_head;
					out_DStream<<trace_head;
					in_DStream_i>>trace_head;
				}

				//in_DStream.skipRawData(240);
				vector<float>data_fv1;
				vector<float>data_fv_i;
				for (int v=0;v<samplenum_i;v++)
				{

					in_DStream >>f_ieeev;
					//ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv1.push_back(f_ieeev);
					in_DStream_i>>f_ieeev;
					//ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv_i.push_back(f_ieeev);



				}

                
				CalFO fo_c;
				fo_c.setData1D(data_fv1);
				fo_c.order_d_1=order_1_f;


				CalFO fo_ci;
				fo_ci.setData1D(data_fv_i);
				fo_ci.order_d_1=order_1_f;

				if ((order_1_f-0)>0.0)
				{
					fo_c.runFD();
					fo_ci.runFD();
				}
				else
				{
					fo_c.run1D();
					fo_ci.run1D();

				}


				vector<float> data_e;
				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=sqrt(data_fv1[v]*data_fv1[v]+data_fv_i[v]*data_fv_i[v]); 
					data_e.push_back(f_ieeev);
				}
				float max_data_e=*max_element(data_e.begin(),data_e.end());
                

				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=(data_fv1[v]*fo_ci.FOD[v]-data_fv_i[v]*fo_c.FOD[v])/(data_e[v]*data_e[v]+eps_f*max_data_e*max_data_e)/(2*pi); 
					//ieee2ibm(&f_ibmv,&f_ieeev,1);
					out_DStream<<f_ieeev;

				}

				data_fv1.clear();
				data_fv_i.clear();
			}		





		}


	}




	fileName_s=ui.lineEdit_FName->text();
	fileNamei_s=ui.lineEdit_FName_i->text();
	QMessageBox::information(this,"Cal ",tr("IF_OK"));


}







void FractionOrderIF::ibm2ieee(void *to, const void *from, int len)
{
	register unsigned fr; /* fraction */
	register int exp; /* exponent */
	register int sgn; /* sign */

	for (; len-- > 0; to = (char *)to + 4, from = (char *)from + 4) {
		/* split into sign, exponent, and fraction */
		fr = *(long *)from; /* pick up value */
		sgn = fr >> 31; /* save sign */
		fr <<= 1; /* shift sign out */
		exp = fr >> 25; /* save exponent */
		fr <<= 7; /* shift exponent out */

		if (fr == 0) { /* short-circuit for zero */
			exp = 0;
			goto done;
		}

		/* adjust exponent from base 16 offset 64 radix point before first digit
		to base 2 offset 127 radix point after first digit */
		/* (exp - 64) * 4 + 127 - 1 == exp * 4 - 256 + 126 == (exp << 2) - 130 */
		exp = (exp << 2) - 130;

		/* (re)normalize */
		while (fr < 0x80000000) { /* 3 times max for normalized input */
			--exp;
			fr <<= 1;
		}

		if (exp <= 0) { /* underflow */
			if (exp < -24) /* complete underflow - return properly signed zero */
				fr = 0;
			else /* partial underflow - return denormalized number */
				fr >>= -exp;
			exp = 0;
		} else if (exp >= 255) { /* overflow - return infinity */
			fr = 0;
			exp = 255;
		} else { /* just a plain old number - remove the assumed high bit */
			fr <<= 1;
		}

done:
		/* put the pieces back together and return it */
		*(unsigned *)to = (fr >> 9) | (exp << 23) | (sgn << 31);
	}

}

void FractionOrderIF::ieee2ibm(void *to, const void *from, int len)
{
	register unsigned fr; /* fraction */
	register int exp; /* exponent */
	register int sgn; /* sign */

	for (; len-- > 0; to = (char *)to + 4, from = (char *)from + 4) {
		/* split into sign, exponent, and fraction */
		fr = *(unsigned *)from; /* pick up value */
		sgn = fr >> 31; /* save sign */
		fr <<= 1; /* shift sign out */
		exp = fr >> 24; /* save exponent */
		fr <<= 8; /* shift exponent out */

		if (exp == 255) { /* infinity (or NAN) - map to largest */
			fr = 0xffffff00;
			exp = 0x7f;
			goto done;
		}
		else if (exp > 0) /* add assumed digit */
			fr = (fr >> 1) | 0x80000000;
		else if (fr == 0) /* short-circuit for zero */
			goto done;

		/* adjust exponent from base 2 offset 127 radix point after first digit
		to base 16 offset 64 radix point before first digit */
		exp += 130;
		fr >>= -exp & 3;
		exp = (exp + 3) >> 2;

		/* (re)normalize */
		while (fr < 0x10000000) { /* never executed for normalized input */
			--exp;
			fr <<= 4;
		}

done:
		/* put the pieces back together and return it */
		fr = (fr >> 8) | (exp << 24) | (sgn << 31);
		*(unsigned *)to = fr;
	}
	
}
 







void FractionOrderIF::on_Processing_AIF_pc_clicked()
{

	
	QFile DataFile(fileName_s);
	if (!DataFile.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	
	//in
	QDataStream in_DStream(&DataFile); 
	in_DStream.setByteOrder(QDataStream::LittleEndian);
	



	float f_ieeev,f_sum,f_num;
	int i_nonezero_num;
	//float f_ibmv;
	int inline1_i=ui.lineEdit_inline1->text().toInt();
	int inline2_i=ui.lineEdit_inline2->text().toInt();
	int crossline1_i=ui.lineEdit_crossline1->text().toInt();
	int crossline2_i=ui.lineEdit_crossline2->text().toInt();
	int inlinenum_i=inline2_i-inline1_i+1;
	int crosslinenum_i=crossline2_i-crossline1_i+1;
	int samplenum_i=ui.lineEdit_samplenum->text().toInt();
	QChar segy_head(1);
	QChar trace_head(1);

	//out
	QString order_1_s=ui.lineEdit_order->text();
	float order_1_f=1.0-(order_1_s.toFloat());
	QFile SEGYFile_F(fileName_s.replace(".sgy","_AIF_"+ui.lineEdit_order->text()+"D_i.txt"));
	SEGYFile_F.open(QIODevice::WriteOnly);
	QTextStream out_DStream(&SEGYFile_F); 
	in_DStream.skipRawData(3600);
	if (!in_DStream.atEnd())
	{


		for (int i=0;i<inlinenum_i;i++)
		{
			for (int t=0;t<crosslinenum_i;t++)
			{



				in_DStream.skipRawData(240);
				vector<float>data_fv1;
				vector<float>data_fv_i;
				f_sum=0;
				i_nonezero_num=0;
				f_num=0;
				for (int v=0;v<samplenum_i;v++)
				{

					
					in_DStream >>f_ieeev;					
					if ((f_ieeev-0.0)>0.000001)
					{
						i_nonezero_num++;
					}
					if (i_nonezero_num>1)
					{
						f_sum+=f_ieeev;	
						f_num++;
					}
                    					



				}
				
				data_fv1.push_back((f_sum/f_num));
				

				
				for (int v=0;v<data_fv1.size();v++)
				{

					
					out_DStream<<data_fv1[v]<<"\n";

				}

				
			}		





		}


	}




	fileName_s=ui.lineEdit_FName->text();
	fileNamei_s=ui.lineEdit_FName_i->text();
	QMessageBox::information(this,"Cal ",tr("AIF_OK"));



}

void FractionOrderIF::on_Processing_IF_pc_Modify_clicked()
{

	const float pi=3.1415926;
	QFile DataFile(fileName_s);
	if (!DataFile.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	QFile DataFile_i(fileNamei_s);
	if (!DataFile_i.open(QIODevice::ReadOnly ))
	{
		QMessageBox::warning(this, tr("Warning"),
			tr("Open File1 Failure")); 
		return ;
	};
	//in
	QDataStream in_DStream(&DataFile); 
	in_DStream.setByteOrder(QDataStream::LittleEndian);
	QDataStream in_DStream_i(&DataFile_i); 
	in_DStream_i.setByteOrder(QDataStream::LittleEndian);




	float f_ieeev;
	//float f_ibmv;
	int inline1_i=ui.lineEdit_inline1->text().toInt();
	int inline2_i=ui.lineEdit_inline2->text().toInt();
	int crossline1_i=ui.lineEdit_crossline1->text().toInt();
	int crossline2_i=ui.lineEdit_crossline2->text().toInt();
	int inlinenum_i=inline2_i-inline1_i+1;
	int crosslinenum_i=crossline2_i-crossline1_i+1;
	int samplenum_i=ui.lineEdit_samplenum->text().toInt();
	float eps_f=ui.lineEdit_eps->text().toFloat();
	QChar segy_head(1);
	QChar trace_head(1);

	//out
	QString order_1_s=ui.lineEdit_order->text();
	float order_1_f=1.0-(order_1_s.toFloat());
	QFile SEGYFile_F(fileName_s.replace(".sgy","_IF_"+ui.lineEdit_order->text()+"D_i.sgy"));
	SEGYFile_F.open(QIODevice::WriteOnly);
	QDataStream out_DStream(&SEGYFile_F);  
	out_DStream.setByteOrder(QDataStream::LittleEndian);






	for (int h=0;h<1800;h++)
	{
		in_DStream>>segy_head;
		out_DStream<<segy_head;
		in_DStream_i>>segy_head;
	}

	//in_DStream.skipRawData(3600);
	if (!in_DStream.atEnd())
	{


		for (int i=0;i<inlinenum_i;i++)
		{
			for (int t=0;t<crosslinenum_i;t++)
			{



				for (int h=0;h<120;h++)
				{
					in_DStream>>trace_head;
					out_DStream<<trace_head;
					in_DStream_i>>trace_head;
				}

				//in_DStream.skipRawData(240);
				vector<float>data_fv1;
				vector<float>data_fv_i;
				for (int v=0;v<samplenum_i;v++)
				{

					in_DStream >>f_ieeev;
					//ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv1.push_back(f_ieeev);
					in_DStream_i>>f_ieeev;
					//ibm2ieee(&f_ieeev,&f_ibmv,1);
					data_fv_i.push_back(f_ieeev);



				}


				CalFO fo_c;
				fo_c.setData1D(data_fv1);
				fo_c.order_d_1=order_1_f;


				CalFO fo_ci;
				fo_ci.setData1D(data_fv_i);
				fo_ci.order_d_1=order_1_f;
				fo_c.run1D();
				fo_ci.run1D();
				

				vector<float> data_e;
				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=sqrt(data_fv1[v]*data_fv1[v]+data_fv_i[v]*data_fv_i[v]); 
					data_e.push_back(f_ieeev);
				}
				float max_data_e=*max_element(data_e.begin(),data_e.end());
                
				vector<float> data_if1D;
				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=(data_fv1[v]*fo_ci.FOD[v]-data_fv_i[v]*fo_c.FOD[v])/(data_e[v]*data_e[v]+eps_f*max_data_e*max_data_e)/(2*pi); 
					//ieee2ibm(&f_ibmv,&f_ieeev,1);
					
					data_if1D.push_back(f_ieeev);

				}
				
				CalFO fif_c;
				fif_c.setData1D(data_if1D);
				fif_c.order_d_1=order_1_f;
				fif_c.runFIF();
				
				for (int v=0;v<samplenum_i;v++)
				{

					f_ieeev=fif_c.FOD[v]; 
					//ieee2ibm(&f_ibmv,&f_ieeev,1);
					out_DStream<<f_ieeev;

				}

				data_fv1.clear();
				data_fv_i.clear();
			}		





		}


	}




	fileName_s=ui.lineEdit_FName->text();
	fileNamei_s=ui.lineEdit_FName_i->text();
	QMessageBox::information(this,"Cal ",tr("IF_OK"));


}