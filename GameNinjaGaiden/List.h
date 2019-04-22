#pragma once
template<class className>
struct List
{
	struct Node
	{
		Node* pNext;
		Node* pPre;
		className m_value;
		static Node* Create(className value)
		{
			Node* node = new Node();
			node->m_value = value;
			node->pNext = node->pPre = 0;
			return node;
		}
		Node()
		{
			//m_value = value;
			//pNext = pPre = 0;
		}
	};

	Node* pHead;
	Node* pTail;
	int Count;
	static List* Create()
	{
		List *l = new List();
		l->pHead = l->pTail = 0;
		l->Count = 0;
		return l;
	}
	bool _Contain(className item)
	{
		for (Node* p = pHead; p; p = p->pNext)
			if (p->m_value == item)
				return true;
		return false;
	}
	void _Add(className item)
	{	/*for(Node* p = pHead;p;p=p->pNext) if(p->m_value==item) return;*/

		if (_Contain(item))
			return;

		Count++;
		Node* node = Node::Create(item);
		if (pHead == 0)
		{
			pHead = pTail = node;
		}
		else {
			node->pPre = pTail;
			pTail->pNext = node;
			pTail = node;
		}
	}
	void _Remove(className item)
	{
		for (Node* p = pHead; p; p = p->pNext)
			if (p->m_value == item)
			{
				Node*q = p;	Count--;
				if (p == pHead)
				{
					pHead->pPre = 0;
					pHead = p->pNext;
					q->m_value = 0;
					delete q;
					q = 0;
					return;
				}
				if (p == pTail)
				{
					pTail = p->pPre; pTail->pNext = 0;
					q->m_value = 0;
					delete q;
					q = 0;
					return;
				}
				p->pPre->pNext = p->pNext;
				p->pNext->pPre = p->pPre;
				q->m_value = 0;
				delete q;
				q = 0;
				return;
			}
	}
	void Clear()
	{
		while (Count > 0)
		{
			Node*q = pHead;
			pHead->pPre = 0;
			pHead = pHead->pNext;
			q->m_value = 0;
			delete q; q = 0;
			Count--;
		}
		pHead = pTail = 0;
		Count = 0;
	}
	className operator[](int i)
	{
		for (Node* p = pHead; p; p = p->pNext)
		{
			if (i == 0)
				return p->m_value;
			i--;
		}
		return 0;
	}

	int size()
	{
		return Count;
	}

	className at(int i)
	{
		return (*this)[i];
	}
	className Get(char* i)
	{
		return (*this)[i];
	}
	void Release()
	{
		for (Node* p = pHead; p;)
		{
			Node* q = p;
			p = p->pNext;
			if (q->m_value)
			{
				q->m_value->Release();
				q->m_value = 0;
			}
			delete q;
			q = 0;
		}
		pHead = pTail = 0;
		delete this;
	}
	~List()
	{

	}
	List()
	{
		pHead = pTail = 0;
		Count = 0;
	}
};
