/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "source/fastcgi/fastcgi.h"

#include <gtest/gtest.h>

#include "source/foundation/net.h"

using namespace tg::fastcgi;

class PacketHeaderTest : public testing::Test {
 public:
  void SetUp() override { of = PacketHeader::of(PacketType::ABORT_REQUEST, 0x2fe2, 0x3da8, 0x66); }

 protected:
  PacketHeader of;
  PacketHeader def;
};

class BeginRequestBodyTest : public testing::Test {
 public:
  void SetUp() override { of = BeginRequestBody::of(Role::AUTHORIZER, Flags::KEEP_CONNECTION); }

 protected:
  BeginRequestBody of;
  BeginRequestBody def;
};

class EndRequestBodyTest : public testing::Test {
 public:
  void SetUp() override { of = EndRequestBody::of(0x76543210, ProtocolStatus::UNKNOWN_ROLE); }

 protected:
  EndRequestBody of;
  EndRequestBody def;
};

class ParamsBodyTest : public testing::Test {
 public:
  void SetUp() override { of = ParamsBody::of(0x01234567, 0x89abcdef); }

 protected:
  ParamsBody of;
  ParamsBody def;
};

TEST_F(PacketHeaderTest, Of_BigIndian) {
  if constexpr (tg::net::IsBigEndian()) {
    EXPECT_EQ(Version::V1, of.version_);
    EXPECT_EQ(Version::V1, of.version());
    EXPECT_EQ(PacketType::ABORT_REQUEST, of.type_);
    EXPECT_EQ(0x2fe2, of.request_id_be_);
    EXPECT_EQ(0x3da8, of.content_length_be_);
    EXPECT_EQ(0x66, of.padding_length_);
    EXPECT_EQ(EMPTY_FIELD, of.reserved_);
    EXPECT_EQ(EMPTY_FIELD, of.reserved());

    of.type(PacketType::DATA);
    EXPECT_EQ(PacketType::DATA, of.type());
    EXPECT_EQ(PacketType::DATA, of.type_);

    of.request_id(0x22fd);
    EXPECT_EQ(0x22fd, of.request_id());
    EXPECT_EQ(0x22fd, of.request_id_be_);

    of.content_length(0x878a);
    EXPECT_EQ(0x878a, of.content_length());
    EXPECT_EQ(0x878a, of.content_length_be_);

    of.padding_length(0x8e);
    EXPECT_EQ(0x8e, of.padding_length());
    EXPECT_EQ(0x8e, of.padding_length_);

    of.reserved(0x26);
    EXPECT_EQ(0x26, of.reserved());
    EXPECT_EQ(0x26, of.reserved_);
  }
}

TEST_F(PacketHeaderTest, Of_LittleIndian) {
  if constexpr (tg::net::IsLittleEndian()) {
    EXPECT_EQ(Version::V1, of.version_);
    EXPECT_EQ(Version::V1, of.version());
    EXPECT_EQ(PacketType::ABORT_REQUEST, of.type_);
    EXPECT_EQ(0xe22f, of.request_id_be_);
    EXPECT_EQ(0xa83d, of.content_length_be_);
    EXPECT_EQ(0x66, of.padding_length_);
    EXPECT_EQ(EMPTY_FIELD, of.reserved_);
    EXPECT_EQ(EMPTY_FIELD, of.reserved());

    of.type(PacketType::DATA);
    EXPECT_EQ(PacketType::DATA, of.type());
    EXPECT_EQ(PacketType::DATA, of.type_);

    of.request_id(0x22fd);
    EXPECT_EQ(0x22fd, of.request_id());
    EXPECT_EQ(0xfd22, of.request_id_be_);

    of.content_length(0x878a);
    EXPECT_EQ(0x878a, of.content_length());
    EXPECT_EQ(0x8a87, of.content_length_be_);

    of.padding_length(0x8e);
    EXPECT_EQ(0x8e, of.padding_length());
    EXPECT_EQ(0x8e, of.padding_length_);

    of.reserved(0x26);
    EXPECT_EQ(0x26, of.reserved());
    EXPECT_EQ(0x26, of.reserved_);
  }
}

TEST_F(PacketHeaderTest, Def) {
  EXPECT_EQ(Version::V1, def.version_);
  EXPECT_EQ(Version::V1, def.version());
  EXPECT_EQ(PacketType::UNKNOWN, def.type_);
  EXPECT_EQ(PacketType::UNKNOWN, def.type());
  EXPECT_EQ(0, def.request_id_be_);
  EXPECT_EQ(0, def.request_id());
  EXPECT_EQ(0, def.content_length_be_);
  EXPECT_EQ(0, def.content_length());
  EXPECT_EQ(0, def.padding_length_);
  EXPECT_EQ(0, def.padding_length());
  EXPECT_EQ(EMPTY_FIELD, def.reserved_);
  EXPECT_EQ(EMPTY_FIELD, def.reserved());
}

TEST_F(BeginRequestBodyTest, Of) {
  EXPECT_EQ(Role::AUTHORIZER, of.role());
  if constexpr (tg::net::IsBigEndian()) {
    EXPECT_EQ(static_cast<RoleBotType>(Role::AUTHORIZER), of.role_be_);
  } else {
    EXPECT_EQ(static_cast<RoleBotType>(Role::AUTHORIZER), tg::net::ToNetworkEndian(of.role_be_));
  }
  EXPECT_EQ(Flags::KEEP_CONNECTION, of.flags());
  EXPECT_EQ(Flags::KEEP_CONNECTION, of.flags_);

  auto rptr = of.reserved();
  EXPECT_EQ(rptr, of.reserved_);
  rptr[4] = 0x55;
  EXPECT_EQ(EMPTY_FIELD, rptr[0]);
  EXPECT_EQ(EMPTY_FIELD, rptr[1]);
  EXPECT_EQ(EMPTY_FIELD, rptr[2]);
  EXPECT_EQ(EMPTY_FIELD, rptr[3]);
  EXPECT_EQ(0x55, rptr[4]);
}

TEST_F(BeginRequestBodyTest, Def) {
  EXPECT_EQ(Role::INVALID, def.role());
  EXPECT_EQ(static_cast<RoleBotType>(Role::INVALID), def.role_be_);
  EXPECT_EQ(Flags::EMPTY, def.flags());
  EXPECT_EQ(Flags::EMPTY, def.flags_);

  auto rptr = def.reserved();
  EXPECT_EQ(rptr, def.reserved_);
  rptr[4] = 0x8a;
  EXPECT_EQ(EMPTY_FIELD, rptr[0]);
  EXPECT_EQ(EMPTY_FIELD, rptr[1]);
  EXPECT_EQ(EMPTY_FIELD, rptr[2]);
  EXPECT_EQ(EMPTY_FIELD, rptr[3]);
  EXPECT_EQ(0x8a, rptr[4]);
}

TEST_F(EndRequestBodyTest, Of) {
  EXPECT_EQ(0x76543210, of.app_status());
  if constexpr (tg::net::IsBigEndian()) {
    EXPECT_EQ(0x76543210, of.app_status_be_);
  } else {
    EXPECT_EQ(0x76543210, tg::net::ToNetworkEndian(of.app_status_be_));
  }
  EXPECT_EQ(ProtocolStatus::UNKNOWN_ROLE, of.protocol_status());
  EXPECT_EQ(ProtocolStatus::UNKNOWN_ROLE, of.protocol_status_);

  auto rptr = of.reserved();
  EXPECT_EQ(rptr, of.reserved_);
  rptr[2] = 0xfe;
  EXPECT_EQ(EMPTY_FIELD, rptr[0]);
  EXPECT_EQ(EMPTY_FIELD, rptr[1]);
  EXPECT_EQ(0xfe, rptr[2]);
}

TEST_F(EndRequestBodyTest, Def) {
  EXPECT_EQ(0, def.app_status());
  EXPECT_EQ(0, def.app_status_be_);
  EXPECT_EQ(ProtocolStatus::REQUEST_COMPLETE, def.protocol_status());
  EXPECT_EQ(ProtocolStatus::REQUEST_COMPLETE, def.protocol_status_);

  auto rptr = def.reserved();
  EXPECT_EQ(rptr, def.reserved_);
  rptr[2] = 0xfe;
  EXPECT_EQ(EMPTY_FIELD, rptr[0]);
  EXPECT_EQ(EMPTY_FIELD, rptr[1]);
  EXPECT_EQ(0xfe, rptr[2]);
}

TEST_F(ParamsBodyTest, Of) {
  EXPECT_EQ(0x01234567, of.name_length());
  EXPECT_EQ(0x89abcdef, of.value_length());
  if constexpr (tg::net::IsBigEndian()) {
    EXPECT_EQ(0x01234567, of.name_length_be_);
    EXPECT_EQ(0x89abcdef, of.value_length_be_);
  } else {
    EXPECT_EQ(0x01234567, tg::net::ToNetworkEndian(of.name_length_be_));
    EXPECT_EQ(0x89abcdef, tg::net::ToNetworkEndian(of.value_length_be_));
  }
}

TEST_F(ParamsBodyTest, Def) {
  EXPECT_EQ(0, def.name_length());
  EXPECT_EQ(0, def.value_length());
  EXPECT_EQ(0, def.name_length_be_);
  EXPECT_EQ(0, def.value_length_be_);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}