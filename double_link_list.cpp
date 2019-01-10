#include<iostream>
#include<vector>
#include<stdio.h>
#include<map>
using namespace std;

struct Node
{
	int num;
	int key;
	Node* next=NULL;
	Node* pre=NULL;
	Node(int k = -1, int n = -1) :key(k), num(n) {}
};

class DoubleListNode {

public:
	Node * head;
	Node * tail;
	DoubleListNode()
	{
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->pre = head;
	}
	void remove(Node* item);
	void sethead(Node* item);
	void dump();
	~DoubleListNode();

};
DoubleListNode::~DoubleListNode()
{
	delete head;
	delete tail;
}

void DoubleListNode::remove(Node* item) //从链表中移除
{
	Node* preNode = item->pre;
	Node* nextNode = item->next;
	if (preNode)
		preNode->next = nextNode;
	if (nextNode)
		nextNode->pre = preNode;
	return;
}
void DoubleListNode::sethead(Node* item) //将节点放置到头
{
	//Node* preNode = item->pre;
	//if (item->pre != head)//加了判断后，当移除的item是第一个时，再调用  sethead就不会执行下面的语句，会出问题（只从链表中移除，没有添加）。
	//{
	item->next = head->next;
	item->pre = head;
	head->next->pre = item;
	head->next = item;
	//}
	return;
}
void DoubleListNode::dump()
{
	Node* index = head->next;
	printf("\n");
	while (index&&index != tail)
	{
		printf("%d ", index->num);
		index = index->next;
	}
	printf("\n");
}
class LRUCache {
public:
	map<int, Node*>m_map; //存放key和对应Node
	DoubleListNode list;
	Node* head = NULL;
	Node* pre;
	int cap = 0;
	int cnt = 0;
	int len = 0;
	LRUCache(int capacity = 0) :cap(capacity) {};
	
	int get(int key) {

		if (m_map.find(key) != m_map.end())
		{
			Node* ret = m_map[key];
			list.remove(ret);
			list.sethead(ret);
			return ret->num;
		}
		return -1;
	}

	void put(int key, int value) {

		if (m_map.find(key) != m_map.end())//若key存在，将对应节点从链表移除。更新num,并放置到列表头。
		{
			Node* ret = m_map[key];
			list.remove(ret);
			ret->num = value;
			list.sethead(ret);
			return;
		}
		if (cnt >= cap) //若超过容量，将末尾节点移除
		{
			Node* p = list.tail->pre;
			list.remove(p);
			cnt--;
			m_map.erase(p->key);
			delete p;
		}
		Node* item = new Node; //新建节点并插入到链表头部，
		item->num = value;
		item->key = key;
		list.sethead(item);
		m_map[key] = item;
		cnt++;
		return;
	}
};
