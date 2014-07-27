// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GarageStatus.proto

#ifndef PROTOBUF_GarageStatus_2eproto__INCLUDED
#define PROTOBUF_GarageStatus_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GarageStatus_2eproto();
void protobuf_AssignDesc_GarageStatus_2eproto();
void protobuf_ShutdownFile_GarageStatus_2eproto();

class GarageStatus;
class GarageStatus_DoorStatus;

// ===================================================================

class GarageStatus_DoorStatus : public ::google::protobuf::Message {
 public:
  GarageStatus_DoorStatus();
  virtual ~GarageStatus_DoorStatus();

  GarageStatus_DoorStatus(const GarageStatus_DoorStatus& from);

  inline GarageStatus_DoorStatus& operator=(const GarageStatus_DoorStatus& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GarageStatus_DoorStatus& default_instance();

  void Swap(GarageStatus_DoorStatus* other);

  // implements Message ----------------------------------------------

  GarageStatus_DoorStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GarageStatus_DoorStatus& from);
  void MergeFrom(const GarageStatus_DoorStatus& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 garageId = 1;
  inline bool has_garageid() const;
  inline void clear_garageid();
  static const int kGarageIdFieldNumber = 1;
  inline ::google::protobuf::uint32 garageid() const;
  inline void set_garageid(::google::protobuf::uint32 value);

  // required uint32 timestamp = 2;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimestampFieldNumber = 2;
  inline ::google::protobuf::uint32 timestamp() const;
  inline void set_timestamp(::google::protobuf::uint32 value);

  // required bool isClosed = 3;
  inline bool has_isclosed() const;
  inline void clear_isclosed();
  static const int kIsClosedFieldNumber = 3;
  inline bool isclosed() const;
  inline void set_isclosed(bool value);

  // optional uint32 uniqueId = 4;
  inline bool has_uniqueid() const;
  inline void clear_uniqueid();
  static const int kUniqueIdFieldNumber = 4;
  inline ::google::protobuf::uint32 uniqueid() const;
  inline void set_uniqueid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:GarageStatus.DoorStatus)
 private:
  inline void set_has_garageid();
  inline void clear_has_garageid();
  inline void set_has_timestamp();
  inline void clear_has_timestamp();
  inline void set_has_isclosed();
  inline void clear_has_isclosed();
  inline void set_has_uniqueid();
  inline void clear_has_uniqueid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 garageid_;
  ::google::protobuf::uint32 timestamp_;
  bool isclosed_;
  ::google::protobuf::uint32 uniqueid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_GarageStatus_2eproto();
  friend void protobuf_AssignDesc_GarageStatus_2eproto();
  friend void protobuf_ShutdownFile_GarageStatus_2eproto();

  void InitAsDefaultInstance();
  static GarageStatus_DoorStatus* default_instance_;
};
// -------------------------------------------------------------------

class GarageStatus : public ::google::protobuf::Message {
 public:
  GarageStatus();
  virtual ~GarageStatus();

  GarageStatus(const GarageStatus& from);

  inline GarageStatus& operator=(const GarageStatus& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GarageStatus& default_instance();

  void Swap(GarageStatus* other);

  // implements Message ----------------------------------------------

  GarageStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GarageStatus& from);
  void MergeFrom(const GarageStatus& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef GarageStatus_DoorStatus DoorStatus;

  // accessors -------------------------------------------------------

  // repeated .GarageStatus.DoorStatus doors = 1;
  inline int doors_size() const;
  inline void clear_doors();
  static const int kDoorsFieldNumber = 1;
  inline const ::GarageStatus_DoorStatus& doors(int index) const;
  inline ::GarageStatus_DoorStatus* mutable_doors(int index);
  inline ::GarageStatus_DoorStatus* add_doors();
  inline const ::google::protobuf::RepeatedPtrField< ::GarageStatus_DoorStatus >&
      doors() const;
  inline ::google::protobuf::RepeatedPtrField< ::GarageStatus_DoorStatus >*
      mutable_doors();

  // @@protoc_insertion_point(class_scope:GarageStatus)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::GarageStatus_DoorStatus > doors_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_GarageStatus_2eproto();
  friend void protobuf_AssignDesc_GarageStatus_2eproto();
  friend void protobuf_ShutdownFile_GarageStatus_2eproto();

  void InitAsDefaultInstance();
  static GarageStatus* default_instance_;
};
// ===================================================================


// ===================================================================

// GarageStatus_DoorStatus

// required uint32 garageId = 1;
inline bool GarageStatus_DoorStatus::has_garageid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GarageStatus_DoorStatus::set_has_garageid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GarageStatus_DoorStatus::clear_has_garageid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GarageStatus_DoorStatus::clear_garageid() {
  garageid_ = 0u;
  clear_has_garageid();
}
inline ::google::protobuf::uint32 GarageStatus_DoorStatus::garageid() const {
  return garageid_;
}
inline void GarageStatus_DoorStatus::set_garageid(::google::protobuf::uint32 value) {
  set_has_garageid();
  garageid_ = value;
}

// required uint32 timestamp = 2;
inline bool GarageStatus_DoorStatus::has_timestamp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GarageStatus_DoorStatus::set_has_timestamp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GarageStatus_DoorStatus::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GarageStatus_DoorStatus::clear_timestamp() {
  timestamp_ = 0u;
  clear_has_timestamp();
}
inline ::google::protobuf::uint32 GarageStatus_DoorStatus::timestamp() const {
  return timestamp_;
}
inline void GarageStatus_DoorStatus::set_timestamp(::google::protobuf::uint32 value) {
  set_has_timestamp();
  timestamp_ = value;
}

// required bool isClosed = 3;
inline bool GarageStatus_DoorStatus::has_isclosed() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GarageStatus_DoorStatus::set_has_isclosed() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GarageStatus_DoorStatus::clear_has_isclosed() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GarageStatus_DoorStatus::clear_isclosed() {
  isclosed_ = false;
  clear_has_isclosed();
}
inline bool GarageStatus_DoorStatus::isclosed() const {
  return isclosed_;
}
inline void GarageStatus_DoorStatus::set_isclosed(bool value) {
  set_has_isclosed();
  isclosed_ = value;
}

// optional uint32 uniqueId = 4;
inline bool GarageStatus_DoorStatus::has_uniqueid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void GarageStatus_DoorStatus::set_has_uniqueid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void GarageStatus_DoorStatus::clear_has_uniqueid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void GarageStatus_DoorStatus::clear_uniqueid() {
  uniqueid_ = 0u;
  clear_has_uniqueid();
}
inline ::google::protobuf::uint32 GarageStatus_DoorStatus::uniqueid() const {
  return uniqueid_;
}
inline void GarageStatus_DoorStatus::set_uniqueid(::google::protobuf::uint32 value) {
  set_has_uniqueid();
  uniqueid_ = value;
}

// -------------------------------------------------------------------

// GarageStatus

// repeated .GarageStatus.DoorStatus doors = 1;
inline int GarageStatus::doors_size() const {
  return doors_.size();
}
inline void GarageStatus::clear_doors() {
  doors_.Clear();
}
inline const ::GarageStatus_DoorStatus& GarageStatus::doors(int index) const {
  return doors_.Get(index);
}
inline ::GarageStatus_DoorStatus* GarageStatus::mutable_doors(int index) {
  return doors_.Mutable(index);
}
inline ::GarageStatus_DoorStatus* GarageStatus::add_doors() {
  return doors_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::GarageStatus_DoorStatus >&
GarageStatus::doors() const {
  return doors_;
}
inline ::google::protobuf::RepeatedPtrField< ::GarageStatus_DoorStatus >*
GarageStatus::mutable_doors() {
  return &doors_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GarageStatus_2eproto__INCLUDED
