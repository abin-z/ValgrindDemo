#include <iostream>

void leak_memory01()
{
  int* data = new int{999};  // 分配内存
  *data = 123;               // 使用内存
  // delete data;            // 不delete，故意制造内存泄漏
}

void leak_memory02()
{
  int* data = new int[100];  // 分配内存
  data[0] = 123;             // 使用内存
  delete data;               // 应该使用delete[]，故意制造内存泄漏
}

int main()
{
  std::cout << "Running leak demo..." << std::endl;
  leak_memory01();
  std::cout << "Memory leak in leak_memory01()..." << std::endl;
  leak_memory02();
  std::cout << "Memory leak in leak_memory02()..." << std::endl;
  std::cout << "Done." << std::endl;
  return 0;
}
