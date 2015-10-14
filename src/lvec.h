#ifndef lvec_h
#define lvec_h

#include <string>
#include <stdexcept>
#include <cstring>
#include "visitor.h"
#include "vec.h"

namespace ldat {

  template<typename T>
  class lvec : public vec {
    public: 
      lvec(vecsize size) : vec(), size_(size) {
        vec_ = new T[size];
      }

      ~lvec() {
        delete [] vec_;
      }

      vecsize size() const {
        return size_;
      }

      double get_of_type(vecsize i, double type) const {
        return vec_[i];
      }

      int get_of_type(vecsize i, int type) const {
        return vec_[i];
      }

      std::string get_of_type(vecsize i, const std::string& type) const {
        throw std::runtime_error("Can't convert numeric to string.");
      }

      void visit(lvec_visitor* visitor) {
        visitor->visit(*this);
      }

      T get(vecsize i) const {
        return vec_[i];
      }

      void set(vecsize i, T value) {
        vec_[i] = value;
      }

      const T* data() const {
        return vec_;
      }

      T* data() {
        return vec_;
      }

    private:
      T* vec_;
      vecsize size_;
  };

  template<>
  class lvec<std::string> : public vec {
    public:
      lvec(vecsize size, unsigned int strlen) : vec(), size_(size), 
          strlen_(strlen) {
        vec_ = new char[size_ * strlen_];
      }

      ~lvec() {
        delete [] vec_;
      }

      vecsize size() const {
        return size_;
      }

      double get_of_type(vecsize i, double type) const {
        throw std::runtime_error("Can't convert a string to double.");
      }

      int get_of_type(vecsize i, int type) const {
        throw std::runtime_error("Can't convert a string to integer.");
      }

      std::string get_of_type(vecsize i, const std::string& type) const {
        return get(i);
      }

      void visit(lvec_visitor* visitor) {
        visitor->visit(*this);
      }

      std::string get(vecsize i) const {
        vecsize offset = i * strlen_;
        return std::string(vec_ + offset);
      }

      void set(vecsize i, const std::string& str) {
        vecsize offset = i * strlen_;
        std::strncpy(vec_ + offset, str.c_str(), strlen_);
        vec_[offset + strlen_ - 1] = 0;
      }

    private:
      char* vec_;
      vecsize size_;
      unsigned int strlen_;
  };
}

#endif
