#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>    
using namespace std;

//size表示目的缓冲区大小，把src拷贝到dest中，保证不溢出，并且目的缓冲区是一个完整的C串
//strlcpy的特色就是自动在字符串拷贝时在最后添加'\0'，当然也相应的在cpy时cpy的实际size被减了1
size_t strlcpy(char *dst, const char *src, size_t siz)
{
	//register关键字请求让编译器将所声明的变量直接放入寄存器里面，以提高读取速度
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	if (s == 0 || d == 0)
		return 0;

	/* Copy as many bytes as will fit */ 
	//注意这里为什么是n为2时，只存一个数，是为了保证留下一位'\0'的空间
	if (n != 0 && --n != 0) 
	{
		do 
		{
			if ((*d++ = *s++) == '\0')
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) 
	{
		if (siz != 0)
			*d = '\0';      /* NUL-terminate dst 将之前所保留的那位存放'\0'*/ 
		while (*s++);
	}

	return(s - src - 1);    /* count does not include NUL 返回的数值为s中被遍历的长度，而不是根据siz真正cpy的数值*/
}

size_t strlcpy2(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	if (s == 0 || d == 0)
		return 0;

	while (n > 1)
	{
		if ((*d++ = *s++) == '\0')
			break;
		n--;
	}

	if (n == 1 || n == 0)
	{
		if (siz != 0)
			*d = '\0';
		while (*s++ != '\0');
	}

	return(s - src - 1);    /* count does not include NUL 返回的数值为s中被遍历的长度，而不是根据siz真正cpy的数值*/
}

int main_strlcpy()
{
	
	char dst[20] = { '0' };
	const char *src = "abcde";
	size_t siz = 0;
	cout << strlcpy(dst, src, siz) << endl;
	for (int i = 0; i < siz; i++)
	{
		if (dst[i] == '\0')
			break;
		cout << dst[i];
	}
	cout << endl;
	
	return 0;
}