#pragma once
#include <iostream>
#include <string>
using namespace std;

//T为文本串如"Now is the time"，P为模式串如"time"，时间复杂度O(m*n)，其中m与n为P和T的长度
int bf_match(string P, string T)
{
	int sizeP = P.size();
	int sizeT = T.size();
	int i = 0, j = 0;
	for (; i < sizeP - sizeT + 1; i++)
	{
		for (; j < sizeT; j++)
		{
			if (T[j] != P[i + j])
				break;
		}
		if (j >= sizeT)
			break;
	}
	return (i < sizeP - sizeT + 1) ? (i) : (-1);  //这里的i在成功时返回的是成功的位置，失败则是-1
}

/*
KMP算法的核心，是一个被称为部分匹配表(Partial Match Table)的数组，PMT中的值是字符串的前缀集合与后缀集合的交集中最长元素的长度。
例如，对于”aba”，它的前缀集合为{”a”, ”ab”}，后缀 集合为{”ba”, ”a”}。
两个集合的交集为{”a”}，那么长度最长的元素就是字符串”a”了，长 度为1，所以对于”aba”而言，它在PMT表中对应的值就是1。
再比如，对于字符串”ababa”，它的前缀集合为{”a”, ”ab”, ”aba”, ”abab”}，它的后缀集合为{”baba”, ”aba”, ”ba”, ”a”}， 
两个集合的交集为{”a”, ”aba”}，其中最长的元素为”aba”，长度为3。

我们看到如果是在 j 位 失配，那么影响 j 指针回溯的位置的其实是第 j −1 位的 PMT 值，
所以为了编程的方便， 我们不直接使用PMT数组，而是将PMT数组向后偏移一位。我们把新得到的这个数组称为next数组。

现在，我们再看一下如何编程快速求得next数组。（next数组只与模式串字符串自身有关，与文本字符串无关，所以可以单独构建）
其实，求next数组的过程完全可以看成模式字符串自匹配的过程，一旦字符串匹配成功，那么当前的next值就是匹配成功的字符串的长度。
具体来说，就是从模式字符串的第一位(注意，不包括第0位，第0位必为-1，模式串的第一个字符就是第一位)开始对自身进行最长前后缀集的运算。 
在任一位置，能匹配的最长长度就是当前位置的next值。
（next数组的next[0] = -1，next[1] = 0，雷打不动，从next[2]开始真正计算，此时可以理解为模式串的j为0，而文本串的i为1，其中i与j为0时均为首）
*/


//总结KMP算法思想，首先根据模式串自身特性，建立Next数组，其中存储在第多少位失配时，模式串自身回到多少位的信息。时间复杂度O(m+n)
//然后在主算法中，进行文本串i的按位匹配，每当出现失配时，i位置不变，而j根据Next数组回到一个相对较优的位置继续判断
//Next[0] = -1实现的基础为j = -1.其核心在于使每次j = 0时都配对不上而回到Next[0]时能顺利进行而不是陷入死循环
int *buildNext(string P)
{
	int sizeP = P.size();
	int *Next = new int[sizeP + 1]; //注意n+1，使代码能够存到Next[sizeP]
	int i = 0; int j = -1;   //双指针，i代表文本串指针，j代表模式串指针（这里的文本串和模式串都是P自身）
	Next[0] = -1;
	while (i < sizeP)
	{
		if (j == -1 || P[i] == P[j])
		{
			i++;
			j++;
			//Next[i] = j;
			Next[i] = ((P[i] != P[j]) ? (j) : (Next[j]));   //优化的Next建表判断，吸取前面的当P[i] == P[j]时的经验，减少循环
		}
		else
			j = Next[j];    //Next用于存储当失配时，模式串自身将回到的位置，所以这里可以在失配时调用自己回到对应的位置j
	}
	return Next;
}

int KMP_match(string P, string T)
{
	if (T.empty())
		return 0;

	int sizeP = P.size();
	int sizeT = T.size();

	if (sizeP > sizeT)
		return -1;

	int *next = buildNext(P);
	int i = 0, j = 0;    //i为文本串的指针，而j为模式串的指针
	while (i < sizeT && j < sizeP)
	{
		if (j == -1 || T[i] == P[j])   //注意next[0] = -1，所以j可能被移到-1位
		{
			i++;
			j++;
		}
		else
			j = next[j];   //模式串右移，注意文本串不会回退，next表用于存储当出现失配时j应该回退的地方
	}
	delete[] next;
	return (j == sizeP) ? (i - j) : (-1);;
}