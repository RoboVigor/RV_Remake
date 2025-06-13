/**
* Author: Rian
* Date: 6/6/2025.
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <unordered_map>

#include "NODE.h"
#include "ProtocolDataConfig.h"

#define ProtocolBufferLength 128

namespace Drivers::APP
{
  class PROTOCOL
  {
  public:
    struct ProtocolInfo
    {
      /* 基础配置 */
      NODE* node;       //该数据绑定的节点
      ProtocolType protocolType;  //包协议类型，枚举量 包含除数据段的其他协议包中其他数据长

      /* 接收配置 */
      uint8_t index;    //接收时数据字节index，用于判断该字节的属于哪个段
      uint8_t receiveEnable;  //是否接收
      uint8_t tempBuffer[ProtocolBufferLength]; //临时缓冲区用于存储完整数据帧进行数据校验
      ProtocolType_pDataOffset pDataOffset;  //协议中数据段偏移量
      uint16_t RXlength;  //数据段长度
      uint8_t* RXdata;    //数据存放地址

      /* 发送配置 */
      uint16_t frequency;  //发送频率
      uint16_t TXlength;
      uint8_t* TXdata;
    };

    typedef std::pmr::unordered_map<uint16_t , ProtocolInfo> ProtocolMapType;

    ProtocolMapType protocolMap;

    explicit PROTOCOL(ProtocolMapType protocolMap);

    void init(
      void (*Pack)(uint16_t id, PROTOCOL* protocol),
      void (*Unpack)(uint16_t id, PROTOCOL* protocol));

    void protocolPack(uint16_t id);
    void protocolUnpack(uint16_t id);

    void (*protocolPackCallback)(uint16_t id, PROTOCOL* protocol);
    void (*protocolUnpackCallback)(uint16_t id, PROTOCOL* protocol);
  private:
  };
}
#endif //PROTOCOL_H
