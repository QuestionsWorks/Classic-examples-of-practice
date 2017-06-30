#include <cstdlib>

template <typename T>
class Pointer
{
public:
  Pointer(T* inPtr);
  ~Pointer();
  T& operator*();
  const T& operator*() const;
  T* operator->();
  const T* operator->() const;

  operator bool() const { return (mPtr != NULL); }

protected:
  T* mPtr;
private:
  Pointer(const Pointer<T>& src);
  Pointer<T>& operator=(const Pointer<T>& rhs);
};

template <typename T>
Pointer<T>::Pointer(T* inPtr)
{
  mPtr = inPtr;
}

template <typename T>
Pointer<T>::~Pointer()
{
  delete mPtr;
}

template <typename T>
T* Pointer<T>::operator->()
{
  return (mPtr);
}

template <typename T>
const T* Pointer<T>::operator->() const
{
  return (mPtr);
}

template <typename T>
T& Pointer<T>::operator*()
{
  return (*mPtr);
}

template <typename T>
const T& Pointer<T>::operator*() const
{
  return (*mPtr);
}
