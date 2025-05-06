#include <iostream>

void normal_memory01()
{
  int* data = new int{999};  // 分配内存
  *data = 123;               // 使用内存
  delete data;               // 正常释放内存
}

void normal_memory02()
{
  int* data = new int[100];  // 分配内存
  data[0] = 123;             // 使用内存
  delete[] data;             // 正常释放内存
}

int main()
{
  std::cout << "Running normal demo..." << std::endl;
  normal_memory01();
  std::cout << "Memory normal in normal_memory01()..." << std::endl;
  normal_memory02();
  std::cout << "Memory normal in normal_memory02()..." << std::endl;
  std::cout << "Done." << std::endl;
  return 0;
}
