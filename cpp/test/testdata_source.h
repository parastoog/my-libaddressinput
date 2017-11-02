// Copyright (C) 2013 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// An implementation of the Source interface, that reads address metadata from a
// text file, to be used in tests.

#ifndef I18N_ADDRESSINPUT_TEST_TESTDATA_SOURCE_H_
#define I18N_ADDRESSINPUT_TEST_TESTDATA_SOURCE_H_

#include <libaddressinput/source.h>

#include <string>

namespace i18n {
namespace addressinput {

extern const char kDataFileName[];

// Gets address metadata from a text file. Sample usage:
//    class MyClass {
//     public:
//      MyClass(const MyClass&) = delete;
//      MyClass& operator=(const MyClass&) = delete;
//
//      MyClass() : data_ready_(BuildCallback(this, &MyClass::OnDataReady)),
//                              source_(/*aggregate=*/true,
//                                      "/absolute/path/to/test/data/file") {}
//
//      ~MyClass() {}
//
//      void GetData(const std::string& key) {
//        source_->Get(key, *data_ready_);
//      }
//
//     private:
//      void OnDataReady(bool success,
//                       const std::string& key,
//                       std::string* data) {
//        ...
//        delete data;
//      }
//
//      const std::unique_ptr<const Source::Callback> data_ready_;
//      const TestdataSource source_;
//    };
class TestdataSource : public Source {
 public:
  TestdataSource(const TestdataSource&) = delete;
  TestdataSource& operator=(const TestdataSource&) = delete;

  // Will return aggregate data if |aggregate| is set to true.
  // This constructor uses a relative path to the test file.
  explicit TestdataSource(bool aggregate);

  // |abs_testdata_path| is an absolute path to the test data file.
  TestdataSource(bool aggregate, const std::string& abs_testdata_path);

  virtual ~TestdataSource();

  // Source implementation.
  virtual void Get(const std::string& key, const Callback& data_ready) const;

 private:
  const bool aggregate_;
  const std::string abs_testdata_path_;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_TEST_TESTDATA_SOURCE_H_
