// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GarageHistoryRequest.proto

#ifndef PROTOBUF_GarageHistoryRequest_2eproto__INCLUDED
#define PROTOBUF_GarageHistoryRequest_2eproto__INCLUDED

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
void  protobuf_AddDesc_GarageHistoryRequest_2eproto();
void protobuf_AssignDesc_GarageHistoryRequest_2eproto();
void protobuf_ShutdownFile_GarageHistoryRequest_2eproto();

class GarageHistoryRequest;

// ===================================================================

class GarageHistoryRequest : public ::google::protobuf::Message {
 public:
  GarageHistoryRequest();
  virtual ~GarageHistoryRequest();

  GarageHistoryRequest(const GarageHistoryRequest& from);

  inline GarageHistoryRequest& operator=(const GarageHistoryRequest& from) {
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
  static const GarageHistoryRequest& default_instance();

  void Swap(GarageHistoryRequest* other);

  // implements Message ----------------------------------------------

  GarageHistoryRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GarageHistoryRequest& from);
  void MergeFrom(const GarageHistoryRequest& from);
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

  // optional uint32 startTime = 1;
  inline bool has_starttime() const;
  inline void clear_starttime();
  static const int kStartTimeFieldNumber = 1;
  inline ::google::protobuf::uint32 starttime() const;
  inline void set_starttime(::google::protobuf::uint32 value);

  // optional sint32 interval = 2;
  inline bool has_interval() const;
  inline void clear_interval();
  static const int kIntervalFieldNumber = 2;
  inline ::google::protobuf::int32 interval() const;
  inline void set_interval(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:GarageHistoryRequest)
 private:
  inline void set_has_starttime();
  inline void clear_has_starttime();
  inline void set_has_interval();
  inline void clear_has_interval();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 starttime_;
  ::google::protobuf::int32 interval_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_GarageHistoryRequest_2eproto();
  friend void protobuf_AssignDesc_GarageHistoryRequest_2eproto();
  friend void protobuf_ShutdownFile_GarageHistoryRequest_2eproto();

  void InitAsDefaultInstance();
  static GarageHistoryRequest* default_instance_;
};
// ===================================================================


// ===================================================================

// GarageHistoryRequest

// optional uint32 startTime = 1;
inline bool GarageHistoryRequest::has_starttime() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GarageHistoryRequest::set_has_starttime() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GarageHistoryRequest::clear_has_starttime() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GarageHistoryRequest::clear_starttime() {
  starttime_ = 0u;
  clear_has_starttime();
}
inline ::google::protobuf::uint32 GarageHistoryRequest::starttime() const {
  return starttime_;
}
inline void GarageHistoryRequest::set_starttime(::google::protobuf::uint32 value) {
  set_has_starttime();
  starttime_ = value;
}

// optional sint32 interval = 2;
inline bool GarageHistoryRequest::has_interval() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GarageHistoryRequest::set_has_interval() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GarageHistoryRequest::clear_has_interval() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GarageHistoryRequest::clear_interval() {
  interval_ = 0;
  clear_has_interval();
}
inline ::google::protobuf::int32 GarageHistoryRequest::interval() const {
  return interval_;
}
inline void GarageHistoryRequest::set_interval(::google::protobuf::int32 value) {
  set_has_interval();
  interval_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GarageHistoryRequest_2eproto__INCLUDED
