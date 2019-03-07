#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "beginner_tutorials/Num.h"


#include "thrift_gen/HelloWorldService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::HelloWorldService;
using namespace  ::std;

class HelloWorldServiceHandler : virtual public HelloWorldServiceIf {
 public:
  HelloWorldServiceHandler() {
    // Your initialization goes here
  }

  void geHello(hello& _return) 
  {
    beginner_tutorials::Num msg;
    // msg.num = count;
    msg.first_name = "Ros";
    msg.last_name = "Thrift";
    msg.age = 21;
    msg.abc[msg.num] = "hello";

    hello h;
      h.first_Name= msg.first_name;
      h.last_Name=msg.last_name;
      _return=h;

    std::cout <<"Data Has beeen sent to Java FROM ROS/Thrift";
  }

  void sayHello() {
    // Your implementation goes here
    printf("geHello\n");
  }
};



int main(int argc, char **argv)
{

  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<HelloWorldServiceHandler> handler(new HelloWorldServiceHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new HelloWorldServiceProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();



  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<beginner_tutorials::Num>("chatter", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (count!=99)
  {
    beginner_tutorials::Num msg;
    msg.num = count;
    msg.first_name = "BIlal";
    msg.last_name = "Akbar";
    msg.age = 21;
    msg.abc[msg.num] = "hello";

    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

    ++count;

    
  }
  
  

  return 0;
}
