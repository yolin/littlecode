#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace fs = boost::filesystem;
using namespace std::chrono_literals;

// 模擬 segment 結構
struct SegmentInfo {
    boost::posix_time::ptime start_time;
};

struct Segment {
    SegmentInfo new_one;
    int period;              // 單位秒
    int time_offset_ms;      // 單位毫秒
};

class recorder {
public:
    recorder() {
        segment_.period = 5;
        segment_.time_offset_ms = 0;
        segment_.new_one.start_time = boost::posix_time::second_clock::universal_time();
    }

    void update_segment_start_time() {
        segment_.new_one.start_time = boost::posix_time::second_clock::universal_time();
    }

    bool motion_dectected_in_last_segment_period();

private:
    Segment segment_;
};

const std::string OBJECT_DETECTION_METADATA_LOG = "metadata.log";
const std::string OBJECT_DETECTION_START_TIMESTAMP = "start_timestamp";

std::time_t ptime_to_epoch_time(const boost::posix_time::ptime& pt) {
    static const boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
    return (pt - epoch).total_seconds();
}

bool recorder::motion_dectected_in_last_segment_period() {
    static std::time_t mot_update_time = 0;
    std::cout << "[TRACE] object_dectected_in_last_segment_period enter\n";

    if (fs::exists(OBJECT_DETECTION_METADATA_LOG)) {
        mot_update_time = fs::last_write_time(OBJECT_DETECTION_METADATA_LOG) + 2;
    }
    else if (std::time(nullptr) < mot_update_time) {
        // do nothing
    }
    else {
        if (fs::exists(OBJECT_DETECTION_START_TIMESTAMP)) {
            std::cout << "[INFO] remove " << OBJECT_DETECTION_START_TIMESTAMP << "\n";
            fs::remove(OBJECT_DETECTION_START_TIMESTAMP);
        }
        return false;
    }

    if (!fs::exists(OBJECT_DETECTION_START_TIMESTAMP)) {
        std::ofstream ofs(OBJECT_DETECTION_START_TIMESTAMP);
        ofs << "created";
        ofs.close();
    }

    std::time_t mot_start_time = fs::last_write_time(OBJECT_DETECTION_START_TIMESTAMP) - segment_.period * 2;
    std::time_t start_time = ptime_to_epoch_time(segment_.new_one.start_time - boost::posix_time::milliseconds(segment_.time_offset_ms));

    std::cout << "[DEBUG] mot_update_time: " << mot_update_time << ", mot_start_time: " << mot_start_time << "\n";
    std::cout << "[DEBUG] start_time: " << start_time << "\n";

    return (start_time >= mot_start_time) && (start_time <= mot_update_time);
}

int main() {
    std::ofstream(OBJECT_DETECTION_METADATA_LOG) << "simulate";
    std::ofstream(OBJECT_DETECTION_START_TIMESTAMP) << "simulate";

    recorder r;
    int counter = 0;

    while (true) {
        if (counter % 5 == 0) {
            r.update_segment_start_time();
            std::time_t now = std::time(nullptr) - 10;
            std::cout << "[UPDATE] segment_.new_one.start_time 更新為現在時間-10 seconds：" << now << std::endl;
        }

        bool result = r.motion_dectected_in_last_segment_period();
        std::cout << "[CHECK] " << (result ? "✅ Motion Detected" : "❌ No Motion") << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
    }

    return 0;
}
