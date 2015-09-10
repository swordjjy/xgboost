// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_DECISIONTREES_XGBOOST_TREE_FBS_H_
#define FLATBUFFERS_GENERATED_DECISIONTREES_XGBOOST_TREE_FBS_H_

#include "flatbuffers/flatbuffers.h"


namespace xgboost {
namespace tree {
namespace fbs {

struct Node;
struct Tree;
struct Forest;

MANUALLY_ALIGNED_STRUCT(4) Node FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t feature_id_;
  float value_;
  int32_t left_child_index_;
  uint8_t default_left_child_;
  int8_t __padding0;
  int16_t __padding1;

 public:
  Node(int32_t feature_id, float value, int32_t left_child_index, uint8_t default_left_child)
    : feature_id_(flatbuffers::EndianScalar(feature_id)), value_(flatbuffers::EndianScalar(value)), left_child_index_(flatbuffers::EndianScalar(left_child_index)), default_left_child_(flatbuffers::EndianScalar(default_left_child)), __padding0(0), __padding1(0) { (void)__padding0; (void)__padding1; }

  int32_t feature_id() const { return flatbuffers::EndianScalar(feature_id_); }
  void mutate_feature_id(int32_t feature_id) { flatbuffers::WriteScalar(&feature_id_, feature_id); }
  float value() const { return flatbuffers::EndianScalar(value_); }
  void mutate_value(float value) { flatbuffers::WriteScalar(&value_, value); }
  int32_t left_child_index() const { return flatbuffers::EndianScalar(left_child_index_); }
  void mutate_left_child_index(int32_t left_child_index) { flatbuffers::WriteScalar(&left_child_index_, left_child_index); }
  uint8_t default_left_child() const { return flatbuffers::EndianScalar(default_left_child_); }
  void mutate_default_left_child(uint8_t default_left_child) { flatbuffers::WriteScalar(&default_left_child_, default_left_child); }
};
STRUCT_END(Node, 16);

struct Tree FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::Vector<const Node *> *nodes() const { return GetPointer<const flatbuffers::Vector<const Node *> *>(4); }
  flatbuffers::Vector<const Node *> *mutable_nodes() { return GetPointer<flatbuffers::Vector<const Node *> *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* nodes */) &&
           verifier.Verify(nodes()) &&
           verifier.EndTable();
  }
};

struct TreeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_nodes(flatbuffers::Offset<flatbuffers::Vector<const Node *>> nodes) { fbb_.AddOffset(4, nodes); }
  TreeBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  TreeBuilder &operator=(const TreeBuilder &);
  flatbuffers::Offset<Tree> Finish() {
    auto o = flatbuffers::Offset<Tree>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<Tree> CreateTree(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::Vector<const Node *>> nodes = 0) {
  TreeBuilder builder_(_fbb);
  builder_.add_nodes(nodes);
  return builder_.Finish();
}

struct Forest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::Vector<flatbuffers::Offset<Tree>> *trees() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tree>> *>(4); }
  flatbuffers::Vector<flatbuffers::Offset<Tree>> *mutable_trees() { return GetPointer<flatbuffers::Vector<flatbuffers::Offset<Tree>> *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* trees */) &&
           verifier.Verify(trees()) &&
           verifier.VerifyVectorOfTables(trees()) &&
           verifier.EndTable();
  }
};

struct ForestBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_trees(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tree>>> trees) { fbb_.AddOffset(4, trees); }
  ForestBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ForestBuilder &operator=(const ForestBuilder &);
  flatbuffers::Offset<Forest> Finish() {
    auto o = flatbuffers::Offset<Forest>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<Forest> CreateForest(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tree>>> trees = 0) {
  ForestBuilder builder_(_fbb);
  builder_.add_trees(trees);
  return builder_.Finish();
}

inline const xgboost::tree::fbs::Forest *GetForest(const void *buf) { return flatbuffers::GetRoot<xgboost::tree::fbs::Forest>(buf); }

inline Forest *GetMutableForest(void *buf) { return flatbuffers::GetMutableRoot<Forest>(buf); }

inline bool VerifyForestBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<xgboost::tree::fbs::Forest>(); }

inline void FinishForestBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<xgboost::tree::fbs::Forest> root) { fbb.Finish(root); }

}  // namespace fbs
}  // namespace tree
}  // namespace xgboost

#endif  // FLATBUFFERS_GENERATED_DECISIONTREES_XGBOOST_TREE_FBS_H_
