//
// Created by znbd on 23-4-7.
//

#include <cstring>
#include <rclcpp/rclcpp.hpp>
#include "chcnav_driver/msg/chcnav_gpchc.hpp"
#include "chcnav_serial.hpp"
//#include ""
#define DEG2RAD 0.017453292

using namespace std;

void BufferCallBack(const char *pType, void *pData, void *pPub) {

    if (string(pType) == "$GPCHC"){
        auto *pub = (rclcpp::Publisher<chcnav_driver::msg::CHCNAVGpchc>::SharedPtr *) pPub;
        auto message = (chcnav_driver::msg::CHCNAVGpchc*)pData;
        cout << "heading:"<< message->heading << typeid(message->heading).name() << endl << endl;
        (*pub)->publish(*message);
        delete message;
    }

}
//
//
class CHCNAVPublisher : public rclcpp::Node {
public:
    explicit CHCNAVPublisher(const string &name) : Node(name) {
        devices = new CHCNAVSerial("/dev/ttyS1", 4800);

        gpchc_pub = this->create_publisher<chcnav_driver::msg::CHCNAVGpchc>("chcnav_imugnss/GPCHC", 10);

    }

    ~CHCNAVPublisher() override {
        delete devices;
    }

    void publish_flow() {
        printf("Start Grabbing!\n");
        devices->parseFlow(BufferCallBack, &this->gpchc_pub);
    }






private:

    CHCNAVSerial *devices = nullptr;
    rclcpp::Publisher<chcnav_driver::msg::CHCNAVGpchc>::SharedPtr gpchc_pub;



};
void print_usage() {
    cerr << "Usage: test_serial {-e|<serial port address>} ";
    cerr << "<baudrate> [test string]" << endl;
}

int main(int argc,char** argv)
{
//    auto t = CHCNAVSerial("/dev/ttyS1", 4800);
//    t.parseFlow(BufferCallBack, nullptr);
//    if (argc < 2) {
//        print_usage();
//        return 0;
//    }
//
//    // Argument 1 is the serial port or enumerate flag
//    string port(argv[1]);
//
//    if (port == "-e") {
//        enumerate_ports();
//        return 0;
//    } else if (argc < 3) {
//        print_usage();
//        return 1;
//    }
//    auto t = RS232("/dev/ttyS0", 115200);
//    auto t = RS232("/dev/ttyS1", 4800);
//    t.readData(BufferCallBack, nullptr);


//    if (*strPiece.begin()=="$GPCHC")






    rclcpp::init(argc, argv);
    auto node = make_shared<CHCNAVPublisher>("CHCNAV_CGI610_node");
//    rclcpp::spin(node);
    node->publish_flow();
    rclcpp::shutdown();
    return 0;





}


