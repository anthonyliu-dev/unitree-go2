// Go2 EDU: read-only telemetry subscriber (no command publisher).
// Build with unitree_sdk2 and run: ./bin/go2_read_state eno2
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include <unitree/robot/channel/channel_factory.hpp>
#include <unitree/robot/channel/channel_subscriber.hpp>
#include <unitree/idl/go2/LowState_.hpp>

using namespace unitree::robot;
using LowState = unitree_go::msg::dds_::LowState_;

class StateReader {
public:
    void Start() {
        subscriber_.reset(new ChannelSubscriber<LowState>("rt/lowstate"));
        subscriber_->InitChannel(
            std::bind(&StateReader::OnState, this, std::placeholders::_1), 1);
    }

    unsigned long Count() const { return count_.load(); }

private:
    void OnState(const void* message) {
        const auto* state = static_cast<const LowState*>(message);
        const auto n = ++count_;
if (n == 1 || n % 500 == 0) {
    std::cout << "\n--- Go2 State: " << n
              << " messages ---\n";

    for (int i = 0; i < 12; ++i) {
        std::cout << "Motor[" << i << "]"
                  << " position: "
                  << state->motor_state()[i].q()
                  << " rad | velocity: "
                  << state->motor_state()[i].dq()
                  << " rad/s\n";
    }

    const auto& imu = state->imu_state();

    std::cout << "IMU RPY (rad): ";
    for (int i = 0; i < 3; ++i) {
        std::cout << imu.rpy()[i] << " ";
    }

    std::cout << "\nIMU acceleration (m/s^2): ";
    for (int i = 0; i < 3; ++i) {
        std::cout << imu.accelerometer()[i] << " ";
    }

    std::cout << std::endl;
}    }

    std::atomic<unsigned long> count_{0};
    ChannelSubscriberPtr<LowState> subscriber_;
};

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " networkInterface\n"
                  << "Example: " << argv[0] << " eno2\n";
        return 1;
    }

    ChannelFactory::Instance()->Init(0, argv[1]);
    StateReader reader;
    reader.Start();
    std::cout << "Listening for rt/lowstate on " << argv[1]
              << ". Read-only; no motion commands. Press Ctrl+C to stop.\n";

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (reader.Count() == 0) {
            std::cout << "No LowState data yet. Check Ethernet / DDS / robot state.\n";
        }
    }
}
