//--------------------------------------������˵����-------------------------------------------
//		����˵������OpenCV3������š�OpenCV3���鱾����ʾ������79
//		����������H-S��άֱ��ͼ�Ļ���
//		�����������ò���ϵͳ�� Windows 7 64bit
//		������������IDE�汾��Visual Studio 2010
//		������������OpenCV�汾��	3.0 beta
//		2014��11�� Created by @ǳī_ë����
//		2014��12�� Revised by @ǳī_ë����
//------------------------------------------------------------------------------------------------



//---------------------------------��ͷ�ļ��������ռ�������֡�----------------------------
//		����������������ʹ�õ�ͷ�ļ��������ռ�
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;



//-----------------------------------��ShowHelpText( )������-----------------------------
//		 ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�79������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------��main( )������-----------------------------------------
//          ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main( )
{

	//��1������Դͼ��ת��ΪHSV��ɫģ��
	Mat srcImage, hsvImage;
	srcImage=imread("79-2.jpg");
	cvtColor(srcImage,hsvImage, COLOR_BGR2HSV);

	system("color 2F");
	ShowHelpText();

	//��2������׼��
	//��ɫ������Ϊ30���ȼ��������Ͷ�����Ϊ32���ȼ�
	int hueBinNum = 30;//ɫ����ֱ��ͼֱ������
	int saturationBinNum = 32;//���Ͷȵ�ֱ��ͼֱ������
	int histSize[ ] = {hueBinNum, saturationBinNum};
	// ����ɫ���ı仯��ΧΪ0��179
	float hueRanges[] = { 0, 180 };
	//���履�Ͷȵı仯��ΧΪ0���ڡ��ס��ң���255����������ɫ��
	float saturationRanges[] = { 0, 256 };
	const float* ranges[] = { 
    hueRanges, saturationRanges };
	MatND dstHist;
	//����׼����calcHist�����н������0ͨ���͵�1ͨ����ֱ��ͼ
	int channels[] = {0, 1};

	//��3����ʽ����calcHist������ֱ��ͼ����
	calcHist( &hsvImage,//���������
		1, //�������Ϊ1
		channels,//ͨ������
		Mat(), //��ʹ����Ĥ
		dstHist, //�����Ŀ��ֱ��ͼ
		2, //��Ҫ�����ֱ��ͼ��ά��Ϊ2
		histSize, //���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		ranges,//ÿһά��ֵ��ȡֵ��Χ����
		true, // ָʾֱ��ͼ�Ƿ���ȵı�ʶ����true��ʾ���ȵ�ֱ��ͼ
		false );//�ۼƱ�ʶ����false��ʾֱ��ͼ�����ý׶λᱻ����

	//��4��Ϊ����ֱ��ͼ׼������
	double maxValue=0;//���ֵ
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//����������������ȫ����Сֵ�����ֵ����maxValue��
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10, CV_8UC3);

	//��5��˫��ѭ��������ֱ��ͼ����
	for( int hue = 0; hue < hueBinNum; hue++ )
		for( int saturation = 0; saturation < saturationBinNum; saturation++ )
		{
			float binValue = dstHist.at<float>(hue, saturation);//ֱ��ͼ����ֵ
			int intensity = cvRound(binValue*255/maxValue);//ǿ��

			//��ʽ���л���
			rectangle( histImg, Point(hue*scale, saturation*scale),
				Point( (hue+1)*scale - 1, (saturation+1)*scale - 1),
				Scalar::all(intensity),FILLED );
		}

		//��6����ʾЧ��ͼ
		imshow( "�ز�ͼ", srcImage );
		imshow( "H-S ֱ��ͼ", histImg );

    // �������H S��һάֱ��ͼ���Ա�
    MatND hueHist, saturateHist;
    int hist_size[] = { 256 };
    float range[] = { 0, 256 };
    const float* rangeshs[] = { range };
    //��3������ֱ��ͼ�ļ��㣨H�������֣�
    int channels_h[] = { 0 };
    calcHist(&srcImage, 1, channels_h, Mat(), //��ʹ����Ĥ
      hueHist, 1, hist_size, rangeshs,
      true, false);

    //��4������ֱ��ͼ�ļ��㣨S�������֣�
    int channels_g[] = { 1 };
    calcHist(&srcImage, 1, channels_g, Mat(), // do not use mask
      saturateHist, 1, hist_size, rangeshs,
      true, // the histogram is uniform
      false);

    //����׼��
    double maxValue_red, maxValue_green;
    minMaxLoc(hueHist, 0, &maxValue_red, 0, 0);
    minMaxLoc(saturateHist, 0, &maxValue_green, 0, 0);
    scale = 1;
    int histHeight = 256;
    Mat histImage = Mat::zeros(histHeight, 256 * 2, CV_8UC3);
    //��ʽ��ʼ����
    for (int i = 0; i<256; i++)
    {
      //����׼��
      float binValue_red = hueHist.at<float>(i);
      float binValue_green = saturateHist.at<float>(i);
      int intensity_red = cvRound(binValue_red*histHeight / maxValue_red);  //Ҫ���Ƶĸ߶�
      int intensity_green = cvRound(binValue_green*histHeight / maxValue_green);  //Ҫ���Ƶĸ߶�

      //���ƺ�ɫ������ֱ��ͼ
      rectangle(histImage, Point(i*scale, histHeight - 1),
        Point((i + 1)*scale - 1, histHeight - intensity_red),
        Scalar(255, 0, 0));

      //������ɫ������ֱ��ͼ
      rectangle(histImage, Point((i + 256)*scale, histHeight - 1),
        Point((i + 256 + 1)*scale - 1, histHeight - intensity_green),
        Scalar(0, 255, 0));
    }

    //�ڴ�������ʾ�����ƺõ�ֱ��ͼ
    imshow("ͼ���HSһάֱ��ͼ", histImage);

		waitKey();
}