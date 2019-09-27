#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>    
using namespace std;

//size��ʾĿ�Ļ�������С����src������dest�У���֤�����������Ŀ�Ļ�������һ��������C��
//strlcpy����ɫ�����Զ����ַ�������ʱ��������'\0'����ȻҲ��Ӧ����cpyʱcpy��ʵ��size������1
size_t strlcpy(char *dst, const char *src, size_t siz)
{
	//register�ؼ��������ñ��������������ı���ֱ�ӷ���Ĵ������棬����߶�ȡ�ٶ�
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	if (s == 0 || d == 0)
		return 0;

	/* Copy as many bytes as will fit */ 
	//ע������Ϊʲô��nΪ2ʱ��ֻ��һ��������Ϊ�˱�֤����һλ'\0'�Ŀռ�
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
			*d = '\0';      /* NUL-terminate dst ��֮ǰ����������λ���'\0'*/ 
		while (*s++);
	}

	return(s - src - 1);    /* count does not include NUL ���ص���ֵΪs�б������ĳ��ȣ������Ǹ���siz����cpy����ֵ*/
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

	return(s - src - 1);    /* count does not include NUL ���ص���ֵΪs�б������ĳ��ȣ������Ǹ���siz����cpy����ֵ*/
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