#include <ros/ros.h>
#include <example_service/ExampleServiceMsg.h> //注意添加消息类型的头文件
#include <iostream>
#include <string>
using namespace std;

//request是一个example_service::ExampleServiceMsgRequest类型的参数
//response是一个example_service::ExampleServiceMsgResponse类型的参数
bool callback(example_service::ExampleServiceMsgRequest& request, example_service::ExampleServiceMsgResponse& response)
{
    ROS_INFO("callback activated"); //等同于printf和cout
    string in_name(request.name); //定义一个string格式的变量
    response.on_the_list=false;

//这里只定义了两个名称，只有输入这两个名称中的一个才会反馈对应的信息    
    if (in_name.compare("Bob")==0)
 {
        ROS_INFO("asked about Bob");
        response.age = 32;
        response.good_guy=false;
        response.on_the_list=true;
        response.nickname="BobTheTerrible";
    } 
     if (in_name.compare("Ted")==0)
 {
        ROS_INFO("asked about Ted");
        response.age = 21;
        response.good_guy=true;
        response.on_the_list=true;
        response.nickname="Ted the Benevolent";
    }    

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_service");//初始化节点，以example_service命名
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("lookup_by_name", callback); //创建了一个service，名称为lookup_by_name，当一个"request"发送给这个service，callback函数就会被激活，在这里没有循环执行的函数，所以这个节点会处于暂停状态直到接受到"request"的时候才会被唤醒
  ROS_INFO("Ready to look up names.");
  ros::spin();

  return 0;
}
