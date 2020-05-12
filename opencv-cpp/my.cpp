#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

int main()
{

Mat srcImage = imread("20.jpg");

Mat midImage, dstImage;

// 显示原始图
imshow("原始图", srcImage);


// 霍夫圆变换
cvtColor(srcImage, midImage, CV_BGR2GRAY);// 转为灰度图
GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);// 模糊
vector<Vec3f> circles;
HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1, 30, 115, 90, 0, 0);

// 找出圆盘
int pos = 0;
int max = -1;
for (size_t i = 0; i < circles.size(); i++)
{
Vec3f f = circles[i];
if (f[2] > max && f[0] + f[2] < midImage.rows && f[0] - f[2] >= 0 && f[1] + f[2] < midImage.cols && f[1] - f[2] > 0)
{
max = f[2];
pos = i;
}
}

if (circles.size() > 0)
{
// 找到圆心
Point center(circles[pos][0], circles[pos][1]);
// 找到的半径
int radius = circles[pos][2];

// 绘制圆心
circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);

// 绘制圆轮廓
circle(srcImage, center, radius, Scalar(255), 2);
}

// 效果图
imshow("霍夫圆变换", srcImage);

// 霍夫线变换
Canny(srcImage, midImage, 100, 300, 3);// 边缘检测
cvtColor(midImage, dstImage, CV_GRAY2BGR);// 转为灰度图
vector<Vec4i> lines;
// 检测直线，最小投票为100，线条不短于50，间隙不小于10
HoughLinesP(midImage,lines, 1, CV_PI / 180, 100, 50, 10);

for (size_t i = 0; i < lines.size(); i++)
{
Vec4i l = lines[i];
Point pt1(l[0], l[1]);
Point pt2(l[2], l[3]);
line(dstImage, pt1, pt2, Scalar(186, 88, 255), 1, CV_AA);
}

//imshow("边缘检测图", midImage);

imshow("霍夫线变换", dstImage);

waitKey(0);

return 0;
}
