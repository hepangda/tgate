/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <cstdint>

namespace tg::fastcgi {

constexpr uint8_t EMPTY_FIELD = 0;

using VersionBotType = uint8_t;
enum class Version : VersionBotType {
  V1 = 1,
};

using PacketTypeBotType = uint8_t;
enum class PacketType : PacketTypeBotType {
  BEGIN_REQUEST = 1,
  ABORT_REQUEST = 2,
  END_REQUEST = 3,
  PARAMS = 4,
  STDIN = 5,
  STDOUT = 6,
  STDERR = 7,
  DATA = 8,
  GET_VALUES = 9,
  GET_VALUES_RESULT = 10,
  UNKNOWN = 11,
};

using RoleBotType = uint16_t;
enum class Role : RoleBotType {
  INVALID = 0,
  RESPONDER = 1,
  AUTHORIZER = 2,
  FILTER = 3,
};

using FlagsBotType = uint8_t;
enum class Flags : FlagsBotType {
  EMPTY = 0,
  KEEP_CONNECTION = 1,
};

using ProtocolStatusBotType = uint8_t;
enum class ProtocolStatus : ProtocolStatusBotType {
  REQUEST_COMPLETE = 0,
  CANT_MULTIPLEX_CONNECTION = 1,
  OVERLOADED = 2,
  UNKNOWN_ROLE = 3,
};

struct PacketHeader {
  Version version_{Version::V1};
  PacketType type_{PacketType::UNKNOWN};
  uint16_t request_id_be_{0};
  uint16_t content_length_be_{0};
  uint8_t padding_length_{0};
  uint8_t reserved_{EMPTY_FIELD};

  static PacketHeader of(PacketType type, uint16_t request_id, uint16_t content_length, uint8_t padding_length);

  [[nodiscard]] Version version() const;

  [[nodiscard]] PacketType type() const;
  void type(PacketType type);

  [[nodiscard]] uint16_t request_id() const;
  void request_id(uint16_t request_id);

  [[nodiscard]] uint16_t content_length() const;
  void content_length(uint16_t content_length);

  [[nodiscard]] uint8_t padding_length() const;
  void padding_length(uint8_t padding_length);

  [[nodiscard]] uint8_t reserved() const;
  void reserved(uint8_t reserved);
};

struct BeginRequestBody {
  RoleBotType role_be_{static_cast<RoleBotType>(Role::INVALID)};
  Flags flags_{Flags::EMPTY};
  uint8_t reserved_[5] = {EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD};

  static BeginRequestBody of(Role role, Flags flags);

  [[nodiscard]] Role role() const;
  void role(Role role);

  [[nodiscard]] Flags flags() const;
  void flags(Flags flags);

  uint8_t *reserved();
};

struct EndRequestBody {
  uint32_t app_status_be_{0};
  ProtocolStatus protocol_status_{ProtocolStatus::REQUEST_COMPLETE};
  uint8_t reserved_[3] = {EMPTY_FIELD, EMPTY_FIELD, EMPTY_FIELD};

  static EndRequestBody of(uint32_t app_status, ProtocolStatus protocol_status);

  [[nodiscard]] uint32_t app_status() const;
  void app_status(uint32_t app_status);

  [[nodiscard]] ProtocolStatus protocol_status() const;
  void protocol_status(ProtocolStatus protocol_status);

  uint8_t *reserved();
};

struct ParamsBody {
  uint32_t name_length_be_{0};
  uint32_t value_length_be_{0};

  static ParamsBody of(uint32_t name_length, uint32_t value_length);

  [[nodiscard]] uint32_t name_length() const;
  void name_length(uint32_t name_length);

  [[nodiscard]] uint32_t value_length() const;
  void value_length(uint32_t value_length);
};

}  // namespace tg::fastcgi