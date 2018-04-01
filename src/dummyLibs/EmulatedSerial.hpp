#ifndef EmulatedSerial_hpp
#define EmulatedSerial_hpp

#include <stdio.h>
#include <string>

class EmulatedSerial
{
public:
  EmulatedSerial(){};

  void begin(int baudrate) {}

  size_t print(const std::string &s) { printf("Serial: %s", s.c_str()); }
  size_t print(const char s[]) { printf("Serial: %s", s); }
  size_t print(char s) { printf("Serial: %s", &s); }
  size_t print(int n, int = 10) { printf("Serial: %d", n); }
  size_t print(unsigned int n, int = 10) { printf("Serial: %d", n); }
  size_t print(long n, int = 10) { printf("Serial: %d", n); }
  size_t print(unsigned long n, int = 10) { printf("Serial: %d", n); }
  size_t print(double f, int = 2) { printf("Serial: %f", f); }
  size_t print(void) { printf("Serial: (void)"); }

  size_t println(const std::string &s) { printf("Serial: %s\n", s.c_str()); }
  size_t println(const char s[]) { printf("Serial: %s\n", s); }
  size_t println(char s) { printf("Serial: %s\n", &s); }
  size_t println(int n, int = 10) { printf("Serial: %d\n", n); }
  size_t println(unsigned int n, int = 10) { printf("Serial: %d\n", n); }
  size_t println(long n, int = 10) { printf("Serial: %d\n", n); }
  size_t println(unsigned long n, int = 10) { printf("Serial: %d\n", n); }
  size_t println(double f, int = 2) { printf("Serial: %f\n", f); }
  size_t println(void) { printf("Serial: (void)\n"); }
};

EmulatedSerial Serial;
#endif