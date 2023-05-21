/**********************************************************
 *  CContainer.h
 *
 *  Created on: 17 dec. 2021
 *      Author: GarnierAndrew
 *
 **********************************************************/

#include <cstdlib>
#include <cassert>
#include<iostream>
#include<cstddef>
#include<cassert>

template<class T>
class CContainer {
public:
	typedef T*(*t_ptfTV)(T*,void*);
private:
	class CNode{
	public:
		CNode*	m_pPrev;
		CNode*	m_pNext;
		T*		m_pObj;
	private:
		CNode() = delete;
		CNode(const CNode& other) = delete;
		CNode& operator=(const CNode&) = delete;
		~CNode();
	public:
		CNode( CNode*pNext,CNode*pPrev, T*pObj);
		CNode*DelReturnNext();

	};
private:
	CNode*	m_pHead;
	CNode*	m_pTail;
	size_t	m_szCard;

public:
	CContainer();
	CContainer(const CContainer& other);
	virtual ~CContainer();

	void*DelObject(T*pObj);
	CContainer<T>* Flush();
	CContainer<T>& operator=(const CContainer<T>& other);
	size_t Card()const;
	T*PushBack(T*pObj);

	size_t ParseCount(t_ptfTV pParseMethod,void*pParam)const;

	T*Parse(t_ptfTV pParseMethod,void*pParam)const;
	T*ParseDelIf(t_ptfTV pParseMethod,void*pParam);

};


template<class T>
CContainer<T>::CNode::CNode(CNode*pPrev, CNode*pNext, T*pObj):
	m_pPrev{pPrev},
	m_pNext{pNext},
	m_pObj{pObj}
{
	if(pPrev)	pPrev->m_pNext = this;
	if(pNext)	pNext->m_pPrev = this;
}

template<class T>
CContainer<T>::CNode::~CNode(){

	if(m_pNext)	m_pNext->m_pPrev = m_pPrev;
	if(m_pPrev) m_pPrev->m_pNext = m_pNext;

}

template<class T>
typename CContainer<T>::CNode*CContainer<T>::CNode::DelReturnNext(){

	delete m_pObj;
	CNode*pNodeNext = m_pNext;
	delete this;

	return pNodeNext;
}

template<class T>
CContainer<T>::CContainer():
	m_pHead(nullptr),
	m_pTail(nullptr),
	m_szCard(0)
{}


template<class T>
CContainer<T>::CContainer(const CContainer<T>& other):
	CContainer()
{
	CNode*pParse = other.m_pHead;
	while(pParse){
		PushBack(new T(*pParse->m_pObj));
		pParse = pParse->m_pNext;
	}
}

template<class T>
CContainer<T>::~CContainer(){
	Flush();
}

template<class T>
void*CContainer<T>::DelObject(T*pObj){

	CNode* pParse=m_pHead;
	while(pParse && pParse->m_pObj!=pObj){
		pParse=pParse->m_pNext;
	}
	if(pParse){
		if(pParse==m_pHead)m_pHead=m_pHead->m_pNext;
		if(pParse==m_pTail)m_pTail=m_pTail->m_pPrev;
		pParse->DelReturnNext();
		m_szCard--;
	}
    return nullptr;
}

template<class T>
CContainer<T>*::CContainer<T>::Flush(){

	while(m_pHead){
		m_pHead = m_pHead->DelReturnNext();
		m_szCard--;
	}
	assert(m_szCard == 0);
	m_pTail = nullptr;

	return nullptr;
}

template<class T>
CContainer<T>& CContainer<T>::operator=(const CContainer<T>& other){
	Flush();
	CNode*pParse = other.m_pHead;
	while(pParse){
		PushBack(new T(*pParse->m_pObj));
		pParse = pParse->m_pNext;
	}
	return *this;
}


template<class T>
size_t CContainer<T>::Card()const{
	return m_szCard;
}

template<class T>
T*CContainer<T>::PushBack(T*pObj){

	if(m_szCard == 0){
		assert(m_pHead == nullptr);
		assert(m_pTail == nullptr);
		m_pTail = new CNode(nullptr,nullptr,pObj);
		m_pHead = m_pTail;
	}
	else{
		m_pTail = new CNode(m_pTail,nullptr,pObj);
	}
	assert(m_pTail->m_pObj == pObj);
	m_szCard++;

	return m_pTail->m_pObj;

	return nullptr;
}


template<class T>
T*CContainer<T>::Parse(t_ptfTV pParseMethod,void*pParam)const{

	CNode*pParse = m_pHead;
	while(pParse){
		if(pParseMethod(pParse->m_pObj,pParam))	return pParse->m_pObj;
		pParse = pParse->m_pNext;
	}

	return nullptr;
}

template<class T>
size_t CContainer<T>::ParseCount(t_ptfTV pParseMethod,void*pParam)const{

	size_t iVal = 0;

	CNode*pParse = m_pHead;
	while(pParse){
		if(pParseMethod(pParse->m_pObj,pParam))	iVal++;
		pParse = pParse->m_pNext;
	}

	return iVal;
}

template<class T>
T*CContainer<T>::ParseDelIf(t_ptfTV pParseMethod,void*pParam){

	CNode*pParse = m_pHead;

	while(pParse){
		if(pParseMethod(pParse->m_pObj,pParam)){
			if(pParse == m_pHead)	m_pHead = pParse->m_pNext;
			if(pParse == m_pTail)	m_pTail = pParse->m_pPrev;
			pParse = pParse->DelReturnNext();
			m_szCard--;
		}
		else{
			pParse = pParse->m_pNext;
		}
	}
	return nullptr;
}


