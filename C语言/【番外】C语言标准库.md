# 考试写题常用内容

## 字符和字符串操作

<ctype.h> 用于检测字符和进行大小写转换

```c
// 检查字符，返回0或1

int isalpha(int c)
// 检查字符是否是字母
int isupper(int c)
// 检查字符是否是大写字母
int islower(int c)
// 检查字符是否是小写字母	
int isdigit(int c)
// 检查字符是否是十进制数字

// 大小写转换

int tolower(int c)
// 转成小写字母并返回
int toupper(int c)
// 转成大写字母并返回

```

<string.h> 加入了一些字符串操作函数

```c
// 比较、复制、计算长度

int strcmp(const char *str1, const char *str2)
// 把 str1 所指向的字符串和 str2 所指向的字符串进行比较，常用于以字典序排序
char *strcpy(char *dest, const char *src)
// 把 src 所指向的字符串复制到 dest
size_t strlen(const char *str)
// 计算字符串 str 的长度，直到空结束字符，但不包括空结束字符

// 查找

char *strrchr(const char *str, int c)
// 在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置
char *strstr(const char *haystack, const char *needle)
// 在字符串 haystack 中查找第一次出现字符串 needle（不包含空结束字符）的位置
```

## 数学和时间运算

<limits.h> 和 <float.h> 自带了一些有用的常量

```c
FLT_MANT_DIG  // float 十进制有效位数
DBL_MANT_DIG  // double 十进制有效位数

DBL_MAX       // double 最大值 
DBL_MIN       // double 最小正值
FLT_MAX       // float 最大值

INT_MAX       // int 最大值
INT_MIN       // int 最小值
LLONG_MAX     // long long 最大值
```

<math.h> 提供了数学运算函数和数学常量，考试最常用

```c
// 常量

M_PI	      // 圆周率 π
M_E	        // 自然对数的底数 e

// 库函数

double pow(double x, double y)
// 返回 x 的 y 次幂
double sqrt(double x)
// 返回 x 的平方根
double fabs(double x)
// 返回 x 的绝对值
double ceil(double x)
// 返回 x 向上取整
double floor(double x)
// 返回 x 向下取整
double fmod(double x, double y)
// 返回 x 除以 y 的余数
double log(double x)
// 返回以 e 为底的 log(x)
double sin(double x)
// 返回 sin x
double asin(double x)
// 返回 arcsin x
```

<time.h> 的数据类型和函数可以快速求解有关日期的题目，不过比较复杂

```c
// 数据类型

time_t is  // 一个适合存储日历时间的类型，单位是秒
struct tm  // 一个用来保存时间和日期的结构体
// tm结构体中最重要的内容：
int tm_sec;   // 秒，范围从 0 到 59
int tm_min;   // 分，范围从 0 到 59
int tm_hour;  // 小时，范围从 0 到 23
int tm_mday;  // 一月中的第几天，范围从 1 到 31
int tm_mon;   // 月，范围从 0 到 11
int tm_year;  // 自 1900 年起的年数

// 函数

double difftime(time_t time1, time_t time2)
// 返回 time1 和 time2 之间相差的秒数 (time1-time2)
struct tm *localtime(const time_t *timer)
// timer 的值被分解为 tm 结构，并用本地时区表示
time_t mktime(struct tm *timeptr)
// 把 timeptr 所指向的结构转换为一个依据本地时区的 time_t 值
```

## 文件操作和杂项工具

<stdio.h> 提供了程序向文件或终端输入输出的功能（考试不考这些内容）

```c
// 数据类型

size_t   // 无符号整数类型，它是 sizeof 关键字的结果，表示对象大小
FILE     // 文件流
fpos_t   // 文件位置

// 库宏

NULL     // 空指针常量
EOF      // 一个表示已经到达文件结束的负整数

// 库函数

int fclose(FILE *stream)
// 关闭流 stream 刷新所有的缓冲区
FILE *fopen(const char *filename, const char *mode)
// 使用给定的模式 mode 打开 filename 所指向的文件 

int fgetc(FILE *stream)
// 从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动 
char *fgets(char *str, int n, FILE *stream)
// 从指定的流 stream 读取一行，并把它存储在 str 所指向的字符串内 当读取 (n-1) 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定 
int fputc(int char, FILE *stream)
// 把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动 
int fputs(const char *str, FILE *stream)
// 把字符串写入到指定的流 stream 中，但不包括空字符 

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
// 从给定流 stream 读取数据到 ptr 所指向的数组中 
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
// 把 ptr 所指向的数组中的数据写入到给定流 stream 中 

int printf(const char *format, ...)
// 发送格式化输出到标准输出 stdout 
int scanf(const char *format, ...)
// 从标准输入 stdin 读取格式化输入 
int fprintf(FILE *stream, const char *format, ...)
// 发送格式化输出到流 stream 中 
int fscanf(FILE *stream, const char *format, ...)
// 从流 stream 读取格式化输入 

int fseek(FILE *stream, long int offset, int whence)
// 设置流 stream 的文件位置为给定的偏移 offset，参数 offset 意味着从给定的 whence 位置查找的字节数 
void rewind(FILE *stream)
// 设置文件位置为给定流 stream 的文件的开头 

int feof(FILE *stream)
// 测试给定流 stream 的文件结束标识符 
int ferror(FILE *stream)
// 测试给定流 stream 的错误标识符 
void clearerr(FILE *stream)
// 清除给定流 stream 的文件结束和错误标识符 
long int ftell(FILE *stream)
// 返回给定流 stream 的当前文件位置 
```

<stdlib.h> 提供了标准的一些杂项工具

```c

int atoi(const char *str)
// 把参数 str 所指向的字符串转换为一个整数（类型为 int 型）。
double strtod(const char *str, char **endptr)
// 把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。

void *calloc(size_t nitems, size_t size)
// 分配所需的内存空间，并返回一个指向它的指针。
void free(void *ptr)
// 释放之前调用 calloc、malloc 或 realloc 所分配的内存空间。
void *malloc(size_t size)
// 分配所需的内存空间，并返回一个指向它的指针。
void *realloc(void *ptr, size_t size)
// 尝试重新调整之前调用 malloc 或 calloc 所分配的 ptr 所指向的内存块的大小。

int abs(int x)
// 返回 x 的绝对值。

int rand(void)
// 返回一个范围在 0 到 RAND_MAX 之间的伪随机数。
void srand(unsigned int seed)
// 该函数播种由函数 rand 使用的随机数发生器。

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
// 数组排序，在【番外】零碎知识中有详细的解释
```

# 部分标准库列表

```c
<stdlib.h>	       // 基础工具：内存管理、程序工具、字符串转换、随机数
<stdio.h>	         // 输入/输出
<string.h>	       // 字符串处理
<ctype.h>	         // 用来确定包含于字符数据中的类型的函数
<math.h>	         // 常用数学函数
<limits.h>	       // 基本类型的大小
<float.h>	         // 浮点数类型的极限
<time.h>	         // 时间/日期工具

// 本篇笔记仅总结以上库的内容，此外截止C11，标准库还有如下内容

<errno.h>	         // 报告错误条件的宏
<locale.h>	       // 本地化工具
<setjmp.h>	       // 非局部跳转
<signal.h>	       // 信号处理
<stdarg.h>	       // 可变参数
<stddef.h>	       // 常用宏定义
<assert.h>	       // 条件编译宏，将参数与零比较

<iso646.h>         // (C95)	符号的替代写法
<wchar.h>          // (C95)	扩展多字节和宽字符工具
<wctype.h>         // (C95)	用来确定包含于宽字符数据中的类型的函数
<complex.h>        // (C99)	复数运算
<fenv.h>           // (C99)	浮点数环境
<inttypes.h>       // (C99)	整数类型的格式转换
<stdbool.h>        // (C99)	布尔类型
<stdint.h>         // (C99)	定宽整数类型
<tgmath.h>         // (C99)	泛型数学（包装 math.h 和 complex.h 的宏）

<stdalign.h>       // (C11)	alignas 与 alignof 便利宏
<stdatomic.h>      // (C11)	原子类型
<threads.h>        // (C11)	线程库
<stdnoreturn.h>    // (C11)	noreturn 便利宏
<uchar.h>          // (C11)	UTF-16 和 UTF-32 字符工具

```

## <ctype.h>

用于检查字符的函数，以下函数皆接收 int 并返回 0 或非 0

```c
int isalnum(int c)  // 检查字符是否是字母和数字	
int isalpha(int c)  // 检查字符是否是字母	
int iscntrl(int c)  // 检查字符是否是控制字 (ASCII 码为0～31或127)
int isdigit(int c)  // 检查字符是否是十进制数字	
int isgraph(int c)  // 检查字符是否有图形表示法 (字母+数字+标点)
int islower(int c)  // 检查字符是否是小写字母	
int isprint(int c)  // 检查字符是否是可打印的 (字母+数字+标点+空白)
int ispunct(int c)  // 检查字符是否是标点符号字符	
int isspace(int c)  // 检查字符是否是空白字符 (空格和制表符)
int isupper(int c)  // 检查字符是否是大写字母	
int isxdigit(int c) // 检查字符是否是十六进制数字 (0～9/a～f/A～F)
```

用于大小写转换的函数

```c
int tolower(int c)  // 该函数把大写字母转换为小写字母
int toupper(int c)  // 该函数把小写字母转换为大写字母
```

## <float.h>

一组与浮点数有关的常量，为了方便记忆可以拆分成前后缀

```c
// 前缀
FLT  // float
DBL  // double
LDBL // long double
// 后缀
_RADIX      // 浮点数的基数（通常为2）这是只有FLT才有的后缀
_MANT_DIG   // 有效位数
_DIG        // 十进制位数精度，即保证多少位不失真
_MIN_EXP    // 以基数为底的最小负指数
_MIN_10_EXP // 最小负十进制指数
_MAX_EXP    // 以基数为底的最大指数
_MAX_10_EXP // 最大十进制指数
_MAX        // 该类型的最大正值
_MIN        // 该类型的最小正值
_EPSILON    // 该类型的相对误差
```

## <limits.h>

一组与整数有关的常量，为了方便记忆可以拆分成前后缀

```c
// 前缀
CHAR    // char
SCHAR   // signed char
UCHAR   // unsigned char
SHRT    // short
USHRT   // unsigned short
INT     // int
UINT    // unsigned int
LONG    // long
ULONG   // unsigned long
LLONG   // long long
ULLONG  // unsigned long long
// 后缀
_BIT    // 只有char才有,表示char类型的位数,通常为8
_MIN    // 该类型的最负小值，只有非unsigned类型才有
_MAX    // 该类型的最大值
// 常见的具体数值
SHRT_MAX == 32767
INT_MAX == 2147483647
LLONG_MAX == 9223372036854775807LL
```

## <math.h>

一组数学常量

```c
M_PI	      // 圆周率 π
M_E	        // 自然对数的底数 e
M_LOG2E	    // log2(e)
M_LOG10E  	// log10(e)
M_LN2	      // ln(2)
M_LN10	    // ln(10)
M_PI_2	    // π/2
M_PI_4	    // π/4
M_1_PI	    // 1/π
M_2_PI	    // 2/π
M_2_SQRTPI	// 2/√π
M_SQRT2	    // √2
M_SQRT1_2	  // 1/√2
```

一组表示数学错误的宏

```c
HUGE_VAL	  // 当函数结果溢出时返回的值（正无穷大）
HUGE_VALF   // 当函数结果溢出时返回的值（正无穷大，浮点型）
HUGE_VALL	  // 当函数结果溢出时返回的值（正无穷大，长双精度）
INFINITY	  // 正无穷大
NAN	        // 非数字值（Not-A-Number）比如 0/0
FP_INFINITE	// 表示无穷大
FP_NAN	    // 表示非数字值
FP_NORMAL	  // 表示正常的浮点数
FP_SUBNORMAL// 表示次正规数
FP_ZERO	    // 表示零
```

数学运算函数

```c
double acos(double x) // 返回以弧度表示的 x 的反余弦。
double asin(double x) // 返回以弧度表示的 x 的反正弦。
double atan(double x) // 返回以弧度表示的 x 的反正切。
double atan2(double y, double x) // 返回以弧度表示的 y/x 的反正切。y 和 x 的值的符号决定了正确的象限。
double cos(double x)   // 返回弧度角 x 的余弦。
double cosh(double x)  // 返回 x 的双曲余弦。
double sin(double x)   // 返回弧度角 x 的正弦。
double sinh(double x)  // 返回 x 的双曲正弦。
double tanh(double x)  // 返回 x 的双曲正切。
double exp(double x) // 返回 e 的 x 次幂的值。
double frexp(double x, int *exponent) //把浮点数 x 分解成尾数和指数。返回值是尾数，并将指数存入 exponent 中。所得的值是 x = mantissa * 2 ^ exponent。
double ldexp(double x, int exponent) //返回 x 乘以 2 的 exponent 次幂。
double log(double x)  //返回 x 的自然对数（基数为 e 的对数）。
double log10(double x) //返回 x 的常用对数（基数为 10 的对数）。
double modf(double x, double *integer) //返回值为小数部分（小数点后的部分），并设置 integer 为整数部分。
double pow(double x, double y)  //返回 x 的 y 次幂。
double sqrt(double x) //返回 x 的平方根。
double ceil(double x) //返回大于或等于 x 的最小的整数值。
double fabs(double x) //返回 x 的绝对值。
double floor(double x) // 返回小于或等于 x 的最大的整数值。
double fmod(double x, double y) // 返回 x 除以 y 的余数。
```

## <time.h>

与时间相关的常量与宏

```c
NULL	          // 空指针常量
CLOCKS_PER_SEC	// 每秒的时钟周期数
TIME_UTC	      // 表示 UTC 时间（C11）
```

变量类型

```c
size_t     // 无符号整数类型，它是 sizeof 关键字的结果
clock_t    // 这是一个适合存储处理器时间的类型
time_t is  // 一个适合存储日历时间的类型
struct tm  // 一个用来保存时间和日期的结构

// tm被定义为如下内容：
struct tm {
   int tm_sec;   // 秒，范围从 0 到 59
   int tm_min;   // 分，范围从 0 到 59
   int tm_hour;  // 小时，范围从 0 到 23
   int tm_mday;  // 一月中的第几天，范围从 1 到 31
   int tm_mon;   // 月，范围从 0 到 11
   int tm_year;  // 自 1900 年起的年数
   int tm_wday;  // 一周中的第几天，范围从 0 到 6
   int tm_yday;  // 一年中的第几天，范围从 0 到 365
   int tm_isdst; // 夏令时
};

```

库函数

```c
char *asctime(const struct tm *timeptr)
// 返回一个指向字符串的指针，它代表了结构 timeptr 的日期和时间
clock_t clock(void)
// 返回程序执行起（一般为程序的开头），处理器时钟所使用的时间
char *ctime(const time_t *timer)
// 返回一个表示当地时间的字符串，当地时间是基于参数 timer
double difftime(time_t time1, time_t time2)
// 返回 time1 和 time2 之间相差的秒数 (time1-time2)
struct tm *gmtime(const time_t *timer)
// timer 的值被分解为 tm 结构，并用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示
struct tm *localtime(const time_t *timer)
// timer 的值被分解为 tm 结构，并用本地时区表示
time_t mktime(struct tm *timeptr)
// 把 timeptr 所指向的结构转换为一个依据本地时区的 time_t 值
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
// 根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中
time_t time(time_t *timer)
// 计算当前日历时间，并把它编码成 time_t 格式
int timespec_get(struct timespec *ts, int base);
// 获取当前时间（C11）
```

## <string.h>

包含空指针常量 `NULL` 和 `size_t` 类型

库函数如下

```c
void *memchr(const void *str, int c, size_t n)
// 在参数 str 所指向的字符串的前 n 个字节中搜索第一次出现字符 c（一个无符号字符）的位置
int memcmp(const void *str1, const void *str2, size_t n)
// 把 str1 和 str2 的前 n 个字节进行比较
void *memcpy(void *dest, const void *src, size_t n)
// 从 src 复制 n 个字符到 dest
void *memmove(void *dest, const void *src, size_t n)
// 另一个用于从 src 复制 n 个字符到 dest 的函数
void *memset(void *str, int c, size_t n)
// 将指定的值 c 复制到 str 所指向的内存区域的前 n 个字节中
char *strcat(char *dest, const char *src)
// 把 src 所指向的字符串追加到 dest 所指向的字符串的结尾
char *strncat(char *dest, const char *src, size_t n)
// 把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止
char *strchr(const char *str, int c)
// 在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置
int strcmp(const char *str1, const char *str2)
// 把 str1 所指向的字符串和 str2 所指向的字符串进行比较
int strncmp(const char *str1, const char *str2, size_t n)
// 把 str1 和 str2 进行比较，最多比较前 n 个字节
int strcoll(const char *str1, const char *str2)
// 把 str1 和 str2 进行比较，结果取决于 LC_COLLATE 的位置设置
char *strcpy(char *dest, const char *src)
// 把 src 所指向的字符串复制到 dest
char *strncpy(char *dest, const char *src, size_t n)
// 把 src 所指向的字符串复制到 dest，最多复制 n 个字符
size_t strcspn(const char *str1, const char *str2)
// 检索字符串 str1 开头连续有几个字符都不含字符串 str2 中的字符
char *strerror(int errnum)
// 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针
size_t strlen(const char *str)
// 计算字符串 str 的长度，直到空结束字符，但不包括空结束字符
char *strpbrk(const char *str1, const char *str2)
// 检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置
char *strrchr(const char *str, int c)
// 在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置
size_t strspn(const char *str1, const char *str2)
// 检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标
char *strstr(const char *haystack, const char *needle)
// 在字符串 haystack 中查找第一次出现字符串 needle（不包含空结束字符）的位置
char *strtok(char *str, const char *delim)
// 分解字符串 str 为一组字符串，delim 为分隔符
size_t strxfrm(char *dest, const char *src, size_t n)
// 根据程序当前的区域选项中的 LC_COLLATE 来转换字符串 src 的前 n 个字符，并把它们放置在字符串 dest 中
```

## <stdio.h>

变量类型

```c
size_t
// 无符号整数类型，它是 sizeof 关键字的结果，表示对象大小。
FILE
// 文件流类型，适合存储文件流信息的对象类型。
fpos_t
// 文件位置类型，适合存储文件中任何位置的对象类型。
```

库宏

```c
NULL
// 这个宏是一个空指针常量的值。
_IOFBF、_IOLBF 和 _IONBF
// 这些宏扩展了带有特定值的整型常量表达式，并适用于 setvbuf 函数的第三个参数。
BUFSIZ
// 这个宏是一个整数，该整数代表了 setbuf 函数使用的缓冲区大小。
EOF
// 这个宏是一个表示已经到达文件结束的负整数。
FOPEN_MAX
// 这个宏是一个整数，该整数代表了系统可以同时打开的文件数量。
FILENAME_MAX
// 这个宏是一个整数，该整数代表了字符数组可以存储的文件名的最大长度。如果实现没有任何限制，则该值应为推荐的最大值。
L_tmpnam
// 这个宏是一个整数，该整数代表了字符数组可以存储的由 tmpnam 函数创建的临时文件名的最大长度。
SEEK_CUR、SEEK_END 和 SEEK_SET
// 这些宏是在 fseek 函数中使用，用于在一个文件中定位不同的位置。
TMP_MAX
// 这个宏是 tmpnam 函数可生成的独特文件名的最大数量。
stderr、stdin 和 stdout
// 这些宏是指向 FILE 类型的指针，分别对应于标准错误、标准输入和标准输出流。
```

库函数

```c
int fclose(FILE *stream)
// 关闭流 stream 刷新所有的缓冲区 
void clearerr(FILE *stream)
// 清除给定流 stream 的文件结束和错误标识符 
int feof(FILE *stream)
// 测试给定流 stream 的文件结束标识符 
int ferror(FILE *stream)
// 测试给定流 stream 的错误标识符 
int fflush(FILE *stream)
// 刷新流 stream 的输出缓冲区 
int fgetpos(FILE *stream, fpos_t *pos)
// 获取流 stream 的当前文件位置，并把它写入到 pos 
FILE *fopen(const char *filename, const char *mode)
// 使用给定的模式 mode 打开 filename 所指向的文件 
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
// 从给定流 stream 读取数据到 ptr 所指向的数组中 
FILE *freopen(const char *filename, const char *mode, FILE *stream)
// 把一个新的文件名 filename 与给定的打开的流 stream 关联，同时关闭流中的旧文件 
int fseek(FILE *stream, long int offset, int whence)
// 设置流 stream 的文件位置为给定的偏移 offset，参数 offset 意味着从给定的 whence 位置查找的字节数 
int fsetpos(FILE *stream, const fpos_t *pos)
// 设置给定流 stream 的文件位置为给定的位置 参数 pos 是由函数 fgetpos 给定的位置 
long int ftell(FILE *stream)
// 返回给定流 stream 的当前文件位置 
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
// 把 ptr 所指向的数组中的数据写入到给定流 stream 中 
int remove(const char *filename)
// 删除给定的文件名 filename，以便它不再被访问 
int rename(const char *old_filename, const char *new_filename)
// 把 old_filename 所指向的文件名改为 new_filename 
void rewind(FILE *stream)
// 设置文件位置为给定流 stream 的文件的开头 
void setbuf(FILE *stream, char *buffer)
// 定义流 stream 应如何缓冲 
int setvbuf(FILE *stream, char *buffer, int mode, size_t size)
// 另一个定义流 stream 应如何缓冲的函数 
FILE *tmpfile(void)
// 以二进制更新模式(wb+)创建临时文件 
char *tmpnam(char *str)
// 生成并返回一个有效的临时文件名，该文件名之前是不存在的 
int fprintf(FILE *stream, const char *format, ...)
// 发送格式化输出到流 stream 中 
int printf(const char *format, ...)
// 发送格式化输出到标准输出 stdout 
int sprintf(char *str, const char *format, ...)
// 发送格式化输出到字符串 
int vfprintf(FILE *stream, const char *format, va_list arg)
// 使用参数列表发送格式化输出到流 stream 中 
int vprintf(const char *format, va_list arg)
// 使用参数列表发送格式化输出到标准输出 stdout 
int vsprintf(char *str, const char *format, va_list arg)
// 使用参数列表发送格式化输出到字符串 
int fscanf(FILE *stream, const char *format, ...)
// 从流 stream 读取格式化输入 
int scanf(const char *format, ...)
// 从标准输入 stdin 读取格式化输入 
int sscanf(const char *str, const char *format, ...)
// 从字符串读取格式化输入 
int fgetc(FILE *stream)
// 从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动 
char *fgets(char *str, int n, FILE *stream)
// 从指定的流 stream 读取一行，并把它存储在 str 所指向的字符串内 当读取 (n-1) 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定 
int fputc(int char, FILE *stream)
// 把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动 
int fputs(const char *str, FILE *stream)
// 把字符串写入到指定的流 stream 中，但不包括空字符 
int getc(FILE *stream)
// 从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动 
int getchar(void)
// 从标准输入 stdin 获取一个字符（一个无符号字符） 
char *gets(char *str)
// 从标准输入 stdin 读取一行，并把它存储在 str 所指向的字符串中 当读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定 
int putc(int char, FILE *stream)
// 把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动 
int putchar(int char)
// 把参数 char 指定的字符（一个无符号字符）写入到标准输出 stdout 中 
int puts(const char *str)
// 把一个字符串写入到标准输出 stdout，直到空字符，但不包括空字符 换行符会被追加到输出中 
int ungetc(int char, FILE *stream)
// 把字符 char（一个无符号字符）推入到指定的流 stream 中，以便它是下一个被读取到的字符 
void perror(const char *str)
// 把一个描述性错误消息输出到标准错误 stderr 首先输出字符串 str，后跟一个冒号，然后是一个空格 
int snprintf(char *str, size_t size, const char *format, ...)
// 格式字符串到 str 中 
```

## <stdlib.h>

变量类型

```c
size_t
// 这是无符号整数类型，它是 sizeof 关键字的结果
wchar_t
// 这是一个宽字符常量大小的整数类型
div_t
// 这是 div 函数返回的结构
ldiv_t
// 这是 ldiv 函数返回的结构
```

库宏

```c
NULL
// 这个宏是一个空指针常量的值
EXIT_FAILURE
// 这是 exit 函数失败时要返回的值
EXIT_SUCCESS
// 这是 exit 函数成功时要返回的值
RAND_MAX
// 这个宏是 rand 函数返回的最大值
MB_CUR_MAX
// 这个宏表示在多字节字符集中的最大字符数，不能大于 MB_LEN_MAX
```

库函数

```c
double atof(const char *str)
// 把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。
int atoi(const char *str)
// 把参数 str 所指向的字符串转换为一个整数（类型为 int 型）。
long int atol(const char *str)
// 把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。
double strtod(const char *str, char **endptr)
// 把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。
long int strtol(const char *str, char **endptr, int base)
// 把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。
unsigned long int strtoul(const char *str, char **endptr, int base)
// 把参数 str 所指向的字符串转换为一个无符号长整数（类型为 unsigned long int 型）。
void *calloc(size_t nitems, size_t size)
// 分配所需的内存空间，并返回一个指向它的指针。
void free(void *ptr)
// 释放之前调用 calloc、malloc 或 realloc 所分配的内存空间。
void *malloc(size_t size)
// 分配所需的内存空间，并返回一个指向它的指针。
void *realloc(void *ptr, size_t size)
// 尝试重新调整之前调用 malloc 或 calloc 所分配的 ptr 所指向的内存块的大小。
void abort(void)
// 使一个异常程序终止。
int atexit(void (*func)(void))
// 当程序正常终止时，调用指定的函数 func。
void exit(int status)
// 使程序正常终止。
char *getenv(const char *name)
// 搜索 name 所指向的环境字符串，并返回相关的值给字符串。
int system(const char *string)
// 由 string 指定的命令传给要被命令处理器执行的主机环境。
void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
// 执行二分查找。
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
// 数组排序。
int abs(int x)
// 返回 x 的绝对值。
div_t div(int numer, int denom)
// 分子除以分母。
long int labs(long int x)
// 返回 x 的绝对值。
ldiv_t ldiv(long int numer, long int denom)
// 分子除以分母。
int rand(void)
// 返回一个范围在 0 到 RAND_MAX 之间的伪随机数。
void srand(unsigned int seed)
// 该函数播种由函数 rand 使用的随机数发生器。
int mblen(const char *str, size_t n)
// 返回参数 str 所指向的多字节字符的长度。
size_t mbstowcs(schar_t *pwcs, const char *str, size_t n)
// 把参数 str 所指向的多字节字符的字符串转换为参数 pwcs 所指向的数组。
int mbtowc(wchar_t *pwc, const char *str, size_t n)
// 检查参数 str 所指向的多字节字符。
size_t wcstombs(char *str, const wchar_t *pwcs, size_t n)
// 把数组 pwcs 中存储的编码转换为多字节字符，并把它们存储在字符串 str 中。
int wctomb(char *str, wchar_t wchar)
// 检查对应于参数 wchar 所给出的多字节字符的编码。
```