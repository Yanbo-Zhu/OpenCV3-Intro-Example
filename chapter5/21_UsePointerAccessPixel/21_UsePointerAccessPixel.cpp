//--------------------------------------������˵����-------------------------------------------
//		����˵������OpenCV3������š�OpenCV3���鱾����ʾ������21
//		������������ָ���������
//		������������IDE�汾��Visual Studio 2010
//		������������OpenCV�汾��	3.0 beta
//		2014��11�� Created by @ǳī_ë����
//		2014��12�� Revised by @ǳī_ë����
//------------------------------------------------------------------------------------------------

//---------------------------------��ͷ�ļ��������ռ�������֡�--------------------------
//		����������������ʹ�õ�ͷ�ļ��������ռ�
//-----------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
using namespace std;  
using namespace cv;  

//-----------------------------------��ȫ�ֺ����������֡�-----------------------------------
//          ������ȫ�ֺ�������
//-----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div);  
void ShowHelpText();



//--------------------------------------��main( )������---------------------------------------
//          ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main( )  
{  
	//��1������ԭʼͼ����ʾ
	Mat srcImage = imread("1.jpg");  
	imshow("ԭʼͼ��",srcImage);  

	//��2����ԭʼͼ�Ĳ����������������Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//Ч��ͼ�Ĵ�С��������ԭͼƬ��ͬ 

	ShowHelpText();

	//��3����¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());  

	//��4��������ɫ�ռ���������
  for (int i = 0; i < 100; i++)
	  colorReduce(srcImage,dstImage,32);  

	//��5����������ʱ�䲢���
	time0 = ((double)getTickCount() - time0)/getTickFrequency()/100.0;
	cout<<"\t�˷�������ʱ��Ϊ�� "<<time0<<"��"<<endl;  //�������ʱ��

	//��6����ʾЧ��ͼ
	imshow("Ч��ͼ",dstImage);  
	waitKey(0);  
}  


//---------------------------------��colorReduce( )������---------------------------------
//          ������ʹ�á�ָ����ʣ�C������[ ]�����������ɫ�ռ���������
//----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div)  
{  
	//����׼��
	outputImage = inputImage.clone();  //����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows;  //����
	int colNumber = outputImage.cols*outputImage.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���
  uchar mask = 0xFF << 6;  // e.g. ���� div=16, mask= 0xF0
	//˫��ѭ�����������е�����ֵ
	for(int i = 0;i < rowNumber;i++)  //��ѭ��
	{  
		uchar* data = outputImage.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		for(int j = 0;j < colNumber;j++)   //��ѭ��
		{  	
			// ---------����ʼ����ÿ�����ء�-------------     
      data[j] = data[j] & mask + div / 2;
			// ----------������������---------------------
		}  //�д�������
	}  
}

void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
  //����׼��
  outputImage = inputImage.clone();  //����ʵ�ε���ʱ����
  int rowNumber = outputImage.rows;  //����
  int colNumber = outputImage.cols*outputImage.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���
  
  //��ȡָ��ͼ�񻺳�����ָ��
  uchar mask = 0xFF << 6;  // e.g. ���� div=16, mask= 0xF0
  uchar *data = outputImage.data;
  //˫��ѭ�����������е�����ֵ
  for (int i = 0; i < rowNumber; i++)  //��ѭ��
  {
    for (int j = 0; j < colNumber; j++)   //��ѭ��
    {
      // ---------����ʼ����ÿ�����ء�-------------     
      data[j] = data[j] & mask + div / 2;
      // ----------������������---------------------
    }  //�д�������
    data += outputImage.step;
  }
}


//-----------------------------------��ShowHelpText( )������----------------------------------
//          ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�21������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

