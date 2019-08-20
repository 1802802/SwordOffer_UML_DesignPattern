#pragma once
#include <iostream>

//�����ļ����࣬����m_ref_countΪǿ���ü�����m_weak_countΪ�����ü���
class Counters
{
public:
	Counters() {}
	int m_ref_count = 0;
	int m_weak_count = 0;
};

template<typename T> class weak_ptr;

template<typename T> class shared_ptr
{
public:
	friend class weak_ptr<T>;

	shared_ptr() {}

	shared_ptr(T *ptr) : m_ptr(ptr) { (m_count->m_ref_count)++; }

	shared_ptr(const shared_ptr<T>& input)
	{
		m_ptr = input.m_ptr;
		m_count = input.m_count;
		(m_count->m_ref_count)++;
	}

	shared_ptr &operator=(const shared_ptr<T>& input)
	{
		if (input.m_ptr != m_ptr)
		{
			release();
			m_count = input.m_count;
			m_ptr = input.m_ptr;
			(m_count->m_ref_count)++;
		}
		return *this;
	}

	//����*��������Ϊ��ʹһ���������ֵ���һ��ָ��һ������(*dp).print ---> *m_ptr.print
	T  &operator*()
	{
		return *m_ptr;
	}

	//����->��������Ϊ��ʹһ���������ֵ���һ��ָ��һ������dp->print ---> m_ptr->print
	T* &operator->()
	{
		return m_ptr;
	}

	bool operator==(const shared_ptr &other)
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const shared_ptr &other)
	{
		return m_ptr != other.m_ptr;
	}

	int getCount() const
	{
		if (m_count->m_ref_count > 0)
			return m_count->m_ref_count;
		else
			return -1;
	}

	void release()
	{
		cout << "����release����" << endl;
		if (--(m_count->m_ref_count) == 0)
		{
			cout << "release��������" << endl;
			delete m_count;
			delete m_ptr;
			m_ptr = nullptr;
			m_count = nullptr;
		}
	}

	~shared_ptr()
	{
		release();
	}
private:
	//m_count��m_ptr��Ϊָ���������һ��Ҫ�ǵ���������
	//����˫�������ǰ��׺����ָ�����ʱ�����ܻᵼ��ѭ�����ã��Ӷ����������޷���������ָ������ָ����ڴ�
	Counters *m_count = new Counters();
	T *m_ptr = nullptr;
};

//weak_ptr����˼�������ָ�룬���������Ӷ�������ü������G������operator*��operator->��ʹ��ʱ��Ӧ��ͨ��weak_ptr��lock��������һ��shared_ptr��
//ͨ��expired�������ԭʼָ���Ƿ�Ϊ�գ�lock��ת��Ϊshare_ptr
template<typename T> class weak_ptr
{
public:
	friend class shared_ptr<T>;

	weak_ptr() {}

	weak_ptr(T *ptr) : m_ptr(ptr) { (m_count->m_ref_count)++; (m_count->m_weak_count)++; }

	weak_ptr(const weak_ptr<T>& input)
	{
		m_ptr = input.m_ptr;
		m_count = input.m_count;
		(m_count->m_weak_count)++;
	}

	weak_ptr(const shared_ptr<T>& input)
	{
		m_ptr = input.m_ptr;
		m_count = input.m_count;
		(m_count->m_weak_count)++;
	}

	weak_ptr &operator=(const weak_ptr<T>& input)
	{
		if (input.m_ptr != m_ptr)
		{
			release();
			m_count = input.m_count;
			m_ptr = input.m_ptr;
			(m_count->m_weak_count)++;
		}
		return *this;
	}

	weak_ptr &operator=(const shared_ptr<T>& input)
	{
		release();
		m_count = input.m_count;
		m_ptr = input.m_ptr;
		(m_count->m_weak_count)++;
		return *this;
	}

	int getCount() const
	{
		if (m_count->m_ref_count > 0)
			return m_count->m_ref_count;
		else
			return -1;
	}

	int getWeakCount() const
	{
		if (m_count->m_weak_count  > 0)
			return m_count->m_weak_count;
		else
			return -1;
	}

	//weak_ptrֻ��أ����ǲ�delete���ݱ���
	void release()
	{
		cout << "����release����" << endl;
		if (m_count != nullptr)
		{
			if (--(m_count->m_weak_count) < 1 && m_count->m_ref_count < 1)
			{
				cout << "release��������" << endl;
				m_count = nullptr;
				//delete m_count;
				//delete m_ptr;
				//m_count = nullptr;
				//m_ptr = nullptr;
			}
		}
	}

	bool expired()
	{
		if (m_count != nullptr)
		{
			if (m_count->m_ref_count > 0)
			{
				cout << "empty " << m_count->m_ref_count << endl;
				return false;
			}
		}
		return true;
	}

	shared_ptr<T> lock()
	{
		return shared_ptr<T>(*this);
	}

	~weak_ptr()
	{
		release();
	}
	
private:
	Counters *m_count = new Counters();
	T *m_ptr = nullptr;
};




template<typename T> struct DefaultDeleter
{
	void operator()(T *p)
	{
		if (p)
		{
			delete p;
			p = NULL;
		}
	}
};

template<typename T, typename Deleter = DefaultDeleter<T>> class unique_ptr
{
public:
	//construct 
	unique_ptr(T *pT = NULL);
	//destroy
	~unique_ptr();

	//not allow copyable
private:
	unique_ptr(const unique_ptr &) = delete;
	unique_ptr &operator=(const unique_ptr &) = delete;

public:
	//reset 
	void reset(T *p);
	//release the own of the pointer
	T *release();
	//get the pointer
	T *get();

public:
	//convert unique_ptr to bool
	operator bool() const;
	//overload for operator *
	T &operator*();
	//overload for operator ->
	T *operator->();

private:
	//pointer
	T *m_pT;
	//deleter
	Deleter m_deleter;
	//call deleter
	void del();
};

//construct 
template<typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T *pT) :m_pT(pT)
{

}

//destroy
template<typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr()
{
	del();
}

//call deleter
template<typename T, typename Deleter>
void unique_ptr<T, Deleter>::del()
{
	if (*this)
	{
		m_deleter(m_pT);
		m_pT = NULL;
	}
}

//get the pointer
template<typename T, typename Deleter>
T *unique_ptr<T, Deleter>::get()
{
	return m_pT;
}

//reset 
template<typename T, typename Deleter>
void unique_ptr<T, Deleter>::reset(T *p)
{
	del();
	m_pT = p;
}

//release the own of the pointer
template<typename T, typename Deleter>
T *unique_ptr<T, Deleter>::release()
{
	T *p = m_pT;
	m_pT = NULL;
	return p;
}

//convert unique_ptr to bool
template<typename T, typename Deleter>
unique_ptr<T, Deleter>::operator bool()const
{
	return NULL != m_pT;
}

//overload for operator *
template<typename T, typename Deleter>
T &unique_ptr<T, Deleter>::operator*()
{
	assert(*this);
	return *m_pT;
}

//overload for operator ->
template<typename T, typename Deleter>
T *unique_ptr<T, Deleter>::operator->()
{
	return &*(*this);
}