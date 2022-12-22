/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "fastcgi.h"

#include "source/foundation/net.h"

namespace tg::fastcgi {

// -------------------- PacketHeader --------------------
PacketHeader PacketHeader::of(PacketType type, uint16_t request_id, uint16_t content_length, uint8_t padding_length) {
  PacketHeader it;
  it.type(type);
  it.request_id(request_id);
  it.content_length(content_length);
  it.padding_length(padding_length);
  return it;
}

PacketType PacketHeader::type() const { return type_; }

void PacketHeader::type(PacketType type) { type_ = type; }

uint16_t PacketHeader::request_id() const { return net::ToLocalEndian(request_id_be_); }

void PacketHeader::request_id(uint16_t request_id) { request_id_be_ = net::ToNetworkEndian(request_id); }

uint16_t PacketHeader::content_length() const { return net::ToLocalEndian(content_length_be_); }

void PacketHeader::content_length(uint16_t content_length) {
  content_length_be_ = net::ToNetworkEndian(content_length);
}

uint8_t PacketHeader::padding_length() const { return padding_length_; }

void PacketHeader::padding_length(uint8_t padding_length) { padding_length_ = padding_length; }

Version PacketHeader::version() const { return version_; }

uint8_t PacketHeader::reserved() const { return reserved_; }

void PacketHeader::reserved(uint8_t reserved) { reserved_ = reserved; }

// -------------------- BeginRequestBody --------------------
BeginRequestBody BeginRequestBody::of(Role role, Flags flags) {
  BeginRequestBody it;
  it.role(role);
  it.flags(flags);
  return it;
}

Role BeginRequestBody::role() const { return static_cast<Role>(net::ToLocalEndian(role_be_)); }

void BeginRequestBody::role(Role role) { role_be_ = net::ToNetworkEndian(static_cast<RoleBotType>(role)); }

Flags BeginRequestBody::flags() const { return flags_; }

void BeginRequestBody::flags(Flags flags) { flags_ = flags; }

uint8_t* BeginRequestBody::reserved() { return reserved_; }

// -------------------- EndRequestBody --------------------
EndRequestBody EndRequestBody::of(uint32_t app_status, ProtocolStatus protocol_status) {
  EndRequestBody it;
  it.app_status(app_status);
  it.protocol_status(protocol_status);
  return it;
}

uint32_t EndRequestBody::app_status() const { return net::ToLocalEndian(app_status_be_); }

void EndRequestBody::app_status(uint32_t app_status) { app_status_be_ = net::ToNetworkEndian(app_status); }

ProtocolStatus EndRequestBody::protocol_status() const { return protocol_status_; }

void EndRequestBody::protocol_status(ProtocolStatus protocol_status) { protocol_status_ = protocol_status; }

uint8_t* EndRequestBody::reserved() { return reserved_; }

// -------------------- ParamsBody --------------------
ParamsBody ParamsBody::of(uint32_t name_length, uint32_t value_length) {
  ParamsBody it;
  it.name_length(name_length);
  it.value_length(value_length);
  return it;
}

uint32_t ParamsBody::name_length() const { return net::ToLocalEndian(name_length_be_); }

void ParamsBody::name_length(uint32_t name_length) { name_length_be_ = net::ToNetworkEndian(name_length); }

uint32_t ParamsBody::value_length() const { return net::ToLocalEndian(value_length_be_); }

void ParamsBody::value_length(uint32_t value_length) { value_length_be_ = net::ToNetworkEndian(value_length); }

}  // namespace tg::fastcgi