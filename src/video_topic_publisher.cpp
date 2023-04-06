#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;

  std::cout<<"capture video"<<std::endl;
  VideoCapture cap("/home/jaeyong/Chanhoe_Segmentation/mb1_out.mp4");
  if (!cap.isOpened())
  {
    printf("Can't open the camera");
    return -1;
  }
  std::cout<<"capturing video is done"<<std::endl;
  Mat img, img_modified;

  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/camera/color/image_raw", 1);
  // cv::Mat image = cv::imread(argv[1], IMREAD_COLOR);
  // cv::waitKey(30);
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> img;
    if (img.empty())
		{
			printf("empty image");
			return 0;
		}
    std::cout<<"=========================="<<endl
    <<"camera info"<<endl
    <<"row : "<<img.rows<<endl
    <<"col : "<<img.cols<<endl;
    cv::resize(img,img_modified,Size(640,480));
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img_modified).toImageMsg();

    // imshow("camera img", img);
    // cv::waitKey(0);
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

}
/*


using namespace cv;
using namespace std;

int main(int ac, char** av) {

	VideoCapture cap("test.mp4");
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);

	if (!cap.isOpened())
	{
		printf("Can't open the camera");
		return -1;
	}

	Mat img;

	while (1)
	{
		cap >> img;
		
		if (img.empty())
		{
			printf("empty image");
			return 0;
		}
		
		imshow("camera img", img);

		if (waitKey(25) == 27)
			break;
	}


	return 0;
}
*/
