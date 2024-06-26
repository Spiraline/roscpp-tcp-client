#ifndef ROSBRIDGE_TCP_CLIENT_H_
#define ROSBRIDGE_TCP_CLIENT_H_

#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <ros/ros.h>
#include <signal.h>

using boost::asio::ip::tcp;
using json = nlohmann::json;

class ROSBridgeTCPClient
{
private:
  ros::NodeHandle nh_;
  boost::asio::io_service io_service_;
  boost::shared_ptr<tcp::socket> socket_;
  static constexpr int PACKET_SIZE = 2048;
  const std::string DELIMITER = "{\"op\":";
  std::vector<char> recv_buffer_;
  std::thread recv_thread_;

  std::string rosbridge_ip_;
  int rosbridge_port_;

  bool bridge_connected_{false};

  std::unordered_set<std::string> adv_topic_set_;

  ros::Rate rate_{ros::Rate(1)};

  // key: topic name
  // value: last msg에 대한 json
  std::unordered_map<std::string, json> mailbox_;

public:
  ROSBridgeTCPClient();
  ~ROSBridgeTCPClient();
  void advertise(const std::string &topic_name, const std::string &topic_type);
  void subscribe(const std::string &topic_name, const std::string &topic_type, int throttle_rate, int queue_length);
  void publish(const std::string &topic_name, const std::string &topic_type, const json &msg_json);

  inline std::unordered_map<std::string, json>& getMailBox(){
    return mailbox_;
  };

private:
  bool connect();
  void receiveCallback(const boost::system::error_code& ec, std::size_t recv_byte);
};

#include <rosbridge_tcp_client/impl/rosbridge_tcp_client.hpp>

#endif